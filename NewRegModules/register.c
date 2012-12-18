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

#include "register.h"

#define DELAY	10

/*********************************************************************************
                           UPDATE CHECKSUM!!!!!!!!
 *********************************************************************************/

static char *version="$VER: register.module 55.99 (11.05.99)";

Att_List *build_text_display(struct Window *,ObjectList *,char *);

static unsigned long
	matchword=MAKE_ID('J','J','M','P'),
	matchword2=22091973;
static unsigned long global_checksum=0xe34692b4; /*0xe3476d70;*/
static unsigned long run_count=0;
static serial_data serial={0};
static rego_data rego={0};
static unsigned long matchword3=~22091973,matchword4=~22091973;

int __asm __saveds L_Module_Entry(
	register __a0 struct List *files,
	register __a1 struct Screen *callback1,
	register __a2 IPCData *callback2,
	register __a3 IPCData *main_ipc,
	register __d0 ULONG mod_id,
	register __d1 ULONG mod_data)
{
	NewConfigWindow newwin;
	struct Window *window;
	ObjectList *objlist;
	Att_List *list;
	TimerHandle *timer;
	short count=0;
	struct Task *task;
	rego_data test={0};

	// Call back to main program
	((void __asm (*)
		(register __a0 struct List *,
		register __a1 rego_data *,
		register __a2 rego_data *,
		register __a3 void **,
		register __d0 ULONG))callback2)(files,&test,&rego,&newwin.parent,global_checksum);

	// Won't work with DOpus library > 55
	if (DOpusBase->lib_Version>55)
		return 0;

	// Fix IPC
	main_ipc->proc=(struct Process *)FindTask(0);
	main_ipc->proc->pr_Task.tc_UserData=main_ipc;
	main_ipc->list=0;
	if (!main_ipc->command_port)
		main_ipc->command_port=CreateMsgPort();

	// Fill out new window
	newwin.parent=0;
	newwin.dims=&serial_window;
	newwin.title=GetString(locale,MSG_TITLE);
	newwin.locale=locale;
	newwin.port=0;
	newwin.flags=WINDOW_VISITOR|WINDOW_NO_CLOSE|WINDOW_REQ_FILL|WINDOW_AUTO_KEYS;
	newwin.font=0;

	// Initialise timer
	if (!(timer=AllocTimer(UNIT_VBLANK,0)))
		return 0;

	// Open window
	if (!(window=OpenConfigWindow(&newwin)) ||
		!(objlist=AddObjectList(window,serial_objects)))
	{
		CloseConfigWindow(window);
		FreeTimer(timer);
		return 0;
	}

	// Set ok flag
	*((ULONG *)mod_data)|=(1<<28);

	// Display text
	list=build_text_display(window,objlist,message0);

	// Start timer
	StartTimer(timer,DELAY,0);

	// Event loop
	FOREVER
	{
		struct IntuiMessage *msg;
		BOOL break_flag=0;

		// Timer returned?
		if (CheckTimer(timer))
		{
			// Exit
			break_flag=1;
		}

		// Any Intuition messages?
		while (msg=GetWindowMsg(window->UserPort))
		{
			struct IntuiMessage copy_msg;

			// Copy message and reply
			copy_msg=*msg;
			ReplyWindowMsg(msg);

			// Gadget?
			if (copy_msg.Class==IDCMP_GADGETUP)
			{
				struct Gadget *gadget;

				// Get gadget
				gadget=(struct Gadget *)copy_msg.IAddress;

				// Look at gadget ID
				switch (gadget->GadgetID)
				{
					// Ok
					case GAD_SERIAL_OKAY:

						break_flag=1;
						break;
				}
			}
		}

		if (break_flag) break;

		Wait(1<<window->UserPort->mp_SigBit|1<<timer->port->mp_SigBit);
	}

	// Close window
	CloseConfigWindow(window);

	// Free list and timer
	Att_RemList(list,0);
	FreeTimer(timer);

	// Success
	return 1;
}


Att_List *build_text_display(struct Window *window,ObjectList *objlist,char *text)
{
	Att_List *list;
	struct TextExtent extent;
	short want_len,max_len,textlen=0,width;
	char *textpos=0;
	struct Rectangle rect;
	char old;

	// Allocate a new list
	list=Att_NewList(0);

	// Get list object size
	GetObjectRect(objlist,GAD_TEXT_DISPLAY,&rect);
	width=RECTWIDTH(&rect)-28;

	// Go through text
	FOREVER
	{
		// No current line?
		if (!textpos) textpos=text;

		// Move on from current line
		else
		{
			// Were we on a newline?
			if (textlen==0) ++textpos;

			// No
			else
			{
				// Bump pointer
				textpos+=textlen;

				// If this leaves us on a newline or space, skip over it
				if (*textpos=='\n' || *textpos=='\t') ++textpos;
			}
		}

		// End of text?
		if (!*textpos) break;

		// If we're on a space, skip over it
		if (*textpos==' ') ++textpos;

		// Calculate desired length of the line
		for (want_len=0;textpos[want_len] && textpos[want_len]!='\n';++want_len);

		// Blank line?
		if (want_len==0)
		{
			textlen=0;
		}

		// Not blank
		else
		{
			// Get maximum length that will actually fit
			max_len=TextFit(
				window->RPort,
				textpos,
				want_len,
				&extent,
				0,1,
				width,window->RPort->TxHeight);

			// Go from here to end of current word
			want_len=max_len;
			while ( textpos[want_len] &&
					textpos[want_len]!='\n' && 
					textpos[want_len]!=' ') ++want_len;

			// Loop until successful
			do
			{
				// Get text size
				TextExtent(window->RPort,textpos,want_len,&extent);

				// Will it fit?
				if (extent.te_Width<=width)
				{
					// Save size
					textlen=want_len;
					break;
				}

				// Come backwards to word break
				for (--want_len;want_len>0 && textpos[want_len]!=' ';--want_len);

				// Didn't find one?
				if (want_len<1)
				{
					// Get maximum length
					want_len=max_len;
				}
			} while(1);
		}

		// Null out break temporarily
		old=textpos[textlen];
		textpos[textlen]=0;

		// Add node
		Att_NewNode(list,textpos,0,0);

		// Restore character
		textpos[textlen]=old;
	}

	// Add list to display
	SetGadgetChoices(objlist,GAD_TEXT_DISPLAY,list);
	return list;
}
