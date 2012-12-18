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

#include "update.h"
#include "dopusprog:position.h"

char *version="$VER: update.module 68.0 (3.10.98)";

int __asm __saveds L_Module_Entry(
	register __a0 struct List *files,
	register __a1 struct Screen *screen,
	register __a2 IPCData *ipc,
	register __a3 IPCData *main_ipc,
	register __d0 ULONG mod_id,
	register __d1 EXT_FUNC(func_callback))
{
	ULONG oldflags,flags=0;
	BPTR file;
	struct Window *window=0;
	BOOL old=0;

	// Check that directory exists
	if (!(file=Lock("dopus5:System",ACCESS_READ)))
	{
		// Create directory
		file=CreateDir("dopus5:System");
	}

	// Unlock lock
	UnLock(file);

	// Try to open new update file
	if (!(file=Open("dopus5:system/update-history",MODE_OLDFILE)))
	{
		// Open old file
		if (file=Open("dopus5:update-history",MODE_OLDFILE)) old=1;
	}

	// Got file?
	if (file)
	{
		// Read from old file
		Read(file,(char *)&flags,sizeof(ULONG));
		Close(file);
	}

	// Save flags
	oldflags=flags;

	// Delete old file
	if (old)
	{
		DeleteFile("dopus5:update-history");
		oldflags=0;
	}

	// Haven't done paths?
	if (!(flags&UPDATEF_DONE_PATHS))
	{
	}

	// Haven't done commands?
	if (!(flags&UPDATEF_DONE_COMMANDS))
	{
		// Create commands directory
		if (file=CreateDir("dopus5:Commands"))
		{
			// Unlock directory
			UnLock(file);

			// Set flag
			flags|=UPDATEF_DONE_COMMANDS;
		}
	}

	// Haven't done desktop?
	if (!(flags&UPDATEF_DONE_DESKTOP))
	{
		// Create desktop folder
		if (file=CreateDir("dopus5:Desktop"))
		{
			// Unlock directory
			UnLock(file);

			// Set flag
			flags|=UPDATEF_DONE_DESKTOP;
		}
	}

	// Haven't moved position-info?
	if (!(flags&UPDATEF_DONE_POSITION))
	{
		// Move position-info and ftp.config into System directory
		Rename("dopus5:position-info","dopus5:System/position-info");

		// Move ftp.config from root path if it's there
		if (!(Rename("dopus5:ftp.config","dopus5:System/ftp.config")))
		{
			// See if it has its own directory
			if (Rename("dopus5:ftp/ftp.config","dopus5:System/ftp.config"))
			{
				// Delete directory (will fail if not empty)
				DeleteFile("dopus5:ftp");
			}
		}

		// Set flag
		flags|=UPDATEF_DONE_POSITION;
	}

	// Haven't done leftouts?
	if (!(flags&UPDATEF_DONE_LEFTOUTS))
	{
		struct List list;
		APTR memory;

		// Open status window
		window=open_status(screen);

		// Read position-info file
		if (memory=read_position_info(&list))
		{
			// Convert leftouts
			if (update_do_leftouts(&list,memory))
				flags|=UPDATEF_DONE_LEFTOUTS;

			// Free memory
			FreeMemHandle(memory);
		}
	}

	// Haven't done groups?
	if (!(flags&UPDATEF_DONE_GROUPS))
	{
		// Open status window
		if (!window) window=open_status(screen);

		if (update_groups())
			flags|=UPDATEF_DONE_GROUPS;
	}

	// Haven't done storage?
	if (!(flags&UPDATEF_DONE_STORAGE))
	{
		// Open status window
		if (!window) window=open_status(screen);

		if (update_storage())
			flags|=UPDATEF_DONE_STORAGE;	
	}

	// Haven't done filetypes?
	if (!(flags&UPDATEF_DONE_FILETYPES))
	{
		// Open status window
		if (!window) window=open_status(screen);

		// This update does filetypes
		update_filetypes();

		// This one does the environment variable stuff
		update_envarc();

		// Set flag
		flags|=UPDATEF_DONE_FILETYPES;
	}

	// Haven't done path keys
	if (!(flags&UPDATEF_DONE_PATH_KEYS))
	{
		struct List list;
		APTR memory;

		// Open status window
		if (!window) window=open_status(screen);

		// Delete pathformat module
		DeleteFile("dopus5:modules/pathformat.module");

		// Read position-info file
		if (memory=read_position_info(&list))
		{
			// Convert path keys
			update_do_pathkeys(&list);

			// Free memory
			FreeMemHandle(memory);
		}

		// Set flag
		flags|=UPDATEF_DONE_PATH_KEYS;
	}

	// Haven't done theme stuff
	if (!(flags&UPDATEF_DONE_THEMES))
	{
		// Create sounds directory
		if (file=CreateDir("dopus5:Sounds"))
		{
			// Unlock directory
			UnLock(file);
		}

		// Create themes directory
		if (file=CreateDir("dopus5:Themes"))
		{
			// Unlock directory
			UnLock(file);
		}

		// Set flag
		flags|=UPDATEF_DONE_THEMES;
	}

	// Have flags changed?
	if (oldflags!=flags)
	{
		// Set bits to 'rwed'
		SetProtection("dopus5:system/update-history",0);

		// Open update file
		if (file=Open("dopus5:system/update-history",MODE_NEWFILE))
		{
			Write(file,(char *)&flags,sizeof(ULONG));
			Close(file);
		}
	}

	// Set bits to 'hr'
	SetProtection("dopus5:system/update-history",FIBF_WRITE|FIBF_EXECUTE|FIBF_DELETE|128);

	// Delete our own file
	DeleteFile("dopus5:modules/update.module");

	// Close status window
	if (window) CloseConfigWindow(window);
	return 1;
}

struct Window *open_status(struct Screen *screen)
{
	return OpenStatusWindow(
		GetString(locale,MSG_UPDATE_TITLE),
		GetString(locale,MSG_PLEASE_WAIT),
		screen,
		0,
		WINDOW_NO_CLOSE|WINDOW_NO_ACTIVATE);
}


// Convert leftouts
BOOL update_do_leftouts(struct List *list,APTR memory)
{
	struct DosList *dos;
	short count=0;
	BOOL asked=0,dowb=1;

	// Lock dos list
	dos=LockDosList(LDF_VOLUMES|LDF_READ);

	// Go through dos list
	while (dos=NextDosEntry(dos,LDF_VOLUMES))
	{
		BPTR old,lock;
		char buf[40];

		// Get volume name
		lsprintf(buf,"%b:",dos->dol_Name);

		// Lock device
		if (lock=Lock(buf,ACCESS_READ))
		{
			APTR file;
	
			// CD to this volume
			old=CurrentDir(lock);

			// Look for .dopusdrop file
			if (file=OpenBuf(".dopusdrop",MODE_OLDFILE,4096))
			{
				// Convert left-outs
				count+=update_convert_leftouts(file,memory,list);

				// Close file
				CloseBuf(file);

				// Delete file
				DeleteFile(".dopusdrop");
			}

			// Allowed read workbench-leftouts?
			if (dowb)
			{
				// See if workbench leftout file exists
				if (file=OpenBuf(".backdrop",MODE_OLDFILE,4096))
				{
					// Haven't asked yet?
					if (!asked)
					{
						// Show requester
						dowb=SimpleRequestTags(0,
							GetString(locale,MSG_UPDATE_TITLE),
							GetString(locale,MSG_YES_NO),
							GetString(locale,MSG_UPDATE_CONVERT_WB),0);

						// Set flag
						asked=1;
					}

					// Ok to do Workbench left-outs?
					if (dowb)
					{
						// Convert left-outs
						count+=update_convert_leftouts(file,memory,list);
					}

					// Close file
					CloseBuf(file);
				}
			}

			// Restore CD
			UnLock(CurrentDir(old));
		}
	}

	// Unlock dos list
	UnLockDosList(LDF_VOLUMES|LDF_READ);

	// Added anything?
	if (count)
	{
		APTR iff;
		struct Node *node;

		// Open file
		if (!(iff=IFFOpen("dopus5:System/position-info",IFF_WRITE,ID_OPUS)))
			return 0;

		// Go through entries
		for (node=list->lh_Head;node->ln_Succ;node=node->ln_Succ)
		{
			// Valid path, or AppIcon?
			if ((node->ln_Name && *node->ln_Name) ||
				node->ln_Type==PTYPE_APPICON)
			{
				ULONG id=0;
				short size=0;

				// Position?
				if (node->ln_Type==PTYPE_POSITION)
				{
					// Get id and chunk size
					id=ID_POSI;
					size=sizeof(position_rec)-sizeof(struct Node);
				}

				// Left-out?
				else
				if (node->ln_Type==PTYPE_LEFTOUT)
				{
					// Get id and chunk size
					id=ID_LOUT;
					size=sizeof(leftout_record)-sizeof(struct Node);
				}

				// AppIcon?
				else
				if (node->ln_Type==PTYPE_APPICON)
				{
					// Get id and chunk size
					id=ID_ICON;
					size=sizeof(leftout_record)-sizeof(struct Node);
				}

				// Write chunk
				if (!(IFFWriteChunk(iff,(APTR)(node+1),id,size+((node->ln_Name)?strlen(node->ln_Name):0))))
					break;
			}
		}

		// Close file
		IFFClose(iff);
	}

	return 1;
}


BOOL update_groups(void)
{
	struct AnchorPath *anchor;
	long error;
	unsigned char newstuff[10];
	short depth=0;

	// Allocate anchor
	if (!(anchor=AllocVec(sizeof(struct AnchorPath)+256,MEMF_CLEAR)))
		return 0;

	// Build new-stuff to write
	newstuff[0]='\n';
	newstuff[1]=0xff;
	newstuff[2]=0xff;
	newstuff[3]=0xff;
	newstuff[4]=0xff;
	newstuff[5]=0;
	newstuff[6]=0;
	newstuff[7]=0;
	newstuff[8]=0;

	// Initialise anchor
	anchor->ap_Strlen=256;

	// Start match
	error=MatchFirst("dopus5:groups/#?",anchor);
	while (!error)
	{
		// Directory?
		if (anchor->ap_Info.fib_DirEntryType>0)
		{
			// New directory?
			if (!(anchor->ap_Flags&APF_DIDDIR))
			{
				// Set bit to enter directory
				anchor->ap_Flags|=APF_DODIR;
				++depth;
			}

			// Old directory
			else
			{
				// Clear bit
				anchor->ap_Flags&=~APF_DIDDIR;
				--depth;
			}
		}

		// File, not in 'root' directory
		else
		if (depth>0)
		{
			short len;
			BPTR file;

			// Icon?
			if ((len=strlen(anchor->ap_Info.fib_FileName))>5 &&
				stricmp(anchor->ap_Info.fib_FileName+len-5,".info")==0)
			{
				// Delete the icon
				DeleteFile(anchor->ap_Buf);
			}

			// Normal file, try to open
			else
			if (file=Open(anchor->ap_Buf,MODE_OLDFILE))
			{
				char buf[264];
				short len;

				// Read data
				len=Read(file,buf,260);
				buf[len]=0;

				// Close file
				Close(file);

				// Got data?
				if (len>5)
				{
					// Re-create file
					if (file=Open(anchor->ap_Buf,MODE_NEWFILE))
					{
						// Write data
						Write(file,buf,len);
						Write(file,newstuff,9);
						Close(file);
					}
				}
			}
		}

		// Get next
		error=MatchNext(anchor);
	}

	// Clean up
	MatchEnd(anchor);
	FreeVec(anchor);

	return 1;
}


// Convert left-out file
short update_convert_leftouts(APTR file,APTR memory,struct List *list)
{
	char ch;
	short pos=0;
	char buf[512];
	short count=0;

	// Read entries in file
	while (ReadBuf(file,&ch,1)==1)
	{
		// End of line?
		if (ch=='\n')
		{
			BPTR lout;

			// Null-terminate name
			buf[pos]=0;

			// Lock left-out
			if (lout=Lock(buf,ACCESS_READ))
			{
				leftout_record *left;
				struct List *search;

				// Get full pathname
				DevNameFromLock(lout,buf,512);

				// See if its already in the list
				search=list;
				while (left=(leftout_record *)FindNameI(search,buf))
				{
					// Left out?
					if (left->node.ln_Type==PTYPE_LEFTOUT)
						break;

					// Keep searching
					search=(struct List *)left;
				}

				// Not already in list?
				if (!left)
				{
					// Allocate new entry
					if (left=AllocMemH(memory,sizeof(leftout_record)+strlen(buf)))
					{
						// Fill out entry
						left->flags|=LEFTOUTF_NO_POSITION;
						stccpy(left->icon_label,FilePart(buf),32);
						strcpy(left->name,buf);
						left->node.ln_Name=left->name;
						left->node.ln_Type=PTYPE_LEFTOUT;

						// Add to list
						AddTail(list,(struct Node *)left);
						++count;
					}
				}

				// Unlock file
				UnLock(lout);
			}

			// Reset position
			pos=0;
		}

		// Otherwise, store in buffer
		else
		if (pos<510) buf[pos++]=ch;
	}

	return count;
}

// Update storage directory
BOOL update_storage(void)
{
	BPTR old,lock,dir;
	struct DiskObject *icon;
	struct FileInfoBlock __aligned info;

	// Lock storage directory
	if (!(lock=Lock("dopus5:storage",ACCESS_READ)))
	{
		// Doesn't exist?
		if (IoErr()==ERROR_OBJECT_NOT_FOUND)
		{
			// Try to create it
			lock=CreateDir("dopus5:storage");
		}

		// Fail?
		if (!lock) return 0;
	}

	// CD to storage
	old=CurrentDir(lock);

	// Get directory icon
	icon=GetDefDiskObject(WBDRAWER);

	// Make modules directory
	if (dir=CreateDir("Modules"))
	{
		// Write icon
		if (icon) PutDiskObject("Modules",icon);
		UnLock(dir);
	}

	// Make filetype directory
	if (dir=CreateDir("Filetypes"))
	{
		short len,res;

		// Write icon
		if (icon) PutDiskObject("Filetypes",icon);
		UnLock(dir);

		// Examine directory
		Examine(lock,&info);

		// Go through directory
		res=ExNext(lock,&info);
		while (res)
		{
			short type;
			char filename[60];

			// Store name and type
			stccpy(filename,info.fib_FileName,60);
			type=info.fib_DirEntryType;

			// Get next
			res=ExNext(lock,&info);

			// File, not an icon?
			if (type<0 && ((len=strlen(filename))<6 || strcmpi(filename+len-5,".info")!=0))
			{
				ULONG pad[4];
				BPTR file;
				BOOL ok=0;

				// Open file
				if (file=Open(filename,MODE_OLDFILE))
				{
					// Read data
					if (Read(file,(char *)pad,sizeof(pad))==sizeof(pad))
					{
						// Filetype?
						if (pad[0]==ID_FORM &&
							pad[2]==ID_OPUS &&
							pad[3]==ID_TYPE) ok=1;
					}

					// Close file
					Close(file);
				}

				// Ok to move?
				if (ok)
				{
					char name[80];

					// Build name
					strcpy(name,"Filetypes/");
					strcat(name,filename);

					// Do rename
					if (Rename(filename,name))
					{
						// Build icon names
						strcat(filename,".info");
						strcat(name,".info");

						// Rename icon
						Rename(filename,name);
					}
				}
			}
		}
	}

	// Free icon
	if (icon) FreeDiskObject(icon);

	// Restore cd
	UnLock(CurrentDir(old));

	return 1;
}


// Delete 'default' filetypes
void update_filetypes(void)
{
	if (DeleteFile("dopus5:filetypes/Default"))
		DeleteDiskObject("dopus5:filetypes/Default");
	if (DeleteFile("dopus5:storage/filetypes/Default"))
		DeleteDiskObject("dopus5:storage/filetypes/Default");
}


// Update environment variable stuff
void update_envarc(void)
{
	// Do this for env: and envarc:
	update_envarc_do("env:");
	update_envarc_do("envarc:");
}

void update_envarc_do(char *path)
{
	BPTR lock,oldcd,dir;

	// Go to directory
	if (!(lock=Lock(path,ACCESS_READ)))
		return;

	// Change dir
	oldcd=CurrentDir(lock);

	// Check dir doesn't exist already
	if (dir=Lock("dopus",ACCESS_READ))
	{
		struct FileInfoBlock __aligned fib;

		// Examine dir
		Examine(dir,&fib);
		UnLock(dir);

		// A directory?
		if (fib.fib_DirEntryType>0)
		{
			// Nothing to do
			UnLock(CurrentDir(oldcd));
			return;
		}
	}

	// Make dopus directory
	if (dir=CreateDir("dopus_temp"))
	{
		// Shift things into there
		Rename("dopus","dopus_temp/dopus");
		Rename("dopus_read","dopus_temp/Text Viewer");
		Rename("dopus_font","dopus_temp/Font Viewer");
		Rename("Icon Clock","dopus_temp/Icon Clock");
		Rename("dopus_show","dopus_temp/ShowUseDatatypesFirst");
		Rename("dopus_print","dopus_temp/Print");

		// Unlock directory
		UnLock(dir);

		// Rename directory
		Rename("dopus_temp","DOpus");
	}

	// Restore CD
	UnLock(CurrentDir(oldcd));
}


// Read position-info file
APTR read_position_info(struct List *list)
{
	APTR memory;
	APTR iff;

	// Allocate memory handle
	if (!(memory=NewMemHandle(4096,1024,MEMF_CLEAR)))
		return 0;

	// Initialise list
	NewList(list);

	// Open position info file
	if (iff=IFFOpen("dopus5:System/position-info",IFF_READ,ID_OPUS))
	{
		ULONG id;

		// Read file
		while (id=IFFNextChunk(iff,0))
		{
			struct Node *entry;

			// Valid chunk?
			if (id!=ID_POSI && id!=ID_LOUT && id!=ID_ICON && id!=ID_STRT)
				continue;

			// Allocate record
			if (!(entry=AllocMemH(memory,IFFChunkSize(iff)+sizeof(struct Node))))
				continue;

			// Read chunk data
			IFFReadChunkBytes(iff,(APTR)(entry+1),-1);

			// Set type and name pointer
			if (id==ID_POSI)
			{
				entry->ln_Type=PTYPE_POSITION;
				entry->ln_Name=((position_rec *)entry)->name;
			}
			else
			if (id==ID_LOUT)
			{
				entry->ln_Type=PTYPE_LEFTOUT;
				entry->ln_Name=((leftout_record *)entry)->name;
			}
			else
			if (id==ID_ICON)
			{
				entry->ln_Type=PTYPE_APPICON;
				entry->ln_Name=((leftout_record *)entry)->name;
			}

			// Add to list
			AddTail(list,entry);
		}

		// Close file
		IFFClose(iff);
	}

	return memory;
}


// Convert path keys
void update_do_pathkeys(struct List *list)
{
	Cfg_ButtonBank *bank;
	struct Node *node;

	// Check list isn't empty
	if (IsListEmpty(list)) return;

	// Try to open hotkeys bank
	if (!(bank=OpenButtonBank("dopus5:buttons/hotkeys")))
	{
		// Create a new bank
		if (!(bank=NewButtonBank(0,0))) return;

		// Initialise bank
		strcpy(bank->window.name,"Hotkeys");
		bank->window.pos.Left=-1;
		bank->window.pos.Width=128;
		bank->window.pos.Height=-1;
		bank->window.columns=1;
		bank->window.rows=0;
	}

	// Go through list
	for (node=list->lh_Head;node->ln_Succ;node=node->ln_Succ)
	{
		position_rec *pos;
		Cfg_Button *button;	
		Cfg_ButtonFunction *func;
		Cfg_Instruction *ins;
		char label[400],*ptr;

		// Position?
		if (node->ln_Type!=PTYPE_POSITION)
			continue;

		// Valid path?
		if (!node->ln_Name || !*node->ln_Name)
			continue;

		// Get pointer
		pos=(position_rec *)node;

		// No key set?
		if (pos->code==0xffff) continue;

		// Copy path
		strcpy(label+80,node->ln_Name);

		// Get pointer to end of path
		ptr=label+79+strlen(label+80);

		// Strip trailing slash
		if (*ptr=='/') *ptr=0;

		// Get pointer to filename
		if (!(ptr=FilePart(label+80)) || !*ptr) ptr=label+80;

		// Build label
		lsprintf(label,GetString(locale,MSG_READ_DIR_BUTTON),ptr);

		// Create a button
		if (!(button=NewButtonWithFunc(bank->memory,label,FTYPE_LEFT_BUTTON)))
			continue;

		// Get function
		func=(Cfg_ButtonFunction *)button->function_list.mlh_Head;

		// Build command
		strcpy(label,"ScanDir ");

		// New lister?
		if (pos->flags&POSITIONF_OPEN_NEW)
			strcat(label,"NEW ");

		// Mode
		strcat(label,"MODE=");

		// Icon action/icon/name
		if (pos->flags&POSITIONF_ICON_ACTION)
			strcat(label,"action ");
		else
		if (pos->flags&POSITIONF_ICON)
			strcat(label,"icon ");
		else
			strcat(label,"name ");

		// Show all?
		if (pos->flags&POSITIONF_ICON &&
			pos->flags&POSITIONF_SHOW_ALL)
			strcat(label,"SHOWALL ");

		// Add path
		strcat(label,node->ln_Name);

		// Create instruction
		if (ins=NewInstruction(bank->memory,INST_COMMAND,label))
			AddTail((struct List *)&func->instructions,(struct Node *)ins);

		// Set key info
		func->function.code=pos->code;
		func->function.qual=pos->qual;
		func->function.qual_mask=pos->qual_mask;
		func->function.qual_same=pos->qual_same;

		// Set flags
		func->function.flags2=FUNCF2_HOTKEY_FUNC|FUNCF2_VALID_IX;

		// Add button to list
		AddTail(&bank->buttons,&button->node);

		// Increment row count
		++bank->window.rows;
	}

	// Any buttons in bank?
	if (bank->window.rows>0)
	{
		// Save bank
		SaveButtonBank(bank,"dopus5:buttons/hotkeys");
	}

	// Free bank
	CloseButtonBank(bank);
}
