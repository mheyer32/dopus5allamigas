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

#include "dopusbase.h"
#include "read_ilbm.h"
#include "wb.h"
#include "filetypes.h"
#include "images.h"
#include "dos_patch.h"

// Locale
#define CATCOMP_NUMBERS
#include "string_data.h"

struct MyLibrary
{
        struct             Library ml_Lib;
        ULONG              ml_SegList;
        ULONG              ml_Flags;
        APTR               ml_ExecBase; /* pointer to exec base  */
        ULONG              ml_UserData;
};

struct LibData
{
	WB_Data			wb_data;
	char			null_string[4];

	struct MinList		notify_list;
	struct SignalSemaphore	notify_lock;

	struct Library		*dos_base;
	struct Library		*icon_base;

	IPCData			*launch_proc;
	struct MinList		launch_list;
	struct SignalSemaphore	launch_lock;
	ULONG			launch_count;

	BPTR			path_list;
	struct SignalSemaphore	path_lock;

	struct Library		*int_base;
	struct MinList		error_list;
	ULONG			error_wait;

	struct DOpusLocale	locale;

	struct ListLock		semaphores;

	APTR			memory;

	struct ListLock		device_list;
	ULONG			flags;

	Class			*dt_class;
	ULONG			old_openlib;
	struct MyLibrary	dt_lib;

	ULONG a4;

	IPCData			*fake_wb;
	struct MyLibrary	*dopus_base;
	struct Library		*gfx_base;

	struct ListLock		file_list;
	BPTR			last_file;

	struct ListLock		filetype_cache;
	ULONG			ft_cache_count;
	ULONG			ft_cache_max;

	struct Library		*TimerBase;
	struct IORequest	timer_io;
};

typedef struct {
	struct MinNode		node;
	struct MsgPort		*port;
	ULONG			userdata;
	ULONG			type;
} NotifyNode;

typedef struct {
	struct Node		node;
	unsigned long		flags;
	struct DosList		*dos_ptr;
	struct MsgPort		*dol_Task;
	char			dol_Name[34];
} DeviceNode;

#define STRING_CONVERT_KEY	3000

#define DNF_OK		(1<<0)

extern struct Library *SysBase;
//extern struct Library *DOSBase;
//extern struct Library *IntuitionBase;
//extern struct Library *GfxBase;
extern struct Library *GadToolsBase;
extern struct Library *AslBase;
extern struct Library *UtilityBase;
extern struct Library *LocaleBase;
extern struct Library *LayersBase;
extern struct Library *IconBase;
extern struct Library *WorkbenchBase;
extern struct Library *DataTypesBase;
extern struct Library *CyberGfxBase;
extern struct TextFont *topaz_font;

extern struct List 		image_list;
extern struct SignalSemaphore	image_lock;
extern APTR			image_memory;
extern APTR			chip_memory;

extern Class
	*listview_class,*image_class,*button_class,*palette_class,*string_class,
	*check_class,*view_class,*frame_class;

extern char decimal_point;

extern IPCData *launcher_ipc;

#define GET_DOPUSLIB	((struct MyLibrary *)FindName(&((struct ExecBase *)*((ULONG *)4))->LibList,"dopus5.library"))

void KPrintF __ARGS((char *,...));
void lsprintf __ARGS((char *,...));
void lsprintfa __ARGS((char *,...));
void __asm LSprintf(register __a3 char *buffer,register __a0 char *string,register __a1 APTR data);
ULONG __asm L_DivideU(
	register __d0 unsigned long,
	register __d1 unsigned long,
	register __a0 unsigned long *,
	register __a1 struct Library *);

#include "pools.h"

// functions.a
__asm L_BtoCStr(register __a0 BSTR,register __a1 char *,register __d0 int);

// timer.c
struct TimerHandle *__asm L_AllocTimer(register __d0 ULONG unit,register __a0 struct MsgPort *);
void __asm L_FreeTimer(register __a0 struct TimerHandle *handle);
void __asm L_StartTimer(register __a0 TimerHandle *handle,register __d0 ULONG seconds,register __d1 ULONG micros);
BOOL __asm L_CheckTimer(register __a0 TimerHandle *handle);
void __asm L_StopTimer(register __a0 TimerHandle *handle);

// pathlist.c
BPTR __asm L_GetDosPathList(register __a0 BPTR);
void __asm L_FreeDosPathList(register __a0 BPTR);
void __asm L_CopyLocalEnv(register __a0 struct Library *DOSBase);

// strings.c
__asm L_StrCombine(register __a0 char *buf,
	register __a1 char *one,
	register __a2 char *two,
	register __d0 int lim);
__asm L_StrConcat(register __a0 char *buf,
	register __a1 char *cat,
	register __d0 int lim);
__asm L_Atoh(register __a0 unsigned char *,
	register __d0 int);


// gui.c
void __asm L_DrawBox(
	register __a0 struct RastPort *rp,
	register __a1 struct Rectangle *rect,
	register __a2 struct DrawInfo *info,
	register __d0 BOOL recessed);
void __asm L_DrawFieldBox(
	register __a0 struct RastPort *rp,
	register __a1 struct Rectangle *rect,
	register __a2 struct DrawInfo *info);
BOOL __asm L_WriteIcon(
	register __a0 char *name,
	register __a1 struct DiskObject *diskobj,
	register __a6 struct MyLibrary *libbase);
ULONG __asm L_ScreenInfo(register __a0 struct Screen *screen);

void draw_field_box(
	struct RastPort *rp,
	struct Rectangle *rect,
	struct DrawInfo *info,
	struct Library *GfxBase);


// misc.c
void __asm L_BuildKeyString(
	register __d0 unsigned short,
	register __d1 unsigned short,
	register __d2 unsigned short,
	register __d3 unsigned short,
	register __a0 char *);
USHORT __asm L_QualValid(register __d0 unsigned short);
BOOL __asm L_ConvertRawKey(
	register __d0 USHORT code,
	register __d1 USHORT qual,
	register __a0 char *key);
void __asm L_SetBusyPointer(register __a0 struct Window *);
void __asm L_ActivateStrGad(
	register __a0 struct Gadget *,
	register __a1 struct Window *);
void __asm L_RefreshStrGad(
	register __a0 struct Gadget *,
	register __a1 struct Window *);
void __asm L_Itoa(
	register __d0 long num,
	register __a0 char *str,
	register __d1 char sep);
void __asm L_ItoaU(
	register __d0 unsigned long num,
	register __a0 char *str,
	register __d1 char sep);
void __asm L_BytesToString(
	register __d0 unsigned long bytes,
	register __a0 char *string,
	register __d1 short places,
	register __d2 char sep);
void __asm L_DivideToString(
	register __a0 char *string,
	register __d0 unsigned long bytes,
	register __d1 unsigned long div,
	register __d2 short places,
	register __d3 char sep);
void __asm L_Ito26(
	register __d0 unsigned long num,
	register __a0 char *str);
BOOL __asm L_SerialValid(register __a0 serial_data *data);
void __asm L_WriteFileIcon(
	register __a0 char *source,
	register __a1 char *dest,
	register __a6 struct MyLibrary *libbase);
BOOL __asm L_GetWBArgPath(
	register __a0 struct WBArg *arg,
	register __a1 char *buffer,
	register __d0 long size,
	register __a6 struct MyLibrary *libbase);
struct PubScreenNode *__asm L_FindPubScreen(
	register __a0 struct Screen *screen,
	register __d0 BOOL lock);


// simplerequest.c
__asm L_DoSimpleRequest(register __a0 struct Window *,
	register __a1 struct DOpusSimpleRequest *,
	register __a6 struct Library *);
__asm L_SimpleRequest(
	register __a0 struct Window *parent,
	register __a1 char *title,
	register __a2 char *buttons,
	register __a3 char *message,
	register __a4 char *buffer,
	register __a5 APTR params,
	register __d0 long buffersize,
	register __d1 ULONG flags,
	register __a6 struct Library *);


// drag_routines.c
DragInfo *__asm L_GetDragInfo(
	register __a0 struct Window *,
	register __a1 struct RastPort *,
	register __d0 long width,
	register __d1 long height,
	register __d2 long);
void __asm L_FreeDragInfo(register __a0 DragInfo *drag);
void __asm L_HideDragImage(register __a0 DragInfo *drag);
void __asm L_GetDragImage(
	register __a0 DragInfo *drag,
	register __d0 ULONG x,
	register __d1 ULONG y);
void __asm L_GetDragMask(register __a0 DragInfo *drag);
void __asm L_ShowDragImage(
	register __a0 DragInfo *drag,
	register __d0 ULONG x,
	register __d1 ULONG y);
void __asm L_AddDragImage(register __a0 DragInfo *drag);
void __asm L_RemDragImage(register __a0 DragInfo *drag);
void __asm L_StampDragImage(
	register __a0 DragInfo *drag,
	register __d0 ULONG x,
	register __d1 ULONG y);
BOOL __asm L_CheckDragDeadlock(
	register __a0 DragInfo *drag);
BOOL __asm L_BuildTransDragMask(
	register __a0 USHORT *mask,
	register __a1 USHORT *image,
	register __d0 short width,
	register __d1 short height,
	register __d2 short depth);



// layout_routines.c
struct Window *__asm L_OpenConfigWindow(
	register __a0 NewConfigWindow *,
	register __a6 struct MyLibrary *);
void __asm L_CloseConfigWindow(register __a0 struct Window *);
void __asm L_StripIntuiMessages(register __a0 struct Window *);
void __asm L_CloseWindowSafely(register __a0 struct Window *);
__asm L_CalcObjectDims(
	register __a0 void *parent,
	register __a1 struct TextFont *use_font,
	register __a2 struct IBox *pos,
 	register __a3 struct IBox *dest_pos,
 	register __a4 GL_Object *,
 	register __d0 ULONG flags,
 	register __d1 GL_Object *,
 	register __d2 GL_Object *);
__asm L_CalcWindowDims(
	register __a0 struct Screen *screen,
	register __a1 ConfigWindow *win_pos,
	register __a2 struct IBox *dest_pos,
	register __a3 struct TextFont *font,
	register __d0 ULONG flags);
ObjectList *__asm L_AddObjectList(
	register __a0 struct Window *,
	register __a1 ObjectDef *objects);
void __asm L_FreeObject(
	register __a0 ObjectList *objlist,
	register __a1 GL_Object *object);
void __asm L_FreeObjectList(register __a0 ObjectList *objlist);
GL_Object *__asm L_GetObject(
	register __a0 ObjectList *list,
	register __d0 int id);
void __asm L_StoreGadgetValue(
	register __a0 ObjectList *list,
	register __a1 struct IntuiMessage *msg,
	register __a6 struct MyLibrary *);
void __asm L_UpdateGadgetValue(
	register __a0 ObjectList *list,
	register __a1 struct IntuiMessage *msg,
	register __d0 USHORT id,
	register __a6 struct MyLibrary *);
void __asm L_SetGadgetValue(
	register __a0 ObjectList *list,
	register __d0 USHORT id,
	register __d1 ULONG value);
long __asm L_GetGadgetValue(
	register __a0 ObjectList *list,
	register __a1 USHORT id,
	register __a6 struct MyLibrary *);
__asm L_CheckObjectArea(
	register __a0 GL_Object *object,
	register __d0 int x,
	register __d1 int y);
void __asm L_DisplayObject(
	register __a0 struct Window *,
	register __a1 GL_Object *object,
	register __d0 int fg,
	register __d1 int bg,
	register __a2 char *txt);
void __asm L_AddWindowMenus(
	register __a0 struct Window *,
	register __a1 MenuData *menudata);
void __asm L_FreeWindowMenus(
	register __a0 struct Window *);
void __asm L_SetWindowBusy(register __a0 struct Window *);
void __asm L_ClearWindowBusy(register __a0 struct Window *);
STRPTR __asm L_GetString(
	register __a0 struct DOpusLocale *li,
	register __d0 LONG stringNum);
struct Gadget *__asm L_FindKeyEquivalent(
	register __a0 ObjectList *list,
	register __a1 struct IntuiMessage *msg,
	register __d0 int process);
void __asm L_ShowProgressBar(
	register __a0 struct Window *,
	register __a1 GL_Object *object,
	register __d0 ULONG total,
	register __d1 ULONG count);
void __asm L_SetObjectKind(
	register __a0 ObjectList *list,
	register __d0 ULONG id,
	register __d1 USHORT kind);
void __asm L_DisableObject(
	register __a0 ObjectList *list,
	register __d0 ULONG id,
	register __d1 BOOL state);
__asm L_BoundsCheckGadget(
	register __a0 ObjectList *list,
	register __d0 ULONG id,
	register __d1 int min,
	register __d2 int max);
void __asm L_RefreshObjectList(
	register __a0 struct Window *,
	register __a1 ObjectList *ref_list);
struct IntuiMessage *__asm L_GetWindowMsg(
	register __a0 struct MsgPort *port);
void __asm L_ReplyWindowMsg(
	register __a0 struct IntuiMessage *msg);
void __asm L_SetGadgetChoices(
	register __a0 ObjectList *list,
	register __d0 ULONG id,
	register __a1 APTR choices);
void __asm L_SetWindowID(
	register __a0 struct Window *,
	register __a1 WindowID *id,
	register __d0 ULONG window_id,
	register __a2 struct MsgPort *port);
ULONG __asm L_GetWindowID(register __a0 struct Window *);
struct MsgPort *__asm L_GetWindowAppPort(register __a0 struct Window *);
BOOL __asm L_GetObjectRect(
	register __a0 ObjectList *list,
	register __d0 ULONG id,
	register __a1 struct Rectangle *rect);

void __asm L_StartRefreshConfigWindow(
	register __a0 struct Window *,
	register __d0 long final_state);
void __asm L_EndRefreshConfigWindow(
	register __a0 struct Window *);


// menu_routines.c
struct Menu *__asm L_BuildMenuStrip(
	register __a0 MenuData *menudata,
	register __a1 struct DOpusLocale *locale);
struct MenuItem *__asm L_FindMenuItem(
	register __a0 struct Menu *menu,
	register __d0 USHORT id);


// list_management.c
Att_List *__asm L_Att_NewList(register __d0 ULONG);
Att_Node *__asm L_Att_NewNode(
	register __a0 Att_List *list,
	register __a1 char *name,
	register __d0 ULONG data,
	register __d1 ULONG flags);
void __asm L_Att_RemNode(register __a0 Att_Node *node);
void __asm L_Att_PosNode(
	register __a0 Att_List *list,
	register __a1 Att_Node *node,
	register __a2 Att_Node *before);
void __asm L_Att_RemList(
	register __a0 Att_List *list,
	register __d0 long flags);
Att_Node *__asm L_Att_FindNode(
	register __a0 Att_List *list,
	register __d0 long number);
__asm L_Att_NodeNumber(
	register __a0 Att_List *list,
	register __a1 char *name);
Att_Node *__asm L_Att_FindNodeData(
	register __a0 Att_List *list,
	register __d0 ULONG data);
__asm L_Att_NodeDataNumber(
	register __a0 Att_List *list,
	register __d0 ULONG data);
char *__asm L_Att_NodeName(
	register __a0 Att_List *list,
	register __d0 long number);
__asm L_Att_NodeCount(register __a0 Att_List *list);
void __asm L_Att_ChangeNodeName(
	register __a0 Att_Node *node,
	register __a1 char *name);
__asm L_Att_FindNodeNumber(
	register __a0 Att_List *list,
	register __a1 Att_Node *node);
void __asm L_AddSorted(
	register __a0 struct List *list,
	register __a1 struct Node *node);
struct Node *__asm L_FindNameI(
	register __a0 struct List *list,
	register __a1 char *name);
void __asm L_LockAttList(
	register __a0 Att_List *list,
	register __d0 short exclusive);
void __asm L_UnlockAttList(register __a0 Att_List *list);
void __asm L_SwapListNodes(
	register __a0 struct List *list,
	register __a1 struct Node *swap1,
	register __a2 struct Node *swap2);
BOOL __asm L_IsListLockEmpty(register __a0 struct ListLock *);

// memory.c
void *__asm L_NewMemHandle(
	register __d0 ULONG puddle_size,
	register __d1 ULONG thresh_size,
	register __d2 ULONG type);
void __asm L_FreeMemHandle(register __a0 MemHandle *handle);
void __asm L_ClearMemHandle(register __a0 MemHandle *handle);
void *__asm L_AllocMemH(
	register __a0 MemHandle *handle,
	register __d0 ULONG size);
void __asm L_FreeMemH(register __a0 void *memory);


// config routines
Cfg_Lister *__asm L_NewLister(register __a0 char *path);
Cfg_ButtonBank *__asm L_NewButtonBank(register __d0 BOOL,register __d1 short type);
Cfg_Button *__asm L_NewButton(register __a0 APTR memory);
Cfg_Function *__asm L_NewFunction(register __a0 APTR memory,register __d0 UWORD type);
Cfg_ButtonFunction *__asm L_NewButtonFunction(register __a0 APTR memory,register __d0 UWORD type);
Cfg_Instruction *__asm L_NewInstruction(register __a0 APTR memory,register __d0 short type,register __a1 char *string);
Cfg_Filetype *__asm L_NewFiletype(register __a0 APTR memory);

short __asm L_ReadSettings(register __a0 CFG_SETS *,register __a1 char *name);
Cfg_Lister *__asm L_ReadListerDef(register __a0 struct _IFFHandle *iff,register __d0 ULONG);
Cfg_ButtonBank *__asm L_OpenButtonBank(register __a0 char *name);
Cfg_FiletypeList *__asm L_ReadFiletypes(
	register __a0 char *name,
	register __a1 APTR memory);
Cfg_Button *__asm L_ReadButton(
	register __a0 struct _IFFHandle *iff,
	register __a1 APTR memory);
Cfg_Function *__asm L_ReadFunction(
	register __a0 struct _IFFHandle *iff,
	register __a1 APTR memory,
	register __a2 struct List *func_list,
	register __a3 Cfg_Function *function);

void __asm L_DefaultSettings(register __a0 CFG_SETS *);
void __asm L_DefaultEnvironment(register __a0 CFG_ENVR *);
Cfg_ButtonBank *__asm L_DefaultButtonBank(void);

__asm L_SaveListerDef(register __a0 struct _IFFHandle *iff,register __a1 Cfg_Lister *lister);
__asm L_SaveButton(register __a0 struct _IFFHandle *iff,register __a1 Cfg_Button *button);
__asm L_SaveFunction(register __a0 struct _IFFHandle *iff,register __a1 Cfg_Function *function);

void __asm L_CloseButtonBank(register __a0 Cfg_ButtonBank *bank);
void __asm L_FreeListerDef(register __a0 Cfg_Lister *lister);
void __asm L_FreeButtonList(register __a0 struct List *list);
void __asm L_FreeButtonImages(register __a0 struct List *list);
void __asm L_FreeButton(register __a0 Cfg_Button *button);
void __asm L_FreeFunction(register __a0 Cfg_Function *function);
void __asm L_FreeButtonFunction(register __a0 Cfg_ButtonFunction *function);
void __asm L_FreeInstruction(register __a0 Cfg_Instruction *ins);
void __asm L_FreeInstructionList(register __a0 Cfg_Function *func);
void __asm L_FreeFiletypeList(register __a0 Cfg_FiletypeList *list);
void __asm L_FreeFiletype(register __a0 Cfg_Filetype *type);

Cfg_ButtonBank *__asm L_CopyButtonBank(register __a0 Cfg_ButtonBank *orig);
Cfg_Button *__asm L_CopyButton(register __a0 Cfg_Button *orig,register __a1 APTR,register __d0 short);
Cfg_Filetype *__asm L_CopyFiletype(register __a0 Cfg_Filetype *,register __a1 APTR);
Cfg_Function *__asm L_CopyFunction(register __a0 Cfg_Function *orig,register __a1 APTR,register __a2 Cfg_Function *new);
Cfg_ButtonFunction *__asm L_CopyButtonFunction(register __a0 Cfg_ButtonFunction *,register __a1 APTR,register __a2 Cfg_ButtonFunction *);

Cfg_Function *__asm L_FindFunctionType(
	register __a0 struct List *list,
	register __d0 UWORD type);


// popup menus
USHORT __asm L_DoPopUpMenu(register __a0 struct Window *,register __a1 PopUpMenu *,register __a2 PopUpItem **,register __d0 USHORT);
PopUpItem *__asm L_GetPopUpItem(register __a0 PopUpMenu *menu,register __d0 USHORT id);


// ipc
__asm  L_IPC_Launch(
	register __a0 struct ListLock *list,
	register __a1 IPCData **storage,
	register __a2 char *name,
	register __d0 ULONG entry,
	register __d1 ULONG stack,
	register __d2 ULONG data,
	register __a3 struct Library *dos_base,
	register __a6 struct MyLibrary *);
__asm  L_IPC_Startup(
	register __a0 IPCData *ipc,
	register __a1 APTR data,
	register __a2 struct MsgPort *reply);
ULONG __asm  L_IPC_Command(
	register __a0 IPCData *ipc,
	register __d0 ULONG command,
	register __d1 ULONG flags,
	register __a1 APTR data,
	register __a2 APTR data_free,
	register __a3 struct MsgPort *reply);
void __asm  L_IPC_Reply(register __a0 IPCMessage *msg);
void __asm  L_IPC_Free(register __a0 IPCData *ipc);
IPCData *__asm  L_IPC_FindProc(
	register __a0 struct ListLock *list,
	register __a1 char *name,
	register __d0 BOOL,
	register __d1 ULONG);
IPCData *__asm  L_IPC_ProcStartup(
	register __a0 ULONG *data,
	register __a1 ULONG (*__asm code)(register __a0 IPCData *,register __a1 APTR));
void __asm L_IPC_Quit(
	register __a0 IPCData *ipc,
	register __d0 ULONG quit_flags,
	register __d1 BOOL wait);
void __asm L_IPC_Hello(
	register __a0 IPCData *ipc,
	register __a1 IPCData *owner);
void __asm L_IPC_Goodbye(
	register __a0 IPCData *ipc,
	register __a1 IPCData *owner,
	register __d0 ULONG goodbye_flags);
ULONG __asm L_IPC_GetGoodbye(register __a0 IPCMessage *msg);
ULONG __asm L_IPC_ListQuit(
	register __a0 struct ListLock *list,
	register __a1 IPCData *owner,
	register __d0 ULONG quit_flags,
	register __d1 BOOL wait);
void __asm L_IPC_Flush(register __a0 IPCData *ipc);
void __asm L_IPC_ListCommand(
	register __a0 struct ListLock *list,
	register __d0 ULONG command,
	register __d1 ULONG flags,
	register __d2 ULONG data,
	register __d3 BOOL wait);
void __asm L_IPC_QuitName(
	register __a0 struct ListLock *,
	register __a1 char *name,
	register __d0 ULONG quit_flags);


// Image routines
APTR __asm L_OpenImage(register __a0 char *name,register __a1 OpenImageInfo *);
void __asm L_CloseImage(register __a0 APTR image);
APTR __asm L_CopyImage(register __a0 APTR image);
void __asm L_FlushImages(void);
short __asm L_RenderImage(
	register __a0 struct RastPort *rp,
	register __a1 APTR image,
	register __d0 unsigned short left,
	register __d1 unsigned short top,
	register __a2 struct TagItem *tags);
void __asm L_GetImageAttrs(
	register __a0 APTR imptr,
	register __a1 struct TagItem *tags);
BOOL __asm L_RemapImage(
	register __a0 Image_Data *image,
	register __a1 struct Screen *screen,
	register __a2 ImageRemap *remap);
void __asm L_FreeRemapImage(
	register __a0 Image_Data *image,
	register __a1 ImageRemap *remap);


// status window
struct Window *__asm L_OpenStatusWindow(
	register __a0 char *,
	register __a1 char *,
	register __a2 struct Screen *,
	register __d1 LONG,
	register __d0 ULONG,
	register __a6 struct MyLibrary *);
void __asm L_SetStatusText(
	register __a0 struct Window *,
	register __a1 char *text);
void __asm L_UpdateStatusGraph(
	register __a0 struct Window *,
	register __a1 char *text,
	register __d0 ULONG total,
	register __d1 ULONG count);


// read_ilbm
ILBMHandle *__asm L_ReadILBM(
	register __a0 char *name,
	register __d0 ULONG flags);
void __asm L_FreeILBM(register __a0 ILBMHandle *ilbm);
void __asm L_DecodeILBM(
	register __a0 char *source,
	register __d0 unsigned short width,
	register __d1 unsigned short height,
	register __d2 unsigned short depth,
	register __a1 struct BitMap *dest,
	register __d3 unsigned long flags,
	register __d4 char comp);
void __asm L_DecodeRLE(register __a0 RLEinfo *rle);
ILBMHandle *__asm L_FakeILBM(
	register __a0 USHORT *imagedata,
	register __a1 ULONG *palette,
	register __d0 short width,
	register __d1 short height,
	register __d2 short depth,
	register __d3 ULONG flags);

// anim
void __asm L_AnimDecodeRIFFXor(
	register __a0 unsigned char *delta,
	register __a1 char *plane,
	register __d0 unsigned short rowbytes,
	register __d1 unsigned short sourcebytes);
void __asm L_AnimDecodeRIFFSet(
	register __a0 unsigned char *delta,
	register __a1 char *plane,
	register __d0 unsigned short rowbytes,
	register __d1 unsigned short sourcebytes);


// palette
void __asm L_LoadPalette32(
	register __a0 struct ViewPort *vp,
	register __a1 unsigned long *palette);
void __asm L_GetPalette32(
	register __a0 struct ViewPort *vp,
	register __a1 unsigned long *palette,
	register __d0 unsigned short count,
	register __d1 short first);


// buffered_io
APTR __asm L_OpenBuf(
	register __a0 char *name,
	register __d0 long mode,
	register __d1 long buffer_size);
void __asm L_CloseBuf(register __a0 APTR file);
long __asm L_ReadBuf(
	register __a0 APTR file,
	register __a1 char *data,
	register __d0 long size);
long __asm L_WriteBuf(
	register __a0 APTR file,
	register __a1 char *data,
	register __d0 long size);
void __asm L_FlushBuf(register __a0 APTR file);
long __asm L_SeekBuf(
	register __a0 APTR file,
	register __d0 long offset,
	register __d1 long mode);
long __asm L_ExamineBuf(
	register __a0 APTR file,
	register __a1 struct FileInfoBlock *fib);
BPTR __asm L_FHFromBuf(
	register __a0 APTR file);


// diskio
DiskHandle *__asm L_OpenDisk(register __a0 char *disk,register __a1 struct MsgPort *);
void __asm L_CloseDisk(register __a0 DiskHandle *handle);


// boopsi
struct Gadget *__asm L_AddScrollBars(
	register __a0 struct Window *,
	register __a1 struct List *list,
	register __a2 struct DrawInfo *draw_info,
	register __d0 short noidcmpupdate);
struct Gadget *__asm L_FindBOOPSIGadget(
	register __a0 struct List *list,
	register __d0 USHORT id);
void __asm L_BOOPSIFree(register __a0 struct List *list);
struct Gadget *__asm L_CreateTitleGadget(
	register __a0 struct Screen *screen,
	register __a1 struct List *list,
	register __d0 BOOL cover_zoom,
	register __d1 short offset,
	register __d2 short type,
	register __d3 unsigned short id,
	register __a6 struct MyLibrary *libbase);
struct Gadget *__asm L_FindGadgetType(
	register __a0 struct Gadget *gadget,
	register __d0 UWORD type);
void __asm L_FixTitleGadgets(register __a0 struct Window *window);


// launcher
void launcher_proc(void);


// iff
struct _IFFHandle *__asm L_IFFOpen(
	register __a0 char *,
	register __d0 unsigned short,
	register __d1 ULONG);
void __asm L_IFFClose(register __a0 struct _IFFHandle *);
long __asm L_IFFPushChunk(
	register __a0 struct _IFFHandle *,
	register __d0 ULONG);
long __asm L_IFFWriteChunkBytes(
	register __a0 struct _IFFHandle *,
	register __a1 char *,
	register __d0 long);
long __asm L_IFFPopChunk(register __a0 struct _IFFHandle *);
long __asm L_IFFWriteChunk(
	register __a0 struct _IFFHandle *,
	register __a1 char *,
	register __d0 ULONG,
	register __d1 ULONG);
unsigned long __asm L_IFFNextChunk(
	register __a0 struct _IFFHandle *handle,
	register __d0 unsigned long form);
long __asm L_IFFChunkSize(register __a0 struct _IFFHandle *handle);
long __asm L_IFFReadChunkBytes(
	register __a0 struct _IFFHandle *handle,
	register __a1 APTR buffer,
	register __d0 long size);
APTR __asm L_IFFFileHandle(register __a0 struct _IFFHandle *handle);
long __asm L_IFFChunkRemain(register __a0 struct _IFFHandle *handle);
unsigned long __asm L_IFFChunkID(register __a0 struct _IFFHandle *handle);
unsigned long __asm L_IFFGetFORM(register __a0 struct _IFFHandle *handle);


long __asm L_GetSemaphore(
	register __a0 struct SignalSemaphore *sem,
	register __d0 long exclusive,
	register __a1 char *data);
void __asm L_FreeSemaphore(
	register __a0 struct SignalSemaphore *sem);
void __asm L_ShowSemaphore(
	register __a0 struct SignalSemaphore *sem);
void __asm L_InitListLock(
	register __a0 struct ListLock *ll,
	register __a1 char *name);


// layout_utils.c
void __asm L_InitWindowDims(
	register __a0 struct Window *,
	register __a1 WindowDimensions *dims);
void __asm L_StoreWindowDims(
	register __a0 struct Window *,
	register __a1 WindowDimensions *dims);
BOOL __asm L_CheckWindowDims(
	register __a0 struct Window *,
	register __a1 WindowDimensions *dims);
void __asm L_LayoutResize(register __a0 struct Window *);


// devices
struct DosList *__asm L_DeviceFromLock(
	register __a0 BPTR lock,
	register __a1 char *name,
	register __a6 struct MyLibrary *libbase);
struct DosList *__asm L_DeviceFromHandler(
	register __a0 struct MsgPort *port,
	register __a1 char *name,
	register __a6 struct MyLibrary *libbase);
BOOL __asm L_DevNameFromLock(
	register __d1 BPTR lock,
	register __d2 char *buffer,
	register __d3 long len,
	register __a6 struct MyLibrary *libbase);


// datatypes
ULONG __asm dt_dispatch(
	register __a0 Class *cl,
	register __a2 Object *obj,
	register __a1 Msg msg);
void dt_install_patch(struct LibData *data);
void dt_remove_patch(struct LibData *data);


// icon cache
struct DiskObject *__asm L_GetCachedDefDiskObject(
	register __d0 long type,
	register __a6 struct MyLibrary *libbase);
void __asm L_FreeCachedDiskObject(
	register __a0 struct DiskObject *icon,
	register __a6 struct MyLibrary *libbase);
struct DiskObject *__asm L_GetCachedDiskObject(
	register __a0 char *name,
	register __a6 struct MyLibrary *libbase);
struct DiskObject *__asm L_GetCachedDiskObjectNew(
	register __a0 char *name,
	register __a6 struct MyLibrary *libbase);
unsigned long __asm L_IconCheckSum(
	register __a0 struct DiskObject *icon,
	register __d0 short which);


// progress
struct _ProgressWindow *__asm L_OpenProgressWindow(
	register __a0 struct TagItem *,
	register __a6 struct MyLibrary *lib);
void __asm L_CloseProgressWindow(
	register __a0 struct _ProgressWindow *);
void __asm L_HideProgressWindow(
	register __a0 struct _ProgressWindow *);
void __asm L_ShowProgressWindow(
	register __a0 struct _ProgressWindow *,
	register __a1 struct Screen *,
	register __a2 struct Window *);
void __asm L_SetProgressWindow(
	register __a0 struct _ProgressWindow *,
	register __a1 struct TagItem *);
BOOL __asm L_CheckProgressAbort(
	register __a0 struct _ProgressWindow *prog);


// string_hook
char *__asm L_GetSecureString(
	register __a0 struct Gadget *);


// search
long __asm L_SearchFile(
	register __a0 APTR file,
	register __a1 UBYTE *search_text,
	register __d0 ULONG flags,
	register __a2 UBYTE *buffer,
	register __d1 ULONG buffer_size);


// dates
char *__asm L_ParseDateStrings(
	register __a0 char *string,
	register __a1 char *date_buffer,
	register __a2 char *time_buffer,
	register __a3 long *range);

BOOL __asm L_DateFromStrings(
	register __a0 char *date,
	register __a1 char *time,
	register __a2 struct DateStamp *ds);


// filetypes
APTR __asm L_GetMatchHandle(register __a0 char *name,register __a6 struct MyLibrary *);
void __asm L_FreeMatchHandle(register __a0 MatchHandle *handle);
BOOL __asm L_MatchFiletype(
	register __a0 MatchHandle *handle,
	register __a1 Cfg_Filetype *type,
	register __a6 struct MyLibrary *);


// dos patches
BPTR __asm L_PatchedCreateDir(register __d1 char *name);
BPTR __asm L_OriginalCreateDir(
	register __d1 char *name,
	register __a6 struct MyLibrary *libbase);
BPTR __asm L_PatchedDeleteFile(register __d1 char *name);
long __asm L_OriginalDeleteFile(
	register __d1 char *name,
	register __a6 struct MyLibrary *libbase);


// requesters
long __asm L_AsyncRequest(
	register __a0 IPCData *my_ipc,
	register __d0 long type,
	register __a1 struct Window *,
	register __a2 REF_CALLBACK(callback),
	register __a3 APTR data,
	register __d1 struct TagItem *tags,
	register __a6 struct MyLibrary *libbase);
struct IntuiMessage *__asm L_CheckRefreshMsg(
	register __a0 struct Window *,
	register __d0 ULONG mask);


// bitmap.c
struct BitMap *__asm L_NewBitMap(
	register __d0 ULONG sizex,
	register __d1 ULONG sizey,
	register __d2 ULONG depth,
	register __d3 ULONG flags,
	register __a0 struct BitMap *friend_bitmap);
void __asm L_DisposeBitMap(
	register __a0 struct BitMap *bm);


// args.c
FuncArgs *__asm L_ParseArgs(
	register __a0 char *,
	register __a1 char *);
void __asm L_DisposeArgs(register __a0 FuncArgs *);


// appmsg.c
DOpusAppMessage *__asm L_AllocAppMessage(
	register __a0 APTR memory,
	register __a1 struct MsgPort *reply,
	register __d0 short num);
void __asm L_FreeAppMessage(
	register __a0 DOpusAppMessage *msg);
void __asm L_ReplyAppMessage(
	register __a0 DOpusAppMessage *msg);
BOOL __asm L_CheckAppMessage(register __a0 DOpusAppMessage *msg);
DOpusAppMessage *__asm L_CopyAppMessage(
	register __a0 DOpusAppMessage *orig,
	register __a1 APTR memory);
BOOL __asm L_SetWBArg(
	register __a0 DOpusAppMessage *msg,
	register __d0 short num,
	register __d1 BPTR lock,
	register __a1 char *name,
	register __a2 APTR memory);


// notify.c
APTR __asm L_AddNotifyRequest(
	register __d0 ULONG type,
	register __d1 ULONG userdata,
	register __a0 struct MsgPort *port,
	register __a6 struct MyLibrary *libbase);
void __asm L_RemoveNotifyRequest(
	register __a0 NotifyNode *node,
	register __a6 struct MyLibrary *libbase);
void __asm L_SendNotifyMsg(
	register __d0 ULONG type,
	register __d1 ULONG data,
	register __d2 ULONG flags,
	register __d3 short wait,
	register __a0 char *name,
	register __a1 struct FileInfoBlock *fib,
	register __a6 struct MyLibrary *libbase);
