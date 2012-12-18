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

#ifndef _DOPUS_HOOK
#define _DOPUS_HOOK

/*****************************************************************************

 Directory Opus Direct Hooks

 *****************************************************************************/

// Use this command to get the address of the hooks from the Opus process.
// Send it to the main Opus IPC, and supply the address of a DOpusCallbackInfo
// structure in the data field of the message

#define HOOKCMD_GET_CALLBACKS	0x40100

#define DOPUS_HOOK_COUNT	45

// This structure will grow in the future, correct use of the dc_Count field
// ensures innocent memory won't get overwritten.

typedef struct
{
	// Set to the number of hooks you want
	USHORT		dc_Count;

	// Create a file entry
	APTR __asm	(*dc_CreateFileEntry)
				(register __a0 ULONG lister,
				 register __a1 struct FileInfoBlock *fib,
				 register __d0 BPTR lock);

	// Change parameters of a file entry
	VOID __asm	(*dc_FileSet)
				(register __a0 ULONG lister,
				 register __a1 APTR entry,
				 register __a2 struct TagItem *tags);

	// Sort list of entries into a lister
	VOID __asm	(*dc_SortFileList)
				(register __a0 ULONG lister,
				 register __a1 struct List *list,
				 register __d0 long file_count,
				 register __d1 long dir_count);

	// Add single entry to a lister
	APTR __asm	(*dc_AddFileEntry)
				(register __a0 ULONG lister,
				 register __a1 APTR entry,
				 register __d0 BOOL sort);

	// Resort a lister
	VOID __asm	(*dc_ResortLister)
				(register __a0 ULONG lister,
				 register __a1 struct ListFormat *format);

	// Refresh a lister
	VOID __asm	(*dc_RefreshLister)
				(register __a0 ULONG lister,
				 register __d0 ULONG flags);

	// Lock lister file list
	VOID __asm	(*dc_LockFileList)
				(register __a0 ULONG lister,
				 register __d0 BOOL exclusive);

	// Unlock file list
	VOID __asm	(*dc_UnlockFileList)
				(register __a0 ULONG lister);

	// Find entry in a lister by name
	APTR __asm	(*dc_FindFileEntry)
				(register __a0 ULONG lister,
				 register __a1 char *name);

	// Change comment of an entry
	BOOL __asm	(*dc_SetFileComment)
				(register __a0 ULONG lister,
				 register __a1 char *name,
				 register __a2 char *comment);

	// Remove file entry from a lister
	VOID __asm	(*dc_RemoveFileEntry)
				(register __a0 ULONG lister,
				 register __a1 APTR entry);

	// Query file entry
	BOOL __asm	(*dc_FileQuery)
				(register __a0 ULONG lister,
				 register __a1 APTR entry,
				 register __a2 struct TagItem *tags);

	// Show help
	void __asm	(*dc_ShowHelp)
				(register __a0 char *file_name,
				 register __a1 char *node_name);


	// Convert entry pointer from one type to another
	APTR __asm	(*dc_ConvertEntry)
				(register __a0 APTR entry);


	// Get lister pointer from a path handle
	ULONG __asm	(*dc_GetLister)
				(register __a0 APTR path);


	// Get first source lister
	APTR __asm 	(*dc_GetSource)
				(register __a0 APTR handle,
				 register __a1 char *path);


	// Get next source lister
	APTR __asm	(*dc_NextSource)
				(register __a0 APTR handle,
				 register __a1 char *path);


	// Unlock source listers
	void __asm	(*dc_UnlockSource)
				(register __a0 APTR handle);


	// Get next destination lister
	APTR __asm	(*dc_GetDest)
				(register __a0 APTR handle,
				 register __a1 char *path);


	// End use of source lister
	void __asm	(*dc_EndSource)
				(register __a0 APTR handle,
				 register __d0 long complete);


	// End use of destination lister
	void __asm	(*dc_EndDest)
				(register __a0 APTR handle,
				 register __d0 long complete);


	// Get next selected entry
	APTR __asm	(*dc_GetEntry)
				(register __a0 APTR handle);


	// Examine an entry
	ULONG __asm	(*dc_ExamineEntry)
				(register __a0 APTR entry,
				 register __d0 long type);


	// End use of an entry
	void __asm	(*dc_EndEntry)
				(register __a0 APTR handle,
				 register __a1 APTR entry,
				 register __d0 BOOL deselect);


	// Mark an entry for removal
	void __asm	(*dc_RemoveEntry)
				(register __a0 APTR entry);


	// Return count of selected entries
	long __asm	(*dc_EntryCount)
				(register __a0 APTR handle);


	// Mark an entry to be reloaded
	void __asm	(*dc_ReloadEntry)
				(register __a0 APTR handle,
				 register __a1 APTR entry);


	// Add a file to a lister
	void __asm	(*dc_AddFile)
				(register __a0 APTR handle,
				 register __a1 char *path,
				 register __a2 struct FileInfoBlock *fib,
				 register __a3 ULONG lister);


	// Delete a file from a lister
	void __asm	(*dc_DelFile)
				(register __a0 APTR handle,
				 register __a1 char *path,
				 register __a2 char *name,
				 register __a3 ULONG lister);

	// Load/reload a file in a lister
	void __asm	(*dc_LoadFile)
				(register __a0 APTR handle,
				 register __a1 char *path,
				 register __a2 char *name,
				 register __d0 long flags,
				 register __d1 BOOL reload);


	// Perform changes on a lister
	void __asm	(*dc_DoChanges)
				(register __a0 APTR handle);


	// Check for user abort
	BOOL __asm (*dc_CheckAbort) (register __a0 APTR handle);


	// Get window pointer from a path handle
	struct Window *	(*dc_GetWindow) (register __a0 APTR path);


	// Get Opus ARexx port name
	struct MsgPort *(*dc_GetPort)
				(register __a0 char *ame);


	// Get Opus public screen name
	struct Screen *	(*dc_GetScreen)
				(register __a0 char *name);


	// Get information about the Opus screen
	DOpusScreenData *(*dc_GetScreenData)(void);


	// Free screen data structure			
	void __asm	(*dc_FreeScreenData)(void);
			

	// Open progress indicator in a lister
	void __asm	(*dc_OpenProgress)
				(register __a0 APTR path,
				 register __a1 char *operation,
				 register __d0 long total);


	// Update progress indicator
	void __asm	(*dc_UpdateProgress)
				(register __a0 APTR path,
				 register __a1 char *name,
				 register __d0 long count);


	// Close progress indicator
	void __asm	(*dc_CloseProgress)
				(register __a0 APTR path);


	// Show 'File exists - Replace?' requester
	long __asm	(*dc_ReplaceReq)
				(register __a0 struct Window *window,
				 register __a1 struct Screen *screen,
				 register __a2 IPCData *ipc,
				 register __a3 struct FileInfoBlock *file1,
				 register __a4 struct FileInfoBlock *file2,
				 register __d0 long flags);


	// Some private functions
	void __asm	(*dc_Private1)(void);
	void __asm	(*dc_Private2)(void);


	// Send an ARexx command direct to Opus
	ULONG __asm	(*dc_SendCommand)
				(register __a0 APTR handle,
				 register __a1 char *command,
				 register __a2 char **result,
				 register __d0 ULONG flags);


	// Make DOpus check if the desktop needs updating
	void __asm	(*dc_CheckDesktop)
				{register __a0 char *path);
} DOpusCallbackInfo;


// Values for dc_FileSet/dc_FileQuery

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
#define HFFS_VERSION		( TAG_USER + 0xc )	// VersionInfo *	- Version information
#define HFFS_MENU		( TAG_USER + 0xd )	// struct List *	- Custom menus for entry
#define HFFS_ICON		( TAG_USER + 0xe )	// struct DiskObject *	- not implemented



// Holds version information (used by HFFS_VERSION)
typedef struct _VersionInfo {
	UWORD		vi_Version;		// Major version #
	UWORD		vi_Revision;		// Minor revision #
	long		vi_Days;		// Days of date
	ULONG		vi_Flags;		// Flags
	char		vi_Char;		// Version character
	char		vi_String[1];		// Version string
} VersionInfo;



// Flags for dc_RefreshLister()
#define HOOKREFRESH_DATE	(1<<0)
#define HOOKREFRESH_FULL	(1<<1)



// Type value for dc_ExamineEntry()
enum
{
	EE_NAME,		// Get pointer to name (READ ONLY!)
	EE_TYPE,		// Get type (<0 = file, >0 = dir)
};


// Define this if you want to use dc_ResortLister
#ifdef	DOPUSHOOK_INCLUDE_FORMAT



// Sort format
struct SortFormat {
	BYTE	sf_Sort;			// Sort method
	BYTE	sf_SortFlags;			// Sort flags
	BYTE	sf_Separation;			// File separation
};

#define SORT_REVERSE			(1<<0)	// Sort in reverse order

// List format
struct ListFormat {

	// Colour fields, not used at present
	UBYTE			lf_FilesUnsel[2];	// Unselected files
	UBYTE			lf_FilesSel[2];		// Selected files
	UBYTE			lf_DirsUnsel[2];	// Unselected directories
	UBYTE			lf_DirsSel[2];		// Selected directories

	// Sort information
	struct SortFormat	lf_Sort;		// Sort method
	BYTE			lf_DisplayPos[16];	// Item display position
	BYTE			lf_DisplayLen[15];	// Display length (not used)

	UBYTE			lf_Flags;		// See LFORMATF_xxx below

	// Not used
	BYTE			lf_ShowFree;		// Show free space type

	// You must call ParsePattern() yourself
	char			lf_ShowPattern[40];	// Show pattern
	char			lf_HidePattern[40];	// Hide pattern
	char			lf_ShowPatternP[40];	// Show pattern parsed
	char			lf_HidePatternP[40];	// Hide pattern parsed
};

#define LFORMATF_REJECT_ICONS		(1<<0)	// Reject icons
#define LFORMATF_HIDDEN_BIT		(1<<1)	// Respect the H bit
#define LFORMATF_ICON_VIEW		(1<<2)	// Default to icon view
#define LFORMATF_SHOW_ALL		(1<<3)	// Show all

// Used for the sf_Sort and lf_DisplayPos fields
enum
{
	DISPLAY_NAME,
	DISPLAY_SIZE,
	DISPLAY_PROTECT,
	DISPLAY_DATE,
	DISPLAY_COMMENT,
	DISPLAY_FILETYPE,
	DISPLAY_OWNER,
	DISPLAY_GROUP,
	DISPLAY_NETPROT,
	DISPLAY_VERSION,

	DISPLAY_LAST
};

// Used for the sf_Separation field
enum
{
	SEPARATE_MIX,
	SEPARATE_DIRSFIRST,
	SEPARATE_FILESFIRST,
};

#endif

#endif
