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

#define DOSBase (data->dos_base)

/********************************** CreateDir **********************************/

// Patched CreateDir()
BPTR __asm L_PatchedCreateDir(register __d1 char *name)
{
	struct LibData *data;
	struct MyLibrary *libbase;
	struct FileInfoBlock *fib;
	BPTR lock;

	// Get library
	if (!(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Call original function
	lock=((BPTR __asm (*)
			(register __d1 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_CREATEDIR])
			(name,data->dos_base);

	// Failed?
	if (!lock) return 0;

	// Get directory information
	if (fib=dospatch_fib(lock,libbase,1))
	{
		// Send notification
		L_SendNotifyMsg(DN_DOS_ACTION,0,DNF_DOS_CREATEDIR,0,(char *)(fib+1),fib,libbase);

		// Free info block
		FreeVec(fib);
	}
	return lock;
}


// Calls original CreateDir directly
BPTR __asm __saveds L_OriginalCreateDir(
	register __d1 char *name,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If patch wasn't installed, call DOS directly
	if (!(data->flags&LIBDF_DOS_PATCH))
		return CreateDir(name);

	// Create directory
	return
		((BPTR __asm (*)
			(register __d1 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_CREATEDIR])
			(name,data->dos_base);
}

/********************************** DeleteFile **********************************/

// Patched DeleteFile()
long __asm L_PatchedDeleteFile(register __d1 char *name)
{
	struct LibData *data;
	struct MyLibrary *libbase;
	char *buf=0;
	BPTR lock;
	long res;
	APTR wsave=(APTR)-1;
	struct Process *task;

	// Get library
	if (!(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Find process
	if (task=(struct Process *)FindTask(0))
	{
		// Is it a process?
		if (task->pr_Task.tc_Node.ln_Type==NT_PROCESS)
		{
			// Save pointer and turn requesters off
			wsave=task->pr_WindowPtr;
			task->pr_WindowPtr=(APTR)-1;
		}
		else task=0;
	}

	// Try to lock file to delete
	if (lock=Lock(name,ACCESS_READ))
	{
		// Allocate buffer
		if (buf=AllocVec(512,MEMF_CLEAR))
		{
			// Get full path
			L_DevNameFromLock(lock,buf,512,libbase);
		}

		// Unlock file
		UnLock(lock);
	}

	// Fix requesters
	if (task) task->pr_WindowPtr=wsave;

	// Call original function
	res=((long __asm (*)
			(register __d1 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_DELETEFILE])
			(name,data->dos_base);

	// Failed?
	if (!res) return 0;

	// Got name?
	if (buf && *buf)
	{
		// Send notification
		L_SendNotifyMsg(DN_DOS_ACTION,0,DNF_DOS_DELETEFILE,0,buf,0,libbase);
	}

	// Free buffer
	FreeVec(buf);
	return res;
}


// Original DeleteFile
long __asm __saveds L_OriginalDeleteFile(
	register __d1 char *name,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If patch wasn't installed, call DOS directly
	if (!(data->flags&LIBDF_DOS_PATCH))
		return DeleteFile(name);

	// Delete file
	return
		((BPTR __asm (*)
			(register __d1 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_DELETEFILE])
			(name,data->dos_base);
}


/********************************** SetFileDate **********************************/

// Patched SetFileDate()
BOOL __asm L_PatchedSetFileDate(
	register __d1 char *name,
	register __d2 struct DateStamp *date)
{
	struct LibData *data;
	struct MyLibrary *libbase;
	BOOL res;
	BPTR lock;
	APTR wsave=(APTR)-1;
	struct Process *task;

	// Get library
	if (!(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Call original function
	res=((BOOL __asm (*)
			(register __d1 char *,register __d2 struct DateStamp *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_SETFILEDATE])
			(name,date,data->dos_base);

	// Failed?
	if (!res) return 0;

	// Find process
	if (task=(struct Process *)FindTask(0))
	{
		// Is it a process?
		if (task->pr_Task.tc_Node.ln_Type==NT_PROCESS)
		{
			// Save pointer and turn requesters off
			wsave=task->pr_WindowPtr;
			task->pr_WindowPtr=(APTR)-1;
		}
		else task=0;
	}

	// Try to lock file
	if (lock=Lock(name,ACCESS_READ))
	{
		struct FileInfoBlock *fib;

		// Get directory information
		if (fib=dospatch_fib(lock,libbase,0))
		{
			// Send notification
			L_SendNotifyMsg(DN_DOS_ACTION,0,DNF_DOS_SETFILEDATE,0,(char *)(fib+1),fib,libbase);

			// Free info block
			FreeVec(fib);
		}

		// Unlock file
		UnLock(lock);
	}

	// Fix requesters
	if (task) task->pr_WindowPtr=wsave;

	return res;
}


// Calls original SetFileDate directly
BOOL __asm __saveds L_OriginalSetFileDate(
	register __d1 char *name,
	register __d2 struct DateStamp *date,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If patch wasn't installed, call DOS directly
	if (!(data->flags&LIBDF_DOS_PATCH))
		return (BOOL)SetFileDate(name,date);

	// Set date
	return
		((BOOL __asm (*)
			(register __d1 char *,register __d2 struct DateStamp *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_SETFILEDATE])
			(name,date,data->dos_base);
}


/********************************** SetComment **********************************/

// Patched SetComment()
BOOL __asm L_PatchedSetComment(
	register __d1 char *name,
	register __d2 char *comment)
{
	struct LibData *data;
	struct MyLibrary *libbase;
	BOOL res;
	BPTR lock;
	APTR wsave=(APTR)-1;
	struct Process *task;

	// Get library
	if (!(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Call original function
	res=((BOOL __asm (*)
			(register __d1 char *,register __d2 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_SETCOMMENT])
			(name,comment,data->dos_base);

	// Failed?
	if (!res) return 0;

	// Find process
	if (task=(struct Process *)FindTask(0))
	{
		// Is it a process?
		if (task->pr_Task.tc_Node.ln_Type==NT_PROCESS)
		{
			// Save pointer and turn requesters off
			wsave=task->pr_WindowPtr;
			task->pr_WindowPtr=(APTR)-1;
		}
		else task=0;
	}

	// Lock file
	if (lock=Lock(name,ACCESS_READ))
	{
		struct FileInfoBlock *fib;

		// Get directory information
		if (fib=dospatch_fib(lock,libbase,0))
		{
			// Send notification
			L_SendNotifyMsg(DN_DOS_ACTION,0,DNF_DOS_SETCOMMENT,0,(char *)(fib+1),fib,libbase);

			// Free info block
			FreeVec(fib);
		}

		// Unlock file
		UnLock(lock);
	}

	// Fix requesters
	if (task) task->pr_WindowPtr=wsave;

	return res;
}


// Calls original SetComment directly
BOOL __asm __saveds L_OriginalSetComment(
	register __d1 char *name,
	register __d2 char *comment,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If patch wasn't installed, call DOS directly
	if (!(data->flags&LIBDF_DOS_PATCH))
		return (BOOL)SetComment(name,comment);

	// Set comment
	return
		((BOOL __asm (*)
			(register __d1 char *,register __d2 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_SETCOMMENT])
			(name,comment,data->dos_base);
}


/********************************** SetProtection **********************************/

// Patched SetProtection()
BOOL __asm L_PatchedSetProtection(
	register __d1 char *name,
	register __d2 ULONG mask)
{
	struct LibData *data;
	struct MyLibrary *libbase;
	BOOL res;
	BPTR lock;
	APTR wsave=(APTR)-1;
	struct Process *task;

	// Get library
	if (!(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Call original function
	res=((BOOL __asm (*)
			(register __d1 char *,register __d2 ULONG,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_SETPROTECTION])
			(name,mask,data->dos_base);

	// Failed?
	if (!res) return 0;

	// Find process
	if (task=(struct Process *)FindTask(0))
	{
		// Is it a process?
		if (task->pr_Task.tc_Node.ln_Type==NT_PROCESS)
		{
			// Save pointer and turn requesters off
			wsave=task->pr_WindowPtr;
			task->pr_WindowPtr=(APTR)-1;
		}
		else task=0;
	}

	// Lock file
	if (lock=Lock(name,ACCESS_READ))
	{
		struct FileInfoBlock *fib;

		// Get directory information
		if (fib=dospatch_fib(lock,libbase,0))
		{
			// Send notification
			L_SendNotifyMsg(DN_DOS_ACTION,0,DNF_DOS_SETPROTECTION,0,(char *)(fib+1),fib,libbase);

			// Free info block
			FreeVec(fib);
		}

		// Unlock file
		UnLock(lock);
	}

	// Fix requesters
	if (task) task->pr_WindowPtr=wsave;
	return res;
}


// Calls original SetProtection directly
BOOL __asm __saveds L_OriginalSetProtection(
	register __d1 char *name,
	register __d2 ULONG mask,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If patch wasn't installed, call DOS directly
	if (!(data->flags&LIBDF_DOS_PATCH))
		return (BOOL)SetProtection(name,mask);

	// Set protection
	return
		((BOOL __asm (*)
			(register __d1 char *,register __d2 ULONG,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_SETPROTECTION])
			(name,mask,data->dos_base);
}


/********************************** Rename **********************************/

// Patched Rename()
BOOL __asm L_PatchedRename(
	register __d1 char *oldname,
	register __d2 char *newname)
{
	struct FileInfoBlock *fib=0;
	struct LibData *data;
	struct MyLibrary *libbase;
	BOOL res;
	BPTR lock;
	char old_name[108];
	APTR wsave=(APTR)-1;
	struct Process *task;

	// Get library
	if (!(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Find process
	if (task=(struct Process *)FindTask(0))
	{
		// Is it a process?
		if (task->pr_Task.tc_Node.ln_Type==NT_PROCESS)
		{
			// Save pointer and turn requesters off
			wsave=task->pr_WindowPtr;
			task->pr_WindowPtr=(APTR)-1;
		}
		else task=0;
	}

	// Get lock on old file?
	if (lock=Lock(oldname,ACCESS_READ))
	{
		// Get file information
		if (!(fib=dospatch_fib(lock,libbase,0)))
		{
			// Failed to get info
			UnLock(lock);
			lock=0;
		}
	}

	// Fix requesters
	if (task) task->pr_WindowPtr=wsave;

	// Call original function
	res=((BOOL __asm (*)
			(register __d1 char *,register __d2 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_RENAME])
			(oldname,newname,data->dos_base);

	// Failure?
	if (!res)
	{
		// Unlock and free fib
		if (fib) FreeVec(fib);
		if (lock) UnLock(lock);
		return res;
	}

	// Got no Fib?
	if (!fib) return res;

	// Store old name
	strcpy(old_name,fib->fib_FileName);

	// Turn requesters off
	if (task) task->pr_WindowPtr=(APTR)-1;

	// Get new information
	if (Examine(lock,fib))
	{
		// Copy new name to comment
		stccpy(fib->fib_Comment,fib->fib_FileName,79);

		// Restore old name
		strcpy(fib->fib_FileName,old_name);

		// Send notification
		L_SendNotifyMsg(DN_DOS_ACTION,0,DNF_DOS_RENAME,0,(char *)(fib+1),fib,libbase);
	}

	// Free info block and lock
	FreeVec(fib);
	UnLock(lock);

	// Fix requesters
	if (task) task->pr_WindowPtr=wsave;
	return res;
}


// Calls original Rename directly
BOOL __asm __saveds L_OriginalRename(
	register __d1 char *oldname,
	register __d2 char *newname,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If patch wasn't installed, call DOS directly
	if (!(data->flags&LIBDF_DOS_PATCH))
		return (BOOL)Rename(oldname,newname);

	// Rename file
	return
		((BOOL __asm (*)
			(register __d1 char *,register __d2 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_RENAME])
			(oldname,newname,data->dos_base);
}


/********************************** Relabel **********************************/

// Patched Relabel()
BOOL __asm L_PatchedRelabel(
	register __d1 char *volumename,
	register __d2 char *name)
{
	struct LibData *data;
	struct MyLibrary *libbase;
	struct FileInfoBlock fib;
	BOOL res;

	// Get library
	if (!(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Call original function
	res=((BOOL __asm (*)
			(register __d1 char *,register __d2 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_RELABEL])
			(volumename,name,data->dos_base);

	// Failure?
	if (!res) return res;

	// Fake fib with new name
	strcpy(fib.fib_FileName,name);

	// Send notification
	L_SendNotifyMsg(DN_DOS_ACTION,0,DNF_DOS_RELABEL,0,volumename,&fib,libbase);
	return res;
}


// Calls original Relabel directly
BOOL __asm __saveds L_OriginalRelabel(
	register __d1 char *volumename,
	register __d2 char *name,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Relabel disk
	return
		((BOOL __asm (*)
			(register __d1 char *,register __d2 char *,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_RELABEL])
			(volumename,name,data->dos_base);
}


/********************************** Open **********************************/

// Patched Open()
BPTR __asm L_PatchedOpen(
	register __d1 char *name,
	register __d2 LONG accessMode)
{
	struct LibData *data;
	struct MyLibrary *libbase;
	struct FileInfoBlock *fib;
	BPTR file,lock;
	BOOL create=0;
	APTR wsave=(APTR)-1;
	struct Process *task;
	struct FileHandleWrapper *handle;

	// Get library
	if (!(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Find process
	if (task=(struct Process *)FindTask(0))
	{
		// Is it a process?
		if (task->pr_Task.tc_Node.ln_Type==NT_PROCESS)
		{
			// Save pointer and turn requesters off
			wsave=task->pr_WindowPtr;
			task->pr_WindowPtr=(APTR)-1;
		}
		else task=0;
	}

	// Check mode
	switch (accessMode)
	{
		// Create?
		case MODE_NEWFILE:
			create=1;
			break;

		// Read/write
		case MODE_READWRITE:

			// If file is going to be created, we use it
			if (!(lock=Lock(name,ACCESS_READ))) create=1;
			else UnLock(lock);
			break;
	}

	// Fix requesters
	if (task) task->pr_WindowPtr=wsave;

	// Call original function
	file=((BPTR __asm (*)
			(register __d1 char *,register __d2 LONG,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_OPEN])
			(name,accessMode,data->dos_base);

	// Failure?
	if (!file) return file;

	// If file is Interactive, assume it's not a filesystem
	if (IsInteractive(file)) return file;

	// Allocate FileInfoBlock and buffer
	if (!(fib=AllocVec(sizeof(struct FileInfoBlock)+512,MEMF_CLEAR)))
		return file;

	// Disable requesters
	if (task) task->pr_WindowPtr=(APTR)-1;

	// Get lock on parent directory
	if (lock=ParentOfFH(file))
	{
		// Allocate wrapper handle
		if (handle=AllocVec(sizeof(struct FileHandleWrapper),0))
		{
			// Fill out handle
			handle->fhw_FileHandle=file;
			handle->fhw_Flags=0;
			handle->fhw_Parent=lock;

			// Lock file list
			ObtainSemaphore(&data->file_list.lock);

			// Add to head of list
			AddHead(&data->file_list.list,(struct Node *)handle);

			// Unlock file list
			ReleaseSemaphore(&data->file_list.lock);
		}

		// If this was a create operation, we need to send a message now
		if (create)
		{
			// Get buffer pointer
			char *path=(char *)(fib+1);

			// Get full path of parent, and terminate it
			L_DevNameFromLock(lock,path,512,libbase);
			AddPart(path,"",512);

			// Got path?
			if (*path)
			{
				// Examine the new file
				if (ExamineFH(file,fib))
				{
					// Send notification
					L_SendNotifyMsg(DN_DOS_ACTION,0,DNF_DOS_CREATE,0,path,fib,libbase);
				}
			}
		}

		// Unlock parent, unless handle has grabbed it
		if (!handle) UnLock(lock);
	}

	// Free fib
	FreeVec(fib);

	// Fix requesters
	if (task) task->pr_WindowPtr=wsave;
	return file;
}


// Calls original Open directly
BPTR __asm __saveds L_OriginalOpen(
	register __d1 char *name,
	register __d2 LONG accessMode,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If patch wasn't installed, call DOS directly
	if (!(data->flags&LIBDF_DOS_PATCH))
		return Open(name,accessMode);

	// Open file
	return
		((BPTR __asm (*)
			(register __d1 char *,register __d2 LONG,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_OPEN])
			(name,accessMode,data->dos_base);
}


/********************************** Close **********************************/

// Patched Close()
BOOL __asm L_PatchedClose(register __d1 BPTR file)
{
	struct LibData *data;
	struct MyLibrary *libbase;

	// Get library
	if (!file || !(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If this is the 'last' file, clear pointer
	if (data->last_file==file)
		data->last_file=0;

	// Is file not interactive (ie a filesystem)?
	if (!IsInteractive(file))
	{
		struct FileHandleWrapper *handle;

		// See if we have a wrapper
		if (handle=find_filehandle(file,data))
		{
			// Remove it from the list
			Remove((struct Node *)handle);

			// Unlock the list
			ReleaseSemaphore(&data->file_list.lock);

			// Did the file get written to?
			if (handle->fhw_Flags&FHWF_WRITTEN)
			{
				struct FileInfoBlock *fib;
				APTR wsave=(APTR)-1;
				struct Process *task;

				// Find process
				if (task=(struct Process *)FindTask(0))
				{
					// Is it a process?
					if (task->pr_Task.tc_Node.ln_Type==NT_PROCESS)
					{
						// Save pointer and turn requesters off
						wsave=task->pr_WindowPtr;
						task->pr_WindowPtr=(APTR)-1;
					}
					else task=0;
				}

				// Allocate FileInfoBlock and buffer
				if (fib=AllocVec(sizeof(struct FileInfoBlock)+512,MEMF_CLEAR))
				{
					char *path=(char *)(fib+1);

					// Get full path of parent and terminate it
					L_DevNameFromLock(handle->fhw_Parent,path,512,libbase);
					AddPart(path,"",512);

					// Got path?
					if (*path)
					{
						// Examine the file
						if (ExamineFH(file,fib))
						{
							// Send notification
							L_SendNotifyMsg(DN_DOS_ACTION,0,DNF_DOS_CLOSE,0,path,fib,libbase);
						}
					}

					// Free fib
					FreeVec(fib);
				}

				// Fix requesters
				if (task) task->pr_WindowPtr=wsave;
			}

			// Unlock parent lock
			UnLock(handle->fhw_Parent);

			// Free wrapper handle
			FreeVec(handle);
		}
	}

	// Close file
	return
		((BOOL __asm (*)
			(register __d1 BPTR,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_CLOSE])
			(file,data->dos_base);
}


// Calls original Close directly
BOOL __asm __saveds L_OriginalClose(
	register __d1 BPTR file,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If patch wasn't installed, call DOS directly
	if (!(data->flags&LIBDF_DOS_PATCH))
		return (BOOL)Close(file);

	// Close file
	return
		((BOOL __asm (*)
			(register __d1 BPTR,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_CLOSE])
			(file,data->dos_base);
}


/********************************** Write **********************************/

// Patched Write()
LONG __asm L_PatchedWrite(
	register __d1 BPTR file,
	register __d2 void *wdata,
	register __d3 LONG length)
{
	struct LibData *data;
	struct MyLibrary *libbase;
	struct FileHandleWrapper *handle;

	// Get library
	if (!file || !(libbase=GET_DOPUSLIB)) return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Different to the last file we saw?
	if (data->last_file!=file)
	{
		// See if we have a wrapper
		if (handle=find_filehandle(file,data))
		{
			// Set 'written' flag
			handle->fhw_Flags|=FHWF_WRITTEN;

			// Unlock the list
			ReleaseSemaphore(&data->file_list.lock);
		}

		// Remember this file
		data->last_file=file;
	}

	// Write data
	return
		((LONG __asm (*)
			(register __d1 BPTR,register __d2 void *,register __d3 LONG,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_WRITE])
			(file,wdata,length,data->dos_base);
}


// Calls original Write directly
LONG __asm __saveds L_OriginalWrite(
	register __d1 BPTR file,
	register __d2 void *wdata,
	register __d3 LONG length,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// If patch wasn't installed, call DOS directly
	if (!(data->flags&LIBDF_DOS_PATCH))
		return Write(file,wdata,length);

	// Write data
	return
		((LONG __asm (*)
			(register __d1 BPTR,register __d2 void *,register __d3 LONG,register __a6 struct Library *))
				data->wb_data.old_function[WB_PATCH_WRITE])
			(file,wdata,length,data->dos_base);
}


/******************************************************************************/

// Get information on a filelock
struct FileInfoBlock *dospatch_fib(BPTR lock,struct MyLibrary *libbase,BOOL req)
{
	struct FileInfoBlock *fib=0;
	struct LibData *data;
	BPTR parent;
	BOOL ok=0;
	APTR wsave=(APTR)-1;
	struct Process *task=0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Find process
	if (req && (task=(struct Process *)FindTask(0)))
	{
		// Is it a process?
		if (task->pr_Task.tc_Node.ln_Type==NT_PROCESS)
		{
			// Save pointer and turn requesters off
			wsave=task->pr_WindowPtr;
			task->pr_WindowPtr=(APTR)-1;
		}
		else task=0;
	}

	// Get parent directory
	if (parent=ParentDir(lock))
	{
		// Get FileInfoBlock and a buffer
		if (fib=AllocVec(sizeof(struct FileInfoBlock)+512,MEMF_CLEAR))
		{
			char *buf;

			// Get buffer pointer
			buf=(char *)(fib+1);

			// Get full path of parent, and terminate it
			L_DevNameFromLock(parent,buf,512,libbase);
			AddPart(buf,"",512);

			// Got path?
			if (*buf)
			{
				// Examine the lock
				if (Examine(lock,fib)) ok=1;
			}
		}

		// Not ok?
		if (!ok)
		{
			FreeVec(fib);
			fib=0;
		}

		// Unlock parent
		UnLock(parent);
	}

	// Fix requesters
	if (task) task->pr_WindowPtr=wsave;
	return fib;
}

// Find FileHandle in tracking list
struct FileHandleWrapper *find_filehandle(BPTR file,struct LibData *data)
{
	struct FileHandleWrapper *handle;

	// Lock list
	ObtainSemaphore(&data->file_list.lock);

	// Go through list
	for (handle=(struct FileHandleWrapper *)data->file_list.list.lh_Head;
		handle->fhw_Node.mln_Succ;
		handle=(struct FileHandleWrapper *)handle->fhw_Node.mln_Succ)
	{
		// Match handle
		if (handle->fhw_FileHandle==file)
		{
			// Not the top one?
			if (handle!=(struct FileHandleWrapper *)data->file_list.list.lh_Head)
			{
				// Shift it to the top as the most recently accessed
				Remove((struct Node *)handle);
				AddHead(&data->file_list.list,(struct Node *)handle);
			}

			// Return the handle (leave the list locked)
			return handle;
		}
	}

	// Not found
	ReleaseSemaphore(&data->file_list.lock);
	return 0;
}
