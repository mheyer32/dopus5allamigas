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

#include "iconclock.h"

char *version="$VER: iconclock.module 55.2 (27.05.97)";

int __asm __saveds L_Module_Entry(
	register __a0 struct List *files,
	register __a1 struct Screen *screen,
	register __a2 IPCData *ipc,
	register __a3 IPCData *main_ipc,
	register __d0 ULONG mod_id,
	register __d1 EXT_FUNC(func_callback))
{
	iconclock_data *data;
	IPCData *clock_ipc=0;

	// Already running?
	if (FindSemaphore(NAME_ICONCLOCK)) return 1;

	// Allocate data
	if (data=AllocVec(sizeof(iconclock_data),MEMF_CLEAR))
	{
		// Store A4 and library bases
		data->a4=getreg(REG_A4);
		data->library=DOpusBase;
		data->module=(struct Library *)getreg(REG_A6);
		data->main_ipc=main_ipc;

		// Store initial screen
		data->screen=screen;
		data->pen=-1;

		// Launch process
		if (!(IPC_Launch(
			0,
			&clock_ipc,
			NAME_ICONCLOCK,
			(ULONG)icon_clock,
			4000,
			(ULONG)data,
			(struct Library *)DOSBase))) FreeVec(data);
	}

	// No process?
	if (!clock_ipc) return 0;

	return 1;
}


// Icon clock process
void __saveds icon_clock(void)
{
	IPCData *ipc;
	IPCMessage *msg;
	DOpusNotify *nmsg;
	struct AppMessage *amsg;
	struct Library *DOpusBase;
	iconclock_data *data;
	BOOL quit=0,visible=1;

	// Get dopus library
	if (!(DOpusBase=(struct Library *)FindName(&((struct ExecBase *)*((ULONG *)4))->LibList,"dopus5.library")))
		return;

	// Do startup
	ipc=IPC_ProcStartup((ULONG *)&data,iconclock_startup);

	// Fix A4
	putreg(REG_A4,data->a4);

	// Failed?
	if (!ipc)
	{
		iconclock_cleanup(data);
		return;
	}

	// Got a screen?
	if (data->screen)
	{
		struct Screen *scr=data->screen;

		// Initialise it
		data->screen=0;
		iconclock_init(data,scr);
	}

	// Event loop
	FOREVER
	{
		// Timer?
		if (CheckTimer(data->timer))
		{
			// Update the time if visible
			if (visible)
			{
				// Show time
				iconclock_show(data);
			}

			// Restart timer
			StartTimer(data->timer,0,900000);
		}

		// IPC messages?
		while (msg=(IPCMessage *)GetMsg(ipc->command_port))
		{
			// Reply to message
			IPC_Reply(msg);
		}

		// Notify messages?
		while (nmsg=(DOpusNotify *)GetMsg(data->notify_port))
		{
			// Quit?
			if (nmsg->dn_Type&DN_OPUS_QUIT) quit=1;

			// Hide?
			else
			if (nmsg->dn_Type&DN_OPUS_HIDE)
			{
				// Made invisible
				iconclock_init(data,0);
				visible=0;
			}

			// Show
			else
			if (nmsg->dn_Type&DN_OPUS_SHOW)
			{
				// Screen changed?
				if (data->screen!=((struct Window *)nmsg->dn_Data)->WScreen)
				{
					// Just made visible
					iconclock_init(data,((struct Window *)nmsg->dn_Data)->WScreen);
				}
				visible=1;
			}

			// Reply to the message
			ReplyFreeMsg(nmsg);
		}

		// Requester?
		if (data->about)
		{
			// Handle requester
			if (SysReqHandler(data->about,0,0)>=0)
			{
				// Close requester
				FreeSysRequest(data->about);
				data->about=0;
			}
		}

		// Check quit flag
		if (quit) break;

		// AppMessages?
		while (amsg=(struct AppMessage *)GetMsg(data->app_port))
		{
			// SnapShot?
			if (amsg->am_Type==MTYPE_APPSNAPSHOT)
			{
				struct AppSnapshotMsg *asm;

				// Get SnapShot message pointer
				asm=(struct AppSnapshotMsg *)amsg;

				// Menu operation?
				if (asm->flags&APPSNAPF_MENU)
				{
					// Help?
					if (asm->flags&APPSNAPF_HELP)
					{
						// Send help request
						if (data->main_ipc)
							IPC_Command(data->main_ipc,IPC_HELP,(1<<31),"Icon Clock",0,REPLY_NO_PORT);
					}

					// Colour?
					else
					if (asm->id==0)
					{
						struct Screen *screen;

						// Toggle colour state
						data->colour=1-data->colour;

						// Set menu state
						SetAppIconMenuState(data->appicon,0,data->colour);

						// Save screen
						screen=data->screen;

						// Close and re-open
						iconclock_init(data,0);
						iconclock_init(data,screen);
					}
				}

				// Close?
				else
				if (asm->flags&APPSNAPF_CLOSE) quit=1;

				// Info?
				else
				if (asm->flags&APPSNAPF_INFO)
				{
					// Show info
					iconclock_info(data);
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
					lsprintf(
						data->buffer,
						"%ld/%ld/%ld\n",
						data->icon_x,
						data->icon_y,
						data->colour);

					// Set environment variable
					SetEnv(ENV_ICONCLOCK,data->buffer,TRUE);
				}
			}

			// Double-click?
			else
			if (amsg->am_Type==MTYPE_APPICON &&
				amsg->am_NumArgs==0)
			{
				// Launch date prefs
				WB_Launch("sys:prefs/time",0,0);
			}

			// Reply to message
			ReplyMsg((struct Message *)amsg);
		}

		// Check quit flag
		if (quit) break;

		// Wait for event
		Wait(	1<<ipc->command_port->mp_SigBit|
				1<<data->notify_port->mp_SigBit|
				1<<data->timer->port->mp_SigBit|
				1<<data->app_port->mp_SigBit|
				((data->about)?(1<<data->about->UserPort->mp_SigBit):0));
	}

	// Decrement open count so we can be flushed again
	--data->module->lib_OpenCnt;

	// Cleanup
	iconclock_cleanup(data);
}


// Startup
ULONG __asm __saveds iconclock_startup(
	register __a0 IPCData *ipc,
	register __a1 iconclock_data *data)
{
	struct Library *DOpusBase;

	// Fix A4
	putreg(REG_A4,data->a4);

	// Store IPC
	data->ipc=ipc;

	// Get library
	DOpusBase=data->library;

	// Initialise data
	data->icon_x=NO_ICON_POSITION;
	data->icon_y=NO_ICON_POSITION;

	// Initialise Semaphore
	data->sem.sem.ss_Link.ln_Name=NAME_ICONCLOCK;
	data->sem.ipc=ipc;
	AddSemaphore((struct SignalSemaphore *)&data->sem);

	// Create message ports
	if (!(data->notify_port=CreateMsgPort()) ||
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

	// Get environment variable
	if (GetVar(ENV_ICONCLOCK,data->buffer,sizeof(data->buffer),GVF_GLOBAL_ONLY)>0)
	{
		char *ptr;

		// Get buffer pointer
		ptr=data->buffer;

		// Get position
		read_parse_set(&ptr,&data->icon_x);
		read_parse_set(&ptr,&data->icon_y);
		read_parse_set(&ptr,&data->colour);
	}

	// Bump library open count so we don't get flushed
	++data->module->lib_OpenCnt;

	// Start timer
	StartTimer(data->timer,0,900000);

	return 1;
}


// Cleanup
void iconclock_cleanup(iconclock_data *data)
{
	if (data)
	{
		struct Message *msg;

		// Free screen lock
		iconclock_init(data,0);

		// Remove notify request
		RemoveNotifyRequest(data->notify_req);

		// Close requester
		FreeSysRequest(data->about);
		data->about=0;

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

		// Delete message ports
		DeleteMsgPort(data->notify_port);
		DeleteMsgPort(data->app_port);

		// Free timer
		FreeTimer(data->timer);

		// Remove Semaphore
		RemSemaphore((struct SignalSemaphore *)&data->sem);

		// Free data
		IPC_Free(data->ipc);
		FreeVec(data);
	}
}


// Show current time
void iconclock_show(iconclock_data *data)
{
	struct DateStamp date;
	unsigned long hour,minute,second;
	short time[4],colon,x,y=2,a;
	long flags=CAIF_RENDER|CAIF_SELECT;

	// Open?
	if (!data->screen) return;

	// Get current time
	DateStamp(&date);

	// Get hours and minutes and seconds
	hour=DivideU(date.ds_Minute,60,&minute,UtilityBase);
	second=UDivMod32(date.ds_Tick,TICKS_PER_SECOND);

	// Get colon we need
	if ((second%2)==0) colon=0;
	else
	if (second<30) colon=1;
	else
	colon=2;

	// Get numerals we need for hour
	if (hour>9)
	{
		if (hour>19)
		{
			time[0]=2;
			time[1]=hour-20;
		}
		else
		{
			time[0]=1;
			time[1]=hour-10;
		}
	}
	else
	{
		time[0]=-1;
		time[1]=hour;
	}

	// Get numerals we need for minute
	time[2]=0;
	while (minute>9)
	{
		++time[2];
		minute-=10;
	}
	time[3]=minute;

	// Draw digits
	for (a=0,x=2;a<4;a++,x+=NUMERAL_WIDTH+2)
	{
		// Valid number?
		if (time[a]>-1)
		{
			// Draw number
			BltTemplate(
				(char *)numeral_data[time[a]],
				0,2,
				&data->clock_rp,
				x,y,
				NUMERAL_WIDTH,NUMERAL_HEIGHT);
		}

		// Erase area
		else
		{
			// Save fg pen
			short fg=data->clock_rp.FgPen;

			// Set bg pen
			SetAPen(&data->clock_rp,data->clock_rp.BgPen);

			// Erase it
			RectFill(
				&data->clock_rp,
				x,y,
				x+NUMERAL_WIDTH-1,
				y+NUMERAL_HEIGHT-1);

			// Restore pen
			SetAPen(&data->clock_rp,fg);
		}

		// Time for the colon?
		if (a==1)
		{
			// Draw colon
			BltTemplate(
				(char *)colon_data[colon],
				0,2,
				&data->clock_rp,
				x+NUMERAL_WIDTH+1,y,
				COLON_WIDTH,COLON_HEIGHT);

			// Bump x position
			x+=COLON_WIDTH;
		}
	}

	// Day different?
	if (date.ds_Days!=data->day)
	{
		struct DateTime dt;

		// Fill out dt
		dt.dat_Stamp=date;
		dt.dat_Format=FORMAT_DOS;
		dt.dat_Flags=0;
		dt.dat_StrDay=0;
		dt.dat_StrDate=data->date_buffer;
		dt.dat_StrTime=0;

		// Get date string
		DateToStr(&dt);
		flags|=CAIF_TITLE;
	}

	// Update image
	ChangeAppIcon(data->appicon,&data->clock_image,&data->clock_image,data->date_buffer,flags);
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


// Initialise screen stuff
void iconclock_init(iconclock_data *data,struct Screen *screen)
{
	// Got a screen locked?
	if (data->screen)
	{
		// Free pen
		if (data->pen>-1)
		{
			ReleasePen(data->screen->ViewPort.ColorMap,data->pen);
			data->pen=-1;
		}

		// Unlock it
		UnlockPubScreen(0,data->screen);
		data->screen=0;

		// Remove AppIcon
		if (data->appicon) RemoveAppIcon(data->appicon);
		data->appicon=0;

		// Free bitmap
		FreeVec(data->clock_image.ImageData);
		data->clock_image.ImageData=0;
	}

	// No new screen?
	if (!screen) return;

	// Try to lock screen
	if (FindPubScreen(screen,TRUE))
	{
		short depth=1;

		// Store pointer
		data->screen=screen;

		// Under 39 grab a pen
		if (GfxBase->LibNode.lib_Version>=39 && data->colour)
		{
			// Allocate pen
			if ((data->pen=ObtainPen(
				screen->ViewPort.ColorMap,
				-1,
				0,0xffffffff,0,
				PENF_EXCLUSIVE))>-1)
			{
				// Set colour
				SetRGB32(&screen->ViewPort,data->pen,0,0xffffffff,0);

				// Get depth we need
				for (depth=1;depth<=8;depth++)
					if (1<<depth>data->pen) break;
			}
		}

		// Initialise clock bitmap
		InitBitMap(&data->clock_bm,depth,CLOCK_WIDTH,CLOCK_HEIGHT);

		// Allocate clock bitmap
		if (data->clock_image.ImageData=
			(USHORT *)AllocVec(RASSIZE(CLOCK_WIDTH,CLOCK_HEIGHT)*depth,MEMF_CHIP|MEMF_CLEAR))
		{
			struct TagItem tags[7];
			USHORT *ptr;
			short a;

			// Get bitmap pointers
			ptr=data->clock_image.ImageData;
			for (a=0;a<depth;a++)
			{
				data->clock_bm.Planes[a]=(PLANEPTR)ptr;
				ptr+=((CLOCK_WIDTH+15)>>4)*CLOCK_HEIGHT;
			}

			// Initialise rastport
			InitRastPort(&data->clock_rp);
			data->clock_rp.BitMap=&data->clock_bm;
			SetDrMd(&data->clock_rp,JAM2);

			// Fill in image
			data->clock_image.Width=CLOCK_WIDTH;
			data->clock_image.Height=CLOCK_HEIGHT;
			data->clock_image.Depth=depth;
			data->clock_image.PlanePick=(1<<depth)-1;

			// Fill out fake DiskObject
			data->clock_icon.do_Gadget.Width=CLOCK_WIDTH;
			data->clock_icon.do_Gadget.Height=CLOCK_HEIGHT;
			data->clock_icon.do_Gadget.Flags=GFLG_GADGHIMAGE;
			data->clock_icon.do_Gadget.GadgetRender=&data->clock_image;
			data->clock_icon.do_Gadget.SelectRender=&data->clock_image;
			data->clock_icon.do_CurrentX=data->icon_x;
			data->clock_icon.do_CurrentY=data->icon_y;

			// Set flag to force border on
			SetIconFlags(&data->clock_icon,ICONF_BORDER_ON);

			// AppIcon tags
			tags[0].ti_Tag=DAE_SnapShot;
			tags[0].ti_Data=1;
			tags[1].ti_Tag=DAE_Close;
			tags[1].ti_Data=2;
			tags[2].ti_Tag=DAE_Local;
			tags[2].ti_Data=1;
			tags[3].ti_Tag=DAE_Info;
			tags[3].ti_Data=1;

			// Under 39 we can use colour
			if (GfxBase->LibNode.lib_Version>=39)
			{
				tags[4].ti_Tag=(data->pen>-1)?DAE_Background:TAG_IGNORE;
				tags[4].ti_Data=1;
				tags[5].ti_Tag=(data->colour)?DAE_ToggleMenuSel:DAE_ToggleMenu;
				tags[5].ti_Data=(ULONG)GetString(locale,MSG_ICONCLOCK_COLOUR);
				tags[6].ti_Tag=TAG_END;
			}
			else tags[4].ti_Tag=TAG_END;

			// Add AppIcon
			if (data->appicon=AddAppIconA(0,0,NAME_ICONCLOCK,data->app_port,0,&data->clock_icon,tags))
			{
				// If we have a pen, fill background
				if (data->pen>-1) SetRast(&data->clock_rp,1);

				// Set pen for clock
				SetAPen(&data->clock_rp,(data->pen>-1)?data->pen:1);
				SetBPen(&data->clock_rp,(data->pen>-1)?1:0);

				// Show clock
				iconclock_show(data);
			}
		}

		// Failed?
		if (!data->appicon)
		{
			// Free stuff (this is a bit recursive)
			iconclock_init(data,0);
		}
	}
}


// Show info window
void iconclock_info(iconclock_data *data)
{
	struct EasyStruct easy;

	// Window open?
	if (data->about)
	{
		WindowToFront(data->about);
		ActivateWindow(data->about);
		return;
	}

	// Fill out easy struct
	easy.es_StructSize=sizeof(easy);
	easy.es_Flags=0;
	easy.es_Title=GetString(locale,MSG_ICONCLOCK_TITLE);
	easy.es_TextFormat="Directory Opus 5 Icon Clock\nv55.2 (26.05.97)\n\n© 1997 Jonathan Potter";
	easy.es_GadgetFormat=GetString(locale,MSG_OK);

	// Open requester
	data->about=BuildEasyRequestArgs(data->screen->FirstWindow,&easy,0,0);
}
