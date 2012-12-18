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

/*
	04 Nov 99  Changed diskobjectcopy to use DupDiskObject for V44


*/

#include "dopuslib.h"
#include "dopusmod:modules.h"
#include <proto/newicon.h>

#define UtilityBase	(wb_data->utility_base)
#define ExecLib		((struct ExecBase *)*((ULONG *)4))

// Patch functions
static PatchList
	wb_patches[WB_PATCH_COUNT]={
		{-0x30,L_WB_AddAppWindow,WB_PATCH_WORKBENCH},
		{-0x36,L_WB_RemoveAppWindow,WB_PATCH_WORKBENCH},
		{-0x3c,L_WB_AddAppIcon,WB_PATCH_WORKBENCH},
		{-0x42,L_WB_RemoveAppIcon,WB_PATCH_WORKBENCH},
		{-0x48,L_WB_AddAppMenuItem,WB_PATCH_WORKBENCH},
		{-0x4e,L_WB_RemoveAppMenuItem,WB_PATCH_WORKBENCH},
		{-0x4e,L_WB_CloseWorkBench,WB_PATCH_INTUITION},
		{-0xd2,L_WB_OpenWorkBench,WB_PATCH_INTUITION},
		{-0x54,L_WB_PutDiskObject,WB_PATCH_ICON},
		{-0x8a,L_WB_DeleteDiskObject,WB_PATCH_ICON},
		{-0x162,L_WB_AddPort,WB_PATCH_EXEC},
		{-0x48,L_WB_CloseWindow,WB_PATCH_INTUITION},
		{-0x78,L_PatchedCreateDir,WB_PATCH_DOSFUNC},
		{-0x48,L_PatchedDeleteFile,WB_PATCH_DOSFUNC},
		{-0x18c,L_PatchedSetFileDate,WB_PATCH_DOSFUNC},
		{-0xb4,L_PatchedSetComment,WB_PATCH_DOSFUNC},
		{-0xba,L_PatchedSetProtection,WB_PATCH_DOSFUNC},
		{-0x4e,L_PatchedRename,WB_PATCH_DOSFUNC},
		{-0x1e,L_PatchedOpen,WB_PATCH_DOSFUNC},
		{-0x24,L_PatchedClose,WB_PATCH_DOSFUNC},
		{-0x30,L_PatchedWrite,WB_PATCH_DOSFUNC},
		{-0x2d0,L_PatchedRelabel,WB_PATCH_DOS},
		{-0x5a,L_PatchedWBInfo,WB_PATCH_WORKBENCH},
		{-0x11a,L_PatchedAddTask,WB_PATCH_EXEC},
		{-0x120,L_PatchedRemTask,WB_PATCH_EXEC},
		{-0x126,L_PatchedFindTask,WB_PATCH_EXEC},
		{-0x25e,L_PatchedOpenWindowTags,WB_PATCH_INTUITION},
/*
		{-0x396,L_PatchedAllocBitmap,WB_PATCH_GFX},
*/
		};

// Install workbench emulation patches
void __asm __saveds L_WB_Install_Patch(register __a6 struct MyLibrary *libbase)
{
	WB_Data *wb_data;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Lock patch information
	L_GetSemaphore(&wb_data->patch_lock,SEMF_EXCLUSIVE,0);

	// Are patches not installed?
	if (wb_data->patch_count==0)
	{
		short patch;

		// Allocate patch table
		if (wb_data->old_function=AllocVec(sizeof(APTR)*WB_PATCH_COUNT,MEMF_CLEAR))
		{
			// Forbid while we install the patches
			Forbid();

			// Install patches
			for (patch=0;patch<WB_PATCH_COUNT;patch++)
			{
				struct Library *lib;

				// Get library
				if (lib=wb_get_patchbase(wb_patches[patch].type,(struct LibData *)libbase->ml_UserData))
				{
					// Patch this function
					wb_data->old_function[patch]=
						SetFunction(lib,wb_patches[patch].offset,wb_patches[patch].function);
				}
			}

			// Clear the cache and Permit
			CacheClearU();
			Permit();

			// Increment patch count
			++wb_data->patch_count;
		}
	}

	// Unlock patch information
	L_FreeSemaphore(&wb_data->patch_lock);
}


// Remove workbench patches
BOOL __asm __saveds L_WB_Remove_Patch(register __a6 struct MyLibrary *libbase)
{
	short patch;
	BOOL fail=0;
	APTR old_patch_val[WB_PATCH_COUNT];
	WB_Data *wb_data;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Lock patch information
	L_GetSemaphore(&wb_data->patch_lock,SEMF_EXCLUSIVE,0);

	// Really remove patches?
	if (wb_data->patch_count==1)
	{
		// Try to remove patches
		Forbid();
		for (patch=0;patch<WB_PATCH_COUNT;patch++)
		{
			// Patch installed for this function?
			if (wb_data->old_function[patch])
			{
				struct Library *lib;

				// Get library
				if (lib=wb_get_patchbase(wb_patches[patch].type,(struct LibData *)libbase->ml_UserData))
				{
					// Restore old value
					old_patch_val[patch]=
						SetFunction(lib,wb_patches[patch].offset,wb_data->old_function[patch]);

					// The value returned should have been our patch
					if (old_patch_val[patch]!=wb_patches[patch].function)
					{
						// Something's in there
						fail=1;
						break;
					}
				}
			}
		}

		// Did remove fail?
		if (fail)
		{
			// Restore the vectors that we've changed
			for (;patch>=0;patch--)
			{
				// Patch installed for this function?
				if (wb_data->old_function[patch])
				{
					struct Library *lib;

					// Get library
					if (lib=wb_get_patchbase(wb_patches[patch].type,(struct LibData *)libbase->ml_UserData))
					{
						// Reinstall patch
						SetFunction(lib,wb_patches[patch].offset,wb_data->old_function[patch]);
					}
				}
			}
		}

		// Otherwise, clear our patch pointers
		else
		{
			FreeVec(wb_data->old_function);
			wb_data->old_function=0;
		}

		CacheClearU();
		Permit();
	}

	// If we didn't fail, decrement patch count
	if (!fail && wb_data->patch_count>0)
		--wb_data->patch_count;

	// Unlock patch information
	L_FreeSemaphore(&wb_data->patch_lock);

	return (BOOL)(!fail);
}


// AddAppWindow()
struct AppWindow *__asm __saveds L_WB_AddAppWindow(
	register __d0 ULONG id,
	register __d1 ULONG userdata,
	register __a0 struct Window *window,
	register __a1 struct MsgPort *port,
	register __a2 struct TagItem *tags)
{
	struct MyLibrary *libbase;
	AppEntry *app_entry;
	WB_Data *wb_data;

	// Check valid data
	if (!window || !port) return 0;

	// Open library
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Get new AppEntry
	if (app_entry=new_app_entry(APP_WINDOW,id,userdata,window,0,port,wb_data))
	{
		// Local AppThing?
		if (tags && GetTagData(DAE_Local,0,tags))
		{
			// Set local flag
			app_entry->flags|=APPENTF_LOCAL;
		}

		// Otherwise pass to OS
		else
		{
			app_entry->os_object=
				((struct AppWindow *__asm (*)
					(register __d0 ULONG,
					register __d1 ULONG,
					register __a0 struct Window *,
					register __a1 struct MsgPort *,
					register __a2 struct TagItem *,
					register __a6 struct Library *))wb_data->old_function[WB_PATCH_ADDAPPWINDOW])
					(id,userdata,window,port,tags,wb_data->wb_base);
		}

		// Send notification
		L_SendNotifyMsg(DN_APP_WINDOW_LIST,(ULONG)app_entry,0,FALSE,0,0,libbase);
	}

	// Return object
	return (struct AppWindow *)app_entry;
}


// AddAppIcon()
struct AppIcon *__asm __saveds L_WB_AddAppIcon(
	register __d0 ULONG id,
	register __d1 ULONG userdata,
	register __a0 char *text,
	register __a1 struct MsgPort *port,
	register __a2 BPTR lock,
	register __a3 struct DiskObject *icon,
	register __a4 struct TagItem *tags)
{
	struct MyLibrary *libbase;
	AppEntry *app_entry=0;
	struct LibData *data;
	WB_Data *wb_data;
	BOOL osonly=0;
	APTR object=0;
	short local=2;

	// Check valid data
	if (!icon || !port) return 0;

	// Open library
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get Workbench data pointer
	data=(struct LibData *)libbase->ml_UserData;
	wb_data=&data->wb_data;

	// Pass straight through to OS?
	if (tags && (local=GetTagData(DAE_Local,2,tags))==0) osonly=1;

	// Otherwise, if it's not a local icon and the redirection flag is set, send to Tools menu
	else
	if (local==2 && data->flags&LIBDF_REDIRECT_TOOLS)
	{
		// Add as menu item
		return (struct AppIcon *)L_WB_AddAppMenuItem(
			id,
			userdata,
			text,
			port,
			tags);
	}

	// Get new AppEntry
	if (osonly || (app_entry=new_app_entry(APP_ICON,id,userdata,icon,text,port,wb_data)))
	{
		short a;
		struct TagItem *tag;

		// Any tags?
		if (tags && app_entry)
		{
			struct TagItem *tstate;

			// Support snapshot?
			if (GetTagData(DAE_SnapShot,0,tags))
			{
				// Set flag
				app_entry->flags|=APPENTF_SNAPSHOT;
			}

			// Support info?
			if (GetTagData(DAE_Info,0,tags))
			{
				// Set flag
				app_entry->flags|=APPENTF_INFO;
			}

			// Locked?
			if (GetTagData(DAE_Locked,0,tags))
			{
				// Set flag
				app_entry->flags|=APPENTF_LOCKED;
			}

			// Close item?
			if (a=GetTagData(DAE_Close,0,tags))
			{
				// Set flag
				app_entry->flags|=APPENTF_CLOSE;

				// No open?
				if (a==2) app_entry->flags|=APPENTF_NO_OPEN;
			}

			// Background colour?
			if (tag=FindTagItem(DAE_Background,tags))
			{
				// Set flag
				app_entry->flags|=APPENTF_BACKGROUND;

				// Store colour;
				app_entry->data=tag->ti_Data;
			}

			// Special?
			if (GetTagData(DAE_Special,0,tags))
			{
				// Set flag
				app_entry->flags|=APPENTF_SPECIAL;
			}

			// Set menu base
			app_entry->menu_id_base=GetTagData(DAE_MenuBase,0,tags);

			// Go through tags
			tstate=tags;
			while (tag=NextTagItem(&tstate))
			{
				// Menu item?
				if ((tag->ti_Tag==DAE_Menu ||
					 tag->ti_Tag==DAE_ToggleMenu ||
					 tag->ti_Tag==DAE_ToggleMenuSel) && tag->ti_Data)
				{
					struct Node *node;

					// Allocate space for node and name
					if (node=AllocVec(sizeof(struct Node)+strlen((char *)tag->ti_Data)+1,MEMF_CLEAR))
					{
						// Copy name
						node->ln_Name=(char *)(node+1);
						strcpy(node->ln_Name,(char *)tag->ti_Data);

						// Set flags
						if (tag->ti_Tag==DAE_ToggleMenu) node->ln_MenuFlags=MNF_TOGGLE;
						else
						if (tag->ti_Tag==DAE_ToggleMenuSel) node->ln_MenuFlags=MNF_TOGGLE|MNF_SEL;

						// Add to list
						AddTail((struct List *)&app_entry->menu,(struct Node *)node);
					}
				}
			}
		}

		// Local AppThing?
		if (local==1 && !osonly)
		{
			// Set local flag
			app_entry->flags|=APPENTF_LOCAL;
		}

		// Otherwise, pass to OS
		else
		{
			object=
				((APTR __asm (*)
					(register __d0 ULONG,
					register __d1 ULONG,
					register __a0 char *,
					register __a1 struct MsgPort *,
					register __a2 BPTR,
					register __a3 struct DiskObject *,
					register __a4 struct TagItem *,
					register __a6 struct Library *))wb_data->old_function[WB_PATCH_ADDAPPICON])
					(id,userdata,text,port,lock,icon,tags,wb_data->wb_base);
			if (app_entry) app_entry->os_object=object;
		}

		// Send notification
		if (app_entry)
			L_SendNotifyMsg(DN_APP_ICON_LIST,(ULONG)app_entry,0,FALSE,0,0,libbase);
	}

	// Return object
	return (struct AppIcon *)((app_entry)?(APTR)app_entry:object);
}


// AddAppMenuItem()
struct AppMenuItem *__asm __saveds L_WB_AddAppMenuItem(
	register __d0 ULONG id,
	register __d1 ULONG userdata,
	register __a0 char *text,
	register __a1 struct MsgPort *port,
	register __a2 struct TagItem *tags)
{
	struct MyLibrary *libbase;
	AppEntry *app_entry=0;
	WB_Data *wb_data;
	BOOL osonly=0;
	APTR object=0;

	// Check valid data
	if (!port) return 0;

	// Open library
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Pass straight through?
	if (tags && !(GetTagData(DAE_Local,1,tags))) osonly=1;

	// Get new AppEntry
	if (osonly || (app_entry=new_app_entry(APP_MENU,id,userdata,0,text,port,wb_data)))
	{
		// Local AppThing?
		if (tags && GetTagData(DAE_Local,0,tags))
		{
			// Set local flag
			app_entry->flags|=APPENTF_LOCAL;
		}

		// Otherwise pass to OS
		else
		{
			object=
				((APTR __asm (*)
					(register __d0 ULONG,
					register __d1 ULONG,
					register __a0 char *,
					register __a1 struct MsgPort *,
					register __a2 struct TagItem *,
					register __a6 struct Library *))wb_data->old_function[WB_PATCH_ADDAPPMENU])
					(id,userdata,text,port,tags,wb_data->wb_base);
			if (app_entry) app_entry->os_object=object;
		}

		// Send notification
		if (app_entry)
		{
			struct Task *thistask;
			short toolmanger=0;

			// Get current task
			thistask=FindTask(0);

			// Is this from ToolManager?
			if (thistask->tc_Node.ln_Name &&
				strcmp(thistask->tc_Node.ln_Name,"ToolManager Handler")==0)
				toolmanger=1;

			// Send notify message
			L_SendNotifyMsg(DN_APP_MENU_LIST,(ULONG)app_entry,toolmanger,FALSE,0,0,libbase);
		}
	}

	// Return object
	return (struct AppMenuItem *)((app_entry)?(APTR)app_entry:object);
}


// RemoveAppWindow()
BOOL __asm __saveds L_WB_RemoveAppWindow(
	register __a0 struct AppWindow *window)
{
	AppEntry *entry;
	struct MyLibrary *libbase;
	WB_Data *wb_data;
	APTR os_object;

	// Valid pointer?
	if (!(entry=(AppEntry *)window)) return 1;

	// Open library
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Free entry
	os_object=rem_app_entry(entry,wb_data,0);

	// Workbench object?
	if (os_object)
	{
		// Remove workbench object
		((BOOL __asm (*)
			(register __a0 struct AppWindow *,
			register __a6 struct Library *))wb_data->old_function[WB_PATCH_REMAPPWINDOW])
			(os_object,wb_data->wb_base);
	}

	// Send notification
	L_SendNotifyMsg(DN_APP_WINDOW_LIST,(ULONG)window,DNF_WINDOW_REMOVED,FALSE,0,0,libbase);
	return 1;
}


// RemoveAppIcon()
BOOL __asm __saveds L_WB_RemoveAppIcon(
	register __a0 struct AppIcon *icon)
{
	AppEntry *entry;
	struct MyLibrary *libbase;
	WB_Data *wb_data;
	APTR os_object;
	BOOL local;

	// Valid pointer?
	if (!(entry=(AppEntry *)icon)) return 1;

	// Open library
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Check valid object
	if (find_app_entry(entry,wb_data))
	{
		// Is it a menu (must have been redirected)?
		if (entry->type==APP_MENU)
		{
			// Unlock list
			L_FreeSemaphore(&wb_data->patch_lock);

			// Remove as menu item
			return L_WB_RemoveAppMenuItem((struct AppMenuItem *)icon);
		}

		// Send notification
		L_SendNotifyMsg(DN_APP_ICON_LIST,(ULONG)entry,DNF_ICON_REMOVED,FALSE,0,0,libbase);

//*********************************************************************TRUE ???

		// Unlock list
		L_FreeSemaphore(&wb_data->patch_lock);

	}

	// Free entry
	if (os_object=rem_app_entry(entry,wb_data,&local))
	{
		// Remove workbench object
		((BOOL __asm (*)
			(register __a0 struct AppIcon *,
			register __a6 struct Library *))wb_data->old_function[WB_PATCH_REMAPPICON])
			(os_object,wb_data->wb_base);
	}

	return 1;
}


// RemoveAppMenuItem()
BOOL __asm __saveds L_WB_RemoveAppMenuItem(
	register __a0 struct AppMenuItem *item)
{
	AppEntry *entry;
	struct MyLibrary *libbase;
	WB_Data *wb_data;
	APTR os_object;
	BOOL local;

	// Valid pointer?
	if (!(entry=(AppEntry *)item)) return 1;

	// Open library
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Free entry
	os_object=rem_app_entry(entry,wb_data,&local);

	// Workbench object?
	if (os_object)
	{
		// Remove workbench object
		((BOOL __asm (*)
			(register __a0 struct AppMenuItem *,
			register __a6 struct Library *))wb_data->old_function[WB_PATCH_REMAPPMENU])
			(os_object,wb_data->wb_base);
	}

	// Send notification
	if (os_object!=(APTR)entry)
		L_SendNotifyMsg(DN_APP_MENU_LIST,(ULONG)entry,1,!local,0,0,libbase);

	return 1;
}


// Find AppWindow
struct AppWindow __asm __saveds *L_WB_FindAppWindow(
	register __a0 struct Window *window,
	register __a6 struct MyLibrary *libbase)
{
	AppEntry *app_entry,*app_window=0;
	WB_Data *wb_data;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Lock list
	L_GetSemaphore(&wb_data->patch_lock,SEMF_SHARED,0);

	// Go through app objects
	for (app_entry=(AppEntry *)wb_data->app_list.mlh_Head;
		app_entry->node.mln_Succ;
		app_entry=(AppEntry *)app_entry->node.mln_Succ)
	{
		// Is this the window?
		if (app_entry->type==APP_WINDOW &&
			app_entry->object==window)
		{
			// Forbid so window can't go
			Forbid();

			// Save pointer
			app_window=app_entry;
			break;
		}
	}

	// Unlock list
	L_FreeSemaphore(&wb_data->patch_lock);
	return (struct AppWindow *)app_window;
}


// Get AppWindow data
struct MsgPort *__asm __saveds L_WB_AppWindowData(
	register __a0 struct AppWindow *window,
	register __a1 ULONG *id,
	register __a2 ULONG *userdata)
{
	AppEntry *entry;

	// Valid entry?
	if (entry=(AppEntry *)window)
	{
		if (id) *id=entry->id;
		if (userdata) *userdata=entry->userdata;
		return entry->port;
	}
	return 0;
}


// Is an AppWindow "local"?
BOOL __asm __saveds L_WB_AppWindowLocal(
	register __a0 struct AppWindow *window)
{
	return (BOOL)((((AppEntry *)window)->flags&APPENTF_LOCAL)?1:0);
}


// Get AppWindow window pointer
struct Window *__asm __saveds L_WB_AppWindowWindow(
	register __a0 struct AppWindow *window)
{
	return (struct Window *)(((AppEntry *)window)->object);
}


// Get AppIcon flags
unsigned long __asm __saveds L_WB_AppIconFlags(
	register __a0 struct AppIcon *icon)
{
	return ((AppEntry *)icon)->flags;
}


// Add a new AppEntry
AppEntry *new_app_entry(
	ULONG type,
	ULONG id,
	ULONG userdata,
	APTR object,
	char *text,
	struct MsgPort *port,
	WB_Data *wb_data)
{
	AppEntry *entry;

	// Allocate new entry
	if (!(entry=AllocVec(sizeof(AppEntry),MEMF_CLEAR)))
		return 0;

	// Fill out AppEntry
	entry->type=type;
	entry->id=id;
	entry->userdata=userdata;
	entry->text=text;
	entry->port=port;
	NewList((struct List *)&entry->menu);

	// AppIcon?
	if (type==APP_ICON)
	{
		struct DiskObject *icon_copy;

		// Copy icon
		if (icon_copy=L_CopyDiskObject((struct DiskObject *)object,0,wb_data->dopus_base))
		{
			// Use copy
			entry->object=icon_copy;
			entry->flags|=APPENTF_ICON_COPY;
		}

		// Couldn't copy
		else
		{
			FreeVec(entry);
			return 0;
		}
	}

	// Otherwise, save object pointer
	else entry->object=object;

	// Lock patch list
	L_GetSemaphore(&wb_data->patch_lock,SEMF_EXCLUSIVE,0);

	// Is this the first entry?
	if (IsListEmpty((struct List *)&wb_data->app_list))
	{
		// Bump library open count so we won't get expunged
		++wb_data->dopus_base->ml_Lib.lib_OpenCnt;
	}

	// Add to list
	AddTail((struct List *)&wb_data->app_list,(struct Node *)entry);

	// Unlock list
	L_FreeSemaphore(&wb_data->patch_lock);
	return entry;
}


// Remove an AppEntry
APTR rem_app_entry(
	AppEntry *entry,
	WB_Data *wb_data,
	BOOL *local)
{
	AppEntry *app_entry;
	APTR retval;

	// Save pointer
	retval=entry;

	// Clear local flag
	if (local) *local=0;

	// Lock AppEntry list
	L_GetSemaphore(&wb_data->patch_lock,SEMF_EXCLUSIVE,0);

	// Look for entry in list
	for (app_entry=(AppEntry *)wb_data->app_list.mlh_Head;
		app_entry!=entry && app_entry->node.mln_Succ;
		app_entry=(AppEntry *)app_entry->node.mln_Succ);

	// Found match?
	if (app_entry==entry)
	{
		// Remove from list
		Remove((struct Node *)entry);

		// Return OS object pointer
		retval=entry->os_object;

		// Local?
		if (local && entry->flags&APPENTF_LOCAL) *local=1;

		// Add to removal list
		AddTail((struct List *)&wb_data->rem_app_list,(struct Node *)entry);

		// Zero the count
		entry->menu_id_base=0;
	}

	// Unlock list
	L_FreeSemaphore(&wb_data->patch_lock);

	// Return pointer to OS object
	return retval;
}


// Free an entry from the removal list
void free_app_entry(AppEntry *entry,WB_Data *wb_data)
{
	struct MinNode *node;

	// Remove entry from list
	Remove((struct Node *)entry);

	// Free menu nodes
	for (node=entry->menu.mlh_Head;node->mln_Succ;)
	{
		// Cache next pointer
		struct MinNode *next=node->mln_Succ;

		// Free node
		FreeVec(node);

		// Get next
		node=next;
	}

	// Free icon
	if (entry->flags&APPENTF_ICON_COPY)
		L_FreeDiskObjectCopy((struct DiskObject *)entry->object,wb_data->dopus_base);

	// Free data structure
	FreeVec(entry);
}


// Find an AppEntry
AppEntry *find_app_entry(AppEntry *entry,WB_Data *wb_data)
{
	AppEntry *app_entry;

	// Lock AppEntry list
	L_GetSemaphore(&wb_data->patch_lock,SEMF_SHARED,0);

	// Look for entry in list
	for (app_entry=(AppEntry *)wb_data->app_list.mlh_Head;
		app_entry!=entry && app_entry->node.mln_Succ;
		app_entry=(AppEntry *)app_entry->node.mln_Succ);

	// Found match?
	if (app_entry==entry) return entry;

	// Unlock list
	L_FreeSemaphore(&wb_data->patch_lock);

	// Not found
	return 0;
}


// Lock the AppList
APTR __asm __saveds L_LockAppList(register __a6 struct MyLibrary *libbase)
{
	WB_Data *wb_data;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Get a lock on the list
	L_GetSemaphore(&wb_data->patch_lock,SEMF_SHARED,0);

	// Increment lock count
	++wb_data->lock_count;

	// Return indicates start of list
	return wb_data;
}


// Get the next app entry of a certain type
APTR __asm __saveds L_NextAppEntry(
	register __a0 APTR last,
	register __d0 ULONG type,
	register __a6 struct MyLibrary *libbase)
{
	WB_Data *wb_data;
	AppEntry *entry;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Invalid "last" pointer?
	if (!last) return 0;

	// Start of list?
	if (last==wb_data) entry=(AppEntry *)wb_data->app_list.mlh_Head;

	// Otherwise, go from next entry
	else entry=(AppEntry *)((AppEntry *)last)->node.mln_Succ;

	// Scan list
	while (entry->node.mln_Succ)
	{
		// Correct type?
		if (entry->type==type) return entry;

		// Get next entry
		entry=(AppEntry *)entry->node.mln_Succ;
	}

	// Not found
	return 0;
}


// Unlock the AppList
void __asm __saveds L_UnlockAppList(register __a6 struct MyLibrary *libbase)
{
	WB_Data *wb_data;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Check it's locked
	if (wb_data->lock_count>0)
	{
		// Unlock the list
		L_FreeSemaphore(&wb_data->patch_lock);

		// Decrement lock count
		--wb_data->lock_count;
	}
}


// Close Workbench screen
LONG __asm __saveds L_WB_CloseWorkBench(void)
{
	WB_Data *wb_data;
	struct MyLibrary *libbase;
	LONG result;

	// Open library
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Send notification
	L_SendNotifyMsg(DN_CLOSE_WORKBENCH,0,0,FALSE,0,0,libbase);

	// Close workbench screen
	result=
		((LONG __asm (*)
			(register __a6 struct Library *))wb_data->old_function[WB_PATCH_CLOSEWORKBENCH])
			(wb_data->int_base);

	return result;
}


// Open Workbench screen
ULONG __asm __saveds L_WB_OpenWorkBench(void)
{
	WB_Data *wb_data;
	struct MyLibrary *libbase;
	ULONG result;

	// Open library
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Send notification
	L_SendNotifyMsg(DN_OPEN_WORKBENCH,0,0,FALSE,0,0,libbase);

	// Open workbench screen
	result=
		((ULONG __asm (*)
			(register __a6 struct Library *))wb_data->old_function[WB_PATCH_OPENWORKBENCH])
			(wb_data->int_base);

	return result;
}


// Change an AppIcon's image
void __asm __saveds L_ChangeAppIcon(
	register __a0 APTR appicon,
	register __a1 struct Image *render,
	register __a2 struct Image *select,
	register __a3 char *title,
	register __d0 ULONG flags,
	register __a6 struct MyLibrary *libbase)
{
	AppEntry *app_entry;
	WB_Data *wb_data;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// Lock AppEntry list
	L_GetSemaphore(&wb_data->patch_lock,SEMF_SHARED,0);

	// Look for entry in list
	for (app_entry=(AppEntry *)wb_data->app_list.mlh_Head;
		app_entry!=(AppEntry *)appicon && app_entry->node.mln_Succ;
		app_entry=(AppEntry *)app_entry->node.mln_Succ);

	// Found it?
	if (app_entry==(AppEntry *)appicon)
	{
		struct DiskObject *icon;

		// Get icon pointer
		if (icon=(struct DiskObject *)app_entry->object)
		{
			ULONG notify_flags=DNF_ICON_CHANGED;

			// Set image and title pointers
			if (flags&CAIF_RENDER)
			{
				icon->do_Gadget.GadgetRender=render;
				notify_flags|=DNF_ICON_IMAGE_CHANGED;
			}				
			if (flags&CAIF_SELECT)
			{
				icon->do_Gadget.SelectRender=select;
				notify_flags|=DNF_ICON_IMAGE_CHANGED;
			}
			if (flags&CAIF_TITLE) app_entry->text=title;

			// Change locked state
			if (flags&CAIF_LOCKED)
			{
				// Set?
				if (flags&CAIF_SET) app_entry->flags|=APPENTF_LOCKED;

				// Clear
				else app_entry->flags&=~APPENTF_LOCKED;
			}

			// Change ghosted state
			if (flags&CAIF_GHOST)
			{
				// Set?
				if (flags&CAIF_SET) app_entry->flags|=APPENTF_GHOSTED;

				// Clear
				else app_entry->flags&=~APPENTF_GHOSTED;
			}

			// Change busy state?
			if (flags&CAIF_BUSY) app_entry->flags|=APPENTF_BUSY;
			else
			if (flags&CAIF_UNBUSY) app_entry->flags&=~APPENTF_BUSY;

			// Send notification
			L_SendNotifyMsg(DN_APP_ICON_LIST,(ULONG)app_entry,notify_flags,FALSE,0,0,libbase);
		}
	}

	// Unlock list
	L_FreeSemaphore(&wb_data->patch_lock);
}


// Set the state of a toggle appicon menu
long __asm __saveds L_SetAppIconMenuState(
	register __a0 APTR appicon,
	register __d0 long item,
	register __d1 long state)
{
	long res=-1,num;
	struct Node *node;
	AppEntry *app_entry=(AppEntry *)appicon;

	// Go through menus
	for (node=(struct Node *)app_entry->menu.mlh_Head,num=0;
		node->ln_Succ && num<item;
		node=node->ln_Succ,num++);

	// Got item?
	if (node->ln_Succ)
	{
		// Get old value
		res=(node->ln_MenuFlags&MNF_SEL)?1:0;

		// Set new value
		if (state) node->ln_MenuFlags|=MNF_SEL;
		else node->ln_MenuFlags&=~MNF_SEL;
	}

	return res;
}


// Copy a DiskObject
struct DiskObject *__asm __saveds L_CopyDiskObject(
	register __a0 struct DiskObject *icon,
	register __d0 ULONG flags,
	register __a6 struct MyLibrary *libbase)
{
	DiskObjectCopy *copy;
	long planesize;
	struct LibData *data;
	WB_Data *wb_data;

	// Valid icon?
	if (!icon) return 0;

	// Get data pointers
	data=(struct LibData *)libbase->ml_UserData;
	wb_data=&data->wb_data;


#define IconBase	(data->icon_base)

	if	(IconBase->lib_Version>=44)
	{	
		struct DiskObject * icon_copy;

		icon_copy=DupDiskObject(icon,TAG_DONE);

		return icon_copy;

	}

#undef IconBase


	// Allocate copy structure
	if (!(copy=L_AllocMemH(data->memory,sizeof(DiskObjectCopy))))
		return 0;

	// Copy DiskObject structure
	CopyMem((char *)icon,(char *)&copy->doc_DiskObject,sizeof(struct DiskObject));

	// Null-out pointers
	copy->doc_DiskObject.do_DefaultTool=0;
	copy->doc_DiskObject.do_ToolTypes=0;
	copy->doc_DiskObject.do_DrawerData=0;
	copy->doc_DiskObject.do_ToolWindow=0;

	// Copying things?
	if (flags&DOCF_COPYALL)
	{
		// Copy default tool
		if (icon->do_DefaultTool &&
			(copy->doc_DiskObject.do_DefaultTool=L_AllocMemH(data->memory,strlen(icon->do_DefaultTool)+1)))
			strcpy(copy->doc_DiskObject.do_DefaultTool,icon->do_DefaultTool);

		// Any tooltypes?
		if (icon->do_ToolTypes)
		{
			short count;

			// Count tooltypes
			for (count=0;icon->do_ToolTypes[count];count++);

			// Allocate array
			if (copy->doc_DiskObject.do_ToolTypes=L_AllocMemH(data->memory,(count+1)<<2))
			{
				// Copy tooltypes
				for (count=0;icon->do_ToolTypes[count];count++)
				{
					// Copy string
					if (copy->doc_DiskObject.do_ToolTypes[count]=
						L_AllocMemH(data->memory,strlen(icon->do_ToolTypes[count])+1))
						strcpy(copy->doc_DiskObject.do_ToolTypes[count],icon->do_ToolTypes[count]);
					else break;
				}
			}
		}

		// Drawer data?
		if (icon->do_DrawerData &&
			(copy->doc_DiskObject.do_DrawerData=L_AllocMemH(data->memory,sizeof(struct DrawerData))))
			CopyMem(
				(char *)icon->do_DrawerData,
				(char *)copy->doc_DiskObject.do_DrawerData,
				sizeof(struct DrawerData));

		// Tool window?
		if (icon->do_ToolWindow &&
			(copy->doc_DiskObject.do_ToolWindow=L_AllocMemH(data->memory,strlen(icon->do_ToolWindow)+1)))
			strcpy(copy->doc_DiskObject.do_ToolWindow,icon->do_ToolWindow);
	}

	// Allowed to copy images?
	if (!(flags&DOCF_NOIMAGE))
	{
		// Primary image?
		if (icon->do_Gadget.GadgetRender)
		{
			// Set image pointer
			copy->doc_DiskObject.do_Gadget.GadgetRender=&copy->doc_GadgetRender;

			// Copy image structure
			copy->doc_GadgetRender=*((struct Image *)icon->do_Gadget.GadgetRender);

			// Calculate plane size
			planesize=UMult32(
						UMult32(
							((copy->doc_GadgetRender.Width+15)>>3&0xfffe),
							copy->doc_GadgetRender.Height),
						copy->doc_GadgetRender.Depth);

			// Allocate image data and copy
			if (copy->doc_Image1=AllocVec(planesize,MEMF_CHIP|MEMF_CLEAR))
			{
				copy->doc_GadgetRender.ImageData=(USHORT *)copy->doc_Image1;
				CopyMem(
					(char *)(((struct Image *)icon->do_Gadget.GadgetRender)->ImageData),
					(char *)copy->doc_GadgetRender.ImageData,
					planesize);
			}

			// Failed
			else
			{
				L_FreeMemH(copy);	
				return 0;
			}
		}

		// Secondary image?
		if (icon->do_Gadget.SelectRender)
		{
			// Set image pointer
			copy->doc_DiskObject.do_Gadget.SelectRender=&copy->doc_SelectRender;

			// Copy image structure
			copy->doc_SelectRender=*((struct Image *)icon->do_Gadget.SelectRender);

			// Calculate plane size
			planesize=UMult32(
						UMult32(
							((copy->doc_SelectRender.Width+15)>>3&0xfffe),
							copy->doc_SelectRender.Height),
						copy->doc_SelectRender.Depth);

			// Allocate image data and copy
			if (copy->doc_Image2=AllocVec(planesize,MEMF_CHIP|MEMF_CLEAR))
			{
				copy->doc_SelectRender.ImageData=(USHORT *)copy->doc_Image2;
				CopyMem(
					(char *)(((struct Image *)icon->do_Gadget.SelectRender)->ImageData),
					(char *)copy->doc_SelectRender.ImageData,
					planesize);
			}

			// Failed
			else
			{
				copy->doc_DiskObject.do_Gadget.SelectRender=0;
				copy->doc_DiskObject.do_Gadget.Flags&=~GFLG_GADGHIMAGE;
			}
		}
	}

	// To signify that this is a copy, we point SpecialInfo at ourselves
	copy->doc_DiskObject.do_Gadget.SpecialInfo=(APTR)copy;

	return (struct DiskObject *)copy;
}


// Free a DiskObject copy
void __asm __saveds L_FreeDiskObjectCopy(
	register __a0 struct DiskObject *icon,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;
	short type;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Valid icon?
	if (!icon) return;

#define IconBase	(data->icon_base)
	if	(IconBase->lib_Version>=44)
	{
		FreeDiskObject(icon);
		return;
	}
#undef IconBase


	// Is this a copy?
	if ((type=L_GetIconType(icon))==ICON_CACHED)
	{
		short count;
		DiskObjectCopy *copy=(DiskObjectCopy *)icon;

		// Free images
		FreeVec(copy->doc_Image1);
		FreeVec(copy->doc_Image2);

		// Free strings and drawerdata
		L_FreeMemH(copy->doc_DiskObject.do_DefaultTool);
		L_FreeMemH(copy->doc_DiskObject.do_DrawerData);
		L_FreeMemH(copy->doc_DiskObject.do_ToolWindow);

		// Tooltypes?
		if (copy->doc_DiskObject.do_ToolTypes)
		{
			// Free tooltypes
			for (count=0;copy->doc_DiskObject.do_ToolTypes[count];count++)
				L_FreeMemH(copy->doc_DiskObject.do_ToolTypes[count]);
			L_FreeMemH(copy->doc_DiskObject.do_ToolTypes);
		}

		// Free copy structure
		L_FreeMemH(copy);
	}

	// Or is it a NewIcon?
	else
	if (type==ICON_NEWICON)
	{
#ifdef DEBUG_ICON
if (((struct NewIconDiskObject *)icon)->nido_Flags&NIDOF_REMAPPED)
	KPrintF("error! icon freed while still remapped\n");
#endif

#define NewIconBase	(data->new_icon_base)
		// Free the NewDiskObject part
		FreeNewDiskObject(((struct NewIconDiskObject *)icon)->nido_NewDiskObject);
#undef NewIconBase

		// Free our part
		FreeVec(icon);
	}

	// Assume it's a real icon
	else
	{
#define IconBase	(data->icon_base)
		FreeDiskObject(icon);
#undef IconBase
	}
}


// AddPort patch
void __asm __saveds L_WB_AddPort(register __a1 struct MsgPort *port)
{
	struct MyLibrary *libbase;
	WB_Data *wb_data;

	// Invalid port?
	if (!port) return;

	// Get library pointer
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)libbase->ml_UserData)->wb_data;

	// ARexx?
	if (port->mp_Node.ln_Name &&
		strcmp(port->mp_Node.ln_Name,"REXX")==0)
	{
		// Send notification
		L_SendNotifyMsg(DN_REXX_UP,0,0,0,0,0,libbase);
	}

	// Pass through
	((void __asm (*)
		(register __a1 struct MsgPort *,register __a6 struct ExecBase *))wb_data->old_function[WB_PATCH_ADDPORT])
		(port,ExecLib);
}


// CloseWindow patch
void __asm __saveds L_WB_CloseWindow(register __a0 struct Window *window)
{
	struct PubScreenNode *node;
	struct MyLibrary *DOpusBase;
	WB_Data *wb_data;
	struct Task *sigtask=0;
	UBYTE sigbit=0;

	// Invalid window?
	if (!window) return;

	// Get library pointer
	if (!(DOpusBase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return;

	// Get Workbench data pointer
	wb_data=&((struct LibData *)DOpusBase->ml_UserData)->wb_data;

	// See if the screen is public
	if (node=FindPubScreen(window->WScreen,0))
	{
		// Is it the Opus screen?
		if (strncmp(node->psn_Node.ln_Name,"DOPUS.",6)==0)
		{
			// Get task to signal
			sigtask=node->psn_SigTask;
			sigbit=node->psn_SigBit;
		}
	}

	// Close window
	((void __asm (*)
		(register __a0 struct Window *,register __a6 struct Library *))wb_data->old_function[WB_PATCH_CLOSEWINDOW])
		(window,wb_data->int_base);

	// Task to signal?
	if (sigtask) Signal(sigtask,1<<sigbit);
}


// Get library base to patch
struct Library *wb_get_patchbase(short type,struct LibData *data)
{
	struct Library *lib=0;

	// Look at type
	switch (type)
	{
		// Workbench
		case WB_PATCH_WORKBENCH:
			lib=WorkbenchBase;
			break;

		// DOS patched function
		case WB_PATCH_DOSFUNC:

			// Does flag allow these patches?
			if (data->flags&LIBDF_DOS_PATCH)
				lib=(struct Library *)DOSBase;
			break;

		// DOS
		case WB_PATCH_DOS:
			lib=(struct Library *)DOSBase;
			break;

		// Intuition
		case WB_PATCH_INTUITION:
			lib=(struct Library *)IntuitionBase;
			break;

		// Graphics
		case WB_PATCH_GFX:
			lib=(struct Library *)GfxBase;
			break;

		// Exec
		case WB_PATCH_EXEC:
			lib=(struct Library *)ExecLib;
			break;

		// Icon
		case WB_PATCH_ICON:
			lib=IconBase;
			break;
	}

	return lib;
}


// CloseWindow patch
ULONG __asm __saveds L_PatchedWBInfo(
	register __a0 BPTR lock,
	register __a1 char *name,
	register __a2 struct Screen *screen)
{
	struct MyLibrary *libbase;
	struct DOpusSemaphore *sem;
	IPCData *main_ipc=0;
	struct LibData *data;
	char buf[10];

	// Get library pointer
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Get DOpus semaphore?
	if (sem=(struct DOpusSemaphore *)FindSemaphore("DOpus Public Semaphore"))
		main_ipc=(IPCData *)sem->main_ipc;

#define DOSBase	(data->dos_base)
	// Patch WBInfo() ?
	if (main_ipc && GetVar("dopus/PatchWBInfo",buf,2,GVF_GLOBAL_ONLY)>0 && buf[0]=='1')
	{
		struct Library *ModuleBase;

		// Open the icon.module
		if (ModuleBase=OpenLibrary("dopus5:modules/icon.module",0))
		{
			BPTR old;
			struct List files;
			struct Node node;
			ULONG res;

			// Switch to this directory
			old=CurrentDir(lock);

			// Build fake file list
			NewList(&files);
			AddTail(&files,&node);
			node.ln_Name=name;

			// Call the module
			res=Module_Entry(&files,screen,0,main_ipc,0,0x96604497);

			// Restore current directory
			CurrentDir(old);

			// Close the module
			CloseLibrary(ModuleBase);
			return res;
		}
	}
#undef DOSBase

	// Call original function
	return ((ULONG __asm (*)
		(register __a0 BPTR,register __a1 char *,register __a2 struct Screen *,register __a6 struct Library *))
			data->wb_data.old_function[WB_PATCH_WBINFO])
			(lock,name,screen,data->wb_data.wb_base);
}


// Patched AddTask (for statistics)
APTR __asm L_PatchedAddTask(register __a1 struct Task *task,register __a2 APTR initialPC,register __a3 APTR finalPC)
{
	struct MyLibrary *libbase;
	struct LibData *data;

	// Get library pointer
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Increment task count
	++data->task_count;

	// Call original function
	return ((APTR __asm (*)
		(register __a1 struct Task *,register __a2 APTR,register __a3 APTR,register __a6 struct Library *))
			data->wb_data.old_function[WB_PATCH_ADDTASK])
			(task,initialPC,finalPC,(struct Library *)*((ULONG *)4));
}

// Patched RemTask (for statistics)
void __asm L_PatchedRemTask(register __a1 struct Task *task)
{
	struct MyLibrary *libbase;
	struct LibData *data;

	// Get library pointer
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Decrement task count
	--data->task_count;

	// Call original function
	((void __asm (*)
		(register __a1 struct Task *,register __a6 struct Library *))
			data->wb_data.old_function[WB_PATCH_REMTASK])
			(task,(struct Library *)*((ULONG *)4));
}


// Patched FindTask
struct Task *__asm L_PatchedFindTask(register __a1 char *name)
{
	struct MyLibrary *libbase;
	struct LibData *data;
	struct Task *task;

	// This task?
	if (!name) return ExecLib->ThisTask;

	// Get library pointer
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Call original function
	if (task=((struct Task *__asm (*)
			(register __a1 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_FINDTASK])
				(name,(struct Library *)*((ULONG *)4)))
		return task;

	// Task not found, were they looking for workbench?
	if (strcmp(name,"Workbench")==0)
	{
		// Return the Launcher task (hopefully all they want is the path list)
		if (data->launcher)
			return (struct Task *)data->launcher->proc;
	}

	// Not found
	return 0;
}


// OpenWindowTags patch
struct Window *__asm __saveds L_PatchedOpenWindowTags(register __a0 struct NewWindow *newwin,register __a1 struct TagItem *tags)
{
	struct MyLibrary *libbase;
	struct LibData *data;
	WB_Data *wb_data;

	// Get library pointer
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get data pointers
	data=(struct LibData *)libbase->ml_UserData;
	wb_data=&data->wb_data;

	// Is window being opened by the kludge task?
	if (data->open_window_kludge==(struct Process *)ExecLib->ThisTask)
	{
		short x,y,w,h;
		struct Screen *scr;
		struct TagItem *tag;
		BOOL lock=0;

#define IntuitionBase	(data->int_base)

		// Get window size
		w=GetTagData(WA_Width,(newwin)?newwin->Width:0,tags);
		h=GetTagData(WA_Height,(newwin)?newwin->Height:0,tags);

		// Get screen
		if (!(scr=(struct Screen *)GetTagData(WA_CustomScreen,(newwin)?(ULONG)newwin->Screen:0,tags)))
		{
			scr=LockPubScreen(0);
			lock=1;
		}

		// Calculate position from mouse pointer		
		x=scr->MouseX-(w>>1);
		y=scr->MouseY-(h>>1);

		// Unlock screen if locked
		if (lock) UnlockPubScreen(0,scr);

		// Set new window position
		if (newwin)
		{
			newwin->LeftEdge=x;
			newwin->TopEdge=y;
		}
		if (tag=FindTagItem(WA_Left,tags)) tag->ti_Data=x;
		if (tag=FindTagItem(WA_Top,tags)) tag->ti_Data=y;

#undef IntuitionBase

		// Kludge is only used once
		data->open_window_kludge=0;
	}

	// Open window
	return ((struct Window * __asm (*)
		(register __a0 struct NewWindow *,register __a1 struct TagItem *,register __a6 struct Library *))wb_data->old_function[WB_PATCH_OPENWINDOWTAGS])
		(newwin,tags,data->int_base);
}


/*
// Patched AllocBitmap to allocate proper bitmap
struct BitMap *__asm __saveds L_PatchedAllocBitmap(
	register __d0 ULONG sizex,
	register __d1 ULONG sizey,
	register __d2 ULONG depth,
	register __d3 ULONG flags,
	register __a0 struct BitMap *friend,
	register __a6 struct Library *GfxBase)
{
	struct AllocBitmapPatchNode *node;
	struct BitMap *bitmap;
	struct MyLibrary *libbase;
	struct LibData *data;

	// Get library pointer
	if (!(libbase=(struct MyLibrary *)FindName(&ExecLib->LibList,"dopus5.library")))
		return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Lock patch list
	ObtainSemaphoreShared((struct SignalSemaphore *)&data->allocbitmap_patch.lock);

	// See if this task is on the list
	for (node=(struct AllocBitmapPatchNode *)data->allocbitmap_patch.list.lh_Head;
		node->abp_Node.mln_Succ;
		node=(struct AllocBitmapPatchNode *)node->abp_Node.mln_Succ)
	{
		// Match the task pointer
		if (node->abp_Task==FindTask(0))
		{
			// No friend supplied?
			if (!friend) //  && flags==0)
			{
				// See if the screen has a custom bitmap
				if (!(GetBitMapAttr(node->abp_Screen->RastPort.BitMap,BMA_FLAGS)&BMF_STANDARD))
				{
					// We now want to allocate a friend bitmap
					flags|=BMF_MINPLANES;
					friend=node->abp_Screen->RastPort.BitMap;
				}
			}
			break;
		}
	}

	// Release the semaphore
	ReleaseSemaphore((struct SignalSemaphore *)&data->allocbitmap_patch.lock);

	// Allocate the bitmap
	bitmap=((struct BitMap *__asm (*)
				(register __d0 ULONG,
				 register __d1 ULONG,
				 register __d2 ULONG,
				 register __d3 ULONG,
				 register __a0 struct BitMap *,
				 register __a6 struct Library *))data->wb_data.old_function[WB_PATCH_ALLOCBITMAP])
				 (sizex,sizey,depth,flags,friend,GfxBase);

	return bitmap;
}
*/


// Add task to patch list
APTR __saveds __asm L_AddAllocBitmapPatch(register __a0 struct Task *task,register __a1 struct Screen *screen,register __a6 struct MyLibrary *libbase)
{
/*
	struct LibData *data;
	struct AllocBitmapPatchNode *node;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Lock patch list
	ObtainSemaphore((struct SignalSemaphore *)&data->allocbitmap_patch.lock);

	// Allocate node
	if (node=AllocVec(sizeof(struct AllocBitmapPatchNode),MEMF_CLEAR))
	{
		// Add to list
		node->abp_Task=task;
		node->abp_Screen=screen;
		AddTail(&data->allocbitmap_patch.list,(struct Node *)node);
	}

	// Release the semaphore
	ReleaseSemaphore((struct SignalSemaphore *)&data->allocbitmap_patch.lock);
	return node;
*/
	return 0;
}


// Remove task from patch list
void __saveds __asm L_RemAllocBitmapPatch(register __a0 APTR handle,register __a6 struct MyLibrary *libbase)
{
/*
	struct LibData *data;
	struct AllocBitmapPatchNode *node;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Lock patch list
	ObtainSemaphore((struct SignalSemaphore *)&data->allocbitmap_patch.lock);

	// Find node
	for (node=(struct AllocBitmapPatchNode *)data->allocbitmap_patch.list.lh_Head;
		node->abp_Node.mln_Succ;
		node=(struct AllocBitmapPatchNode *)node->abp_Node.mln_Succ)
	{
		// Match the handle
		if (handle==(APTR)node)
		{
			// Remove this node
			Remove((struct Node *)node);
			FreeVec(node);
			break;
		}
	}

	// Release the semaphore
	ReleaseSemaphore((struct SignalSemaphore *)&data->allocbitmap_patch.lock);
*/
}
