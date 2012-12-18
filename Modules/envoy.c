/*

Directory Opus 5
Original APL release version 5.82
Copyright 1993-2012 Jonathan Potter & GP Software

This program is free software; you can redistribute it and/or
modify it under the terms of the AROS Public License version 1.1.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
AROS Public License for more details.

The release of Directory Opus 5 under the GPL in NO WAY affects
the existing commercial status of Directory Opus for Windows.

For more information on Directory Opus for Windows please see:

                 http://www.gpsoft.com.au

*/

#include "envoy.h"

typedef struct _PathNode
{
	struct MinNode		node;
	char			path_buf[512];
	char			*path;
	struct _Lister			*lister;
	struct MinList		change_list;
	USHORT			flags;
} PathNode;

static char *version="$VER: envoy.module 44.13 (11.09.95)";

int __asm __saveds L_Module_Entry(
	register __a0 struct List *files,
	register __a1 struct Screen *screen,
	register __a2 IPCData *ipc,
	register __a3 IPCData *main_ipc,
	register __d0 ULONG mod_id,
	register __d1 EXT_FUNC(func_callback))
{
	struct Window *window=0;
	NewConfigWindow newwin;
	ObjectList *objlist;
	struct Library *AccountsBase;
	FunctionEntry *entry;
	BPTR lock,dirlock,olddir;
	struct FileInfoBlock __aligned fib;
	struct UserInfo *user_info;
	struct GroupInfo *group_info=0;
	struct _PathNode *path_node;
	char path[256];

	// Get first entry
	if (!(entry=(FunctionEntry *)func_callback(EXTCMD_GET_ENTRY,IPCDATA(ipc),0)))
		return 0;

	// Get path
	path_node=(struct _PathNode *)func_callback(EXTCMD_GET_SOURCE,IPCDATA(ipc),path);

//KPrintF("Lister handle %ld\n",path_node->lister);

	// Open accounts.library
	if (!(AccountsBase=OpenLibrary("accounts.library",0)))
		return 0;

	// Try and get window to open over
	newwin.parent=(void *)func_callback(EXTCMD_GET_WINDOW,IPCDATA(ipc),path_node);
	newwin.flags=0;

	// Fill out new window
	if (!newwin.parent)
	{
		newwin.parent=screen;
		newwin.flags=WINDOW_SCREEN_PARENT;
	}
	newwin.dims=&_envoy_window;
	newwin.title=GetString(locale,MSG_ENVOY_TITLE);
	newwin.locale=locale;
	newwin.flags|=WINDOW_REQ_FILL|WINDOW_AUTO_KEYS|WINDOW_VISITOR;
	newwin.port=0;
	newwin.font=0;

	// Allocate some data and open window
	if ((user_info=AllocUserInfo()) &&
		(group_info=AllocGroupInfo()) &&
		(window=OpenConfigWindow(&newwin)) &&
		(objlist=AddObjectList(window,_envoy_objects)))
	{
		UWORD owner_id=0,group_id=0;
		short break_flag=0;

		// Lock path
		if (dirlock=Lock(path,ACCESS_READ))
		{
			// Change directory
			olddir=CurrentDir(dirlock);

			// Lock first file
			if (lock=Lock(entry->name,ACCESS_READ))
			{
				short a;

				// Examine file
				Examine(lock,&fib);
				UnLock(lock);

				// Does file have an owner?
				if (fib.fib_OwnerUID && !(IDToUser(fib.fib_OwnerUID,user_info)))
				{
					// Fill out owner field
					SetGadgetValue(objlist,GAD_ENVOY_OWNER_FIELD,(ULONG)user_info->ui_UserName);
				}

				// Does file have a group?
				if (fib.fib_OwnerGID && !(IDToGroup(fib.fib_OwnerGID,group_info)))
				{
					// Fill out group field
					SetGadgetValue(objlist,GAD_ENVOY_GROUP_FIELD,(ULONG)group_info->gi_GroupName);
				}

				// Go through protection bits
				for (a=0;a<4;a++)
				{
					// Group bit set?
					if (fib.fib_Protection&(1<<(FIBB_GRP_READ-a)))
						SetGadgetValue(objlist,GAD_ENVOY_GROUP_READ+a,1);

					// Other bit set?
					if (fib.fib_Protection&(1<<(FIBB_OTR_READ-a)))
						SetGadgetValue(objlist,GAD_ENVOY_OTHER_READ+a,1);
				}
			}

			// Loop for messages
			FOREVER
			{
				struct IntuiMessage *msg;
				IPCMessage *imsg;

				// IPC message?
				while (imsg=(IPCMessage *)GetMsg(ipc->command_port))
				{
					// Quit?
					if (imsg->command==IPC_QUIT ||
						imsg->command==IPC_HIDE ||
						imsg->command==IPC_ABORT) break_flag=1;
					IPC_Reply(imsg);
				}

				// Any intuition messages?
				while (msg=GetWindowMsg(window->UserPort))
				{
					struct IntuiMessage msg_copy;

					// Copy message and reply
					msg_copy=*msg;
					ReplyWindowMsg(msg);

					// Look at message
					switch (msg_copy.Class)
					{
						// Gadget
						case IDCMP_GADGETUP:

							// Look at gadget ID
							switch (((struct Gadget *)msg_copy.IAddress)->GadgetID)
							{
								// Owner list
								case GAD_ENVOY_OWNER:

									// Put up owner list
									envoy_owner_list(window,objlist,user_info,AccountsBase);
									break;

								// Group list
								case GAD_ENVOY_GROUP:

									// Put up group list
									envoy_group_list(window,objlist,group_info,AccountsBase);
									break;

								// Okay
								case GAD_ENVOY_OK:

									// Check valid owner
									if (!(envoy_check_owner(
										window,
										objlist,
										user_info,
										AccountsBase,
										&owner_id)) ||

									// Check valid group
										!(envoy_check_group(
										window,
										objlist,
										group_info,
										AccountsBase,
										&group_id))) break;

									// Set break flag
									break_flag=2;
									break;

								// Cancel
								case GAD_ENVOY_CANCEL:
									break_flag=1;
									break;
							}
							break;


						// Close window
						case IDCMP_CLOSEWINDOW:
							break_flag=1;
							break;


						// Key press
						case IDCMP_RAWKEY:

							// Help?
							if (msg_copy.Code==0x5f &&
								!(msg_copy.Qualifier&VALID_QUALIFIERS))
							{
								// Set busy pointer
								SetWindowBusy(window);

								// Send help request
								func_callback(EXTCMD_GET_HELP,IPCDATA(ipc),"NetSet");

								// Clear busy pointer
								ClearWindowBusy(window);
							}
							break;
					}
				}

				// Look at break flag
				if (break_flag) break;

				// Wait for messages
				Wait(	1<<window->UserPort->mp_SigBit|
						((ipc)?(1<<ipc->command_port->mp_SigBit):0));
			}

			// Want to change settings?
			if (break_flag==2)
			{
				ULONG protect=0;
				ULONG owner_info;
				short a;
				struct progress_packet progress;

				// Look at protection gadgets
				for (a=0;a<4;a++)
				{
					// Group bit set?
					if (GetGadgetValue(objlist,GAD_ENVOY_GROUP_READ+a))
						protect|=(1<<(FIBB_GRP_READ-a));

					// Other bit set?
					if (GetGadgetValue(objlist,GAD_ENVOY_OTHER_READ+a))
						protect|=(1<<(FIBB_OTR_READ-a));
				}

				// Close window
				CloseConfigWindow(window);
				window=0;

				// Build owner info longword
				owner_info=(owner_id<<16)|group_id;

				// Get entry count
				progress.count=func_callback(EXTCMD_ENTRY_COUNT,IPCDATA(ipc),0);

				// Open progress indicator
				progress.path=path_node;
				progress.name=GetString(locale,MSG_ENVOY_PROGRESS_TITLE);
				func_callback(EXTCMD_OPEN_PROGRESS,IPCDATA(ipc),&progress);
				progress.count=0;

				// Go through entries
				while (entry=(FunctionEntry *)func_callback(EXTCMD_GET_ENTRY,IPCDATA(ipc),0))
				{
					struct endentry_packet packet;

					// Update progress info
					if (progress.name=AllocMemH(0,strlen(entry->name)+1))
						strcpy(progress.name,entry->name);
					++progress.count;
					func_callback(EXTCMD_UPDATE_PROGRESS,IPCDATA(ipc),&progress);

					// Check abort
					if (func_callback(EXTCMD_CHECK_ABORT,IPCDATA(ipc),0))
						break;

					// Try to lock entry
					if (lock=Lock(entry->name,ACCESS_READ))
					{
						// Examine file
						Examine(lock,&fib);
						UnLock(lock);

						// Mask out existing network bits from protection
						fib.fib_Protection&=~(FIBF_GRP_READ|FIBF_GRP_WRITE|FIBF_GRP_EXECUTE|FIBF_GRP_DELETE|FIBF_OTR_READ|FIBF_OTR_WRITE|FIBF_OTR_EXECUTE|FIBF_OTR_DELETE);

						// Or in new protection bits
						fib.fib_Protection|=protect;

						// Set protection bits
						SetProtection(entry->name,fib.fib_Protection);
					}

					// Set owner, fill out packet with results
					packet.entry=entry;
					packet.deselect=SetOwner(entry->name,owner_info);

					// Mark function for reload (if successful)
					if (packet.deselect)
						func_callback(EXTCMD_RELOAD_ENTRY,IPCDATA(ipc),entry);

					// End this entry
					func_callback(EXTCMD_END_ENTRY,IPCDATA(ipc),&packet);
				}

				// Turn progress indicator off
				func_callback(EXTCMD_CLOSE_PROGRESS,IPCDATA(ipc),path_node);
			}

			// Restore directory
			UnLock(CurrentDir(olddir));
		}
	}

	// Close down
	CloseConfigWindow(window);
	CloseLibrary(AccountsBase);
	FreeGroupInfo(group_info);
	FreeUserInfo(user_info);
	return 1;
}


// Display owner list
void envoy_owner_list(
	struct Window *window,
	ObjectList *objlist,
	struct UserInfo *owner_info,
	struct Library *AccountsBase)
{
	Att_List *owner_list;
	Att_Node *node;
	short sel;
	char *ptr;

	// Create list
	if (!(owner_list=Att_NewList(0)))
		return;

	// Make window busy
	SetWindowBusy(window);

	// Go through owners
	owner_info->ui_UserID=0;
	while ((NextUser(owner_info))==0)
	{
		// Add this owner to the list
		Att_NewNode(owner_list,owner_info->ui_UserName,1,ADDNODE_SORT);
	}

	// Add "no owner" entry
	node=Att_NewNode(owner_list,GetString(locale,MSG_ENVOY_NO_OWNER),0,ADDNODE_SORT);

	// Get current selection
	ptr=(char *)GetGadgetValue(objlist,GAD_ENVOY_OWNER_FIELD);
	if (!ptr || !*ptr) sel=Att_FindNodeNumber(owner_list,node);
	else sel=Att_NodeNumber(owner_list,ptr);

	// Display owner list
	if ((sel=SelectionList(
		owner_list,
		window,
		0,
		GetString(locale,MSG_ENVOY_GET_OWNER),
		sel,
		0,
		0,
		GetString(locale,MSG_OK),
		GetString(locale,MSG_CANCEL)))!=-1)
	{
		// Get selected node
		if (node=Att_FindNode(owner_list,sel))
		{
			// Fill out owner field
			SetGadgetValue(
				objlist,
				GAD_ENVOY_OWNER_FIELD,
				(node->data)?(ULONG)node->node.ln_Name:0);
		}
	}

	// Clear window busy
	ClearWindowBusy(window);

	// Free list
	Att_RemList(owner_list,0);
}


// Display group list
void envoy_group_list(
	struct Window *window,
	ObjectList *objlist,
	struct GroupInfo *group_info,
	struct Library *AccountsBase)
{
	Att_List *group_list;
	Att_Node *node;
	short sel;
	char *ptr;

	// Create list and GroupInfo structure
	if (!(group_list=Att_NewList(0)))
		return;

	// Make window busy
	SetWindowBusy(window);

	// Go through groups
	group_info->gi_GroupID=0;
	while ((NextGroup(group_info))==0)
	{
		// Add this group to the list
		Att_NewNode(group_list,group_info->gi_GroupName,1,ADDNODE_SORT);
	}

	// Add "no group" entry
	node=Att_NewNode(group_list,GetString(locale,MSG_ENVOY_NO_GROUP),0,ADDNODE_SORT);

	// Get current selection
	ptr=(char *)GetGadgetValue(objlist,GAD_ENVOY_GROUP_FIELD);
	if (!ptr || !*ptr) sel=Att_FindNodeNumber(group_list,node);
	else sel=Att_NodeNumber(group_list,ptr);

	// Display group list
	if ((sel=SelectionList(
		group_list,
		window,
		0,
		GetString(locale,MSG_ENVOY_GET_GROUP),
		sel,
		0,
		0,
		GetString(locale,MSG_OK),
		GetString(locale,MSG_CANCEL)))!=-1)
	{
		// Get selected node
		if (node=Att_FindNode(group_list,sel))
		{
			// Fill out group field
			SetGadgetValue(
				objlist,
				GAD_ENVOY_GROUP_FIELD,
				(node->data)?(ULONG)node->node.ln_Name:0);
		}
	}

	// Clear window busy
	ClearWindowBusy(window);

	// Free list and GroupInfo
	Att_RemList(group_list,0);
}


// Check for valid owner
BOOL envoy_check_owner(
	struct Window *window,
	ObjectList *objlist,
	struct UserInfo *owner_info,
	struct Library *AccountsBase,
	UWORD *owner_id)
{
	char *ptr;

	// Get pointer to owner name
	ptr=(char *)GetGadgetValue(objlist,GAD_ENVOY_OWNER_FIELD);

	// No owner?
	if (!ptr || !*ptr)
	{
		*owner_id=0;
		return 1;
	}

	// Check for valid user
	if (!(NameToUser(ptr,owner_info)))
	{
		// Ok
		*owner_id=owner_info->ui_UserID;
		return 1;
	}

	// Display error
	SimpleRequestTags(
		window,
		GetString(locale,MSG_ENVOY_TITLE),
		GetString(locale,MSG_OK),
		GetString(locale,MSG_ENVOY_BAD_USER),
		ptr);

	// Invalid
	return 0;
}


// Check for valid group
BOOL envoy_check_group(
	struct Window *window,
	ObjectList *objlist,
	struct GroupInfo *group_info,
	struct Library *AccountsBase,
	UWORD *group_id)
{
	char *ptr;

	// Get pointer to group name
	ptr=(char *)GetGadgetValue(objlist,GAD_ENVOY_GROUP_FIELD);

	// No group?
	if (!ptr || !*ptr)
	{
		*group_id=0;
		return 1;
	}

	// Check for valid group
	if (!(NameToGroup(ptr,group_info)))
	{
		// Ok
		*group_id=group_info->gi_GroupID;
		return 1;
	}

	// Display error
	SimpleRequestTags(
		window,
		GetString(locale,MSG_ENVOY_TITLE),
		GetString(locale,MSG_OK),
		GetString(locale,MSG_ENVOY_BAD_GROUP),
		ptr);

	// Invalid
	return 0;
}
