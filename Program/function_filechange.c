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

#include "dopus.h"

// Find a list of file changes for a path
FileChangeList *function_find_filechanges(
	FunctionHandle *handle,
	FileChangeList *start,
	char *path,
	Lister *lister,
	short *substr)
{
	FileChangeList *list;

	// Clear substring flag
	if (substr) *substr=0;

	// Start at beginning?
	if (!start) start=(FileChangeList *)handle->filechange.lh_Head;
	else start=(FileChangeList *)start->node.ln_Succ;

	// Search list
	for (list=start;
		list->node.ln_Succ;
		list=(FileChangeList *)list->node.ln_Succ)
	{
		// Path to match?
		if (path && *path && *list->path)
		{
			// Match on path
			if (stricmp(path,list->path)==0) return list;

			// Accept a sub-string?
			if (substr)
			{
				// Match on sub-string
				if (strnicmp(path,list->path,strlen(list->path))==0)
				{
					*substr=1;
					return list;
				}
			}
		}

		// Match lister pointer
		else
		if (list->lister==lister) return list;
	}

	return 0;
}


// Add a path to the file change list
FileChangeList *function_add_filechanges(
	FunctionHandle *handle,
	char *path,
	Lister *lister)
{
	FileChangeList *list;

	// Allocate new list
	if (!(list=AllocMemH(handle->memory,sizeof(FileChangeList)+strlen(path))))
		return 0;

	// Initialise
	list->node.ln_Name=list->path;
	NewList((struct List *)&list->files);

	// Path supplied?
	if (path) strcpy(list->path,path);

	// Store lister pointer
	list->lister=lister;

	// Add to list
	AddTail(&handle->filechange,&list->node);

	return list;
}


// Add a file to lists
FileChange *function_filechange_addfile(
	FunctionHandle *handle,
	char *path,
	struct FileInfoBlock *info,
	NetworkInfo *network,
	Lister *lister)
{
	FileChangeList *list;
	FileChange *change;

	// Find list for this path, add if not found
	if (!(list=function_find_filechanges(handle,0,path,lister,0)) &&
		!(list=function_add_filechanges(handle,path,lister))) return 0;

	// Get new change entry
	if (!(change=AllocMemH(handle->memory,
		sizeof(FileChange)+
		strlen(info->fib_FileName)+
		strlen(info->fib_Comment)+1))) return 0;

	// Network information?
	if (network &&
		(change->fib_Network=AllocMemH(handle->memory,sizeof(NetworkInfo))))
	{
		// Copy it
		CopyMem((char *)network,(char *)change->fib_Network,sizeof(NetworkInfo));
	}

	// Set type
	change->node.ln_Type=FCTYPE_ADD;

	// Fill out entry
	change->fib_Size=info->fib_Size;
	change->fib_DirEntryType=info->fib_DirEntryType;
	change->fib_Date=info->fib_Date;
	change->fib_Protection=info->fib_Protection;

	// Copy name
	strcpy(change->fib_FileName,info->fib_FileName);
	change->node.ln_Name=change->fib_FileName;

	// Got a comment?
	if (info->fib_Comment[0])
	{
		// Copy comment
		change->fib_Comment=change->node.ln_Name+strlen(change->fib_FileName)+1;
		strcpy(change->fib_Comment,info->fib_Comment);
	}

	// Add to end of list
	AddTail((struct List *)&list->files,&change->node);
	return change;
}


// Add a file to lists (from filename)
FileChange *function_filechange_loadfile(
	FunctionHandle *handle,
	char *path,
	char *name,
	short flags)
{
	char *buffer;
	BPTR lock;
	struct FileInfoBlock __aligned fib;
	FileChange *change=0;
	short len;

	// Allocate buffer
	len=strlen(path)+strlen(name)+((flags&FFLF_ICON)?7:2);
	if (!(buffer=AllocVec(len+1,0))) return 0;

	// Build path name
	strcpy(buffer,path);
	AddPart(buffer,name,len);
	if (flags&FFLF_ICON && !isicon(name)) strcat(buffer,".info");

	// Deferred?
	if (flags&FFLF_DEFERRED)
	{
		struct FileInfoBlock fib;

		// Initialise dummy fib
		stccpy(fib.fib_FileName,name,108);
		fib.fib_Comment[0]=0;

		// Add change
		if (change=function_filechange_addfile(handle,path,&fib,0,0))
		{
			// Set type
			change->node.ln_Type=FCTYPE_LOAD;
		}
	}

	// Lock file
	else
	if (lock=Lock(buffer,ACCESS_READ))
	{
		// Examine file
		Examine(lock,&fib);
		UnLock(lock);

		// Add to lister
		change=function_filechange_addfile(handle,path,&fib,0,0);
	}

	// Allowed to fail?
	else
	if (flags&FFLF_RELOAD)
	{
		// Add a delete command
		change=function_filechange_delfile(handle,path,FilePart(buffer),0,0);
	}

	// Free buffer
	FreeVec(buffer);

	return change;
}


// Add a file for reloading
void function_filechange_reloadfile(
	FunctionHandle *handle,
	char *path,
	char *name,
	short flags)
{
	FileChange *change;

	// Add change to load the file
	if (!(change=function_filechange_loadfile(handle,path,name,FFLF_RELOAD|flags)))
		return;

	// Change type
	if (change->node.ln_Type==FCTYPE_ADD)
		change->node.ln_Type=FCTYPE_RELOAD;
}


// Delete a file to lists
FileChange *function_filechange_delfile(
	FunctionHandle *handle,
	char *path,
	char *name,
	Lister *lister,
	BOOL tail)
{
	FileChangeList *list;
	FileChange *change;

	// Find list for this path, add if not found
	if (!(list=function_find_filechanges(handle,0,path,lister,0)) &&
		!(list=function_add_filechanges(handle,path,lister))) return 0;

	// Get new change entry
	if (!(change=AllocMemH(handle->memory,
		sizeof(FileChange)+
		strlen(name)))) return 0;

	// Set type
	change->node.ln_Type=FCTYPE_DEL;

	// Copy name
	stccpy(change->fib_FileName,name,108);
	change->node.ln_Name=change->fib_FileName;

	// Add to start or end of list
	if (tail)
		AddTail((struct List *)&list->files,&change->node);
	else
		AddHead((struct List *)&list->files,&change->node);

	return change;
}


// Add a size update
FileChange *function_filechange_modify(
	FunctionHandle *handle,
	char *path,
	char *name,
	Tag tag1,...)
{
	FileChangeList *list;
	FileChange *change;
	struct TagItem *tags;

	// Get tag pointer
	tags=(struct TagItem *)&tag1;

	// Find list for this path, add if not found
	if (!(list=function_find_filechanges(handle,0,path,0,0)) &&
		!(list=function_add_filechanges(handle,path,0))) return 0;

	// Get new change entry
	if (!(change=AllocMemH(handle->memory,
		sizeof(FileChange)+
		82+
		strlen(name)))) return 0;

	// Copy name
	stccpy(change->fib_FileName,name,108);
	change->node.ln_Name=change->fib_FileName;

	// Get comment pointer
	change->fib_Comment=change->node.ln_Name+strlen(change->node.ln_Name)+1;

	// Set type
	change->node.ln_Type=FCTYPE_MODIFY;

	// Go through tags
	while (tags->ti_Tag!=TAG_END)
	{
		// Ignore?
		if (tags->ti_Tag==TAG_IGNORE)
		{
			// Get next
			++tags;
			continue;
		}

		// Look at change
		switch (tags->ti_Tag)
		{
			// Size
			case FM_Size:
				change->flags|=FMF_SIZE;
				change->fib_Size=tags->ti_Data;
				break;

			// Date
			case FM_Date:
				change->flags|=FMF_DATE;
				change->fib_Date=*((struct DateStamp *)tags->ti_Data);
				break;

			// Protect
			case FM_Protect:
				change->flags|=FMF_PROTECT;
				change->fib_Protection=tags->ti_Data;
				break;

			// Comment
			case FM_Comment:
				change->flags&=~FMF_NAME;
				change->flags|=FMF_COMMENT;
				stccpy(change->fib_Comment,(char *)tags->ti_Data,80);
				break;

			// Name
			case FM_Name:
				change->flags&=~FMF_COMMENT;
				change->flags|=FMF_NAME;
				stccpy(change->fib_Comment,(char *)tags->ti_Data,80);
				break;
		}

		// Get next tag
		++tags;
	}

	// Add to list
	AddTail((struct List *)&list->files,&change->node);
	return change;
}


// Change a directory name
FileChange *function_filechange_rename(
	FunctionHandle *handle,
	char *path,
	char *name)
{
	FileChangeList *list;
	FileChange *change;

	// Find list for this path, add if not found
	if (!(list=function_find_filechanges(handle,0,path,0,0)) &&
		!(list=function_add_filechanges(handle,path,0))) return 0;

	// Get new change entry
	if (!(change=AllocMemH(handle->memory,sizeof(FileChange)+strlen(name))))
		return 0;

	// Copy name
	stccpy(change->fib_FileName,name,108);

	// Set type
	change->node.ln_Type=FCTYPE_RENAME;

	// Add to list
	AddTail((struct List *)&list->files,&change->node);
	return change;
}


// Do file list changes
void function_filechange_do(FunctionHandle *handle,BOOL strip)
{
	IPCData *ipc;
	Lister *lister;

	// Lock lister list
	lock_listlock(&GUI->lister_list,FALSE);

	// Go through listers
	for (ipc=(IPCData *)GUI->lister_list.list.lh_Head;
		ipc->node.mln_Succ;
		ipc=(IPCData *)ipc->node.mln_Succ)
	{
		BackdropInfo *info;
		short substr;
		BOOL show=0;
		ULONG ref_flags=REFRESHF_SLIDERS|REFRESHF_ICONS|REFRESHF_STATUS;
		FileChangeList *list=0;
		DirEntry *show_file=0;

		// Get lister
		lister=IPCDATA(ipc);

		// If lister has a custom buffer, skip it
		if (lister->cur_buffer->buf_CustomHandler[0])
			continue;

		// Get backdrop pointer
		info=lister->backdrop_info;

		// Any changes for this path?
		while (list=function_find_filechanges(handle,list,lister->cur_buffer->buf_Path,lister,&substr))
		{
			FileChange *change;
			DirBuffer *buffer;
			long flags=SEMF_EXCLUSIVE;

			// Increment count in list if not a sub-string
			if (!substr) ++list->count;

			// Get buffer pointer
			buffer=lister->cur_buffer;

			// If we don't actually own this lister, only attempt to lock the buffer
			if (lister->locker_ipc!=handle->ipc) flags|=SEMF_ATTEMPT;

			// Lock this lister's buffer (if we can)
			if (GetSemaphore(&buffer->semaphore,flags,0))
			{
				// Go through changes
				for (change=(FileChange *)list->files.mlh_Head;
					change->node.ln_Succ;
					change=(FileChange *)change->node.ln_Succ)
				{
					BOOL del_ok=0;

					// If this is a sub-string, all we can accept is a rename
					if (substr &&
						change->node.ln_Type!=FCTYPE_RENAME) continue;

					// Increment count in change
					++change->count;

					// Rename a directory
					if (change->node.ln_Type==FCTYPE_RENAME)
					{
						// Try to rename buffer
						if (strreplace(buffer->buf_Path,list->path,change->fib_FileName,1))
						{
							char *old_path_path,*new_path_path;
							short len=0;

							// Get pointer to after colons
							old_path_path=strchr(list->path,':')+1;
							new_path_path=strchr(change->fib_FileName,':')+1;

							// Replace part in expanded path
							strreplace(
								strchr(buffer->buf_ExpandedPath,':')+1,
								old_path_path,
								new_path_path,1);

							// Is buffer actually showing the path that changed?
							if (stricmp(buffer->buf_Path,change->fib_FileName)==0)
							{
								char *ptr;

								// Get pointer to end of filename
								ptr=change->fib_FileName+strlen(change->fib_FileName)-1;

								// Strip trailing slash
								if (*ptr=='/') *ptr=0;
								else ptr=0;

								// Copy object name
								stccpy(buffer->buf_ObjectName,FilePart(change->fib_FileName),GUI->def_filename_length-1);
								len=-1;

								// Restore slash
								if (ptr) *ptr='/';
							}

							// Refresh path field
							ref_flags|=REFRESHF_NAME|REFRESHF_PATH;

							// Refresh title
							if (len==-1) ref_flags|=REFRESHF_UPDATE_NAME;

							// Set show flag
							show=1;
						}

						// Can only be this for a sub-string
						continue;
					}

					// Load a new file?
					if (change->node.ln_Type==FCTYPE_LOAD)
					{
						char buf[512];
						BPTR lock;
						struct FileInfoBlock __aligned fib;

						// Build path
						strcpy(buf,buffer->buf_Path);
						AddPart(buf,change->fib_FileName,512);

						// Try to lock file
						if (lock=Lock(buf,ACCESS_READ))
						{
							// Get info
							Examine(lock,&fib);
							UnLock(lock);

							// Copy real file data
							change->fib_Size=fib.fib_Size;
							change->fib_DirEntryType=fib.fib_DirEntryType;
							change->fib_Date=fib.fib_Date;
							change->fib_Protection=fib.fib_Protection;

							// Need to allocate buffer for comment
							if (fib.fib_Comment[0] &&
								(change->fib_Comment=AllocMemH(handle->memory,strlen(fib.fib_Comment))))
								strcpy(change->fib_Comment,fib.fib_Comment);

							// Change type to reload
							change->node.ln_Type=FCTYPE_RELOAD;
						}
					}

					// Modify something
					if (change->node.ln_Type==FCTYPE_MODIFY)
					{
						DirEntry *entry;

						// Find entry in buffer
						if ((entry=find_entry(&buffer->entry_list,change->fib_FileName,0,buffer->more_flags&DWF_CASE)) ||
							(entry=find_entry(&buffer->reject_list,change->fib_FileName,0,buffer->more_flags&DWF_CASE)))
						{
							// Modify size?
							if (change->flags&FMF_SIZE)
							{
								// Has size changed?
								if (entry->de_Size!=change->fib_Size ||
									entry->de_Flags&ENTF_NO_SIZE)
								{
									// Clear size out
									buffer->buf_TotalBytes[0]-=entry->de_Size;

									// Set new size
									entry->de_Size=change->fib_Size;
									buffer->buf_TotalBytes[0]+=entry->de_Size;

									// Clear 'no size' flag
									entry->de_Flags&=~ENTF_NO_SIZE;
									show=1;
								}
							}

							// Modify date?
							if (change->flags&FMF_DATE)
							{
								// Has date changed?
								if (CompareDates(&entry->de_Date,&change->fib_Date)!=0)
								{
									// Store new date
									entry->de_Date=change->fib_Date;

									// Get new date string
									date_build_string(&entry->de_Date,entry->de_DateBuf,1);
									show=1;
								}
							}

							// Protection
							if (change->flags&FMF_PROTECT)
							{
								// Has protection changed?
								if (entry->de_Protection!=change->fib_Protection)
								{
									// Store new protection
									entry->de_Protection=change->fib_Protection;

									// Get new protection string
									protect_get_string(entry->de_Protection,entry->de_ProtBuf);
									show=1;
								}
							}

							// Comment?
							if (change->flags&FMF_COMMENT)
							{
								// Store new comment
								direntry_add_string(buffer,entry,DE_Comment,change->fib_Comment);
								show=1;
							}

							// Name
							else
							if (change->flags&FMF_NAME)
							{
								// Has name changed?
								if (strcmp(entry->de_Node.dn_Name,change->fib_Comment)!=0)
								{
									// Store new name
									stccpy(entry->de_Node.dn_Name,change->fib_Comment,entry->de_NameLen);
									show=1;
								}
							}
						}
					}

					// Delete a file
					else
					if (change->node.ln_Type&FCTYPE_DEL)
					{
						DirEntry *entry;

						// Find entry in buffer
						if ((entry=find_entry(&buffer->entry_list,change->fib_FileName,0,buffer->more_flags&DWF_CASE)) ||
							(entry=find_entry(&buffer->reject_list,change->fib_FileName,0,buffer->more_flags&DWF_CASE)))
						{
							BackdropObject *object;
							char *ptr;

							// Icon filename?
							if (ptr=isicon(change->fib_FileName)) *ptr=0;

							// Lock icon list
							if (GetSemaphore(&info->objects.lock,flags,0))
							{
								// Is there an icon for this file?
								if (object=(BackdropObject *)FindNameI(&info->objects.list,change->fib_FileName))
								{
									// Delete if a fake icon, or if not, because we removed the .info
									if (object->flags&BDOF_FAKE_ICON || ptr)
									{
										// Erase object (if in icon mode)
										if (lister->flags&LISTERF_VIEW_ICONS)
											backdrop_render_object(info,object,BRENDERF_CLEAR|BRENDERF_CLIP);

										// Remove object	
										backdrop_remove_object(info,object);
									}
								}

								// Unlock the icon list
								FreeSemaphore(&info->objects.lock);
							}

							// Restore filename
							if (ptr) *ptr='.';
							
							// Remove file from buffer
							removefile(buffer,entry);

							// Flag to refresh
							show=1;
							del_ok=1;
						}
					}

					// Add a file?
					if (change->node.ln_Type&FCTYPE_ADD)
					{
						DirEntry *entry;

						// If this is a reload, only add if we deleted the existing one
						if (change->node.ln_Type==FCTYPE_RELOAD && !del_ok) continue;

						// Create an entry
						if (entry=create_file_entry(
							buffer,0,
							change->fib_FileName,
							change->fib_Size,
							change->fib_DirEntryType,
							&change->fib_Date,
							change->fib_Comment,
							change->fib_Protection,
							0,0,0,
							change->fib_Network))
						{
							// Want to select it?
							if (change->node.ln_Pri&FCF_SELECT)
							{
								// Only do this if lister is locked by us
								if (lister->locker_ipc==handle->ipc)
								{
									// Mark as selected
									entry->de_Flags|=ENTF_SELECTED;
								}
							}

							// Add entry to buffer
							if (add_file_entry(buffer,entry,0))
							{
								// Flag to refresh
								show=1;

								// Want to show it?
								if (change->node.ln_Pri&FCF_SHOW)
								{
									// Save pointer to entry
									show_file=entry;
								}
							}
						}
					}
				}

				// Unlock the buffer
				FreeSemaphore(&buffer->semaphore);
			}
		}

		// Need to refresh?
		if (show)
		{
			// Need icons?
			if (lister->flags&LISTERF_VIEW_ICONS)
			{
				// Get icons
				IPC_Command(lister->ipc,LISTER_GET_ICON,0,0,0,0);
			}

			// Only do this if lister isn't locked by us
			if (lister->locker_ipc!=handle->ipc || !handle->ipc)
			{
				// Refresh lister
				IPC_Command(
					lister->ipc,
					LISTER_REFRESH_WINDOW,
					ref_flags|REFRESHF_DATESTAMP,
					0,
					0,
					0);
			}

			// File to show?
			else
			if (show_file)
			{
				// Tell lister to show this entry
				IPC_Command(lister->ipc,LISTER_FIND_ENTRY,0,show_file,0,0);
			}

			// Fix icon selection count (for icon action mode)
			if (lister->flags&LISTERF_ICON_ACTION)
				backdrop_fix_count(lister->backdrop_info,0);
		}
	}

	// Unlock lister list
	unlock_listlock(&GUI->lister_list);

	// Strip used changes?
	if (strip)
	{
		FileChangeList *list,*nextlist;

		// Go through lists
		for (list=(FileChangeList *)handle->filechange.lh_Head;
			list->node.ln_Succ;
			list=nextlist)
		{
			FileChange *change,*next;

			// Cache next list
			nextlist=(FileChangeList *)list->node.ln_Succ;

			// Go through changes
			for (change=(FileChange *)list->files.mlh_Head;
				change->node.ln_Succ;
				change=next)
			{
				// Cache next
				next=(FileChange *)change->node.ln_Succ;

				// Does change count match list count?
				if (list->count==0 || change->count>=list->count)
				{
					// Remove and free this change
					Remove((struct Node *)change);
					FreeMemH(change->fib_Network);
					FreeMemH(change);
				}

				// Reset change count to 0
				else change->count=0;
			}

			// Is list empty now?
			if (list->count==0 || (IsListEmpty((struct List *)&list->files)))
			{
				// Remove and free this list
				Remove((struct Node *)list);
				FreeMemH(list);
			}

			// Reset list count to 0
			else list->count=0;
		}
	}
}
