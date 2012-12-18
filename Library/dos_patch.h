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

BPTR __asm L_PatchedCreateDir(register __d1 char *name);
BPTR __asm L_OriginalCreateDir(
	register __d1 char *name,
	register __a6 struct MyLibrary *libbase);
long __asm L_PatchedDeleteFile(register __d1 char *name);
long __asm L_OriginalDeleteFile(
	register __d1 char *name,
	register __a6 struct MyLibrary *libbase);
BOOL __asm L_PatchedSetFileDate(
	register __d1 char *name,
	register __d2 struct DateStamp *date);
BOOL __asm L_OriginalSetFileDate(
	register __d1 char *name,
	register __d2 struct DateStamp *date,
	register __a6 struct MyLibrary *libbase);
BOOL __asm L_PatchedSetComment(
	register __d1 char *name,
	register __d2 char *comment);
BOOL __asm L_OriginalSetComment(
	register __d1 char *name,
	register __d2 char *comment,
	register __a6 struct MyLibrary *libbase);
BOOL __asm L_PatchedSetProtection(
	register __d1 char *name,
	register __d2 ULONG mask);
BOOL __asm L_OriginalSetProtection(
	register __d1 char *name,
	register __d2 ULONG mask,
	register __a6 struct MyLibrary *libbase);
BOOL __asm L_PatchedRename(
	register __d1 char *oldname,
	register __d2 char *newname);
BOOL __asm L_OriginalRename(
	register __d1 char *oldname,
	register __d2 char *newname,
	register __a6 struct MyLibrary *libbase);
BPTR __asm L_PatchedOpen(
	register __d1 char *name,
	register __d2 LONG accessMode);
BPTR __asm L_OriginalOpen(
	register __d1 char *name,
	register __d2 LONG accessMode,
	register __a6 struct MyLibrary *libbase);
BOOL __asm L_PatchedClose(register __d1 BPTR file);
BOOL __asm L_OriginalClose(
	register __d1 BPTR file,
	register __a6 struct MyLibrary *libbase);
LONG __asm L_PatchedWrite(
	register __d1 BPTR file,
	register __d2 void *data,
	register __d3 LONG length);
LONG __asm L_OriginalWrite(
	register __d1 BPTR file,
	register __d2 void *data,
	register __d3 LONG length,
	register __a6 struct MyLibrary *libbase);
BOOL __asm L_PatchedRelabel(
	register __d1 char *volumename,
	register __d2 char *name);
BOOL __asm L_OriginalRelabel(
	register __d1 char *volumename,
	register __d2 char *name,
	register __a6 struct MyLibrary *libbase);

struct FileInfoBlock *dospatch_fib(BPTR,struct MyLibrary *,BOOL);

struct FileHandleWrapper
{
	struct MinNode		fhw_Node;
	BPTR			fhw_FileHandle;
	ULONG			fhw_Flags;
	BPTR			fhw_Parent;
};

#define FHWF_WRITTEN		(1<<0)		// File has been written to

struct FileHandleWrapper *find_filehandle(BPTR file,struct LibData *data);
