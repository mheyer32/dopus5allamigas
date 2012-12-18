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

#ifndef _DOPUS_WB
#define _DOPUS_WB

typedef struct
{
	short			patch_count;
	struct SignalSemaphore	patch_lock;
	struct MinList		app_list;
	struct Library		*wb_base;
	struct Library		*int_base;
	struct MyLibrary	*dopus_base;
	APTR			*old_function;

	UWORD			lock_count;
	UWORD			pad;

	struct Library		*utility_base;
	struct MinList		rem_app_list;
	ULONG			pad1[3];
} WB_Data;

typedef struct
{
	long	offset;
	APTR	function;
	short	type;
} PatchList;


enum
{
	WB_PATCH_ADDAPPWINDOW,
	WB_PATCH_REMAPPWINDOW,
	WB_PATCH_ADDAPPICON,
	WB_PATCH_REMAPPICON,
	WB_PATCH_ADDAPPMENU,
	WB_PATCH_REMAPPMENU,
	WB_PATCH_CLOSEWORKBENCH,
	WB_PATCH_OPENWORKBENCH,
	WB_PATCH_PUTDISKOBJECT,
	WB_PATCH_DELETEDISKOBJECT,
	WB_PATCH_ADDPORT,
	WB_PATCH_CLOSEWINDOW,
	WB_PATCH_CREATEDIR,
	WB_PATCH_DELETEFILE,
	WB_PATCH_SETFILEDATE,
	WB_PATCH_SETCOMMENT,
	WB_PATCH_SETPROTECTION,
	WB_PATCH_RENAME,
	WB_PATCH_OPEN,
	WB_PATCH_CLOSE,
	WB_PATCH_WRITE,
	WB_PATCH_RELABEL,
	WB_PATCH_WBINFO,
	WB_PATCH_ADDTASK,
	WB_PATCH_REMTASK,
	WB_PATCH_FINDTASK,
	WB_PATCH_OPENWINDOWTAGS,
//	WB_PATCH_ALLOCBITMAP,

	WB_PATCH_COUNT
};

enum
{
	WB_PATCH_WORKBENCH,
	WB_PATCH_INTUITION,
	WB_PATCH_ICON,
	WB_PATCH_EXEC,
	WB_PATCH_DOS,
	WB_PATCH_GFX,
	WB_PATCH_DOSFUNC,
	WB_PATCH_DATATYPES,
};

void __asm L_WB_Install_Patch(register __a6 struct MyLibrary *);
BOOL __asm L_WB_Remove_Patch(register __a6 struct MyLibrary *);
struct AppWindow *__asm L_WB_AddAppWindow(
	register __d0 ULONG id,
	register __d1 ULONG userdata,
	register __a0 struct Window *window,
	register __a1 struct MsgPort *port,
	register __a2 struct TagItem *tags);
BOOL __asm L_WB_RemoveAppWindow(
	register __a0 struct AppWindow *window);
struct AppIcon *__asm L_WB_AddAppIcon(
	register __d0 ULONG id,
	register __d1 ULONG userdata,
	register __a0 char *text,
	register __a1 struct MsgPort *port,
	register __a2 BPTR lock,
	register __a3 struct DiskObject *object,
	register __a4 struct TagItem *tags);
BOOL __asm L_WB_RemoveAppIcon(
	register __a0 struct AppIcon *icon);
struct AppMenuItem *__asm L_WB_AddAppMenuItem(
	register __d0 ULONG id,
	register __d1 ULONG userdata,
	register __a0 char *text,
	register __a1 struct MsgPort *port,
	register __a2 struct TagItem *tags);
BOOL __asm L_WB_RemoveAppMenuItem(
	register __a0 struct AppMenuItem *item);

struct AppWindow __asm *L_WB_FindAppWindow(
	register __a0 struct Window *window,
	register __a6 struct MyLibrary *);
struct MsgPort *__asm L_WB_AppWindowData(
	register __a0 struct AppWindow *window,
	register __a1 ULONG *id,
	register __a2 ULONG *userdata);
BOOL __asm L_WB_AppWindowLocal(
	register __a0 struct AppWindow *window);
BOOL __asm L_WB_AppIconSnapshot(
	register __a0 struct AppIcon *icon);

APTR __asm L_LockAppList(register __a6 struct MyLibrary *);
APTR __asm L_NextAppEntry(
	register __a0 APTR last,
	register __d0 ULONG type,
	register __a6 struct MyLibrary *);
void __asm L_UnlockAppList(register __a6 struct MyLibrary *);

AppEntry *new_app_entry(
	ULONG type,
	ULONG id,
	ULONG userdata,
	APTR object,
	char *text,
	struct MsgPort *port,
	WB_Data *wb_data);
APTR rem_app_entry(
	AppEntry *entry,
	WB_Data *wb_data,
	BOOL *);
void free_app_entry(AppEntry *entry,WB_Data *);
AppEntry *find_app_entry(AppEntry *entry,WB_Data *wb_data);

LONG __asm L_WB_CloseWorkBench(void);
ULONG __asm L_WB_OpenWorkBench(void);

BOOL __asm L_WB_PutDiskObject(
	register __a0 char *name,
	register __a1 struct DiskObject *diskobj);

typedef struct
{
	struct DiskObject	doc_DiskObject;
	struct Image		doc_GadgetRender;
	struct Image		doc_SelectRender;
	APTR			doc_Image1;
	APTR			doc_Image2;
	APTR			doc_Data;
} DiskObjectCopy;

struct DiskObject *__asm L_CopyDiskObject(
	register __a0 struct DiskObject *icon,
	register __d0 ULONG flags,
	register __a6 struct MyLibrary *libbase);

void __asm L_FreeDiskObjectCopy(
	register __a0 struct DiskObject *icon,
	register __a6 struct MyLibrary *libbase);

BOOL __asm L_WB_DeleteDiskObject(register __a0 char *name);

void __asm L_ChangeAppIcon(
	register __a0 APTR appicon,
	register __a1 struct Image *render,
	register __a2 struct Image *select,
	register __a3 char *title,
	register __d0 ULONG flags,
	register __a6 struct MyLibrary *libbase);

long __asm L_SetAppIconMenuState(
	register __a0 APTR appicon,
	register __d0 long item,
	register __d1 long state);
void __asm L_WB_AddPort(register __a1 struct MsgPort *port);

void __asm L_WB_CloseWindow(register __a0 struct Window *window);

void icon_notify(struct LibData *data,char *name,ULONG flags,short);
char *icon_fullname(struct LibData *data,char *name);

#define INF_FULLNAME	(1<<0)

struct Library *wb_get_patchbase(short type,struct LibData *data);

ULONG __asm L_PatchedWBInfo(
	register __a0 BPTR lock,
	register __a1 char *name,
	register __a2 struct Screen *screen);

APTR __asm L_PatchedAddTask(register __a1 struct Task *task,register __a2 APTR initialPC,register __a3 APTR finalPC);
void __asm L_PatchedRemTask(register __a1 struct Task *task);
struct Task *__asm L_PatchedFindTask(register __a1 char *name);
struct Window *__asm L_PatchedOpenWindowTags(register __a0 struct NewWindow *,register __a1 struct TagItem *);

struct BitMap *__asm L_PatchedAllocBitmap(
	register __d0 ULONG,
	register __d1 ULONG,
	register __d2 ULONG,
	register __d3 ULONG,
	register __a0 struct BitMap *,
	register __a6 struct Library *);

#endif
