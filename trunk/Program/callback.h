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

#define MAINCMD_GET_CALLBACKS	0x40100

DirEntry *__asm HookCreateFileEntry(
	register __a0 Lister *lister,
	register __a1 struct FileInfoBlock *fib,
	register __d0 BPTR lock);

DirEntry *__asm HookAddFileEntry(
	register __a0 Lister *lister,
	register __a1 DirEntry *entry,
	register __d0 BOOL sort);

void __asm HookFileSet(
	register __a0 Lister *lister,
	register __a1 DirEntry *entry,
	register __a2 struct TagItem *tags);

void __asm HookSortFileList(
	register __a0 Lister *lister,
	register __a1 struct List *list,
	register __d0 long file_count,
	register __d1 long dir_count);

void __asm HookResortLister(
	register __a0 Lister *lister,
	register __a1 ListFormat *format);

void __asm HookRefreshLister(
	register __a0 Lister *lister,
	register __d0 ULONG flags);

void __asm HookLockFileList(
	register __a0 Lister *lister,
	register __d0 BOOL exclusive);

void __asm HookUnlockFileList(
	register __a0 Lister *lister);

DirEntry *__asm HookFindFileEntry(
	register __a0 Lister *lister,
	register __a1 char *name);

BOOL __asm HookSetFileComment(
	register __a0 Lister *lister,
	register __a1 char *name,
	register __a2 char *comment);

void __asm HookRemoveFileEntry(
	register __a0 Lister *lister,
	register __a1 DirEntry *entry);

BOOL __asm HookFileQuery(
	register __a0 Lister *lister,
	register __a1 DirEntry *entry,
	register __a2 struct TagItem *tags);

void __asm HookShowHelp(
	register __a0 char *file_name,
	register __a1 char *node_name);


APTR __asm HookConvertEntry(
	register __a0 FunctionEntry *entry);

Lister *__asm HookGetLister(
	register __a0 PathNode *path);

PathNode *__asm HookGetSource(
	register __a0 FunctionHandle *handle,
	register __a1 char *pathbuf);

PathNode *__asm HookNextSource(
	register __a0 FunctionHandle *handle,
	register __a1 char *pathbuf);

void __asm HookUnlockSource(
	register __a0 FunctionHandle *handle);

PathNode *__asm HookGetDest(
	register __a0 FunctionHandle *handle,
	register __a1 char *pathbuf);

void __asm HookEndSource(
	register __a0 FunctionHandle *handle,
	register __d0 long complete);

void __asm HookEndDest(
	register __a0 FunctionHandle *handle,
	register __d0 long complete);

void __asm HookFirstEntry(
	register __a0 FunctionHandle *handle);

APTR __asm HookGetEntry(
	register __a0 FunctionHandle *handle);

ULONG __asm HookExamineEntry(
	register __a0 FunctionEntry *entry,
	register __d0 long type);

void __asm HookEndEntry(
	register __a0 FunctionHandle *handle,
	register __a1 APTR entry,
	register __d0 BOOL deselect);

void __asm HookRemoveEntry(
	register __a0 FunctionEntry *entry);

long __asm HookEntryCount(
	register __a0 FunctionHandle *handle);

void __asm HookReloadEntry(
	register __a0 FunctionHandle *handle,
	register __a1 FunctionEntry *entry);

void __asm HookAddFile(
	register __a0 FunctionHandle *handle,
	register __a1 char *path,
	register __a2 struct FileInfoBlock *fib,
	register __a3 Lister *lister);

void __asm HookDelFile(
	register __a0 FunctionHandle *handle,
	register __a1 char *path,
	register __a2 char *name,
	register __a3 Lister *lister);

void __asm HookLoadFile(
	register __a0 FunctionHandle *handle,
	register __a1 char *path,
	register __a2 char *name,
	register __d0 long flags,
	register __d1 BOOL reload);

void __asm HookDoChanges(
	register __a0 FunctionHandle *handle);

BOOL __asm HookCheckAbort(
	register __a0 FunctionHandle *handle);

struct Window *__asm HookGetWindow(
	register __a0 PathNode *path);

struct MsgPort *__asm HookGetPort(
	register __a0 char *portname);

struct Screen *__asm HookGetScreen(
	register __a0 char *screenname);

DOpusScreenData *__asm HookGetScreenData(void);

void __asm HookFreeScreenData(register __a0 APTR data);

void __asm HookOpenProgress(
	register __a0 PathNode *path,
	register __a1 char *operation,
	register __d0 long total);

void __asm HookUpdateProgress(
	register __a0 PathNode *path,
	register __a1 char *name,
	register __d0 long count);

void __asm HookCloseProgress(
	register __a0 PathNode *path);

long __asm HookReplaceReq(
	register __a0 struct Window *window,
	register __a1 struct Screen *screen,
	register __a2 IPCData *ipc,
	register __a3 struct FileInfoBlock *file1,
	register __a4 struct FileInfoBlock *file2,
	register __d0 long default_option);

ULONG __asm HookGetPointer(
	register __a0 struct pointer_packet *ptr);

void __asm HookFreePointer(
	register __a0 struct pointer_packet *ptr);

ULONG __asm HookSendCommand(
	register __a0 FunctionHandle *handle,
	register __a1 char *command,
	register __a2 char **result,
	register __d0 ULONG flags);

void __asm HookCheckDesktop(
	register __a0 char *path);

BOOL __asm HookMatchDesktop(
	register __a0 char *path);

USHORT __asm HookGetDesktop(
	register __a0 char *path);

void __asm HookGetThemes(
	register __a0 char *path);

BOOL __asm HookScript(
	register __a0 char *name,
	register __a1 char *data);

short __asm HookDesktopPopup(
	register __a0 ULONG flags);

long __asm HookRexxCommand(
	register __a0 char *command,
	register __a1 char *result,
	register __d0 long length,
	register __a2 struct MsgPort *replyport,
	register __d1 ULONG flags);

long __asm HookFileRequest(
	register __a0 struct Window *parent,
	register __a1 char *title,
	register __a2 char *initial_path,
	register __a3 char *pathname,
	register __d0 ULONG flags,
	register __d1 char *pattern);

typedef struct
{
	USHORT	dc_Count;

	APTR	dc_CreateFileEntry;
	APTR	dc_FileSet;
	APTR	dc_SortFileList;
	APTR	dc_AddFileEntry;
	APTR	dc_ResortLister;
	APTR	dc_RefreshLister;
	APTR	dc_LockFileList;
	APTR	dc_UnlockFileList;
	APTR	dc_FindFileEntry;
	APTR	dc_SetFileComment;
	APTR	dc_RemoveFileEntry;
	APTR	dc_FileQuery;
	APTR	dc_ShowHelp;

	APTR	dc_ConvertEntry;
	APTR	dc_GetLister;
	APTR	dc_GetSource;
	APTR	dc_NextSource;
	APTR	dc_UnlockSource;
	APTR	dc_GetDest;
	APTR	dc_EndSource;
	APTR	dc_EndDest;
	APTR	dc_GetEntry;
	APTR	dc_ExamineEntry;
	APTR	dc_EndEntry;
	APTR	dc_RemoveEntry;
	APTR	dc_EntryCount;
	APTR	dc_ReloadEntry;
	APTR	dc_AddFile;
	APTR	dc_DelFile;
	APTR	dc_LoadFile;
	APTR	dc_DoChanges;
	APTR	dc_CheckAbort;
	APTR	dc_GetWindow;
	APTR	dc_GetPort;
	APTR	dc_GetScreen;
	APTR	dc_GetScreenData;
	APTR	dc_FreeScreenData;
	APTR	dc_OpenProgress;
	APTR	dc_UpdateProgress;
	APTR	dc_CloseProgress;
	APTR	dc_ReplaceReq;
	APTR	dc_GetPointer;
	APTR	dc_FreePointer;
	APTR	dc_SendCommand;
	APTR	dc_CheckDesktop;
	APTR	dc_GetDesktop;
	APTR	dc_Script;
	APTR	dc_DesktopPopup;
	APTR	dc_FirstEntry;
	APTR	dc_RexxCommand;
	APTR	dc_FileRequest;
	APTR	dc_GetThemes;
} DOpusCallbackInfo;

#define DOPUS_HOOK_COUNT	52

// Values for HookFileSet

#define HFFS_NAME		( TAG_USER + 0x1 )	// char * 		- Entry name
#define HFFS_SIZE		( TAG_USER + 0x2 )	// ULONG 		- Entry size
#define HFFS_PROTECTION		( TAG_USER + 0x3 )	// ULONG 		- Protection flags
#define HFFS_DATE		( TAG_USER + 0x4 )	// struct Datestamp *	- Entry date
#define HFFS_COMMENT		( TAG_USER + 0x5 )	// char *		- Comment
#define HFFS_SELECTED		( TAG_USER + 0x6 )	// BOOL			- Selected state
#define HFFS_LINK		( TAG_USER + 0x7 )	// BOOL			- Set if a link
#define HFFS_COLOUR		( TAG_USER + 0x8 )	// ULONG		- 1 = device, 2 = assign
#define HFFS_USERDATA		( TAG_USER + 0x9 )	// ULONG		- Userdata
#define HFFS_FILETYPE		( TAG_USER + 0xa )	// char *		- Filetype description
#define HFFS_DISPLAY		( TAG_USER + 0xb )	// char *		- Custom display string
#define HFFS_VERSION		( TAG_USER + 0xc )	// ULONG *		- version, revision, days
#define HFFS_MENU		( TAG_USER + 0xd )	// void *		- not implemented



#define HOOKREFRESH_DATE	(1<<0)
#define HOOKREFRESH_FULL	(1<<1)

long HookInitHooks(DOpusCallbackInfo *);

enum
{
	EE_NAME,		// Get name pointer (READ ONLY!)
	EE_TYPE,		// Get type (<0 = file, >0 = dir)
};
