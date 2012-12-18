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

#include "join.h"

char *version="$VER: join.module 68.0 (3.10.98)";

void get_trunc_filename(char *source,char *dest);

int __asm __saveds L_Module_Entry(
	register __a0 char *args,
	register __a1 struct Screen *screen,
	register __a2 IPCData *ipc,
	register __a3 IPCData *main_ipc,
	register __d0 ULONG mod_id,
	register __d1 EXT_FUNC(func_callback))
{
	join_data *data;
	FunctionEntry *entry;
	Att_Node *current=0;
	short ret=1,start=0;
	BOOL quit_flag=0;

	// Allocate data
	if (!(data=AllocVec(sizeof(join_data),MEMF_CLEAR)))
		return 0;

	// Store pointers
	data->ipc=ipc;
	data->screen=screen;
	data->function=mod_id;

	// Parse arguments
	if (mod_id<2)
		data->args=ParseArgs(func_templates[mod_id],args);

	// Create message port
	data->app_port=CreateMsgPort();

	// Get timer.device base
	if (!OpenDevice("timer.device",0,(struct IORequest *)&data->timer_req,0))
		data->TimerBase=(struct Library *)data->timer_req.tr_node.io_Device;

	// Create list, open window
	if (!(data->join_list=Att_NewList(LISTF_POOL)) ||
		!(join_open(data)))
	{
		join_free(data);
		return 0;
	}

	// Get source path
	func_callback(EXTCMD_GET_SOURCE,IPCDATA(ipc),data->source);

	// Get destination path
	func_callback(EXTCMD_GET_DEST,IPCDATA(ipc),data->dest);

	// Files supplied?
	if (data->args && data->args->FA_Arguments[JOINARG_FROM])
	{
		// Join?
		if (data->function==JOIN)
		{
			char **names;
			short a;

			// Get array pointer
			names=(char **)data->args->FA_Arguments[JOINARG_FROM];

			// Go through names
			for (a=0;names[a];a++)
			{
				char buf[256];

				// Any path characters in name?
				if (strchr(names[a],':') || strchr(names[a],'/'))
				{
					// Use name by itself
					stccpy(buf,names[a],255);
				}

				// Treat as filename in current path
				else
				{
					strcpy(buf,data->source);
					AddPart(buf,names[a],256);
				}

				// Add entry to list
				join_add_file(data,buf,1);
			}

			// Set destination
			SetGadgetValue(
				data->list,
				GAD_JOIN_TO_FIELD,
				(data->args->FA_Arguments[JOINARG_TO])?
					data->args->FA_Arguments[JOINARG_TO]:
					(ULONG)data->dest);

			// If valid destination, start automatically
			if (data->args->FA_Arguments[JOINARG_TO]) start=1;
		}

		// Split
		else
		{
			char buf[256];

			// Any path characters in name?
			if (strchr((char *)data->args->FA_Arguments[SPLITARG_FROM],'/') ||
				strchr((char *)data->args->FA_Arguments[SPLITARG_FROM],':'))
			{
				// Use name by itself
				stccpy(buf,(char *)data->args->FA_Arguments[SPLITARG_FROM],255);
			}

			// Treat as filename in current path
			else
			{
				strcpy(buf,data->source);
				AddPart(buf,(char *)data->args->FA_Arguments[SPLITARG_FROM],256);
			}

			// Add entry to list
			join_add_file(data,buf,1);

			// Set destination
			SetGadgetValue(
				data->list,
				GAD_SPLIT_TO,
				(data->args->FA_Arguments[SPLITARG_TO])?
					data->args->FA_Arguments[SPLITARG_TO]:
					(ULONG)data->dest);
		}
	}

	// Otherwise
	else
	{
		// Get entries
		while (entry=(FunctionEntry *)func_callback(EXTCMD_GET_ENTRY,IPCDATA(ipc),0))
		{
			struct endentry_packet packet;
			char buf[256];

			// Build path
			strcpy(buf,data->source);
			AddPart(buf,entry->name,256);

			// Add entry to list
			join_add_file(data,buf,1);

			// Fill out packet to end entry
			packet.entry=entry;
			packet.deselect=1;

			// End entry
			func_callback(EXTCMD_END_ENTRY,IPCDATA(ipc),&packet);
		}

		// Set destination path
		SetGadgetValue(data->list,(data->function==JOIN)?GAD_JOIN_TO_FIELD:GAD_SPLIT_TO,(ULONG)data->dest);
	}

	// Split?
	if (data->function==SPLIT)
	{
		// Get first node
		current=(Att_Node *)data->join_list->list.lh_Head;

		// Fill out gadgets
		split_do_gadgets(data,current);

		// Arguments supplied?
		if (data->args)
		{
			// Stem?
			if (data->args->FA_Arguments[SPLITARG_STEM])
				SetGadgetValue(data->list,GAD_SPLIT_STEM,data->args->FA_Arguments[SPLITARG_STEM]);

			// Chunk size
			SetGadgetValue(data->list,GAD_SPLIT_INTO,*((ULONG *)data->args->FA_Arguments[SPLITARG_CHUNK]));

			// Auto-start
			start=1;
		}

		// Initial split settings
		else SetGadgetValue(data->list,GAD_SPLIT_INTO,16);
	}

	// Join
	else
	{
		// Display list
		join_add_file(data,0,-1);

		// Disable gadgets
		join_do_gadgets(data,1);
	}

	// Start automatically?
	if (start)
	{
		// Join?
		if (data->function==JOIN)
		{
			// Do join
			if (join_do_join(data)) quit_flag=1;
		}

		// Split
		else
		{
			// Do split
			if (split_do_split(data)!=-1) quit_flag=1;
		}
	}

	// Event loop
	FOREVER
	{
		struct IntuiMessage *msg;
		IPCMessage *imsg;

		// IPC messages?
		if (data->ipc)
		{
			while (imsg=(IPCMessage *)GetMsg(data->ipc->command_port))
			{
				// Abort?
				if (imsg->command==IPC_ABORT || imsg->command==IPC_QUIT)
				{
					quit_flag=1;
					ret=0;
				}
				IPC_Reply(imsg);
			}
		}

		// Appwindow
		if (data->app_window)
		{
			struct AppMessage *amsg;

			// Get messages
			while (amsg=(struct AppMessage *)GetMsg(data->app_port))
			{
				char name[256];
				short arg;

				// Go through arguments
				for (arg=0;arg<amsg->am_NumArgs;arg++)
				{
					// File?
					if (amsg->am_ArgList[arg].wa_Name &&
						*amsg->am_ArgList[arg].wa_Name)
					{
						// Get name
						GetWBArgPath(&amsg->am_ArgList[arg],name,256);

						// Add to list
						join_add_file(data,name,arg);
					}
				}

				// Finish add
				join_add_file(data,0,-1);

				// Reply to message
				ReplyMsg((struct Message *)amsg);
			}
		}

		// Intuition messages
		if (data->window)
		{
			while (msg=GetWindowMsg(data->window->UserPort))
			{
				struct IntuiMessage msg_copy;
				USHORT id=0;

				// Copy message and reply
				msg_copy=*msg;
				ReplyWindowMsg(msg);

				// Get gadget id
				if (msg_copy.Class==IDCMP_GADGETDOWN ||
					msg_copy.Class==IDCMP_GADGETUP)
				{
					id=((struct Gadget *)msg_copy.IAddress)->GadgetID;
				}

				// Look at class
				switch (msg_copy.Class)
				{
					// Close window
					case IDCMP_CLOSEWINDOW:
						quit_flag=1;
						break;


					// Gadget
					case IDCMP_GADGETUP:
						switch (id)
						{
							// Cancel
							case GAD_JOIN_CANCEL:
								quit_flag=1;
								break;


							// Something selected
							case GAD_JOIN_LISTER:

								// Enable gadgets
								join_do_gadgets(data,0);
								break;


							// Add
							case GAD_JOIN_ADD:

								// Add entry
								join_add(data);
								break;


							// Remove
							case GAD_JOIN_REMOVE:

								// Remove entry
								join_remove(data);
								break;


							// Clear
							case GAD_JOIN_CLEAR:

								// Clear list
								join_clear(data);
								break;


							// Move up/down
							case GAD_JOIN_MOVE_UP:
							case GAD_JOIN_MOVE_DOWN:

								// Move item
								join_move(data,id);
								break;


							// Split size
							case GAD_SPLIT_SIZES:
								{
									char *str;
									long size;

									// Custom?
									if (msg_copy.Code<1) break;

									// Get string
									str=GetString(locale,MSG_CHUNK_CUSTOM+msg_copy.Code);

									// Get size
									size=atoi(str);

									// Set field
									SetGadgetValue(data->list,GAD_SPLIT_INTO,size);
								}
								break;


							// Size changed
							case GAD_SPLIT_INTO:
								{
									char *str;
									long size,a;

									// Get size
									size=GetGadgetValue(data->list,GAD_SPLIT_INTO);

									// See if it matches a label
									for (a=MSG_CHUNK_FLOPPY_OFS;;a++)
									{
										// Get label
										str=GetString(locale,a);

										// Done?
										if (str[0]=='-')
										{
											a=MSG_CHUNK_CUSTOM;
											break;
										}

										// Match size?
										if (atoi(str)==size) break;
									}

									// Set cycle gadget
									SetGadgetValue(data->list,GAD_SPLIT_SIZES,a-MSG_CHUNK_CUSTOM);
								}
								break;


							// Join
							case GAD_JOIN_OK:

								// Do join
								if (join_do_join(data)) quit_flag=1;
								break;


							// Split
							case GAD_SPLIT_OK:
								{
									short res;

									// Do split
									if (!(res=split_do_split(data))) quit_flag=1;

									// Fail?
									if (res==-1) break;
								}

							// Skip
							case GAD_SPLIT_SKIP:

								// Get next
								if (current) current=(Att_Node *)current->node.ln_Succ;

								// Valid file?
								if (current && current->node.ln_Succ)
								{
									// Fill out gadgets
									split_do_gadgets(data,current);
									break;
								}

								// Finished
								quit_flag=1;
								break;
						}
						break;


					// Key press
					case IDCMP_RAWKEY:

						// Help?
						if (msg_copy.Code==0x5f &&
							!(msg_copy.Qualifier&VALID_QUALIFIERS))
						{
							// Valid main IPC?
							if (main_ipc)
							{
								// Set busy pointer
								SetWindowBusy(data->window);

								// Send help request
								IPC_Command(main_ipc,IPC_HELP,(1<<31),"Join",0,(struct MsgPort *)-1);

								// Clear busy pointer
								ClearWindowBusy(data->window);
							}
						}
					break;
				}
			}
		}

		if (quit_flag) break;

		Wait(
			((data->window)?(1<<data->window->UserPort->mp_SigBit):0)|
			((data->app_window)?(1<<data->app_port->mp_SigBit):0)|
			((data->ipc)?(1<<data->ipc->command_port->mp_SigBit):0));
	}

	// Free stuff
	join_free(data);
	return ret;
}


// Open join window
BOOL join_open(join_data *data)
{
	// Fill out new window
	data->new_win.parent=data->screen;
	data->new_win.dims=&data->win_dims;
	data->new_win.title=GetString(locale,(data->function==SPLIT)?MSG_SPLIT_TITLE:MSG_JOIN_TITLE);
	data->new_win.locale=locale;
	data->new_win.flags=WINDOW_SCREEN_PARENT|WINDOW_VISITOR|WINDOW_AUTO_KEYS|WINDOW_REQ_FILL;
	if (data->function==JOIN) data->new_win.flags|=WINDOW_SIZE_BOTTOM;

	// Default dimensions
	data->win_dims=(data->function==SPLIT)?split_window:join_window;

	// Open window
	if (!(data->window=OpenConfigWindow(&data->new_win)) ||
		!(data->list=AddObjectList(data->window,(data->function==SPLIT)?split_objects:join_objects)))
	{
		return 0;
	}

	// Add AppWindow
	if (data->app_port)
		data->app_window=AddAppWindowA(0,0,data->window,data->app_port,0);

	return 1;
}


// Close join display
void join_close(join_data *data)
{
	// Window open?
	if (data->window)
	{
		// Remove AppWindow
		if (data->app_window)
		{
			RemoveAppWindow(data->app_window);
			data->app_window=0;
		}

		// Close window
		CloseConfigWindow(data->window);
		data->window=0;
	}
}


// Free join data
void join_free(join_data *data)
{
	if (data)
	{
		// Close window
		join_close(data);

		// Free message port
		DeleteMsgPort(data->app_port);

		// Free list
		Att_RemList(data->join_list,0);

		// Close timer device
		if (data->TimerBase) CloseDevice((struct IORequest *)&data->timer_req);

		// Free arguments
		DisposeArgs(data->args);

		// Free data
		FreeVec(data);
	}
}


// Add file to join list
void join_add_file(join_data *data,char *file,short arg)
{
	// Detach list?
	if (arg==0) SetGadgetChoices(data->list,GAD_JOIN_LISTER,(APTR)~0);

	// Valid file?
	if (file)
	{
		// Add to list
		Att_NewNode(data->join_list,file,0,0);
	}

	// Re-attach list?
	if (arg==-1)
		SetGadgetChoices(data->list,GAD_JOIN_LISTER,data->join_list);
}


// Enable/disable gadgets
void join_do_gadgets(join_data *data,short state)
{
	DisableObject(data->list,GAD_JOIN_REMOVE,state);
	DisableObject(data->list,GAD_JOIN_MOVE_UP,state);
	DisableObject(data->list,GAD_JOIN_MOVE_DOWN,state);
}


// Remove entry
void join_remove(join_data *data)
{
	short item;
	Att_Node *node;

	// Get selection
	if ((item=GetGadgetValue(data->list,GAD_JOIN_LISTER))==-1 ||
		!(node=Att_FindNode(data->join_list,item)))
		return;

	// Remove list
	join_add_file(data,0,0);

	// Remove node
	Att_RemNode(node);

	// No selection
	SetGadgetValue(data->list,GAD_JOIN_LISTER,(ULONG)-1);

	// Attach list
	join_add_file(data,0,-1);

	// Disable gadgets
	join_do_gadgets(data,1);
}


// Clear list
void join_clear(join_data *data)
{
	// Remove list
	join_add_file(data,0,0);

	// Clear list
	Att_RemList(data->join_list,REMLIST_SAVELIST);

	// No selection
	SetGadgetValue(data->list,GAD_JOIN_LISTER,(ULONG)-1);

	// Attach list
	join_add_file(data,0,-1);
}


// Move item
void join_move(join_data *data,short id)
{
	short item;
	Att_Node *node,*swap;

	// Get selection
	if ((item=GetGadgetValue(data->list,GAD_JOIN_LISTER))==-1 ||
		!(node=Att_FindNode(data->join_list,item)))
		return;

	// Get node to swap with
	if (id==GAD_JOIN_MOVE_UP)
	{
		swap=(Att_Node *)node->node.ln_Pred;
		--item;
	}
	else
	{
		swap=(Att_Node *)node->node.ln_Succ;
		++item;
	}

	// Valid swap node?
	if (!swap->node.ln_Pred || !swap->node.ln_Succ)
		return;

	// Remove list
	join_add_file(data,0,0);

	// Swap nodes
	SwapListNodes((struct List *)data->join_list,(struct Node *)node,(struct Node *)swap);

	// Fix selection
	SetGadgetValue(data->list,GAD_JOIN_LISTER,item);

	// Attach list
	join_add_file(data,0,-1);
}


// Add to list
void join_add(join_data *data)
{
	char buf[256];
	struct FileRequester *req;

	// Make window busy
	SetWindowBusy(data->window);

	// Get requester pointer
	req=WINREQUESTER(data->window);

	// Show requester
	if (AslRequestTags(req,
		ASLFR_Window,data->window,
		ASLFR_TitleText,GetString(locale,MSG_JOIN_SELECT_FILE),
		ASLFR_InitialDrawer,data->source,
		TAG_END))
	{
		// Get path
		strcpy(buf,req->fr_Drawer);
		AddPart(buf,req->fr_File,256);

		// Add file
		join_add_file(data,buf,0);
		join_add_file(data,0,-1);

		// Save path
		strcpy(data->source,req->fr_Drawer);
	}

	// Unbusy
	ClearWindowBusy(data->window);
}


// varargs AslRequest()
BOOL __stdargs AslRequestTags(APTR req,Tag tag,...)
{
	return AslRequest(req,(struct TagItem *)&tag);
}


// Check filename
short join_check_filename(join_data *data)
{
	char *ptr;
	short ok=-1;

	// Get filename
	ptr=(char *)GetGadgetValue(data->list,GAD_JOIN_TO_FIELD);

	// Not empty?
	if (*ptr)
	{
		BPTR lock;
		struct FileInfoBlock __aligned fib;

		// See if file exists
		if (lock=Lock(ptr,ACCESS_READ))
		{
			// Examine it
			Examine(lock,&fib);
			UnLock(lock);

			// Is it a file?
			if (fib.fib_DirEntryType<0)
			{
				short res;

				// Show requester
				res=SimpleRequestTags(
					data->window,
					0,
					GetString(locale,MSG_REPLACE_RENAME_ABORT),
					GetString(locale,MSG_FILE_EXISTS),
					fib.fib_FileName);

				// Replace?
				if (res==1) ok=1;

				// Abort
				else
				if (res==0) ok=0;
			}

			// It's a directory, make sure it is properly terminated
			else AddPart(ptr,"",256);
		}

		// Doesn't exist
		else ok=1;
	}

	return ok;
}


// Do join
BOOL join_do_join(join_data *data)
{
	short ret;

	// No files?
	if (IsListEmpty((struct List *)data->join_list)) return 1;

	// Make window busy
	SetWindowBusy(data->window);

	// Check filename
	while ((ret=join_check_filename(data))==-1)
	{
		char buf[256];

		// Get existing name
		strcpy(buf,(char *)GetGadgetValue(data->list,GAD_JOIN_TO_FIELD));

		// Show requester
		if (!(ret=AsyncRequestTags(
			data->ipc,
			REQTYPE_SIMPLE,
			data->window,
			0,
			0,
			AR_Window,data->window,
			AR_Message,GetString(locale,MSG_ENTER_FILENAME),
			AR_Button,GetString(locale,MSG_OK),
			AR_Button,GetString(locale,MSG_CANCEL),
			AR_Buffer,buf,
			AR_BufLen,256,
			TAG_END))) break;

		// Set new name
		SetGadgetValue(data->list,GAD_JOIN_TO_FIELD,(ULONG)buf);
	}

	// Ok?
	if (ret) ret=join_join_files(data);

	// Clear busy
	ClearWindowBusy(data->window);
	return ret;
}

// Join files
BOOL join_join_files(join_data *data)
{
	BPTR in,out;
	APTR progress;
	short count,retcode=0;
	Att_Node *node;
	char *initial_buffer,*ptr;
	struct Library *TimerBase;

	// Get file count
	count=Att_NodeCount(data->join_list);

	// Get timer pointer
	TimerBase=data->TimerBase;

	// Allocate buffer
	if (!(initial_buffer=AllocVec(COPY_INITIAL_BUFFER,0)))
		return 0;

	// Open progress window
	progress=OpenProgressWindowTags(
		PW_Window,data->window,
		PW_Title,GetString(locale,MSG_JOINING_FILES),
		PW_Flags,PWF_FILENAME|PWF_FILESIZE|PWF_GRAPH|PWF_ABORT,
		PW_FileCount,count,
		TAG_END);

	// Open output file
	ptr=(char *)GetGadgetValue(data->list,GAD_JOIN_TO_FIELD);
	while (!(out=Open(ptr,MODE_NEWFILE)))
	{
		// Show error
		if (!(join_show_error(data,MSG_JOIN_ERROR_OPENING_OUTPUT,ptr,0)))
			break;
	}

	// Failed?
	if (!out)
	{
		CloseProgressWindow(progress);
		FreeVec(initial_buffer);
		return 0;
	}

	// Go through files
	for (node=(Att_Node *)data->join_list->list.lh_Head,count=1;
		node->node.ln_Succ;
		node=(Att_Node *)node->node.ln_Succ,count++)
	{
		struct FileInfoBlock __aligned fib;
		long buffer_size,total_size=0;
		char *file_buffer;
		ULONG copytime;
		BOOL abort=0;
		short ret;
		BOOL remove=0;
		long remove_pos;

		// Open file
		while (!(in=Open(node->node.ln_Name,MODE_OLDFILE)))
		{
			// Show error
			if ((ret=
				join_show_error(
					data,
					MSG_JOIN_ERROR_OPENING_INPUT,
					node->node.ln_Name,
					TRUE))!=1)
				break;
		}

		// Failed?
		if (!in) continue;

		// Examine file
		ExamineFH(in,&fib);

		// Set filename and size in progress indicator
		SetProgressWindowTags(
			progress,
			PW_FileName,fib.fib_FileName,
			PW_FileNum,count,
			PW_FileSize,fib.fib_Size<<1,
			TAG_END);

		// Get initial buffer
		buffer_size=COPY_INITIAL_BUFFER;
		file_buffer=initial_buffer;

		// Initial copy time setting
		copytime=750000;

		// Get current position in output file
		remove_pos=Seek(out,0,OFFSET_CURRENT);

		// Loop while data remains
		while (fib.fib_Size>0)
		{
			long read_size,write_size,old_buffersize,size;
			struct timeval start,end;
			BOOL new_buf=0;

			// Check abort
			if (CheckProgressAbort(progress))
			{
				abort=1;
				break;
			}

			// Remember old buffer size
			old_buffersize=buffer_size;

			// Get smaller buffer?
			if (copytime>COPY_HIGH_THRESH)
			{
				// Halve buffer size
				buffer_size>>=1;

				// Minimum 2k
				if (buffer_size<COPY_MIN_BUFFER)
					buffer_size=COPY_MIN_BUFFER;

				// Try for smaller buffer
				if (buffer_size!=old_buffersize) new_buf=1;
			}

			// Get larger buffer?
			else
			if (copytime<COPY_LOW_THRESH)
			{
				// Double buffer size
				buffer_size<<=1;
				new_buf=1;
			}

			// Want to try for new buffer?
			if (new_buf)
			{
				// Free existing buffer (unless it's the initial one)
				if (file_buffer!=initial_buffer)
					FreeVec(file_buffer);

				// Allocate new buffer
				if (!(file_buffer=AllocVec(buffer_size,0)))
				{
					// Failed, fall back to initial buffer
					file_buffer=initial_buffer;
					buffer_size=COPY_INITIAL_BUFFER;
				}
			}

			// Get size to read
			read_size=(fib.fib_Size>buffer_size)?buffer_size:fib.fib_Size;

			// Get current time
			if (TimerBase) GetSysTime(&start);

			// Read data
			while ((size=Read(in,file_buffer,read_size))<1)
			{
				short ret;

				// No error?
				if (size==0) break;

				// Show error
				if ((ret=join_show_error(
					data,
					MSG_JOIN_ERROR_READING,
					node->node.ln_Name,
					TRUE))!=1)
				{
					// Remove?
					if (ret==2) remove=1;

					// Abort
					else abort=1;
					break;
				}
			}

			// Fail?
			if (size<1) break;

			// Did we get back less than we asked for?
			if (size<read_size)
			{
				// Reduce file size by the difference
				fib.fib_Size-=read_size-size;
			}

			// Save read size
			read_size=size;

			// Add to total
			total_size+=size;

			// Update file progress
			SetProgressWindowTags(
				progress,
				PW_FileDone,total_size,
				TAG_END);

			// Check abort
			if (CheckProgressAbort(progress))
			{
				abort=1;
				break;
			}

			// Write data
			if ((write_size=Write(out,file_buffer,read_size))<read_size)
				break;

			// Got timer?
			if (TimerBase)
			{
				// Get current time
				GetSysTime(&end);

				// Calculate time that portion of the copy took
				SubTime(&end,&start);
				copytime=(end.tv_secs*1000000)+end.tv_micro;
			}

			// Add to total
			total_size+=write_size;

			// Update progress
			SetProgressWindowTags(
				progress,
				PW_FileDone,total_size,
				TAG_END);
		}

		// Free buffer
		if (file_buffer!=initial_buffer) FreeVec(file_buffer);

		// Close file
		Close(in);

		// Aborted?
		if (abort) break;

		// Remove?
		if (remove)
		{
			// Seek back to remove position
			Seek(out,remove_pos,OFFSET_BEGINNING);

			// Truncate file
			SetFileSize(out,0,OFFSET_CURRENT);
		}
	}

	// Success?
	if (!node->node.ln_Succ) retcode=1;

	// Close output file
	Close(out);

	// Free buffer
	FreeVec(initial_buffer);

	// Close progress
	CloseProgressWindow(progress);
	
	return retcode;
}


// Show error
short join_show_error(join_data *data,short msg,char *name,BOOL remove)
{
	char buf[256],fault[80],text[128],file[35];
	short err;

	// Get error text
	Fault((err=IoErr()),"",fault,80);
	get_trunc_filename(FilePart(name),file);
	lsprintf(text,GetString(locale,msg),file);

	// Build text
	lsprintf(buf,GetString(locale,MSG_JOIN_ERROR),text,err,fault);

	// Show requester
	return (short)AsyncRequestTags(
		data->ipc,
		REQTYPE_SIMPLE,
		data->window,
		0,
		0,
		AR_Window,data->window,
		AR_Message,buf,
		AR_Button,GetString(locale,(name)?MSG_JOIN_RETRY:MSG_OK),
		(remove)?AR_Button:TAG_IGNORE,(remove)?GetString(locale,MSG_REMOVE):0,
		(name)?AR_Button:TAG_IGNORE,GetString(locale,MSG_CANCEL),
		TAG_END);
}


// Fill out gadgets for split
void split_do_gadgets(join_data *data,Att_Node *node)
{
	// Got a filename?
	if (node && node->node.ln_Name)
	{
		char splitname[60],*ptr;

		// Set filename
		SetGadgetValue(data->list,GAD_SPLIT_FROM,(ULONG)node->node.ln_Name);

		// Get filename for stem
		stccpy(splitname,FilePart(node->node.ln_Name),25);

		// Look for a dot; strip after it
		for (ptr=splitname;*ptr;ptr++)
		{
			if (*ptr=='.')
			{
				*ptr=0;
				break;
			}
		}

		// Set stem
		SetGadgetValue(data->list,GAD_SPLIT_STEM,(ULONG)splitname);
	}
}


// Do split
short split_do_split(join_data *data)
{
	short ret;

	// Make window busy
	SetWindowBusy(data->window);

	// Update gadget values
	UpdateGadgetList(data->list);

	// Split files
	ret=split_split_file(data);

	// Make window unbusy
	ClearWindowBusy(data->window);
	return ret;
}

short split_split_file(join_data *data)
{
	char *path,*name,*stem,*buffer=0;
	long filesize,chunksize,buffersize,count=0,num,progtotal=0;
	struct FileInfoBlock __aligned fib;
	BPTR file,out,old,lock;
	char outname[60],device[40];
	APTR progress;
	BOOL abort=0,floppy=0,ram=0;
	struct DosList *dos;

	// Get strings
	name=(char *)GetGadgetValue(data->list,GAD_SPLIT_FROM);
	path=(char *)GetGadgetValue(data->list,GAD_SPLIT_TO);
	stem=(char *)GetGadgetValue(data->list,GAD_SPLIT_STEM);

	// Invalid path?
	if (!path || !*path ||
		!(lock=Lock(path,ACCESS_READ)))
	{
		// Error
		DisplayBeep(data->window->WScreen);
		ActivateStrGad(GADGET(GetObject(data->list,GAD_SPLIT_TO)),data->window);
		return -1;
	}

	// Get path device
	DeviceFromLock(lock,device);

	// RAM?
	if (strcmp(device,"RAM:")==0) ram=1;

	// Cd to path
	old=CurrentDir(lock);

	// Get DOS list entry
	if (dos=DeviceFromLock(lock,0))
	{
		struct FileSysStartupMsg *msg;

		// Get startup message
		if (msg=(struct FileSysStartupMsg *)BADDR(dos->dol_misc.dol_handler.dol_Startup))
		{
			char device[40];

			// Get device name
			BtoCStr((BPTR)msg->fssm_Device,device,32);

			// Trackdisk or CrossDOS?
			if (strcmp(device,"trackdisk.device")==0 ||
				strcmp(device,"mfm.device")==0) floppy=1;
		}
	}

	// Try to open file
	while (!(file=Open(name,MODE_OLDFILE)))
	{
		// Error
		if (!(join_show_error(data,MSG_SPLIT_ERROR_OPENING_FILE,name,0)))
		{
			// Failed
			UnLock(CurrentDir(old));
			return -1;
		}
	}

	// Examine file
	ExamineFH(file,&fib);
	filesize=fib.fib_Size;

	// Get chunk size
	if ((chunksize=GetGadgetValue(data->list,GAD_SPLIT_INTO)<<10)<1)
		chunksize=filesize;

	// Check chunksize isn't bigger than file
	if (chunksize>filesize)
		chunksize=filesize;

	// Get buffersize
	buffersize=chunksize;

	// Don't use more than a 64k buffer
	if (buffersize>65536)
		buffersize=65536;

	// Get buffer
	if (buffersize>0 && !(buffer=AllocVec(buffersize,0)))
	{
		// Forbid to do this
		Forbid();

		// Get buffer size
		buffersize=AvailMem(MEMF_LARGEST);

		// Get largest buffer
		buffer=AllocVec(buffersize,0);

		// Permit now
		Permit();

		// No buffer?
		if (!buffer)
		{
			// Error
			join_show_error(data,MSG_SPLIT_NO_MEMORY,0,0);
			Close(file);
			UnLock(CurrentDir(old));
			return -1;
		}
	}

	// Calculate number of files
	if (buffersize>0 && filesize>0)
	{
		num=UDivMod32(filesize,chunksize);
		if (num*chunksize<filesize) ++num;
	}
	else
		num=1;

	// Open progress window
	progress=OpenProgressWindowTags(
		PW_Window,data->window,
		PW_Title,GetString(locale,MSG_SPLITTING_FILE),
		PW_Flags,PWF_FILENAME|PWF_FILESIZE|PWF_GRAPH|PWF_ABORT,
		PW_FileCount,num,
		PW_FileName,fib.fib_FileName,
		PW_FileSize,filesize<<1,
		TAG_END);

	// Loop until file is fully split
	while (filesize>0)
	{
		long read;
		BOOL fail=0;
		struct InfoData __aligned info;
		long fileListEntries;
		long dataBlocks;
		long fileLists;
		long totalBlocks;

		// Build filename
		lsprintf(outname,"%s.%03ld",stem,count++);

		// Update progress window
		SetProgressWindowTags(progress,PW_FileNum,count,TAG_END);

		// Loop here (unless RAM)
		while (!fail && !ram)
		{
			// Examine current disk
			Info(lock,&info);

			// Size of this chunk
			read=(chunksize>filesize)?filesize:chunksize;

			// Calculate block size of file
			fileListEntries=(info.id_BytesPerBlock>>2)-56;
			dataBlocks=UDivMod32(read+info.id_BytesPerBlock-1,info.id_BytesPerBlock);
			fileLists=UDivMod32(dataBlocks+fileListEntries-1,fileListEntries);
			totalBlocks=dataBlocks+fileLists;

			// Won't fit?
			if (totalBlocks+info.id_NumBlocksUsed>info.id_NumBlocks)
			{
				// Floppy?
				while (floppy)
				{
					// Build text
					lsprintf(data->buf,GetString(locale,MSG_ENTER_DISK),device);

					// Show requester for next disk
					if (!(AsyncRequestTags(
						data->ipc,
						REQTYPE_SIMPLE,
						data->window,
						0,
						0,
						AR_Window,data->window,
						AR_Message,data->buf,
						AR_Button,GetString(locale,MSG_OK),
						AR_Button,GetString(locale,MSG_CANCEL),
						TAG_END)))
					{
						fail=1;
						abort=1;
						break;
					}

					// Change locks
					UnLock(CurrentDir(old));
					old=0;

					// Lock device
					if (lock=Lock(device,ACCESS_READ))
					{
						// CD to it
						old=CurrentDir(lock);
						break;
					}
				}

				// Show error if not floppy
				if (!floppy)
				{
					// Set error code
					SetIoErr(ERROR_DISK_FULL);

					// Show error
					if (!(join_show_error(data,MSG_JOIN_ERROR_OPENING_OUTPUT,outname,0)))
					{
						fail=1;
					}
				}
			}

			// Ok
			else break;
		}

		// Failed?
		if (fail) break;

		// Open file
		while (!(out=Open(outname,MODE_NEWFILE)))
		{
			// Show error
			if (!(join_show_error(data,MSG_JOIN_ERROR_OPENING_OUTPUT,outname,0)))
			{
				fail=1;
				break;
			}
		}

		// Failed?
		if (fail) break;

		// Do this chunk
		for (read=0;read<chunksize;)
		{
			long size;

			// Check abort
			if (CheckProgressAbort(progress))
			{
				abort=1;
				break;
			}

			// Get size to read
			size=buffersize;
			if (read+size>chunksize)
				size=chunksize-read;

			// Read some data
			while ((size=Read(file,buffer,size))<1)
			{
				// No error?
				if (size==0) break;

				// Show error
				if (!(join_show_error(data,MSG_JOIN_ERROR_READING,name,0)))
					break;
			}

			// Failed?
			if (size<1) break;

			// Update progress
			progtotal+=size;
			SetProgressWindowTags(progress,PW_FileDone,progtotal,TAG_END);

			// Write some data
			Write(out,buffer,size);

			// Increment read count
			read+=size;

			// Update progress
			progtotal+=size;
			SetProgressWindowTags(progress,PW_FileDone,progtotal,TAG_END);
		}

		// Close file
		Close(out);

		// Decrement remaining size
		filesize-=read;

		// Did we abort or fail?
		if (abort || (filesize>0 && read<chunksize))
			break;
	}

	// Close input file
	Close(file);

	// Free buffer
	FreeVec(buffer);

	// Close progress
	CloseProgressWindow(progress);

	// Restore directory
	if (old) UnLock(CurrentDir(old));
	return (short)((abort)?0:((filesize>0)?-1:1));
}


void get_trunc_filename(char *source,char *dest)
{
	if (!source)
		*dest=0;
	else
	{
		stccpy(dest,source,31);
		if (strlen(dest)<strlen(source))
			strcpy(dest+27,"...");
	}
}
