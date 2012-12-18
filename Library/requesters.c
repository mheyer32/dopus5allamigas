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

#include "dopuslib.h"

typedef struct
{
	ULONG				command;
	struct Window		*window;
	APTR				data;
	IPCData				*ipc;
	ULONG				a4;
	struct MyLibrary	*libbase;
} ReqStartup;

struct RequestData
{
	struct DOpusSimpleRequest request;
	char *gadgets[11];
	long return_values[10];
};

void __saveds requester_proc(void);

#define REQCMD_END	0x8752

// Open an asynchronous requester
long __asm __saveds L_AsyncRequest(
	register __a0 IPCData *my_ipc,
	register __d0 long type,
	register __a1 struct Window *window,
	register __a2 REF_CALLBACK(callback),
	register __a3 APTR data,
	register __d1 struct TagItem *tags,
	register __a6 struct MyLibrary *libbase)
{
	ReqStartup *startup;
	IPCData *ipc;
	long result=0;

	// Allocate startup
	if (!(startup=AllocVec(sizeof(ReqStartup),MEMF_CLEAR)))
		return 0;

	// Fill out startup
	startup->command=type;
	startup->window=window;
	startup->data=tags;
	startup->ipc=my_ipc;
	startup->a4=getreg(REG_A4);
	startup->libbase=libbase;

	// Start process
	if (!(L_IPC_Launch(
		0,
		&ipc,
		"dopus_requester_proc",
		(ULONG)requester_proc,
		STACK_DEFAULT,
		(ULONG)startup,(struct Library *)DOSBase,libbase)))
	{
		// Failed to launch
		FreeVec(startup);
		return 0;
	}

	// Event loop
	FOREVER
	{
		IPCMessage *msg;
		short quit=0;

		// Window open?
		if (window && callback)
		{
			struct IntuiMessage *imsg;

			// Check for refresh
			while (imsg=L_CheckRefreshMsg(window,IDCMP_REFRESHWINDOW|IDCMP_CHANGEWINDOW))
			{
				// Handle refresh
				callback(imsg->Class,window,data);

				// Reply to message
				ReplyMsg((struct Message *)imsg);
			}
		}

		// IPC messages?
		while (msg=(IPCMessage *)GetMsg(my_ipc->command_port))
		{
			// Requester message?
			if (msg->command==REQCMD_END)
			{
				// Get result
				result=msg->flags;
				quit=1;
			}

			// Abort?
			else
			if (msg->command==IPC_ABORT || msg->command==IPC_QUIT)
			{
				// Send command to requester process
				L_IPC_Command(ipc,msg->command,msg->flags,msg->data,0,0);
			}

			// Reply to message
			L_IPC_Reply(msg);
		}

		// Check quit flag
		if (quit) break;

		// Wait for event
		Wait(1<<my_ipc->command_port->mp_SigBit|
			((window)?1<<window->UserPort->mp_SigBit:0));
	}

	// Free startup data
	FreeVec(startup);
	return result;
}


// Check for refresh message
struct IntuiMessage *__asm __saveds L_CheckRefreshMsg(
	register __a0 struct Window *window,
	register __d0 ULONG mask)
{
	struct IntuiMessage *msg;

	// Valid window?
	if (!window) return 0;

	// Go through messages
	for (msg=(struct IntuiMessage *)window->UserPort->mp_MsgList.lh_Head;
		msg->ExecMessage.mn_Node.ln_Succ;
		msg=(struct IntuiMessage *)msg->ExecMessage.mn_Node.ln_Succ)
	{
		// Refresh?
		if (msg->Class&mask)
		{
			// Remove it
			Forbid();
			Remove((struct Node *)msg);
			Permit();

			// Return the message
			return msg;
		}
	}

	return 0;
}


// Requester process
void __saveds requester_proc(void)
{
	IPCData *ipc;
	ReqStartup *startup=0;
	struct TagItem *tags;
	struct LibData *libdata;
	long result=0;

	// Do startup
	if (!(ipc=L_IPC_ProcStartup((ULONG *)&startup,0)))
		return;

	// Restore A4
	putreg(REG_A4,startup->a4);

	// Get library data pointer
	libdata=(struct LibData *)startup->libbase->ml_UserData;
#define DOpusBase	(libdata->dopus_base)

	// Get tags pointer
	tags=(struct TagItem *)startup->data;

	// Switch on type
	switch (startup->command)
	{
		// File?
		case REQTYPE_FILE:
			{
				APTR req;

				// Get requester pointer
				if (req=(APTR)GetTagData(AR_Requester,0,tags))
				{
					// Show requester
					result=AslRequest(req,tags);
				}
			}
			break;


		// Simple request
		case REQTYPE_SIMPLE:
			{
				struct RequestData *data;
				struct TagItem *tag,*tstate;
				APTR parent;
				short button=0;

				// Allocate data
				if (!(data=AllocVec(sizeof(*data),MEMF_CLEAR)))
					break;

				// Get flags
				data->request.flags=GetTagData(AR_Flags,0,tags);

				// Get parent
				parent=(APTR)GetTagData(AR_Window,0,tags);

				// Screen parent?
				if ((tag=FindTagItem(AR_Screen,tags)) && !parent)
				{
					// Use screen
					parent=(APTR)tag->ti_Data;
					data->request.flags|=SRF_SCREEN_PARENT;
				}

				// Get title
				data->request.title=(char *)
					GetTagData(AR_Title,(ULONG)GetString(&libdata->locale,MSG_DIRECTORY_OPUS_REQUEST),tags);

				// Get message
				data->request.message=(char *)GetTagData(AR_Message,0,tags);

				// Get gadget pointers
				data->request.gadgets=data->gadgets;
				data->request.return_values=(int *)data->return_values;

				// Get buffer
				data->request.string_buffer=(char *)GetTagData(AR_Buffer,0,tags);
				data->request.string_buffer_2=(char *)GetTagData(AR_Buffer2,0,tags);
				data->request.string_len=GetTagData(AR_BufLen,0,tags);
				data->request.string_len_2=GetTagData(AR_BufLen2,0,tags);

				// Get history
				data->request.history=(Att_List *)GetTagData(AR_History,0,tags);

				// Send IPC
				data->request.ipc=ipc;
				data->request.flags|=SRF_IPC;

				// Get checkmark
				data->request.check_text=(char *)GetTagData(AR_CheckMark,0,tags);
				data->request.check_ptr=(short *)GetTagData(AR_CheckPtr,0,tags);

				// Go through tags
				tstate=tags;
				while (tag=NextTagItem(&tstate))
				{
					// Look at tag
					switch (tag->ti_Tag)
					{
						// Button?
						case AR_Button:

							// Check button number for overflow
							if (button==10) break;

							// Store gadget in array
							data->gadgets[button]=(char *)tag->ti_Data;

							// Automatic return code
							data->return_values[button]=button+1;

							// Increment button number
							++button;
							break;


						// Button return code
						case AR_ButtonCode:

							// Check button number for overflow
							if (button==0) break;

							// Save return code
							data->return_values[button-1]=tag->ti_Data;
							break;
					}
				}

				// Did we get more than one button?
				if (button>1)
				{
					// Make the last gadget a 'cancel' gadget
					data->return_values[button-1]=0;
				}

				// Zero the last gadget pointer
				data->gadgets[button]=0;

				// See if file requester supplied
				if (data->request.filereq=(APTR)GetTagData(AR_Requester,0,tags))
					data->request.flags|=SRF_FILEREQ;

				// Do the request
				result=DoSimpleRequest(parent,&data->request);

				// Free data
				FreeVec(data);
			}
			break;
	}

	// Forbid so we don't end too soon
	Forbid();

	// Send result back
	IPC_Command(startup->ipc,REQCMD_END,result,0,0,0);

	// Free and exit
	IPC_Free(ipc);
#undef DOpusBase
}
