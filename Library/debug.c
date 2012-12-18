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
#include "debug.h"

#undef DEBUG

#ifndef DEBUG
void __asm __saveds L_SetDebug(
	register __a0 char *operation,
	register __a1 char *string_data,
	register __d0 ULONG data,
	register __d1 ULONG flags){};
void __asm __saveds L_ClearDebug(void){};
void __asm __saveds L_ShowDebug(register __a0 char *name){};
void __asm __saveds L_ObtainSemaphore_Debug(register __a0 struct SignalSemaphore *sem,register __a1 char *name){};
void __asm __saveds L_ObtainSemaphoreShared_Debug(register __a0 struct SignalSemaphore *sem){};
ULONG __asm __saveds L_Wait_Debug(register __d0 ULONG bits){};
struct Message *__asm __saveds L_WaitPort_Debug(register __a0 struct MsgPort *port){};

#else

void __asm __saveds L_SetDebug(
	register __a0 char *operation,
	register __a1 char *string_data,
	register __d0 ULONG data,
	register __d1 ULONG flags)
{
	DebugPacket packet;

	// Fill out packet
	packet.task=FindTask(0);
	if (operation) stccpy(packet.operation,operation,39);
	else packet.operation[0]=0;
	if (string_data) stccpy(packet.string_data,string_data,127);
	else packet.string_data[0]=0;
	packet.data=data;
	packet.flags=flags;

	// Send message
	L_IPC_Command(debug_ipc,IPC_SETDEBUG,0,&packet,0,(struct MsgPort *)-2);
}

void __asm __saveds L_ClearDebug(void)
{
	DebugPacket packet;

	// Fill out packet
	packet.task=FindTask(0);

	// Send message
	L_IPC_Command(debug_ipc,IPC_CLEARDEBUG,0,&packet,0,(struct MsgPort *)-2);
}

void __asm __saveds L_ShowDebug(register __a0 char *name)
{
	DebugPacket packet;

	// Fill out packet
	stccpy(packet.operation,name,39);

	// Send message
	L_IPC_Command(debug_ipc,IPC_SHOWDEBUG,0,&packet,0,(struct MsgPort *)-2);
}


/*******************************************/

void __asm __saveds L_ObtainSemaphore_Debug(register __a0 struct SignalSemaphore *sem,register __a1 char *name)
{
	L_SetDebug("ObtainSemaphore",name,(ULONG)sem,(ULONG)sem->ss_Link.ln_Name);
	L_GetSemaphore(sem,TRUE,name);
	L_ClearDebug();
}

void __asm __saveds L_ObtainSemaphoreShared_Debug(register __a0 struct SignalSemaphore *sem)
{
	L_SetDebug("ObtainSemaphoreShared",0,(ULONG)sem,(ULONG)sem->ss_Link.ln_Name);
	L_GetSemaphore(sem,FALSE,0);
	L_ClearDebug();
}

ULONG __asm __saveds L_Wait_Debug(register __d0 ULONG bits)
{
	L_SetDebug("Wait",0,bits,0);
	bits=Wait(bits);
	L_ClearDebug();
	return bits;
}

struct Message *__asm __saveds L_WaitPort_Debug(register __a0 struct MsgPort *port)
{
	struct Message *msg;

	L_SetDebug("WaitPort",0,(ULONG)port,(ULONG)((struct Task *)port->mp_SigTask)->tc_Node.ln_Name);
	msg=WaitPort(port);
	L_ClearDebug();
	return msg;
}


/*******************************************/

#define DOpusBase		(data->wb_data.dopus_base)

void __saveds debug_proc(void)
{
	IPCData *ipc;
	struct LibData *data;
	struct List debug_list;
	IPCMessage *quit=0;
	DebugNode *node;

	// Do startup
	if (!(ipc=L_IPC_ProcStartup((ULONG *)&data,0))) return;

	// Initialise list
	NewList(&debug_list);

	// Event loop
	FOREVER
	{
		IPCMessage *msg;

		// IPC messages?
		while (msg=(IPCMessage *)GetMsg(ipc->command_port))
		{
			// Quit?
			if (msg->command==IPC_QUIT)
			{
				quit=msg;
				msg=0;
			}

			// Set debug
			else if (msg->command==IPC_SETDEBUG)
			{
				DebugPacket *packet=(DebugPacket *)msg->data;
				BOOL new=0;

				// Look for task in list
				for (node=(DebugNode *)debug_list.lh_Head;
					node->node.ln_Succ;
					node=(DebugNode *)node->node.ln_Succ)
				{
					if (node->task==packet->task) break;
				}

				// Not found?
				if (!node || !node->node.ln_Succ)
				{
					// Allocate a new node
					node=AllocVec(sizeof(DebugNode),MEMF_CLEAR);
					new=1;
				}

				// Valid node?
				if (node)
				{
					// Copy packet data
					node->task=packet->task;
					stccpy(node->task_name,packet->task->tc_Node.ln_Name,39);
					stccpy(node->operation,packet->operation,39);
					node->data=packet->data;
					node->flags=packet->flags;
					stccpy(node->string_data,packet->string_data,127);

					// Add to list if new
					if (new) AddTail(&debug_list,(struct Node *)node);
				}
			}

			// Show debug
			else if (msg->command==IPC_SHOWDEBUG)
			{
				DebugPacket *packet=(DebugPacket *)msg->data;
				BOOL ok=0;

				// Go through debug nodes
				for (node=(DebugNode *)debug_list.lh_Head;
					node->node.ln_Succ;
					node=(DebugNode *)node->node.ln_Succ)
				{
					// Match name
					if (strcmp(node->task_name,packet->operation)==0)
					{
						// Show information
						KPrintF("     Task : %s (%lx)\n",node->task_name,node->task);
						KPrintF("Operation : %s\n",node->operation);
						KPrintF("     Data : %lx %s\n",node->data,node->flags);
						KPrintF("          : %s\n\n",node->string_data);
						ok=1;
					}
				}

				// Not found?
				if (!ok) KPrintF("Nothing found for %s\n",packet->operation);
			}

			// Clear debug
			else if (msg->command==IPC_CLEARDEBUG)
			{
				DebugPacket *packet=(DebugPacket *)msg->data;

				// Go through debug nodes
				for (node=(DebugNode *)debug_list.lh_Head;
					node->node.ln_Succ;
					node=(DebugNode *)node->node.ln_Succ)
				{
					// Match task
					if (node->task==packet->task)
					{
						// Remove and free
						Remove((struct Node *)node);
						FreeVec(node);
						break;
					}
				}
			}

			// Reply to the message
			IPC_Reply(msg);
		}

		// Quit?
		if (quit) break;

		// Wait for message
		Wait(1<<ipc->command_port->mp_SigBit);
	}

	// Reply the quit message
	IPC_Reply(quit);

	// Exit
	IPC_Free(ipc);
}

#endif
