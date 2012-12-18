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

char *version="$VER: register.module 68.0 (3.10.98)";

BOOL check_rego(rego_data *data,IPCData *ipc);
long find_position(char *name);
BOOL serial_bad(long number);
Att_List *build_text_display(ObjectList *,char *);

unsigned long
	matchword=MAKE_ID('J','J','M','P'),
	matchword2=22091973;
unsigned long global_checksum=0xa568c1cc;
unsigned long run_count=0;
serial_data serial={0};
rego_data rego={0};
unsigned long matchword3=~22091973,matchword4=~22091973;

int __asm __saveds L_Module_Entry(
	register __a0 struct List *files,
	register __a1 struct Screen *callback1,
	register __a2 IPCData *callback2,
	register __a3 IPCData *main_ipc,
	register __d0 ULONG mod_id,
	register __d1 ULONG mod_data)
{
	NewConfigWindow newwin={(void *)1};
	struct Window *window;
	ObjectList *objlist;
	unsigned char *ptr;
	unsigned long checksum=0,count,position;
	BPTR file;
	rego_data test={0};
	struct InfoData __aligned info;
#ifdef SOLD_VERSION
	TimerHandle *timer=0;
	Att_List *list;
#endif

	// Call back to main program
	if (!(((BOOL __asm (*)
		(register __a0 struct List *,
		register __a1 rego_data *,
		register __a2 rego_data *,
		register __a3 void **,
		register __d0 ULONG))callback2)(files,&test,&rego,&newwin.parent,global_checksum)))
		return 0;

#ifndef SOLD_VERSION
	// Serial number valid?
	if (SerialValid(&serial) && check_rego(&test,main_ipc))
	{
		// Pirate version?
		if (serial_bad(~serial.serial_number))
		{
			test.pirate=1;
			test.pirate_count=run_count+1;
		}

		// Clear pirate flag
		else test.pirate=0;

		// Copy registration
		*((rego_data *)mod_id)=test;
		*((ULONG *)mod_data)|=(1<<28);

		// Update run count?
		if (test.pirate)
		{
			// Find position
			if (!(position=find_position((char *)files)))
				return 0;

			// Reopen file
			if (!(file=Open((char *)files,MODE_READWRITE)))
				return 0;

			// Find position
			Seek(file,position+sizeof(long)*2,OFFSET_BEGINNING);

			// Write run count
			++run_count;
			if ((Write(file,(char *)&run_count,sizeof(run_count)))!=sizeof(run_count))
			{
				Close(file);
				return 0;
			}

			// Close file
			Close(file);
		}

		return 1;
	}
#endif

	// Fill out new window
	newwin.dims=&serial_window;
#ifdef SOLD_VERSION
	newwin.title=GetString(locale,MSG_TITLE);
#else
	newwin.title=GetString(locale,MSG_ENTER_REGISTRATION);
#endif
	newwin.locale=locale;
	newwin.port=0;
	newwin.flags=WINDOW_VISITOR|WINDOW_NO_CLOSE|WINDOW_REQ_FILL|WINDOW_AUTO_KEYS;
	newwin.font=0;

#ifdef SOLD_VERSION
	// Initialise timer
	if (!(timer=AllocTimer(UNIT_VBLANK,0)))
		return 0;
#endif

	// Open window
	if (!(window=OpenConfigWindow(&newwin)) ||
		!(objlist=AddObjectList(window,serial_objects)))
	{
		CloseConfigWindow(window);
		return 0;
	}

	// Set ok flag
	*((ULONG *)mod_data)|=(1<<28);

#ifndef SOLD_VERSION

	// Activate text field
	ActivateStrGad(GADGET(GetObject(objlist,GAD_SERIAL_SERIAL)),window);

#else

	// Display text
	list=build_text_display(objlist,message0);

	// Start timer
	StartTimer(timer,DELAY,0);

#endif

	// Event loop
	FOREVER
	{
		struct IntuiMessage *msg;
		BOOL break_flag=0;

#ifdef SOLD_VERSION
		// Timer returned?
		if (CheckTimer(timer))
		{
			// Exit
			break_flag=1;
		}
#endif

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
					// Cancel
					case GAD_SERIAL_CANCEL:
						CloseConfigWindow(window);
						return 0;

					// Run without registering
					case GAD_SERIAL_RUN:

						// Make window busy and delay
						SetWindowBusy(window);

						// Call back to main program
						((void __asm (*)(register __a0 struct Window *window))callback1)(window);

						// Check registration
						CloseConfigWindow(window);
						return 1;

					// Okay
					case GAD_SERIAL_OKAY:
						break_flag=1;
						break;

					// Another gadget
					default:
						// Activate next gadget
						if (gadget->GadgetID<GAD_SERIAL_ADDRESS3)
							ActivateStrGad(GADGET(GetObject(objlist,gadget->GadgetID+1)),window);
						break;
				}
			}
		}

		// Want to break?
		if (break_flag)
		{
#ifndef SOLD_VERSION
			char buf[24];

			// Clear rego
			memset((char *)&rego,0,sizeof(rego_data));

			// Get data
			strcpy(rego.serial_number,(char *)GetGadgetValue(objlist,GAD_SERIAL_SERIAL));
			strcpy(rego.name,(char *)GetGadgetValue(objlist,GAD_SERIAL_NAME));
			strcpy(rego.company,(char *)GetGadgetValue(objlist,GAD_SERIAL_COMPANY));
			strcpy(rego.address1,(char *)GetGadgetValue(objlist,GAD_SERIAL_ADDRESS1));
			strcpy(rego.address2,(char *)GetGadgetValue(objlist,GAD_SERIAL_ADDRESS2));
			strcpy(rego.address3,(char *)GetGadgetValue(objlist,GAD_SERIAL_ADDRESS3));

			// Fill out serial number data
			strcpy(buf,rego.serial_number);
			buf[4]=0;
			serial.random_key=atoi(buf);

			CopyMem(rego.serial_number+4,serial.serial_check_1,5);
			serial.serial_check_1[5]=0;

			CopyMem(rego.serial_number+9,serial.serial_check_2,4);
			serial.serial_check_2[4]=0;

			serial.serial_number=atoi(rego.serial_number+13);
			serial.serial_number=~serial.serial_number;

			// Check if serial number is valid
			if (!(SerialValid(&serial)) || strlen(rego.serial_number)!=19)
			{
				DisplayBeep(0);
				ActivateStrGad(GADGET(GetObject(objlist,GAD_SERIAL_SERIAL)),window);
				continue;
			}

			// Name must be filled in
			if (strlen(rego.name)<4)
			{
				DisplayBeep(0);
				ActivateStrGad(GADGET(GetObject(objlist,GAD_SERIAL_NAME)),window);
				continue;
			}
#endif
			break;
		}

#ifdef SOLD_VERSION
		Wait(1<<window->UserPort->mp_SigBit|1<<timer->port->mp_SigBit);
#else
		Wait(1<<window->UserPort->mp_SigBit);
#endif
	}

	// Close window
	CloseConfigWindow(window);

#ifdef SOLD_VERSION
	// Free list and timer
	Att_RemList(list,0);
	FreeTimer(timer);

	// Copy rego data across
	test=rego;
	test.pirate=0;
	strcpy(test.serial_number,"0587EHASU4723440000");
	*((rego_data *)mod_id)=test;
#endif

#ifndef SOLD_VERSION
	// Must have valid data now we're here; get dates
	DateStamp(&rego.install_date);
	{
		BPTR lock;
		struct DeviceList *dl;

		// Get root datestamp
		if (lock=Lock((char *)files,ACCESS_READ))
		{
			Info(lock,&info);
			dl=(struct DeviceList *)BADDR(info.id_VolumeNode);
			rego.harddrive_date=dl->dl_VolumeDate;
			UnLock(lock);
		}
	}

	// Copy rego data across
	test=rego;
	test.pirate=0;
	*((rego_data *)mod_id)=test;

	// Checksum and encrypt registration info
	ptr=(unsigned char *)&rego;
	for (count=0;count<sizeof(rego_data)-sizeof(long);count++)
	{
		// Increment checksum, xor byte
		checksum+=*ptr;
		*ptr=~*ptr;
		++ptr;
	}

	// Store checksum
	rego.checksum=~checksum;

	// Get position
	if (!(position=find_position((char *)files)))
		return 0;

	// Reopen file
	if (!(file=Open((char *)files,MODE_READWRITE)))
		return 0;

	// Find position
	Seek(file,position+sizeof(long)*3,OFFSET_BEGINNING);

	// Write serial and registration data
	if ((Write(file,(char *)&serial,sizeof(serial_data))!=sizeof(serial_data)) ||
		(Write(file,(char *)&rego,sizeof(rego_data)))!=sizeof(rego_data))
	{
		Close(file);
		return 0;
	}

	// Close file
	Close(file);
#endif

	// Check registration
	check_rego(&test,main_ipc);

	// Success
	return 1;
}

BOOL check_rego(rego_data *data,IPCData *ipc)
{
	unsigned char *ptr;
	unsigned long checksum=0,count;
	struct Task *task;

	// Decrypt and checksum registration info
	ptr=(unsigned char *)data;
	for (count=0;count<sizeof(rego)-sizeof(long);count++)
	{
		// Xor byte, increment checksum
		*ptr=~*ptr;
		checksum+=*ptr;
		++ptr;
	}

	if (!ipc->command_port)
	{
		// Fix IPC
		(task=FindTask(0))->tc_UserData=ipc;
		ipc->proc=(struct Process *)task;
		ipc->list=0;
	}

	// Does checksum match?
	return (BOOL)
		((ipc->command_port || (ipc->command_port=CreateMsgPort())) &&
			checksum==~data->checksum);
}


long find_position(char *name)
{
	APTR file;
	long val=0,position=0;

	// Open program file
	if (!(file=OpenBuf(name,MODE_OLDFILE,8192)))
		return 0;

	// Search for match word
	while (ReadBuf(file,(char *)&val,sizeof(long))==sizeof(long))
	{
		// Match?
		if (val==matchword)
		{
			ReadBuf(file,(char *)&val,sizeof(long));
			if (val==matchword2) break;
		}

		// Increment position
		position+=sizeof(long);
	}

	// Close file
	CloseBuf(file);

	// Didn't match?
	if (val!=matchword2) return 0;
	return (long)(position+sizeof(long));
}

long bad_array[16]={
	421065,
	440036,
	0};

BOOL serial_bad(long number)
{
	short a;

	for (a=0;bad_array[a];a++)
	{
		if (number==bad_array[a]) return 1;
	}
	return 0;
}


#ifdef SOLD_VERSION
Att_List *build_text_display(ObjectList *objlist,char *text)
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
				objlist->window->RPort,
				textpos,
				want_len,
				&extent,
				0,1,
				width,objlist->window->RPort->TxHeight);

			// Go from here to end of current word
			want_len=max_len;
			while ( textpos[want_len] &&
					textpos[want_len]!='\n' && 
					textpos[want_len]!=' ') ++want_len;

			// Loop until successful
			do
			{
				// Get text size
				TextExtent(objlist->window->RPort,textpos,want_len,&extent);

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
#endif
