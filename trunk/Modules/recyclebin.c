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

#include "recyclebin.h"

static char *version="$VER: recyclebin.module 44.2 (12.06.96)";

int __asm __saveds L_Module_Entry(
	register __a0 char *string,
	register __a1 struct Screen *screen,
	register __a2 IPCData *ipc,
	register __a3 IPCData *main_ipc,
	register __d0 ULONG mod_id,
	register __d1 EXT_FUNC(func_callback))
{
	RecyclePacket *packet;
	RecycleSemaphore *sem;
	IPCData *recycle_ipc;
	long ret=1;

	// Disable multi-tasking
	Forbid();

	// Look for Semaphore
	if (sem=(RecycleSemaphore *)FindSemaphore(NAME_RECYCLEBIN))
	{
		// Lock the semaphore
		ObtainSemaphore((struct SignalSemaphore *)sem);
	}

	// Enable multi-tasking
	Permit();

	// Need to launch?
	if (!sem)
	{
		recyclebin_data *data;

		// Allocate data
		if (data=AllocVec(sizeof(recyclebin_data),MEMF_CLEAR))
		{
			// Store A4 and library bases
			data->a4=getreg(REG_A4);
			data->library=DOpusBase;
			data->module=(struct Library *)getreg(REG_A6);
			data->callback=func_callback;

			// Launch process
			if (!(IPC_Launch(
				0,
				&recycle_ipc,
				NAME_RECYCLEBIN,
				(ULONG)recycle_bin,
				4000,
				(ULONG)data,
				DOSBase))) FreeVec(data);
		}

		// No process?
		if (!recycle_ipc) return 0;
	}

	// Get process from semaphore
	else recycle_ipc=sem->ipc;

	// Allocate packet
	if (packet=AllocVec(sizeof(RecyclePacket),MEMF_CLEAR))
	{
		// Fill out packet
		packet->string=string;
		packet->screen=screen;
		packet->ipc=ipc;
		packet->main_ipc=main_ipc;
		packet->mod_id=mod_id;
		packet->func_callback=func_callback;

		// Send message
		ret=IPC_Command(recycle_ipc,CMD_PASS,0,packet,0,REPLY_NO_PORT);

		// Fix IoErr()
		SetIoErr(packet->err);

		// Free packet
		FreeVec(packet);
	}

	// Release semaphore
	if (sem) ReleaseSemaphore((struct SignalSemaphore *)sem);
	return ret;
}


// Recycle bin process
void __saveds recycle_bin(void)
{
	IPCData *ipc;
	IPCMessage *msg;
	DOpusNotify *nmsg;
	DOpusAppMessage *amsg;
	struct Library *DOpusBase;
	BOOL installed=0;
	recyclebin_data *data;
	struct pointer_packet pkt;
	BOOL quit=0;

	// Get dopus library
	if (!(DOpusBase=(struct Library *)FindName(&((struct ExecBase *)*((ULONG *)4))->LibList,"dopus5.library")))
		return;

	// Do startup
	if (!(ipc=IPC_ProcStartup((ULONG *)&data,recyclebin_startup)))
	{
		recyclebin_cleanup(data,0);
		return;
	}

	// Fix A4
	putreg(REG_A4,data->a4);

	// Fill out pointer packet
	pkt.type=MODPTR_HANDLE;
	pkt.flags=0;
	pkt.pointer=data->reply_port;

	// Get handle
	data->function_handle=(APTR)(data->callback)(EXTCMD_GET_POINTER,0,&pkt);

	// Event loop
	FOREVER
	{
		// IPC messages?
		while (msg=(IPCMessage *)GetMsg(ipc->command_port))
		{
			// Command passed on?
			if (msg->command==CMD_PASS)
			{
				RecyclePacket *packet;

				// Not installed yet?
				if (!installed)
				{
					recycle_bin_install(msg->data,data);
					installed=1;
				}

				// Get packet pointer
				packet=(RecyclePacket *)msg->data;

				// Delete?
				if (packet->mod_id==CMD_DELETE)
				{
					// Delete the file
					msg->command=recyclebin_delete(data,packet->string);
				}

				// Return IoErr()
				packet->err=IoErr();
			}

			// Reply to message
			IPC_Reply(msg);
		}

		// Notify messages?
		while (nmsg=(DOpusNotify *)GetMsg(data->notify_port))
		{
			// Quit?
			if (nmsg->dn_Type&DN_OPUS_QUIT) quit=1;

			// Reply to the message
			ReplyFreeMsg(nmsg);
		}

		// Check quit flag
		if (quit)
		{
			// Try for our semaphore
			if (AttemptSemaphore((struct SignalSemaphore *)&data->sem)) break;

			// Start timer
			StartTimer(data->timer,0,500000);
		}

		// Window open?
		if (data->window)
		{
			struct IntuiMessage *msg,msg_copy;

			// Get messages
			while (msg=GetWindowMsg(data->window->UserPort))
			{
				// Copy message and reply
				msg_copy=*msg;
				ReplyWindowMsg(msg);

				// Look at message
				switch (msg_copy.Class)
				{
					// Close window
					case IDCMP_CLOSEWINDOW:
						recyclebin_close_window(data);
						break;
				}

				// Window has been shut?
				if (!data->window) break;
			}
		}

		// AppMessages?
		while (amsg=(DOpusAppMessage *)GetMsg(data->app_port))
		{
			// SnapShot?
			if (amsg->da_Msg.am_Type==MTYPE_APPSNAPSHOT)
			{
				struct AppSnapshotMsg *asm;

				// Get SnapShot message pointer
				asm=(struct AppSnapshotMsg *)amsg;

				// Menu operation?
				if (asm->flags&APPSNAPF_MENU)
				{
				}

				// Otherwise
				else
				{
					// Unsnapshot?
					if (asm->flags&APPSNAPF_UNSNAPSHOT)
					{
						// Reinitialise position
						data->icon_x=NO_ICON_POSITION;
						data->icon_y=NO_ICON_POSITION;
					}

					// Store position
					else
					{
						data->icon_x=asm->position_x;
						data->icon_y=asm->position_y;
					}

					// Build environment variable
					lsprintf(data->buffer,"%ld/%ld\n",data->icon_x,data->icon_y);

					// Set environment variable
					SetEnv(ENV_RECYCLEBIN,data->buffer,TRUE);
				}
			}

			// Icon manipulation?
			else
			if (amsg->da_Msg.am_Type==MTYPE_APPICON)
			{
				// Double-click?
				if (amsg->da_Msg.am_NumArgs==0)
				{
					struct command_packet pkt;

					// Open window
//					recyclebin_open_window(data);

					pkt.command="lister new";
					pkt.flags=COMMANDF_RESULT;
					(data->callback)(EXTCMD_SEND_COMMAND,data->function_handle,&pkt);
					FreeVec(pkt.result);
				}

				// Drop files
				else
				{
					short arg;
					BOOL icon=0;

					// DOpus message?
					if (CheckAppMessage(amsg))
					{
						// Icon mode?
						if (amsg->da_Flags&DAPPF_ICON_DROP) icon=1;
					}

					// Go through arguments
					for (arg=0;arg<amsg->da_Msg.am_NumArgs;arg++)
					{
						short loop;

						// Build name
						DevNameFromLock(amsg->da_Msg.am_ArgList[arg].wa_Lock,data->buffer,256);

						// Filename?
						if (amsg->da_Msg.am_ArgList[arg].wa_Name &&
							*amsg->da_Msg.am_ArgList[arg].wa_Name)
						{
							// Add name
							AddPart(data->buffer,amsg->da_Msg.am_ArgList[arg].wa_Name,256);
						}

						// Otherwise
						else
						{
							char *ptr;

							// Must be more than a device name
							if (!(ptr=strchr(data->buffer,':')) ||
								ptr[1]==0) continue;
						}

						// Loop to do icons
						for (loop=0;loop<2;loop++)
						{
							// Delete the file
							if (recyclebin_delete(data,data->buffer))
							{
								char *ptr,ch;
								struct delfile_packet del;

								// Isolate name
								ptr=FilePart(data->buffer);
								strcpy(data->name,ptr);
								if (ptr)
								{
									ch=*ptr;
									*ptr=0;
								}

								// Fill out packet
								del.path=data->buffer;
								del.name=data->name;

								// Delete from listers
								(data->callback)(EXTCMD_DEL_FILE,data->function_handle,&del);

								// Fix name
								if (ptr) *ptr=ch;

								// Not doing icons?
								if (!icon) break;

								// Add .info
								if (loop==0) strcat(data->buffer,".info");
							}
							else break;
						}
					}

					// Show changes
					(data->callback)(EXTCMD_DO_CHANGES,data->function_handle,0);
				}
			}

			// Reply to message
			ReplyMsg((struct Message *)amsg);
		}

		// Wait for event
		Wait(	1<<ipc->command_port->mp_SigBit|
				1<<data->notify_port->mp_SigBit|
				1<<data->timer->port->mp_SigBit|
				1<<data->app_port->mp_SigBit|
				((data->window)?1<<data->window->UserPort->mp_SigBit:0));
	}

	// Free handle
	(data->callback)(EXTCMD_FREE_POINTER,0,&pkt);

	// Cleanup
	recyclebin_cleanup(data,1);

	// Decrement open count so we can be flushed again
	--data->module->lib_OpenCnt;
}


// Startup
ULONG __asm __saveds recyclebin_startup(
	register __a0 IPCData *ipc,
	register __a1 recyclebin_data *data)
{
	struct Library *DOpusBase;

	// Store IPC
	data->ipc=ipc;

	// Get library
	DOpusBase=data->library;

	// Initialise data
	data->icon_x=NO_ICON_POSITION;
	data->icon_y=NO_ICON_POSITION;

	// Initialise Semaphore
	data->sem.sem.ss_Link.ln_Name=NAME_RECYCLEBIN;
	data->sem.ipc=ipc;
	AddSemaphore((struct SignalSemaphore *)&data->sem);

	// Create message ports
	if (!(data->notify_port=CreateMsgPort()) ||
		!(data->reply_port=CreateMsgPort()) |\
		!(data->app_port=CreateMsgPort()))
		return 0;

	// Create timer
	if (!(data->timer=AllocTimer(UNIT_VBLANK,0)))
		return 0;

	// Add notify request
	if (!(data->notify_req=
		AddNotifyRequest(
			DN_OPUS_QUIT|DN_OPUS_HIDE|DN_OPUS_SHOW,
			0,
			data->notify_port))) return 0;

	// Bump library open count so we don't get flushed
	++data->module->lib_OpenCnt;

	return 1;
}


// Cleanup
void recyclebin_cleanup(recyclebin_data *data,short release)
{
	if (data)
	{
		struct Message *msg;

		// Remove AppIcon
		if (data->appicon) RemoveAppIcon(data->appicon);

		// Remove notify request
		RemoveNotifyRequest(data->notify_req);

		// Close window
		recyclebin_close_window(data);

		// Flush message ports
		if (data->notify_port)
		{
			while (msg=GetMsg(data->notify_port))
				ReplyFreeMsg(msg);
		}
		if (data->app_port)
		{
			while (msg=GetMsg(data->app_port))
				ReplyFreeMsg(msg);
		}
		if (data->reply_port)
		{
			while (msg=GetMsg(data->reply_port))
				ReplyFreeMsg(msg);
		}

		// Delete message ports
		DeleteMsgPort(data->notify_port);
		DeleteMsgPort(data->app_port);
		DeleteMsgPort(data->reply_port);

		// Free timer
		FreeTimer(data->timer);

		// Remove Semaphore
		Forbid();
		if (release) ReleaseSemaphore((struct SignalSemaphore *)&data->sem);
		RemSemaphore((struct SignalSemaphore *)&data->sem);

		// Free data
		IPC_Free(data->ipc);
		FreeVec(data);
	}
}


// Install the recycle bin
void recycle_bin_install(RecyclePacket *packet,recyclebin_data *data)
{
	struct TagItem tags[3];
	struct DiskObject *trash_icon;

	// Get trashcan icon
	if (!(trash_icon=GetDefDiskObject(WBGARBAGE)) &&
		!(trash_icon=GetDefDiskObject(WBTOOL))) return;

	// AppIcon tags
	tags[0].ti_Tag=DAE_SnapShot;
	tags[0].ti_Data=1;
	tags[1].ti_Tag=DAE_Menu;
	tags[1].ti_Data=(ULONG)GetString(locale,MSG_EMPTY_TRASH);
	tags[2].ti_Tag=TAG_END;

	// Get environment variable
	if (GetVar(ENV_RECYCLEBIN,data->buffer,sizeof(data->buffer),GVF_GLOBAL_ONLY)>0)
	{
		char *ptr;

		// Get buffer pointer
		ptr=data->buffer;

		// Get position
		read_parse_set(&ptr,&data->icon_x);
		read_parse_set(&ptr,&data->icon_y);
	}

	// Set icon position
	trash_icon->do_CurrentX=data->icon_x;
	trash_icon->do_CurrentY=data->icon_y;

	// Set flag for transparent icon
	SetIconFlags(trash_icon,ICONF_TRANSPARENT);

	// Add AppIcon
	data->appicon=AddAppIconA(0,0,NAME_RECYCLEBIN,data->app_port,0,trash_icon,tags);

	// Free icon
	FreeDiskObject(trash_icon);
}


// Parse number out of string, leave pointer at one character after end of number
void read_parse_set(char **ptr,long *val)
{
	// Digit?
	if (isdigit(*(*ptr)))
	{
		*val=atoi(*ptr);
		while (*(*ptr) && isdigit(*(*ptr))) ++*ptr;
		++*ptr;
	}
}


// Open config window
void recyclebin_open_window(recyclebin_data *data)
{
	struct Screen *screen;

	// Is window already open?
	if (data->window)
	{
		// Bring it to the front
		WindowToFront(data->window);
		ActivateWindow(data->window);
		return;
	}

	// Try and find Opus screen, if not get default
	if (!(screen=LockPubScreen("DOPUS.1")))
		screen=LockPubScreen(0);

	// Fill out new window structure
	data->newwin.parent=screen;
	data->newwin.dims=&recyclebin_window;
	data->newwin.title=GetString(locale,MSG_RECYCLEBIN_TITLE);
	data->newwin.locale=locale;
	data->newwin.flags=WINDOW_SCREEN_PARENT|WINDOW_VISITOR|WINDOW_AUTO_KEYS|WINDOW_REQ_FILL;

	// Open window, add objects
	if (!(data->window=OpenConfigWindow(&data->newwin)) ||
		!(data->objlist=AddObjectList(data->window,recyclebin_objects)))
	{
		// Failed
		CloseConfigWindow(data->window);
		data->window=0;

		// Flash error
		DisplayBeep(screen);
	}

	// Success
	else
	{
	}

	// Unlock screen
	if (screen) UnlockPubScreen(0,screen);
}


// Close config window
void recyclebin_close_window(recyclebin_data *data)
{
	// Is window open?
	if (data->window)
	{
		// Close window
		CloseConfigWindow(data->window);
		data->window=0;
	}
}


// Do delete
long recyclebin_delete(recyclebin_data *data,char *name)
{
	char *ptr;
	short len,nlen=-1;
	long ret;

	// Valid name?
	if (!(ptr=name) || !*ptr) return 0;

	// Strip trailing newline
	if (ptr[(len=strlen(ptr)-1)]=='\n')
	{
		nlen=len;
		ptr[len]=0;
	}

	// Icon?
	if ((len=strlen(ptr))>5 && stricmp(ptr+len-5,".info")==0)
	{
		// Clear .info
		ptr[len-5]=0;

		// Delete as an icon
		ret=DeleteDiskObject(ptr);

		// Restore .info
		ptr[len-5]='.';
	}

	// Delete normal file
	else ret=DeleteFile(ptr);

	// Replace newline
	if (nlen>-1) ptr[nlen]='\n';

	// Did we fail?
	if (!ret)
	{
		// If object doesn't exist, it's already deleted
		if (IoErr()==ERROR_OBJECT_NOT_FOUND) ret=DOSTRUE;
	}
	return ret;
}
