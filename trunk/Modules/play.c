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

#include "play.h"
#include "music.h"

char *version="$VER: play.module 68.0 (3.10.98)";

static char *modtypes[]={"SoundTracker","MED","Octalyzer","SoundTracker 15"};

Object *myNewDTObject(play_data *data,APTR name,Tag tag,...);

int __asm __saveds L_Module_Entry(
	register __a0 struct List *files,
	register __a1 struct Screen *screen,
	register __a2 IPCData *ipc,
	register __a3 IPCData *main_ipc,
	register __d0 ULONG mod_id,
	register __d1 ULONG mod_data)
{
	play_data *data;
	struct Node *node;
	short ret=1;

	// Allocate data
	if (!(data=AllocVec(sizeof(play_data),MEMF_CLEAR)))
		return 0;

	// Try to open datatypes
	if (DataTypesBase=OpenLibrary("datatypes.library",0))
	{
		// Allocate signal for dt to talk to us with
		data->dt_signal=AllocSignal(-1);
	}
	else data->dt_signal=-1;

	// Allocate message port
	data->app_port=CreateMsgPort();

	// Store IPC pointer
	data->ipc=ipc;

	// Get colour clock
	data->clock=(((struct GfxBase *)GfxBase)->DisplayFlags&PAL)?3546895:3579545;

	// Cache screen and flags
	data->screen=screen;
	data->flags=mod_data;

	// Initialise icon position
	data->icon_x=NO_ICON_POSITION;
	data->icon_y=NO_ICON_POSITION;

	// Environment variable set?
	if (GetVar(ENV_PLAY,data->buf,sizeof(data->buf),GVF_GLOBAL_ONLY)>0)
	{
		char *ptr=data->buf;

		// Get icon position
		read_parse_set(&ptr,(long *)&data->icon_x);
		read_parse_set(&ptr,(long *)&data->icon_y);
	}

	// Go through files
	for (node=files->lh_Head;node->ln_Succ;node=node->ln_Succ)
	{
		short a;

		// Store file name pointer
		data->file=node->ln_Name;

		// Need to open icon?
		if (!data->app_icon && data->flags&PLAYF_ICON)
		{
			// Open AppIcon
			play_iconify(data);
			data->flags&=~PLAYF_ICON;
		}

		// Need to open window?
		else
		if (!data->window && !data->app_icon && !(data->flags&PLAYF_QUIET))
		{
			// Open the window
			play_open_window(data,screen,(struct Window *)mod_id);
			mod_id=0;

			// Set busy pointer
			if (data->window) SetWindowBusy(data->window);
		}

		// Play file
		a=play_file(data);
		play_cleanup(data);

		// Aborted?
		if (!a)
		{
			ret=-1;
			break;
		}
	}

	// Free data
	play_free(data);

	return ret;
}


// Free play data
void play_free(play_data *data)
{
	if (data)
	{
		// Remove AppIcon
		if (data->app_icon) RemoveAppIcon(data->app_icon);

		// Free icon
		if (data->icon) FreeDiskObject(data->icon);

		// Close window
		CloseConfigWindow(data->window);

		// Free message port
		DeleteMsgPort(data->app_port);

		// Close datatypes
		if (DataTypesBase) CloseLibrary(DataTypesBase);

		// Close music library
		if (MUSICBase) CloseLibrary(MUSICBase);

		// Free signal
		if (data->dt_signal!=-1) FreeSignal(data->dt_signal);

		// Free data
		FreeVec(data);
	}
}


// Initialise audio data
BOOL play_init(play_data *data)
{
	static UBYTE audiochannels[2][4]={{1,8,2,4},{2,4,1,8}};
	short a;
	BOOL fail=0;

	// Create message port
	if (!(data->audio_port=CreateMsgPort()))
		return 0;

	// Open audio device
	for (a=0;a<2;a++)
	{
		// Initialise IO request
		data->audio_req1[a].ioa_Request.io_Message.mn_ReplyPort=data->audio_port;
		data->audio_req1[a].ioa_Request.io_Message.mn_Node.ln_Pri=75;
		data->audio_req1[a].ioa_Request.io_Message.mn_Node.ln_Name=(char *)a;
		data->audio_req1[a].ioa_Data=audiochannels[a];
		data->audio_req1[a].ioa_Length=sizeof(audiochannels[a]);

		// Open device
		if (OpenDevice("audio.device",0,&data->audio_req1[a].ioa_Request,0)) {
			fail=1;
			break;
		}
	}

	// Still ok?
	if (!fail)
	{
		// Allocate play buffers
		for (a=0;a<2;a++)
		{
			if (!(data->play_buffer[a]=AllocVec(PLAY_MAX_SIZE,MEMF_CHIP|MEMF_CLEAR)))
			{
				fail=1;
				break;
			}
		}
	}

	// Did we fail?
	return (BOOL)!fail;
}


// Play a sound file
BOOL play_file(play_data *data)
{
	APTR iff;
	BPTR file;
	unsigned long segment_size;
	short a,type=MSG_TYPE_MONO,volume;

	// Initialise
	data->audio_data=0;
	data->svx_flag=0;
	data->channels=0;
	data->audio_size=0;
	data->stereo_offset=0;
	data->module_type=0;

	// Get volume
	volume=(data->flags>>8)&0x7f;
	if (volume==0 || volume>64) volume=64;

	// Initialise info fields
	play_update_info(data,FilePart(data->file),0,0,GetString(locale,MSG_STATUS_LOADING));

	// Open file as IFF
	if (iff=IFFOpen(data->file,IFF_READ,ID_8SVX))
	{
		ULONG chunk;

		// Parse IFF file
		while (chunk=IFFNextChunk(iff,0))
		{
			// Look at chunk type
			switch (chunk)
			{
				// 8SVX header
				case ID_VHDR:
					IFFReadChunkBytes(iff,&data->header,sizeof(data->header));
					data->svx_flag=1;
					break;

				// Channel
				case ID_CHAN:
					IFFReadChunkBytes(iff,&data->channels,sizeof(data->channels));
					break;

				// Body
				case ID_BODY:
					data->audio_size=IFFChunkSize(iff);
					if (data->audio_data=AllocVec(data->audio_size,MEMF_CLEAR))
					{
						IFFReadChunkBytes(iff,data->audio_data,data->audio_size);
					}
					break;
			}

			// Break out when we have a body
			if (data->audio_data) break;
		}

		// Close file
		IFFClose(iff);
	}

	// If we've got datatypes, see if it matches
	if (!iff &&
		DataTypesBase &&
		(data->dt_object=myNewDTObject(data,data->file,
										SDTA_SignalTask,(ULONG)FindTask(0),
										SDTA_SignalBit,data->dt_signal,
										DTA_GroupID,GID_SOUND,
										TAG_END)))
	{
		struct dtTrigger trigger;
		struct DataType *dt=0;

		// Set sound things
		SetDTAttrs(data->dt_object,0,0,
					SDTA_SignalTask,(ULONG)FindTask(0),
					SDTA_SignalBit,data->dt_signal,
					SDTA_Volume,volume,
					TAG_END);

		// Get datatype pointer
		GetAttr(DTA_DataType,data->dt_object,(ULONG *)&dt);

		// Update status
		play_update_info(
			data,
			(char *)-1,
			"???",
			(dt)?(char *)dt->dtn_Header->dth_Name:(char *)-1,
			GetString(locale,MSG_STATUS_PLAYING));

		// Trigger sound
		trigger.MethodID=DTM_TRIGGER;
		trigger.dtt_GInfo=0;
		trigger.dtt_Function=STM_PLAY;
		trigger.dtt_Data=0;

		// Play sound
		SetSignal(0,1<<data->dt_signal);
		DoDTMethodA(data->dt_object,0,0,(Msg)&trigger);

		// Clear busy pointer
		if (data->window) ClearWindowBusy(data->window);

		// Wait until completed or aborted
		return wait_for_play(data,1);
	}

	// Failed so far?
	if (!iff)
	{
		// Open music library
		if (!MUSICBase &&
			!(MUSICBase=OpenLibrary("dopus5:libs/inovamusic.library",0)))
			MUSICBase=OpenLibrary("inovamusic.library",0);

		// Try for module
		if (MUSICBase &&
			((data->module_type=IsModule(data->file))>0 && data->module_type<100))
		{
			// Start module playing
			if (PlayModule(data->file,TRUE))
			{
				// Failed
				FlushModule();
				return 1;
			}

			// Playing OK
			else
			{
				BOOL res;
				char *type;

				// Get module type
				type=(data->module_type>=MOD_STNTPT && data->module_type<=MOD_OLDST)?
						modtypes[data->module_type-1]:"Module";

				// Update info
				play_update_info(data,(char *)-1,"???",type,GetString(locale,MSG_STATUS_PLAYING));

				// Clear busy pointer
				if (data->window) ClearWindowBusy(data->window);

				// Wait for play to finish
				res=wait_for_play(data,0);

				// Flush module
				FlushModule();
				return res;
			}
		}

		// Read as raw
		else
		if (file=Open(data->file,MODE_OLDFILE))
		{
			// Get size of file
			Seek(file,0,OFFSET_END);
			data->audio_size=Seek(file,0,OFFSET_BEGINNING);

			// Allocate buffer
			if (data->audio_data=AllocVec(data->audio_size,MEMF_CLEAR))
			{
				Read(file,data->audio_data,data->audio_size);
			}
			Close(file);

			// Raw
			type=MSG_TYPE_RAW;
		}
	}

	// Do we have anything to play?
	if (!data->audio_data || !data->audio_size) return 1;

	// Initialise sound stuff
	if (!(play_init(data))) return 0;

	// Is data compressed?
	if (data->svx_flag && data->header.sCompression==1)
	{
		unsigned char *decompress_buf;

		// Update status
		play_update_info(data,(char *)-1,(char *)-1,(char *)-1,GetString(locale,MSG_STATUS_DECOMPRESSING));

		// Subtract 2 from the length and double it
		data->audio_size-=2;
		data->audio_size*=2;

		// Allocate decompression buffer
		if (!(decompress_buf=AllocVec(data->audio_size,MEMF_CLEAR)))
		{
			FreeVec(data->audio_data);
			data->audio_data=0;
			return 1;
		}

		// Decompress audio data
		unpack_delta(data->audio_data+2,data->audio_size,decompress_buf,data->audio_data[1]);

		// Free compressed data, store pointer to new buffer
		FreeVec(data->audio_data);
		data->audio_data=decompress_buf;
	}

	// If an IFF file, get speed from that
	if (data->svx_flag)
	{
		data->play_speed=data->header.samplesPerSec;
		if (data->play_speed==0) data->play_speed=10000;
	}

	// Otherwise default to 10000
	else data->play_speed=10000;

	// Is sample in stereo?
	if (data->channels==6)
	{
		// Halve size, set stereo offset
		data->audio_size>>=1;
		data->stereo_offset=data->audio_size;

		// Stereo type
		type=MSG_TYPE_STEREO;
	}

	// Get size of each segment to play
	segment_size=(data->audio_size<PLAY_MAX_SIZE)?data->audio_size:PLAY_MAX_SIZE;

	// Initialise audio IO requests
	for (a=0;a<2;a++)
	{
		data->audio_req1[a].ioa_Request.io_Command=CMD_WRITE;
		data->audio_req1[a].ioa_Request.io_Flags=ADIOF_PERVOL;
		data->audio_req1[a].ioa_Volume=volume;
		data->audio_req1[a].ioa_Period=(UWORD)UDivMod32(data->clock,data->play_speed);
		data->audio_req1[a].ioa_Cycles=1;

		data->audio_req2[a]=data->audio_req1[a];
		data->audio_req1[a].ioa_Data=(UBYTE *)data->play_buffer[a];
		data->audio_req2[a].ioa_Data=(UBYTE *)data->play_buffer[a]+(PLAY_MAX_SIZE>>1);
	}

	// Update info fields
	play_update_length(data);
	play_update_info(data,(char *)-1,(char *)-1,GetString(locale,type),GetString(locale,MSG_STATUS_PLAYING));

	// Clear busy pointer
	if (data->window) ClearWindowBusy(data->window);

	// Can we play it in one shot?
	if (data->audio_size<=PLAY_MAX_SIZE)
	{
		short got_reply=0;

		// Copy data into play buffers
		for (a=0;a<2;a++)
		{
			CopyMem(
				data->audio_data+(a*data->stereo_offset),
				(char *)data->play_buffer[a],
				data->audio_size);
		}

		// Start sounds playing
		for (a=0;a<2;a++)
		{
			data->audio_req1[a].ioa_Length=data->audio_size;
			BeginIO(&data->audio_req1[a].ioa_Request);
		}

		// Wait until completed or aborted
		FOREVER
		{
			IPCMessage *imsg;

			// IPC messages?
			if (data->ipc)
			{
				short quit_flag=0;

				while (imsg=(IPCMessage *)GetMsg(data->ipc->command_port))
				{
					// Abort?
					if (imsg->command==IPC_ABORT || imsg->command==IPC_QUIT)
						quit_flag=1;
					IPC_Reply(imsg);
				}

				// Abort?
				if (quit_flag) return 0;
			}

			// AppIcon open?
			if (data->app_icon)
			{
				struct AppSnapshotMsg *msg;
				short ret=0,done=0;

				// Get messages
				while (msg=(struct AppSnapshotMsg *)GetMsg(data->app_port))
				{
					// Still got AppIcon?
					if (data->app_icon)
					{
						// Normal message?
						if (msg->ap_msg.am_Type==MTYPE_APPICON)
						{
							// Open up
							play_reveal(data,data->screen);
						}

						// Special message?
						else
						if (msg->ap_msg.am_Type==MTYPE_APPSNAPSHOT)
						{
							// Menu operation?
							if (msg->flags&APPSNAPF_MENU)
							{
								// Next?
								if (msg->id==0)
								{
									ret=1;
									done=1;
								}

								// Abort?
								else
								if (msg->id==1)
								{
									done=1;
								}
							}

							// Snapshot
							else play_snapshot(data,msg);
						}
					}

					// Reply to the message
					ReplyFreeMsg((struct Message *)msg);
				}

				// Finished?
				if (done) return ret;
			}

			// Window open?
			if (data->window)
			{
				struct IntuiMessage *msg,copy_msg;

				// Any Intuition messages?
				while (msg=GetWindowMsg(data->window->UserPort))
				{
					// Copy message and reply
					copy_msg=*msg;
					ReplyWindowMsg(msg);

					// Gadget?
					if (copy_msg.Class==IDCMP_GADGETUP)
					{
						switch (((struct Gadget *)copy_msg.IAddress)->GadgetID)
						{
							// Next
							case GAD_PLAY_NEXT:
								return 1;

							// Abort
							case GAD_PLAY_ABORT:
								return 0;

							// Iconify
							case GAD_ID_ICONIFY:
								play_iconify(data);
								break;
						}
					}

					// Close window
					else
					if (copy_msg.Class==IDCMP_CLOSEWINDOW)
						return 0;

					// Window not valid any more?
					if (!data->window) break;
				}
			}

			// Check replies
			for (a=0;a<2;a++)
			{
				if (!(got_reply&(1<<a)) &&
					(CheckIO(&data->audio_req1[a].ioa_Request))) got_reply|=1<<a;
			}

			// Get any audio replies
			while (GetMsg(data->audio_port));

			// If we've got both replies, break out
			if (got_reply==3) break;

			// Wait for an event
			Wait(   1<<data->audio_port->mp_SigBit|
					((data->ipc)?(1<<data->ipc->command_port->mp_SigBit):0)|
					((data->app_icon)?(1<<data->app_port->mp_SigBit):0)|
					((data->window)?(1<<data->window->UserPort->mp_SigBit):0));
		}

		// Return
		return 1;
	}

	// Too big to play at once, have to double-buffer
	FOREVER
	{
		unsigned char *play_ptr;
		unsigned long play_size;
		short finish_flag=0;
		short reply_bits=0;
		struct IOAudio *audio_req[2];

		// Get pointer to data and initial size
		play_ptr=data->audio_data;
		play_size=data->audio_size;

		// Initialise audio requests
		for (a=0;a<2;a++)
		{
			// Copy initial data into buffers
			CopyMem(
				play_ptr+(a*data->stereo_offset),
				(char *)data->play_buffer[a],
				segment_size);

			// Initialise IO requests
			data->audio_req2[a]=data->audio_req1[a];
			data->audio_req1[a].ioa_Data=(UBYTE *)data->play_buffer[a];
			data->audio_req1[a].ioa_Length=(PLAY_MAX_SIZE>>1);
			data->audio_req2[a].ioa_Data=(UBYTE *)data->play_buffer[a]+(PLAY_MAX_SIZE>>1);
			data->audio_req2[a].ioa_Length=(PLAY_MAX_SIZE>>1);
			audio_req[a]=&data->audio_req2[a];
		}

		// Bump play pointer, decrement remaining length
		play_ptr+=segment_size;
		play_size-=PLAY_MAX_SIZE;

		// Send initial requests
		for (a=0;a<2;a++) BeginIO(&data->audio_req1[a].ioa_Request);

		// Send queued requests
		for (a=0;a<2;a++) BeginIO(&data->audio_req2[a].ioa_Request);

		// Loop until complete or aborted
		FOREVER
		{
			struct Message *msg;
			IPCMessage *imsg;

			// IPC messages?
			if (data->ipc)
			{
				short quit_flag=0;

				while (imsg=(IPCMessage *)GetMsg(data->ipc->command_port))
				{
					// Abort?
					if (imsg->command==IPC_ABORT || imsg->command==IPC_QUIT)
						quit_flag=1;
					IPC_Reply(imsg);
				}

				// Abort?
				if (quit_flag) return 0;
			}

			// AppIcon open?
			if (data->app_icon)
			{
				struct AppSnapshotMsg *msg;
				short ret=0,done=0;

				// Get messages
				while (msg=(struct AppSnapshotMsg *)GetMsg(data->app_port))
				{
					// Still got AppIcon?
					if (data->app_icon)
					{
						// Normal message?
						if (msg->ap_msg.am_Type==MTYPE_APPICON)
						{
							// Open up
							play_reveal(data,data->screen);
						}

						// Special message?
						else
						if (msg->ap_msg.am_Type==MTYPE_APPSNAPSHOT)
						{
							// Menu operation?
							if (msg->flags&APPSNAPF_MENU)
							{
								// Next?
								if (msg->id==0)
								{
									ret=1;
									done=1;
								}

								// Abort?
								else
								if (msg->id==1)
								{
									done=1;
								}
							}

							// Snapshot
							else play_snapshot(data,msg);
						}
					}

					// Reply to the message
					ReplyFreeMsg((struct Message *)msg);
				}

				// Finished?
				if (done) return ret;
			}

			// Window open?
			if (data->window)
			{
				struct IntuiMessage *msg,copy_msg;

				// Any Intuition messages?
				while (msg=GetWindowMsg(data->window->UserPort))
				{
					// Copy message and reply
					copy_msg=*msg;
					ReplyWindowMsg(msg);

					// Gadget?
					if (copy_msg.Class==IDCMP_GADGETUP)
					{
						switch (((struct Gadget *)copy_msg.IAddress)->GadgetID)
						{
							// Next
							case GAD_PLAY_NEXT:
								return 1;

							// Abort
							case GAD_PLAY_ABORT:
								return 0;

							// Iconify
							case GAD_ID_ICONIFY:
								play_iconify(data);
								break;
						}
					}

					// Close window
					else
					if (copy_msg.Class==IDCMP_CLOSEWINDOW)
						return 0;

					// Window not valid any more?
					if (!data->window) break;
				}
			}

			// Check audio ports for replies
			while (msg=GetMsg(data->audio_port))
			{
				short a;

				// Get port number
				a=(short)msg->mn_Node.ln_Name;

				// See if reply is actually due
				if (!(reply_bits&(1<<a)))
				{
					// Still data remaining to play?
					if (play_size>0)
					{
						// Switch to other request
						if (audio_req[a]==&data->audio_req1[a])
							audio_req[a]=&data->audio_req2[a];
						else audio_req[a]=&data->audio_req1[a];

						// Get length of new data
						audio_req[a]->ioa_Length=
							(play_size<(PLAY_MAX_SIZE>>1))?play_size:(PLAY_MAX_SIZE>>1);

						// Copy next lot of data in
						CopyMem(
							play_ptr+(a*data->stereo_offset),
							(char *)audio_req[a]->ioa_Data,
							audio_req[a]->ioa_Length);
					}

					// Set bit to indicate we've got this reply
					reply_bits|=1<<a;
				}
			}

			// Are both replies in?
			if (reply_bits==3)
			{
				// If there's no data left
				if (play_size<=0)
				{
					// If the finish flag was set, clear it and break out of the loop
					if (finish_flag) break;

					// Set finish flag; we'll break next time around
					finish_flag=1;
				}

				// Still some to go
				else
				{
					// Bump buffer pointer
					play_ptr+=(PLAY_MAX_SIZE>>1);

					// Decrement remaining size
					play_size-=audio_req[0]->ioa_Length;

					// Send next lot of queued requests
					for (a=0;a<2;a++) BeginIO((struct IORequest *)audio_req[a]);
				}

				// Clear reply bits
				reply_bits=0;
			}

			// Wait for an event
			Wait(   1<<data->audio_port->mp_SigBit|
					((data->ipc)?(1<<data->ipc->command_port->mp_SigBit):0)|
					((data->app_icon)?(1<<data->app_port->mp_SigBit):0)|
					((data->window)?(1<<data->window->UserPort->mp_SigBit):0));
		}

		// Break out (would loop here)
		break;
	}

	return 1;
}


// Cleanup after playing a sound
void play_cleanup(play_data *data)
{
	short a;

	// Close audio
	for (a=0;a<2;a++)
	{
		// Was the device open?
		if (data->audio_req1[a].ioa_Request.io_Device)
		{
			// Reset the device
			data->audio_req1[a].ioa_Request.io_Command=CMD_RESET;
			data->audio_req1[a].ioa_Request.io_Flags=0;
			DoIO(&data->audio_req1[a].ioa_Request);

			// Close the device
			CloseDevice(&data->audio_req1[a].ioa_Request);
			data->audio_req1[a].ioa_Request.io_Device=0;
		}

		// Free play buffer
		if (data->play_buffer[a])
		{
			FreeVec(data->play_buffer[a]);
			data->play_buffer[a]=0;
		}
	}

	// Close message port
	if (data->audio_port)
	{
		struct Message *msg;

		// Flush all messages
		while (msg=GetMsg(data->audio_port));
		DeleteMsgPort(data->audio_port);
		data->audio_port=0;
	}

	// Free audio buffer
	if (data->audio_data)
	{
		FreeVec(data->audio_data);
		data->audio_data=0;
	}

	// Free dt object
	if (data->dt_object)
	{
		DisposeDTObject(data->dt_object);
		data->dt_object=0;
	}

	// Set busy pointer
	if (data->window) SetWindowBusy(data->window);
}


// Code table for delta unpacking
static char codetodelta[16]={-34,-21,-13,-8,-5,-3,-2,-1,0,1,2,3,5,8,13,21};

// Unpack a delta-compressed data stream
void unpack_delta(char *source,unsigned long size,char *dest,unsigned char start)
{
	unsigned char delta;
	unsigned long i;

	// Go through data stream
	for (i=0;i<size;++i)
	{
		// Get delta value
		delta=source[(i>>1)];

		// High or low nibble?
		if (i&1) delta&=0xf;
		else delta>>=4;

		// Add this delta value
		start+=codetodelta[delta];

		// Store in destination stream
		dest[i]=start;
	}
}


// Update length info field
void play_update_length(play_data *data)
{
	unsigned long minutes,seconds;
	char length_buf[10];

	// Get time to play
	minutes=DivideU(UDivMod32(data->audio_size,data->play_speed),60,&seconds,UtilityBase);
	if (minutes==0 && seconds==0) seconds=1;

	// Build length string
	lsprintf(length_buf,"%02ld:%02ld",minutes,seconds);

	// Update display
	play_update_info(data,(char *)-1,length_buf,(char *)-1,(char *)-1);
}


// varargs stuff
Object *myNewDTObject(play_data *data,APTR name,Tag tag,...)
{
	return NewDTObjectA(name,(struct TagItem *)&tag);
}


// Wait for play
BOOL wait_for_play(play_data *data,BOOL dt)
{
	// Wait until aborted
	FOREVER
	{
		IPCMessage *imsg;

		// IPC messages?
		if (data->ipc)
		{
			short quit_flag=0;

			while (imsg=(IPCMessage *)GetMsg(data->ipc->command_port))
			{
				// Abort?
				if (imsg->command==IPC_ABORT || imsg->command==IPC_QUIT)
					quit_flag=1;

				IPC_Reply(imsg);
			}

			// Abort?
			if (quit_flag) return 0;
		}

		// AppIcon open?
		if (data->app_icon)
		{
			struct AppSnapshotMsg *msg;
			short ret=0,done=0;

			// Get messages
			while (msg=(struct AppSnapshotMsg *)GetMsg(data->app_port))
			{
				// Still got AppIcon?
				if (data->app_icon)
				{
					// Normal message?
					if (msg->ap_msg.am_Type==MTYPE_APPICON)
					{
						// Open up
						play_reveal(data,data->screen);
					}

					// Special message?
					else
					if (msg->ap_msg.am_Type==MTYPE_APPSNAPSHOT)
					{
						// Menu operation?
						if (msg->flags&APPSNAPF_MENU)
						{
							// Next?
							if (msg->id==0)
							{
								ret=1;
								done=1;
							}

							// Abort?
							else
							if (msg->id==1)
							{
								done=1;
							}
						}

						// Snapshot
						else play_snapshot(data,msg);
					}
				}

				// Reply to the message
				ReplyFreeMsg((struct Message *)msg);
			}

			// Finished?
			if (done) return ret;
		}

		// Window open?
		if (data->window)
		{
			struct IntuiMessage *msg,copy_msg;

			// Any Intuition messages?
			while (msg=GetWindowMsg(data->window->UserPort))
			{
				// Copy message and reply
				copy_msg=*msg;
				ReplyWindowMsg(msg);

				// Gadget?
				if (copy_msg.Class==IDCMP_GADGETUP)
				{
					switch (((struct Gadget *)copy_msg.IAddress)->GadgetID)
					{
						// Next
						case GAD_PLAY_NEXT:
							return 1;

						// Abort
						case GAD_PLAY_ABORT:
							return 0;

						// Iconify
						case GAD_ID_ICONIFY:
							play_iconify(data);
							break;
					}
				}

				// Close window
				else
				if (copy_msg.Class==IDCMP_CLOSEWINDOW)
					return 0;

				// Window not valid any more?
				if (!data->window) break;
			}
		}

		// Wait for an event
		if ((Wait(  ((dt)?1<<data->dt_signal:0)|
					((data->ipc)?(1<<data->ipc->command_port->mp_SigBit):0)|
					((data->app_icon)?(1<<data->app_port->mp_SigBit):0)|
					((data->window)?(1<<data->window->UserPort->mp_SigBit):0)))&(1<<data->dt_signal) && dt)
			break;
	}

	// Return
	return 1;
}


// Iconify play requester
void play_iconify(play_data *data)
{
	struct TagItem tags[4];

	// Already iconified?
	if (data->app_icon) return;

	// No port?
	if (!data->app_port) return;

	// No icon yet?
	if (!data->icon &&
		!(data->icon=GetDiskObject("dopus5:icons/play")) &&
		!(data->icon=GetDefDiskObject(WBPROJECT))) return;

	// Fill out tags
	tags[0].ti_Tag=DAE_SnapShot;
	tags[0].ti_Data=1;
	tags[1].ti_Tag=DAE_Menu;
	tags[1].ti_Data=(ULONG)GetString(locale,MSG_PLAY_NEXT);
	tags[2].ti_Tag=DAE_Menu;
	tags[2].ti_Data=(ULONG)GetString(locale,MSG_PLAY_ABORT);
	tags[3].ti_Tag=TAG_END;

	// Set position
	data->icon->do_CurrentX=data->icon_x;
	data->icon->do_CurrentY=data->icon_y;

	// Try to add AppIcon
	if (!(data->app_icon=AddAppIconA(
		0,
		0,
		data->play_name,
		data->app_port,
		0,
		data->icon,
		tags))) return;

	// Save window position
	if (data->window)
		data->pos=*((struct IBox *)&data->window->LeftEdge);

	// Close window
	CloseConfigWindow(data->window);
	data->window=0;
}


// Open play window
void play_open_window(play_data *data,struct Screen *screen,struct Window *parent)
{
	// Fill out new window
	data->new_win.dims=&data->dims;
	data->new_win.title=GetString(locale,MSG_PLAY_TITLE);
	data->new_win.locale=locale;
	data->new_win.flags=WINDOW_AUTO_KEYS|WINDOW_REQ_FILL|WINDOW_VISITOR|WINDOW_ICONIFY;
	data->new_win.port=0;
	data->new_win.font=0;

	// Saved position valid?
	if (data->pos.Width)
	{
		// Use this position
		data->dims.char_dim.Left=0;
		data->dims.char_dim.Top=0;
		data->dims.fine_dim.Left=data->pos.Left;
		data->dims.fine_dim.Top=data->pos.Top;
	}

	// Otherwise, get default size
	else data->dims=play_window;

	// Window as parent?
	if (parent) data->new_win.parent=(void *)parent;

	// Screen as parent
	else
	{
		data->new_win.parent=screen;
		data->new_win.flags|=WINDOW_SCREEN_PARENT;
	}

	// Open window
	if (data->window=OpenConfigWindow(&data->new_win))
	{
		// Add objects
		if (data->objlist=AddObjectList(data->window,play_objects))
		{
			// Initialise fields
			SetGadgetValue(data->objlist,GAD_PLAY_FILENAME,(ULONG)data->play_name);
			SetGadgetValue(data->objlist,GAD_PLAY_LENGTH,(ULONG)data->play_length);
			SetGadgetValue(data->objlist,GAD_PLAY_TYPE,(ULONG)data->play_type);
			SetGadgetValue(data->objlist,GAD_PLAY_STATUS,(ULONG)data->play_status);
		}
	}
}


// Update info fields
void play_update_info(
	play_data *data,
	char *filename,
	char *length,
	char *type,
	char *status)
{
	// Change filename?
	if (filename!=(char *)-1)
	{
		// Copy filename
		if (filename) stccpy(data->play_name,filename,40);
		else *data->play_name=0;

		// Update field if window open
		if (data->window) SetGadgetValue(data->objlist,GAD_PLAY_FILENAME,(ULONG)data->play_name);

		// Or, if AppIcon is open, change label
		else
		if (data->app_icon) ChangeAppIcon(data->app_icon,0,0,data->play_name,CAIF_TITLE);
	}

	// Change length?
	if (length!=(char *)-1)
	{
		// Copy length
		if (length) stccpy(data->play_length,length,40);
		else *data->play_length=0;

		// Update field if window open
		if (data->window) SetGadgetValue(data->objlist,GAD_PLAY_LENGTH,(ULONG)data->play_length);
	}

	// Change type?
	if (type!=(char *)-1)
	{
		// Copy type
		if (type) stccpy(data->play_type,type,40);
		else *data->play_type=0;

		// Update field if window open
		if (data->window) SetGadgetValue(data->objlist,GAD_PLAY_TYPE,(ULONG)data->play_type);
	}

	// Change status?
	if (status!=(char *)-1)
	{
		// Copy status
		if (status) stccpy(data->play_status,status,40);
		else *data->play_status=0;

		// Update field if window open
		if (data->window) SetGadgetValue(data->objlist,GAD_PLAY_STATUS,(ULONG)data->play_status);
	}
}


// Come back from iconified
void play_reveal(play_data *data,struct Screen *scr)
{
	// Remove AppIcon
	if (data->app_icon)
	{
		RemoveAppIcon(data->app_icon);
		data->app_icon=0;
	}

	// Window already open?
	if (data->window) return;

	// Open window
	play_open_window(data,scr,0);
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


// Snapshot icon
void play_snapshot(play_data *data,struct AppSnapshotMsg *msg)
{
	// Unsnapshot?
	if (msg->flags&APPSNAPF_UNSNAPSHOT)
	{
		// Reinitialise position
		data->icon_x=NO_ICON_POSITION;
		data->icon_y=NO_ICON_POSITION;
	}

	// Store position
	else
	{
		data->icon_x=msg->position_x;
		data->icon_y=msg->position_y;
	}

	// Build environment variable
	lsprintf(data->buf,"%ld/%ld",data->icon_x,data->icon_y);

	// Set environment variable
	SetEnv(ENV_PLAY,data->buf,TRUE);
}
