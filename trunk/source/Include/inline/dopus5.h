#ifndef _INLINE_DOPUS_H
#define _INLINE_DOPUS_H

#ifndef CLIB_DOPUS_PROTOS_H
#define CLIB_DOPUS_PROTOS_H
#endif

#ifndef __INLINE_MACROS_H
#include <inline/macros.h>
#endif

//
// functions SimpleRequest(), SelectionList() and WB_LaunchNotify() implemented in 68k assember because of problems
// with a4 and/or a5 registers used as arguments, which make 68k gcc inlines works wrong.
//

#include <exec/types.h>

#ifndef DOPUS_BASE_NAME
#define DOPUS_BASE_NAME DOpusBase
#endif

#define RemovedFunc0() \
	LP0NR(0x1e, RemovedFunc0, \
	, DOPUS_BASE_NAME)

#define RandomDopus(limit) \
	LP1(0x24, UWORD, RandomDopus, int, limit, d0, \
	, DOPUS_BASE_NAME)

#define Atoh(str, len) \
	LP2(0x2a, ULONG, Atoh, char *, str, a0, short, len, d0, \
	, DOPUS_BASE_NAME)

#define BtoCStr(bstr, cstr, len) \
	LP3NR(0x30, BtoCStr, BSTR, bstr, a0, char *, cstr, a1, int, len, d0, \
	, DOPUS_BASE_NAME)

#define DivideU(num, div, rem, utility) \
	LP4(0x36, ULONG, DivideU, ULONG, num, d0, ULONG, div, d1, ULONG *, rem, a0, struct Library *, utility, a1, \
	, DOPUS_BASE_NAME)

#define Itoa(num, str, sep) \
	LP3NR(0x3c, Itoa, long, num, d0, char *, str, a0, char, sep, d1, \
	, DOPUS_BASE_NAME)

#define ItoaU(num, str, sep) \
	LP3NR(0x42, ItoaU, ULONG, num, d0, char *, str, a0, char, sep, d1, \
	, DOPUS_BASE_NAME)

#define Ito26(num, str) \
	LP2NR(0x48, Ito26, ULONG, num, d0, char *, str, a0, \
	, DOPUS_BASE_NAME)

#define BytesToString(bytes, string, places, sep) \
	LP4NR(0x4e, BytesToString, ULONG, bytes, d0, char *, string, a0, short, places, d1, char, sep, d2, \
	, DOPUS_BASE_NAME)

#define DivideToString(string, num, div, places, sep) \
	LP5NR(0x54, DivideToString, char *, string, a0, ULONG, num, d0, ULONG, div, d1, short, places, d2, char, sep, d3, \
	, DOPUS_BASE_NAME)

#define SetBusyPointer(window) \
	LP1NR(0x5a, SetBusyPointer, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define BuildKeyString(code, qual, mask, same, buffer) \
	LP5NR(0x60, BuildKeyString, UWORD, code, d0, UWORD, qual, d1, UWORD, mask, d2, UWORD, same, d3, char *, buffer, a0, \
	, DOPUS_BASE_NAME)

#define ActivateStrGad(gadget, window) \
	LP2NR(0x66, ActivateStrGad, struct Gadget *, gadget, a0, struct Window *, window, a1, \
	, DOPUS_BASE_NAME)

#define AllocTimer(unit, port) \
	LP2(0x6c, struct TimerHandle *, AllocTimer, ULONG, unit, d0, struct MsgPort *, port, a0, \
	, DOPUS_BASE_NAME)

#define FreeTimer(handle) \
	LP1NR(0x72, FreeTimer, TimerHandle *, handle, a0, \
	, DOPUS_BASE_NAME)

#define StartTimer(handle, secs, micro) \
	LP3NR(0x78, StartTimer, TimerHandle *, handle, a0, ULONG, secs, d0, ULONG, micro, d1, \
	, DOPUS_BASE_NAME)

#define CheckTimer(handle) \
	LP1(0x7e, BOOL, CheckTimer, TimerHandle *, handle, a0, \
	, DOPUS_BASE_NAME)

#define StopTimer(handle) \
	LP1NR(0x84, StopTimer, TimerHandle *, handle, a0, \
	, DOPUS_BASE_NAME)

#define GetDosPathList(copy) \
	LP1(0x8a, BPTR, GetDosPathList, BPTR, copy, a0, \
	, DOPUS_BASE_NAME)

#define FreeDosPathList(list) \
	LP1NR(0x90, FreeDosPathList, BPTR, list, a0, \
	, DOPUS_BASE_NAME)

#define DoSimpleRequest(window, simplereq) \
	LP2(0x96, short, DoSimpleRequest, struct Window *, window, a0, struct DOpusSimpleRequest *, simplereq, a1, \
	, DOPUS_BASE_NAME)

#define WriteIcon(name, obj) \
	LP2(0xa8, BOOL, WriteIcon, char *, name, a0, struct DiskObject *, obj, a1, \
	, DOPUS_BASE_NAME)

#define WriteFileIcon(source, dest) \
	LP2NR(0xae, WriteFileIcon, char *, source, a0, char *, dest, a1, \
	, DOPUS_BASE_NAME)

#define GetDragInfo(window, rast, width, height, flags) \
	LP5(0xb4, DragInfo *, GetDragInfo, struct Window *, window, a0, struct RastPort *, rast, a1, long, width, d0, long, height, d1, long, flags, d2, \
	, DOPUS_BASE_NAME)

#define FreeDragInfo(draginfo) \
	LP1NR(0xba, FreeDragInfo, DragInfo *, draginfo, a0, \
	, DOPUS_BASE_NAME)

#define GetDragImage(draginfo, x, y) \
	LP3NR(0xc0, GetDragImage, DragInfo *, draginfo, a0, ULONG, x, d0, ULONG, y, d1, \
	, DOPUS_BASE_NAME)

#define ShowDragImage(draginfo, x, y) \
	LP3NR(0xc6, ShowDragImage, DragInfo *, draginfo, a0, ULONG, x, d0, ULONG, y, d1, \
	, DOPUS_BASE_NAME)

#define HideDragImage(draginfo) \
	LP1NR(0xcc, HideDragImage, DragInfo *, draginfo, a0, \
	, DOPUS_BASE_NAME)

#define StampDragImage(draginfo, x, y) \
	LP3NR(0xd2, StampDragImage, DragInfo *, draginfo, a0, ULONG, x, d0, ULONG, y, d1, \
	, DOPUS_BASE_NAME)

#define GetDragMask(drag) \
	LP1NR(0xd8, GetDragMask, DragInfo *, drag, a0, \
	, DOPUS_BASE_NAME)

#define CheckDragDeadlock(drag) \
	LP1(0xde, BOOL, CheckDragDeadlock, DragInfo *, drag, a0, \
	, DOPUS_BASE_NAME)

#define AddDragImage(drag) \
	LP1NR(0xe4, AddDragImage, DragInfo *, drag, a0, \
	, DOPUS_BASE_NAME)

#define RemDragImage(drag) \
	LP1NR(0xea, RemDragImage, DragInfo *, drag, a0, \
	, DOPUS_BASE_NAME)

#define OpenConfigWindow(newwindow) \
	LP1(0xf0, struct Window *, OpenConfigWindow, NewConfigWindow *, newwindow, a0, \
	, DOPUS_BASE_NAME)

#define CloseConfigWindow(window) \
	LP1NR(0xf6, CloseConfigWindow, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define GetWindowMsg(port) \
	LP1(0xfc, struct IntuiMessage *, GetWindowMsg, struct MsgPort *, port, a0, \
	, DOPUS_BASE_NAME)

#define ReplyWindowMsg(msg) \
	LP1NR(0x102, ReplyWindowMsg, struct IntuiMessage *, msg, a0, \
	, DOPUS_BASE_NAME)

#define StripIntuiMessagesDopus(window) \
	LP1NR(0x108, StripIntuiMessagesDopus, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define CloseWindowSafely(window) \
	LP1NR(0x10e, CloseWindowSafely, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define CalcObjectDims(parent, font, pos, dest, last, flags, obj, ob) \
	LP8A4(0x114, int, CalcObjectDims, void *, parent, a0, struct TextFont *, font, a1, struct IBox *, pos, a2, struct IBox *, dest, a3, GL_Object *, last, d7, ULONG, flags, d0, GL_Object *, obj, d1, GL_Object *, ob, d2, \
	, DOPUS_BASE_NAME)

#define CalcWindowDims(screen, pos, dest, font, flags) \
	LP5(0x11a, int, CalcWindowDims, struct Screen *, screen, a0, ConfigWindow *, pos, a1, struct IBox *, dest, a2, struct TextFont *, font, a3, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define AddObjectList(window, objects) \
	LP2(0x120, ObjectList *, AddObjectList, struct Window *, window, a0, ObjectDef *, objects, a1, \
	, DOPUS_BASE_NAME)

#define FreeObject(objlist, object) \
	LP2NR(0x126, FreeObject, ObjectList *, objlist, a0, GL_Object *, object, a1, \
	, DOPUS_BASE_NAME)

#define FreeObjectList(objlist) \
	LP1NR(0x12c, FreeObjectList, ObjectList *, objlist, a0, \
	, DOPUS_BASE_NAME)

#define RefreshObjectList(window, list) \
	LP2NR(0x132, RefreshObjectList, struct Window *, window, a0, ObjectList *, list, a1, \
	, DOPUS_BASE_NAME)

#define GetObject(list, id) \
	LP2(0x138, GL_Object *, GetObject, ObjectList *, list, a0, int, id, d0, \
	, DOPUS_BASE_NAME)

#define StoreGadgetValue(list, msg) \
	LP2NR(0x13e, StoreGadgetValue, ObjectList *, list, a0, struct IntuiMessage *, msg, a1, \
	, DOPUS_BASE_NAME)

#define SetGadgetValue(list, id, value) \
	LP3NR(0x144, SetGadgetValue, ObjectList *, list, a0, UWORD, id, d0, ULONG, value, d1, \
	, DOPUS_BASE_NAME)

#define GetGadgetValue(list, id) \
	LP2(0x14a, long, GetGadgetValue, ObjectList *, list, a0, UWORD, id, a1, \
	, DOPUS_BASE_NAME)

#define SetObjectKind(list, id, kind) \
	LP3NR(0x150, SetObjectKind, ObjectList *, list, a0, ULONG, id, d0, UWORD, kind, d1, \
	, DOPUS_BASE_NAME)

#define SetGadgetChoices(list, id, choices) \
	LP3NR(0x156, SetGadgetChoices, ObjectList *, list, a0, ULONG, id, d0, APTR, choices, a1, \
	, DOPUS_BASE_NAME)

#define CheckObjectArea(object, x, y) \
	LP3(0x15c, BOOL, CheckObjectArea, GL_Object *, object, a0, int, x, d0, int, y, d1, \
	, DOPUS_BASE_NAME)

#define GetObjectRect(list, id, rect) \
	LP3(0x162, BOOL, GetObjectRect, ObjectList *, list, a0, ULONG, id, d0, struct Rectangle *, rect, a1, \
	, DOPUS_BASE_NAME)

#define DisplayObject(window, object, fg, bg, txt) \
	LP5NR(0x168, DisplayObject, struct Window *, window, a0, GL_Object *, object, a1, int, fg, d0, int, bg, d1, char *, txt, a2, \
	, DOPUS_BASE_NAME)

#define DisableObject(list, id, state) \
	LP3NR(0x16e, DisableObject, ObjectList *, list, a0, ULONG, id, d0, BOOL, state, d1, \
	, DOPUS_BASE_NAME)

#define BoundsCheckGadget(list, id, min, max) \
	LP4(0x174, int, BoundsCheckGadget, ObjectList *, list, a0, ULONG, id, d0, int, min, d1, int, max, d2, \
	, DOPUS_BASE_NAME)

#define AddWindowMenus(window, data) \
	LP2NR(0x17a, AddWindowMenus, struct Window *, window, a0, MenuData *, data, a1, \
	, DOPUS_BASE_NAME)

#define FreeWindowMenus(window) \
	LP1NR(0x180, FreeWindowMenus, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define SetWindowBusy(window) \
	LP1NR(0x186, SetWindowBusy, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define ClearWindowBusy(window) \
	LP1NR(0x18c, ClearWindowBusy, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define GetString(locale, num) \
	LP2(0x192, STRPTR, GetString, struct DOpusLocale *, locale, a0, LONG, num, d0, \
	, DOPUS_BASE_NAME)

#define FindKeyEquivalent(list, msg, process) \
	LP3(0x198, struct Gadget *, FindKeyEquivalent, ObjectList *, list, a0, struct IntuiMessage *, msg, a1, int, process, d0, \
	, DOPUS_BASE_NAME)

#define ShowProgressBar(window, object, total, count) \
	LP4NR(0x19e, ShowProgressBar, struct Window *, window, a0, GL_Object *, object, a1, ULONG, total, d0, ULONG, count, d1, \
	, DOPUS_BASE_NAME)

#define SetWindowID(window, id_ptr, id, port) \
	LP4NR(0x1a4, SetWindowID, struct Window *, window, a0, WindowID *, id_ptr, a1, ULONG, id, d0, struct MsgPort *, port, a2, \
	, DOPUS_BASE_NAME)

#define GetWindowID(window) \
	LP1(0x1aa, ULONG, GetWindowID, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define GetWindowAppPort(window) \
	LP1(0x1b0, struct MsgPort *, GetWindowAppPort, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define Att_NewList(flags) \
	LP1(0x1b6, Att_List *, Att_NewList, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define Att_NewNode(list, name, data, flags) \
	LP4(0x1bc, Att_Node *, Att_NewNode, Att_List *, list, a0, char *, name, a1, ULONG, data, d0, ULONG, flags, d1, \
	, DOPUS_BASE_NAME)

#define Att_RemNode(node) \
	LP1NR(0x1c2, Att_RemNode, Att_Node *, node, a0, \
	, DOPUS_BASE_NAME)

#define Att_PosNode(list, node, before) \
	LP3NR(0x1c8, Att_PosNode, Att_List *, list, a0, Att_Node *, node, a1, Att_Node *, before, a2, \
	, DOPUS_BASE_NAME)

#define Att_RemList(list, flags) \
	LP2NR(0x1ce, Att_RemList, Att_List *, list, a0, long, flags, d0, \
	, DOPUS_BASE_NAME)

#define Att_FindNode(list, number) \
	LP2(0x1d4, Att_Node *, Att_FindNode, Att_List *, list, a0, long, number, d0, \
	, DOPUS_BASE_NAME)

#define Att_NodeNumber(list, name) \
	LP2(0x1da, long, Att_NodeNumber, Att_List *, list, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define Att_FindNodeData(list, data) \
	LP2(0x1e0, Att_Node *, Att_FindNodeData, Att_List *, list, a0, ULONG, data, d0, \
	, DOPUS_BASE_NAME)

#define Att_NodeDataNumber(list, data) \
	LP2(0x1e6, long, Att_NodeDataNumber, Att_List *, list, a0, ULONG, data, d0, \
	, DOPUS_BASE_NAME)

#define Att_NodeName(list, number) \
	LP2(0x1ec, char *, Att_NodeName, Att_List *, list, a0, long, number, d0, \
	, DOPUS_BASE_NAME)

#define Att_NodeCount(list) \
	LP1(0x1f2, long, Att_NodeCount, Att_List *, list, a0, \
	, DOPUS_BASE_NAME)

#define Att_ChangeNodeName(node, name) \
	LP2NR(0x1f8, Att_ChangeNodeName, Att_Node *, node, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define Att_FindNodeNumber(list, node) \
	LP2(0x1fe, long, Att_FindNodeNumber, Att_List *, list, a0, Att_Node *, node, a1, \
	, DOPUS_BASE_NAME)

#define AddSorted(list, node) \
	LP2NR(0x204, AddSorted, struct List *, list, a0, struct Node *, node, a1, \
	, DOPUS_BASE_NAME)

#define BuildMenuStrip(data, locale) \
	LP2(0x20a, struct Menu *, BuildMenuStrip, MenuData *, data, a0, struct DOpusLocale *, locale, a1, \
	, DOPUS_BASE_NAME)

#define FindMenuItem(menu, id) \
	LP2(0x210, struct MenuItem *, FindMenuItem, struct Menu *, menu, a0, UWORD, id, d0, \
	, DOPUS_BASE_NAME)

#define DoPopUpMenu(window, menu, item, code) \
	LP4(0x216, UWORD, DoPopUpMenu, struct Window *, window, a0, PopUpMenu *, menu, a1, PopUpItem **, item, a2, UWORD, code, d0, \
	, DOPUS_BASE_NAME)

#define GetPopUpItem(menu, id) \
	LP2(0x21c, PopUpItem *, GetPopUpItem, PopUpMenu *, menu, a0, UWORD, id, d0, \
	, DOPUS_BASE_NAME)

#define IPC_Startup(ipc, data, reply) \
	LP3(0x222, int, IPC_Startup, IPCData *, ipc, a0, APTR, data, a1, struct MsgPort *, reply, a2, \
	, DOPUS_BASE_NAME)

#define IPC_Command(ipc, command, flags, data, data_free, reply) \
	LP6(0x228, ULONG, IPC_Command, IPCData *, ipc, a0, ULONG, command, d0, ULONG, flags, d1, APTR, data, a1, APTR, data_free, a2, struct MsgPort *, reply, a3, \
	, DOPUS_BASE_NAME)

#define IPC_Reply(msg) \
	LP1NR(0x22e, IPC_Reply, IPCMessage *, msg, a0, \
	, DOPUS_BASE_NAME)

#define IPC_Free(ipc) \
	LP1NR(0x234, IPC_Free, IPCData *, ipc, a0, \
	, DOPUS_BASE_NAME)

#define IPC_FindProc(list, name, act, data) \
	LP4(0x23a, IPCData *, IPC_FindProc, struct ListLock *, list, a0, char *, name, a1, BOOL, act, d0, ULONG, data, d1, \
	, DOPUS_BASE_NAME)

#define IPC_Quit(ipc, flags, wait) \
	LP3NR(0x240, IPC_Quit, IPCData *, ipc, a0, ULONG, flags, d0, BOOL, wait, d1, \
	, DOPUS_BASE_NAME)

#define IPC_Hello(ipc, owner) \
	LP2NR(0x246, IPC_Hello, IPCData *, ipc, a0, IPCData *, owner, a1, \
	, DOPUS_BASE_NAME)

#define IPC_Goodbye(ipc, owner, flags) \
	LP3NR(0x24c, IPC_Goodbye, IPCData *, ipc, a0, IPCData *, owner, a1, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define IPC_GetGoodbye(msg) \
	LP1(0x252, ULONG, IPC_GetGoodbye, IPCMessage *, msg, a0, \
	, DOPUS_BASE_NAME)

#define IPC_ListQuit(list, owner, flags, wait) \
	LP4(0x258, ULONG, IPC_ListQuit, struct ListLock *, list, a0, IPCData *, owner, a1, ULONG, flags, d0, BOOL, wait, d1, \
	, DOPUS_BASE_NAME)

#define IPC_Flush(port) \
	LP1NR(0x25e, IPC_Flush, IPCData *, port, a0, \
	, DOPUS_BASE_NAME)

#define IPC_ListCommand(list, command, flags, data, wait) \
	LP5NR(0x264, IPC_ListCommand, struct ListLock *, list, a0, ULONG, command, d0, ULONG, flags, d1, ULONG, data, d2, BOOL, wait, d3, \
	, DOPUS_BASE_NAME)

#define IPC_ProcStartup(data, code) \
	LP2FP(0x26a, IPCData *, IPC_ProcStartup, ULONG *, data, a0, __fpt, code, a1, \
	, DOPUS_BASE_NAME, ULONG (*__fpt)(IPCData *, APTR))

#define IPC_Launch(list, ipc, name, entry, stack, data, dos) \
	LP7(0x270, int, IPC_Launch, struct ListLock *, list, a0, IPCData **, ipc, a1, char *, name, a2, ULONG, entry, d0, ULONG, stack, d1, ULONG, data, d2, struct Library *, dos, a3, \
	, DOPUS_BASE_NAME)

#define OpenImage(name, info) \
	LP2(0x276, APTR, OpenImage, char *, name, a0, OpenImageInfo *, info, a1, \
	, DOPUS_BASE_NAME)

#define CloseImage(image) \
	LP1NR(0x27c, CloseImage, APTR, image, a0, \
	, DOPUS_BASE_NAME)

#define CopyImage(image) \
	LP1(0x282, APTR, CopyImage, APTR, image, a0, \
	, DOPUS_BASE_NAME)

#define FlushImages() \
	LP0NR(0x288, FlushImages, \
	, DOPUS_BASE_NAME)

#define RenderImage(rp, image, left, top, tags) \
	LP5(0x28e, short, RenderImage, struct RastPort *, rp, a0, APTR, image, a1, UWORD, left, d0, UWORD, top, d1, struct TagItem *, tags, a2, \
	, DOPUS_BASE_NAME)


#define GetImageAttrs(image, tags) \
	LP2NR(0x294, GetImageAttrs, APTR, image, a0, struct TagItem *, tags, a1, \
	, DOPUS_BASE_NAME)


#define NewMemHandle(puddle, thresh, type) \
	LP3(0x29a, void *, NewMemHandle, ULONG, puddle, d0, ULONG, thresh, d1, ULONG, type, d2, \
	, DOPUS_BASE_NAME)

#define FreeMemHandle(handle) \
	LP1NR(0x2a0, FreeMemHandle, void *, handle, a0, \
	, DOPUS_BASE_NAME)

#define ClearMemHandle(handle) \
	LP1NR(0x2a6, ClearMemHandle, void *, handle, a0, \
	, DOPUS_BASE_NAME)

#define AllocMemH(handle, size) \
	LP2(0x2ac, void *, AllocMemH, void *, handle, a0, ULONG, size, d0, \
	, DOPUS_BASE_NAME)

#define FreeMemH(memory) \
	LP1NR(0x2b2, FreeMemH, void *, memory, a0, \
	, DOPUS_BASE_NAME)

#define DrawBox(rp, rect, info, recess) \
	LP4NR(0x2b8, DrawBox, struct RastPort *, rp, a0, struct Rectangle *, rect, a1, struct DrawInfo *, info, a2, BOOL, recess, d0, \
	, DOPUS_BASE_NAME)

#define DrawFieldBox(rp, rect, info) \
	LP3NR(0x2be, DrawFieldBox, struct RastPort *, rp, a0, struct Rectangle *, rect, a1, struct DrawInfo *, info, a2, \
	, DOPUS_BASE_NAME)

#define NewLister(path) \
	LP1(0x2c4, Cfg_Lister *, NewLister, char *, path, a0, \
	, DOPUS_BASE_NAME)

#define NewButtonBank(init, type) \
	LP2(0x2ca, Cfg_ButtonBank *, NewButtonBank, BOOL, init, d0, short, type, d1, \
	, DOPUS_BASE_NAME)

#define NewButton(memory) \
	LP1(0x2d0, Cfg_Button *, NewButton, APTR, memory, a0, \
	, DOPUS_BASE_NAME)

#define NewFunction(memory, type) \
	LP2(0x2d6, Cfg_Function *, NewFunction, APTR, memory, a0, UWORD, type, d0, \
	, DOPUS_BASE_NAME)

#define NewInstruction(memory, type, string) \
	LP3(0x2dc, Cfg_Instruction *, NewInstruction, APTR, memory, a0, short, type, d0, char *, string, a1, \
	, DOPUS_BASE_NAME)

#define ReadSettings(env, name) \
	LP2(0x2e2, short, ReadSettings, CFG_SETS *, env, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define ReadListerDef(iff, id) \
	LP2(0x2e8, Cfg_Lister *, ReadListerDef, APTR, iff, a0, ULONG, id, d0, \
	, DOPUS_BASE_NAME)

#define OpenButtonBank(name) \
	LP1(0x2ee, Cfg_ButtonBank *, OpenButtonBank, char *, name, a0, \
	, DOPUS_BASE_NAME)

#define DefaultSettings(settings) \
	LP1NR(0x2f4, DefaultSettings, CFG_SETS *, settings, a0, \
	, DOPUS_BASE_NAME)

#define DefaultEnvironment(env) \
	LP1NR(0x2fa, DefaultEnvironment, CFG_ENVR *, env, a0, \
	, DOPUS_BASE_NAME)

#define DefaultButtonBank() \
	LP0(0x300, Cfg_ButtonBank *, DefaultButtonBank, \
	, DOPUS_BASE_NAME)

#define SaveSettings(env, name) \
	LP2(0x306, int, SaveSettings, CFG_SETS *, env, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define SaveListerDef(iff, lister) \
	LP2(0x30c, long, SaveListerDef, APTR, iff, a0, Cfg_Lister *, lister, a1, \
	, DOPUS_BASE_NAME)

#define SaveButtonBank(bank, name) \
	LP2(0x312, short, SaveButtonBank, Cfg_ButtonBank *, bank, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define CloseButtonBank(bank) \
	LP1NR(0x318, CloseButtonBank, Cfg_ButtonBank *, bank, a0, \
	, DOPUS_BASE_NAME)

#define FreeListerDef(lister) \
	LP1NR(0x31e, FreeListerDef, Cfg_Lister *, lister, a0, \
	, DOPUS_BASE_NAME)

#define FreeButtonList(list) \
	LP1NR(0x324, FreeButtonList, struct List *, list, a0, \
	, DOPUS_BASE_NAME)

#define FreeButtonImages(list) \
	LP1NR(0x32a, FreeButtonImages, struct List *, list, a0, \
	, DOPUS_BASE_NAME)

#define FreeButton(button) \
	LP1NR(0x330, FreeButton, Cfg_Button *, button, a0, \
	, DOPUS_BASE_NAME)

#define FreeFunction(function) \
	LP1NR(0x336, FreeFunction, Cfg_Function *, function, a0, \
	, DOPUS_BASE_NAME)

#define FreeInstruction(ins) \
	LP1NR(0x33c, FreeInstruction, Cfg_Instruction *, ins, a0, \
	, DOPUS_BASE_NAME)

#define FreeInstructionList(func) \
	LP1NR(0x342, FreeInstructionList, Cfg_Function *, func, a0, \
	, DOPUS_BASE_NAME)

#define CopyButtonBank(bank) \
	LP1(0x348, Cfg_ButtonBank *, CopyButtonBank, Cfg_ButtonBank *, bank, a0, \
	, DOPUS_BASE_NAME)

#define CopyButton(button, memory, type) \
	LP3(0x34e, Cfg_Button *, CopyButton, Cfg_Button *, button, a0, APTR, memory, a1, short, type, d0, \
	, DOPUS_BASE_NAME)

#define CopyFunction(function, memory, newfunc) \
	LP3(0x354, Cfg_Function *, CopyFunction, Cfg_Function *, function, a0, APTR, memory, a1, Cfg_Function *, newfunc, a2, \
	, DOPUS_BASE_NAME)

#define NewFiletype(memory) \
	LP1(0x35a, Cfg_Filetype *, NewFiletype, APTR, memory, a0, \
	, DOPUS_BASE_NAME)

#define ReadFiletypes(name, memory) \
	LP2(0x360, Cfg_FiletypeList *, ReadFiletypes, char *, name, a0, APTR, memory, a1, \
	, DOPUS_BASE_NAME)

#define SaveFiletypeList(list, name) \
	LP2(0x366, int, SaveFiletypeList, Cfg_FiletypeList *, list, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define FreeFiletypeList(list) \
	LP1NR(0x36c, FreeFiletypeList, Cfg_FiletypeList *, list, a0, \
	, DOPUS_BASE_NAME)

#define FreeFiletype(type) \
	LP1NR(0x372, FreeFiletype, Cfg_Filetype *, type, a0, \
	, DOPUS_BASE_NAME)

#define CopyFiletype(orig, memory) \
	LP2(0x378, Cfg_Filetype *, CopyFiletype, Cfg_Filetype *, orig, a0, APTR, memory, a1, \
	, DOPUS_BASE_NAME)

#define FindFunctionType(list, type) \
	LP2(0x37e, Cfg_Function *, FindFunctionType, struct List *, list, a0, UWORD, type, d0, \
	, DOPUS_BASE_NAME)

#define SaveButton(iff, button) \
	LP2(0x384, short, SaveButton, APTR, iff, a0, Cfg_Button *, button, a1, \
	, DOPUS_BASE_NAME)

#define ReadButton(iff, memory) \
	LP2(0x38a, Cfg_Button *, ReadButton, APTR, iff, a0, APTR, memory, a1, \
	, DOPUS_BASE_NAME)

#define ReadFunction(iff, memory, funclist, function) \
	LP4(0x390, Cfg_Function *, ReadFunction, APTR, iff, a0, APTR, memory, a1, struct List *, funclist, a2, Cfg_Function *, function, a3, \
	, DOPUS_BASE_NAME)

#define OpenIFFFile(name, mode, id) \
	LP3(0x396, struct IFFHandle *, OpenIFFFile, char *, name, a0, int, mode, d0, ULONG, id, d1, \
	, DOPUS_BASE_NAME)

#define CloseIFFFile(iff) \
	LP1NR(0x39c, CloseIFFFile, struct IFFHandle *, iff, a0, \
	, DOPUS_BASE_NAME)

#define OpenStatusWindow(title, text, screen, graph, flags) \
	LP5(0x3a2, struct Window *, OpenStatusWindow, char *, title, a0, char *, text, a1, struct Screen *, screen, a2, LONG, graph, d1, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define SetStatusText(window, text) \
	LP2NR(0x3a8, SetStatusText, struct Window *, window, a0, char *, text, a1, \
	, DOPUS_BASE_NAME)

#define UpdateStatusGraph(window, text, total, count) \
	LP4NR(0x3ae, UpdateStatusGraph, struct Window *, window, a0, char *, text, a1, ULONG, total, d0, ULONG, count, d1, \
	, DOPUS_BASE_NAME)

#define ReadILBM(name, flags) \
	LP2(0x3b4, ILBMHandle *, ReadILBM, char *, name, a0, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define FreeILBM(ilbm) \
	LP1NR(0x3ba, FreeILBM, ILBMHandle *, ilbm, a0, \
	, DOPUS_BASE_NAME)

#define DecodeILBM(src, w, h, d, dst, mask, comp) \
	LP7NR(0x3c0, DecodeILBM, char *, src, a0, UWORD, w, d0, UWORD, h, d1, UWORD, d, d2, struct BitMap *, dst, a1, ULONG, mask, d3, char, comp, d4, \
	, DOPUS_BASE_NAME)

#define DecodeRLE(rleinfo) \
	LP1NR(0x3c6, DecodeRLE, RLEinfo *, rleinfo, a0, \
	, DOPUS_BASE_NAME)

#define LoadPalette32(vp, palette) \
	LP2NR(0x3cc, LoadPalette32, struct ViewPort *, vp, a0, ULONG *, palette, a1, \
	, DOPUS_BASE_NAME)

#define GetPalette32(vp, palette, count, first) \
	LP4NR(0x3d2, GetPalette32, struct ViewPort *, vp, a0, ULONG *, palette, a1, UWORD, count, d0, short, first, d1, \
	, DOPUS_BASE_NAME)

#define OpenBuf(name, mode, buffer_size) \
	LP3(0x3d8, APTR, OpenBuf, char *, name, a0, long, mode, d0, long, buffer_size, d1, \
	, DOPUS_BASE_NAME)

#define CloseBuf(file) \
	LP1(0x3de, long, CloseBuf, APTR, file, a0, \
	, DOPUS_BASE_NAME)

#define ReadBuf(file, data, size) \
	LP3(0x3e4, long, ReadBuf, APTR, file, a0, char *, data, a1, long, size, d0, \
	, DOPUS_BASE_NAME)

#define WriteBuf(file, data, size) \
	LP3(0x3ea, long, WriteBuf, APTR, file, a0, char *, data, a1, long, size, d0, \
	, DOPUS_BASE_NAME)

#define FlushBuf(file) \
	LP1(0x3f0, long, FlushBuf, APTR, file, a0, \
	, DOPUS_BASE_NAME)

#define SeekBuf(file, offset, mode) \
	LP3(0x3f6, long, SeekBuf, APTR, file, a0, long, offset, d0, long, mode, d1, \
	, DOPUS_BASE_NAME)

#define ExamineBuf(file, fib) \
	LP2(0x3fc, long, ExamineBuf, APTR, file, a0, struct FileInfoBlock *, fib, a1, \
	, DOPUS_BASE_NAME)

#define OpenDisk(disk, port) \
	LP2(0x402, DiskHandle *, OpenDisk, char *, disk, a0, struct MsgPort *, port, a1, \
	, DOPUS_BASE_NAME)

#define CloseDisk(handle) \
	LP1NR(0x408, CloseDisk, DiskHandle *, handle, a0, \
	, DOPUS_BASE_NAME)

#define AddScrollBars(win, list, drawinfo, noidcmp) \
	LP4(0x40e, struct Gadget *, AddScrollBars, struct Window *, win, a0, struct List *, list, a1, struct DrawInfo *, drawinfo, a2, short, noidcmp, d0, \
	, DOPUS_BASE_NAME)

#define FindBOOPSIGadget(list, id) \
	LP2(0x414, struct Gadget *, FindBOOPSIGadget, struct List *, list, a0, UWORD, id, d0, \
	, DOPUS_BASE_NAME)

#define BOOPSIFree(list) \
	LP1NR(0x41a, BOOPSIFree, struct List *, list, a0, \
	, DOPUS_BASE_NAME)

#define SerialValid(data) \
	LP1(0x420, BOOL, SerialValid, serial_data *, data, a0, \
	, DOPUS_BASE_NAME)

#define WB_Install_Patch() \
	LP0NR(0x426, WB_Install_Patch, \
	, DOPUS_BASE_NAME)

#define WB_Remove_Patch() \
	LP0(0x42c, BOOL, WB_Remove_Patch, \
	, DOPUS_BASE_NAME)

#define WB_AddAppWindow(id, data, window, port, tags) \
	LP5(0x432, struct AppWindow *, WB_AddAppWindow, ULONG, id, d0, ULONG, data, d1, struct Window *, window, a0, struct MsgPort *, port, a1, struct TagItem *, tags, a2, \
	, DOPUS_BASE_NAME)


#define WB_RemoveAppWindow(window) \
	LP1(0x438, BOOL, WB_RemoveAppWindow, struct AppWindow *, window, a0, \
	, DOPUS_BASE_NAME)

#define WB_FindAppWindow(window) \
	LP1(0x43e, struct AppWindow *, WB_FindAppWindow, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define WB_AppWindowData(window, id, userdata) \
	LP3(0x444, struct MsgPort *, WB_AppWindowData, struct AppWindow *, window, a0, ULONG *, id, a1, ULONG *, userdata, a2, \
	, DOPUS_BASE_NAME)

#define WB_AppWindowLocal(window) \
	LP1(0x44a, BOOL, WB_AppWindowLocal, struct AppWindow *, window, a0, \
	, DOPUS_BASE_NAME)

#define LockAppList() \
	LP0(0x450, APTR, LockAppList, \
	, DOPUS_BASE_NAME)

#define NextAppEntry(last, type) \
	LP2(0x456, APTR, NextAppEntry, APTR, last, a0, ULONG, type, d0, \
	, DOPUS_BASE_NAME)

#define UnlockAppList() \
	LP0NR(0x45c, UnlockAppList, \
	, DOPUS_BASE_NAME)

#define AddNotifyRequest(type, data, port) \
	LP3(0x462, APTR, AddNotifyRequest, ULONG, type, d0, ULONG, data, d1, struct MsgPort *, port, a0, \
	, DOPUS_BASE_NAME)

#define RemoveNotifyRequest(node) \
	LP1NR(0x468, RemoveNotifyRequest, APTR, node, a0, \
	, DOPUS_BASE_NAME)

#define SendNotifyMsg(type, data, flags, wait, name, fib) \
	LP6NR(0x46e, SendNotifyMsg, ULONG, type, d0, ULONG, data, d1, ULONG, flags, d2, short, wait, d3, char *, name, a0, struct FileInfoBlock *, fib, a1, \
	, DOPUS_BASE_NAME)

#define StrCombine(s1, s2, s3, len) \
	LP4(0x474, BOOL, StrCombine, char *, s1, a0, char *, s2, a1, char *, s3, a2, int, len, d0, \
	, DOPUS_BASE_NAME)

#define StrConcat(s1, s2, len) \
	LP3(0x47a, BOOL, StrConcat, char *, s1, a0, char *, s2, a1, int, len, d0, \
	, DOPUS_BASE_NAME)

#define WB_Launch(name, screen, wait) \
	LP3(0x480, BOOL, WB_Launch, char *, name, a0, struct Screen *, screen, a1, short, wait, d0, \
	, DOPUS_BASE_NAME)

#define CopyLocalEnv(base) \
	LP1NR(0x486, CopyLocalEnv, struct Library *, base, a0, \
	, DOPUS_BASE_NAME)

#define CLI_Launch(name, screen, cd, in, out, wait, stack) \
	LP7(0x48c, BOOL, CLI_Launch, char *, name, a0, struct Screen *, screen, a1, BPTR, cd, d0, BPTR, in, d1, BPTR, out, d2, short, wait, d3, long, stack, d4, \
	, DOPUS_BASE_NAME)

#define SerialCheck(num, p) \
	LP2(0x492, BOOL, SerialCheck, char *, num, a0, ULONG *, p, a1, \
	, DOPUS_BASE_NAME)

#define ChecksumFile(file, skip) \
	LP2(0x498, ULONG, ChecksumFile, char *, file, a0, ULONG, skip, d0, \
	, DOPUS_BASE_NAME)

#define ReplyFreeMsg(msg) \
	LP1NR(0x49e, ReplyFreeMsg, APTR, msg, a0, \
	, DOPUS_BASE_NAME)

#define TimerActive(timer) \
	LP1(0x4a4, BOOL, TimerActive, TimerHandle *, timer, a0, \
	, DOPUS_BASE_NAME)

#define NewButtonFunction(memory, type) \
	LP2(0x4aa, Cfg_ButtonFunction *, NewButtonFunction, APTR, memory, a0, UWORD, type, d0, \
	, DOPUS_BASE_NAME)

#define IFFOpen(name, mode, form) \
	LP3(0x4b0, APTR, IFFOpen, char *, name, a0, UWORD, mode, d0, ULONG, form, d1, \
	, DOPUS_BASE_NAME)

#define IFFClose(handle) \
	LP1NR(0x4b6, IFFClose, APTR, handle, a0, \
	, DOPUS_BASE_NAME)

#define IFFPushChunk(handle, id) \
	LP2(0x4bc, long, IFFPushChunk, APTR, handle, a0, ULONG, id, d0, \
	, DOPUS_BASE_NAME)

#define IFFWriteChunkBytes(handle, data, size) \
	LP3(0x4c2, long, IFFWriteChunkBytes, APTR, handle, a0, APTR, data, a1, long, size, d0, \
	, DOPUS_BASE_NAME)

#define IFFPopChunk(handle) \
	LP1(0x4c8, long, IFFPopChunk, APTR, handle, a0, \
	, DOPUS_BASE_NAME)

#define IFFWriteChunk(handle, data, chunk, size) \
	LP4(0x4ce, long, IFFWriteChunk, APTR, handle, a0, APTR, data, a1, ULONG, chunk, d0, ULONG, size, d1, \
	, DOPUS_BASE_NAME)

#define FindNameI(list, name) \
	LP2(0x4d4, struct Node *, FindNameI, struct List *, list, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define AnimDecodeRIFFXor(delta, plane, rowbytes, sourcebytes) \
	LP4NR(0x4da, AnimDecodeRIFFXor, unsigned char *, delta, a0, char *, plane, a1, UWORD, rowbytes, d0, UWORD, sourcebytes, d1, \
	, DOPUS_BASE_NAME)

#define AnimDecodeRIFFSet(delta, plane, rowbytes, sourcebytes) \
	LP4NR(0x4e0, AnimDecodeRIFFSet, unsigned char *, delta, a0, char *, plane, a1, UWORD, rowbytes, d0, UWORD, sourcebytes, d1, \
	, DOPUS_BASE_NAME)

#define ConvertRawKey(code, qual, key) \
	LP3(0x4e6, BOOL, ConvertRawKey, UWORD, code, d0, UWORD, qual, d1, char *, key, a0, \
	, DOPUS_BASE_NAME)

#define OpenClipBoard(unit) \
	LP1(0x4ec, struct ClipHandle *, OpenClipBoard, ULONG, unit, d0, \
	, DOPUS_BASE_NAME)

#define CloseClipBoard(clip) \
	LP1NR(0x4f2, CloseClipBoard, struct ClipHandle *, clip, a0, \
	, DOPUS_BASE_NAME)

#define WriteClipString(clip, string, len) \
	LP3(0x4f8, BOOL, WriteClipString, struct ClipHandle *, clip, a0, char *, string, a1, long, len, d0, \
	, DOPUS_BASE_NAME)

#define ReadClipString(clip, string, len) \
	LP3(0x4fe, long, ReadClipString, struct ClipHandle *, clip, a0, char *, string, a1, long, len, d0, \
	, DOPUS_BASE_NAME)

#define LockAttList(list, exclusive) \
	LP2NR(0x504, LockAttList, Att_List *, list, a0, short, exclusive, d0, \
	, DOPUS_BASE_NAME)

#define UnlockAttList(list) \
	LP1NR(0x50a, UnlockAttList, Att_List *, list, a0, \
	, DOPUS_BASE_NAME)

#define RemovedFunc1() \
	LP0NR(0x510, RemovedFunc1, \
	, DOPUS_BASE_NAME)

#define RemovedFunc2() \
	LP0NR(0x516, RemovedFunc2, \
	, DOPUS_BASE_NAME)

#define RemovedFunc3() \
	LP0NR(0x51c, RemovedFunc3, \
	, DOPUS_BASE_NAME)

#define RemovedFunc4() \
	LP0NR(0x522, RemovedFunc4, \
	, DOPUS_BASE_NAME)

#define RemovedFunc5() \
	LP0NR(0x528, RemovedFunc5, \
	, DOPUS_BASE_NAME)

#define RemovedFunc6() \
	LP0NR(0x52e, RemovedFunc6, \
	, DOPUS_BASE_NAME)

#define RemovedFunc7() \
	LP0NR(0x534, RemovedFunc7, \
	, DOPUS_BASE_NAME)

#define GetSemaphore(sem, exc, data) \
	LP3(0x53a, long, GetSemaphore, struct SignalSemaphore *, sem, a0, long, exc, d0, char *, data, a1, \
	, DOPUS_BASE_NAME)

#define FreeSemaphore(sem) \
	LP1NR(0x540, FreeSemaphore, struct SignalSemaphore *, sem, a0, \
	, DOPUS_BASE_NAME)

#define ShowSemaphore(sem) \
	LP1NR(0x546, ShowSemaphore, struct SignalSemaphore *, sem, a0, \
	, DOPUS_BASE_NAME)

#define SaveFunction(iff, func) \
	LP2(0x54c, BOOL, SaveFunction, APTR, iff, a0, Cfg_Function *, func, a1, \
	, DOPUS_BASE_NAME)

#define IFFNextChunk(iff, form) \
	LP2(0x552, ULONG, IFFNextChunk, APTR, iff, a0, ULONG, form, d0, \
	, DOPUS_BASE_NAME)

#define IFFChunkSize(iff) \
	LP1(0x558, long, IFFChunkSize, APTR, iff, a0, \
	, DOPUS_BASE_NAME)

#define IFFReadChunkBytes(iff, buffer, size) \
	LP3(0x55e, long, IFFReadChunkBytes, APTR, iff, a0, APTR, buffer, a1, long, size, d0, \
	, DOPUS_BASE_NAME)

#define IFFFileHandle(iff) \
	LP1(0x564, APTR, IFFFileHandle, APTR, iff, a0, \
	, DOPUS_BASE_NAME)

#define IFFChunkRemain(iff) \
	LP1(0x56a, long, IFFChunkRemain, APTR, iff, a0, \
	, DOPUS_BASE_NAME)

#define IFFChunkID(iff) \
	LP1(0x570, ULONG, IFFChunkID, APTR, iff, a0, \
	, DOPUS_BASE_NAME)

#define IFFGetFORM(iff) \
	LP1(0x576, ULONG, IFFGetFORM, APTR, iff, a0, \
	, DOPUS_BASE_NAME)

#define ScreenInfo(screen) \
	LP1(0x57c, ULONG, ScreenInfo, struct Screen *, screen, a0, \
	, DOPUS_BASE_NAME)

#define GetEditHook(type, flags, tags) \
	LP3(0x582, struct Hook *, GetEditHook, ULONG, type, d0, ULONG, flags, d1, struct TagItem *, tags, a0, \
	, DOPUS_BASE_NAME)


#define FreeEditHook(hook) \
	LP1NR(0x588, FreeEditHook, struct Hook *, hook, a0, \
	, DOPUS_BASE_NAME)

#define InitWindowDims(window, dims) \
	LP2NR(0x58e, InitWindowDims, struct Window *, window, a0, WindowDimensions *, dims, a1, \
	, DOPUS_BASE_NAME)

#define StoreWindowDims(window, dims) \
	LP2NR(0x594, StoreWindowDims, struct Window *, window, a0, WindowDimensions *, dims, a1, \
	, DOPUS_BASE_NAME)

#define CheckWindowDims(window, dims) \
	LP2(0x59a, BOOL, CheckWindowDims, struct Window *, window, a0, WindowDimensions *, dims, a1, \
	, DOPUS_BASE_NAME)

#define InitListLock(ll, name) \
	LP2NR(0x5a0, InitListLock, struct ListLock *, ll, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define IPC_QuitName(list, name, flags) \
	LP3NR(0x5a6, IPC_QuitName, struct ListLock *, list, a0, char *, name, a1, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define QualValid(qual) \
	LP1(0x5ac, UWORD, QualValid, UWORD, qual, d0, \
	, DOPUS_BASE_NAME)

#define FHFromBuf(file) \
	LP1(0x5b2, BPTR, FHFromBuf, APTR, file, a0, \
	, DOPUS_BASE_NAME)

#define WB_AppIconFlags(icon) \
	LP1(0x5b8, ULONG, WB_AppIconFlags, struct AppIcon *, icon, a0, \
	, DOPUS_BASE_NAME)

#define GetWBArgPath(arg, buf, size) \
	LP3(0x5be, BOOL, GetWBArgPath, struct WBArg *, arg, a0, char *, buf, a1, long, size, d0, \
	, DOPUS_BASE_NAME)

#define RemovedFunc8() \
	LP0NR(0x5c4, RemovedFunc8, \
	, DOPUS_BASE_NAME)

#define DeviceFromLock(lock, name) \
	LP2(0x5ca, struct DosList *, DeviceFromLock, BPTR, lock, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define DeviceFromHandler(port, name) \
	LP2(0x5d0, struct DosList *, DeviceFromHandler, struct MsgPort *, port, a0, char *, name, a1, \
	, DOPUS_BASE_NAME)

#define DevNameFromLockDopus(lock, buffer, len) \
	LP3(0x5d6, BOOL, DevNameFromLockDopus, BPTR, lock, d1, char *, buffer, d2, long, len, d3, \
	, DOPUS_BASE_NAME)

#define GetIconFlags(icon) \
	LP1(0x5dc, ULONG, GetIconFlags, struct DiskObject *, icon, a0, \
	, DOPUS_BASE_NAME)

#define SetIconFlags(icon, flags) \
	LP2NR(0x5e2, SetIconFlags, struct DiskObject *, icon, a0, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define GetIconPosition(icon, x, y) \
	LP3NR(0x5e8, GetIconPosition, struct DiskObject *, icon, a0, short *, x, a1, short *, y, a2, \
	, DOPUS_BASE_NAME)

#define SetIconPosition(icon, x, y) \
	LP3NR(0x5ee, SetIconPosition, struct DiskObject *, icon, a0, short, x, d0, short, y, d1, \
	, DOPUS_BASE_NAME)

#define BuildTransDragMask(mask, image, width, height, depth, flags) \
	LP6(0x5f4, BOOL, BuildTransDragMask, UWORD *, mask, a0, UWORD *, image, a1, short, width, d0, short, height, d1, short, depth, d2, long, flags, d3, \
	, DOPUS_BASE_NAME)

#define GetImagePalette(image) \
	LP1(0x5fa, ULONG *, GetImagePalette, APTR, image, a0, \
	, DOPUS_BASE_NAME)

#define FreeImageRemap(remap) \
	LP1NR(0x600, FreeImageRemap, ImageRemap *, remap, a0, \
	, DOPUS_BASE_NAME)

#define SwapListNodes(list, s1, s2) \
	LP3NR(0x606, SwapListNodes, struct List *, list, a0, struct Node *, s1, a1, struct Node *, s2, a2, \
	, DOPUS_BASE_NAME)

#define RemovedFunc9() \
	LP0NR(0x60c, RemovedFunc9, \
	, DOPUS_BASE_NAME)

#define Seed(seed) \
	LP1NR(0x612, Seed, int, seed, d0, \
	, DOPUS_BASE_NAME)

#define RemovedFunc10() \
	LP0NR(0x618, RemovedFunc10, \
	, DOPUS_BASE_NAME)

#define RemovedFunc11() \
	LP0NR(0x61e, RemovedFunc11, \
	, DOPUS_BASE_NAME)

#define RemovedFunc12() \
	LP0NR(0x624, RemovedFunc12, \
	, DOPUS_BASE_NAME)

#define CopyDiskObject(icon, flags) \
	LP2(0x62a, struct DiskObject *, CopyDiskObject, struct DiskObject *, icon, a0, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define FreeDiskObjectCopy(icon) \
	LP1NR(0x630, FreeDiskObjectCopy, struct DiskObject *, icon, a0, \
	, DOPUS_BASE_NAME)

#define IFFFailure(iff) \
	LP1NR(0x636, IFFFailure, APTR, iff, a0, \
	, DOPUS_BASE_NAME)

#define GetCachedDefDiskObject(type) \
	LP1(0x63c, struct DiskObject *, GetCachedDefDiskObject, long, type, d0, \
	, DOPUS_BASE_NAME)

#define FreeCachedDiskObject(icon) \
	LP1NR(0x642, FreeCachedDiskObject, struct DiskObject *, icon, a0, \
	, DOPUS_BASE_NAME)

#define GetCachedDiskObject(name, flags) \
	LP2(0x648, struct DiskObject *, GetCachedDiskObject, char *, name, a0, long, flags, d0, \
	, DOPUS_BASE_NAME)

#define GetCachedDiskObjectNew(name, flags) \
	LP2(0x64e, struct DiskObject *, GetCachedDiskObjectNew, char *, name, a0, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define IconCheckSum(icon, which) \
	LP2(0x654, ULONG, IconCheckSum, struct DiskObject *, icon, a0, short, which, d0, \
	, DOPUS_BASE_NAME)

#define OpenProgressWindow(tags) \
	LP1(0x65a, APTR, OpenProgressWindow, struct TagItem *, tags, a0, \
	, DOPUS_BASE_NAME)


#define CloseProgressWindow(win) \
	LP1NR(0x660, CloseProgressWindow, APTR, win, a0, \
	, DOPUS_BASE_NAME)

#define HideProgressWindow(win) \
	LP1NR(0x666, HideProgressWindow, APTR, win, a0, \
	, DOPUS_BASE_NAME)

#define ShowProgressWindow(prog, scr, win) \
	LP3NR(0x66c, ShowProgressWindow, APTR, prog, a0, struct Screen *, scr, a1, struct Window *, win, a2, \
	, DOPUS_BASE_NAME)

#define SetProgressWindow(win, tags) \
	LP2NR(0x672, SetProgressWindow, APTR, win, a0, struct TagItem *, tags, a1, \
	, DOPUS_BASE_NAME)


#define GetProgressWindow(win, tags) \
	LP2NR(0x678, GetProgressWindow, APTR, win, a0, struct TagItem *, tags, a1, \
	, DOPUS_BASE_NAME)


#define SetNotifyRequest(req, flags, mask) \
	LP3NR(0x67e, SetNotifyRequest, APTR, req, a0, ULONG, flags, d0, ULONG, mask, d1, \
	, DOPUS_BASE_NAME)

#define ChangeAppIcon(icon, render, select, title, flags) \
	LP5NR(0x684, ChangeAppIcon, APTR, icon, a0, struct Image *, render, a1, struct Image *, select, a2, char *, title, a3, ULONG, flags, d0, \
	, DOPUS_BASE_NAME)

#define CheckProgressAbort(win) \
	LP1(0x68a, BOOL, CheckProgressAbort, APTR, win, a0, \
	, DOPUS_BASE_NAME)

#define GetSecureString(gad) \
	LP1(0x690, char *, GetSecureString, struct Gadget *, gad, a0, \
	, DOPUS_BASE_NAME)

#define NewButtonWithFunc(mem, label, type) \
	LP3(0x696, Cfg_Button *, NewButtonWithFunc, APTR, mem, a0, char *, label, a1, short, type, d0, \
	, DOPUS_BASE_NAME)

#define FreeButtonFunction(func) \
	LP1NR(0x69c, FreeButtonFunction, Cfg_ButtonFunction *, func, a0, \
	, DOPUS_BASE_NAME)

#define CopyButtonFunction(function, memory, newfunc) \
	LP3(0x6a2, Cfg_ButtonFunction *, CopyButtonFunction, Cfg_ButtonFunction *, function, a0, APTR, memory, a1, Cfg_ButtonFunction *, newfunc, a2, \
	, DOPUS_BASE_NAME)

#define FindPubScreen(scr, lock) \
	LP2(0x6a8, struct PubScreenNode *, FindPubScreen, struct Screen *, scr, a0, BOOL, lock, d0, \
	, DOPUS_BASE_NAME)

#define SetAppIconMenuState(icon, item, state) \
	LP3(0x6ae, long, SetAppIconMenuState, APTR, icon, a0, long, item, d0, long, state, d1, \
	, DOPUS_BASE_NAME)

#define SearchFile(file, text, flags, buffer, size) \
	LP5(0x6b4, long, SearchFile, APTR, file, a0, UBYTE *, text, a1, ULONG, flags, d0, UBYTE *, buffer, a2, ULONG, size, d1, \
	, DOPUS_BASE_NAME)

#define ParseDateStrings(string, date, time, range) \
	LP4(0x6ba, char *, ParseDateStrings, char *, string, a0, char *, date, a1, char *, time, a2, long *, range, a3, \
	, DOPUS_BASE_NAME)

#define DateFromStrings(date, time, ds) \
	LP3(0x6c0, BOOL, DateFromStrings, char *, date, a0, char *, time, a1, struct DateStamp *, ds, a2, \
	, DOPUS_BASE_NAME)

#define GetMatchHandle(name) \
	LP1(0x6c6, APTR, GetMatchHandle, char *, name, a0, \
	, DOPUS_BASE_NAME)

#define FreeMatchHandle(handle) \
	LP1NR(0x6cc, FreeMatchHandle, APTR, handle, a0, \
	, DOPUS_BASE_NAME)

#define MatchFiletype(handle, type) \
	LP2(0x6d2, BOOL, MatchFiletype, APTR, handle, a0, APTR, type, a1, \
	, DOPUS_BASE_NAME)

#define LayoutResize(window) \
	LP1NR(0x6d8, LayoutResize, struct Window *, window, a0, \
	, DOPUS_BASE_NAME)

#define GetFileVersion(name, ver, rev, date, prog) \
	LP5(0x6de, BOOL, GetFileVersion, char *, name, a0, short *, ver, d0, short *, rev, d1, struct DateStamp *, date, a1, APTR, prog, a2, \
	, DOPUS_BASE_NAME)

#define AsyncRequest(ipc, type, window, callback, data, tags) \
	LP6(0x6e4, long, AsyncRequest, IPCData *, ipc, a0, long, type, d0, struct Window *, window, a1, REF_CALLBACK, callback, a2, APTR, data, a3, struct TagItem *, tags, d1, \
	, DOPUS_BASE_NAME)


#define CheckRefreshMsg(window, mask) \
	LP2(0x6ea, struct IntuiMessage *, CheckRefreshMsg, struct Window *, window, a0, ULONG, mask, d0, \
	, DOPUS_BASE_NAME)

#define RemapImage(image, screen, remap) \
	LP3(0x6f0, BOOL, RemapImage, APTR, image, a0, struct Screen *, screen, a1, ImageRemap *, remap, a2, \
	, DOPUS_BASE_NAME)

#define FreeRemapImage(image, remap) \
	LP2NR(0x6f6, FreeRemapImage, APTR, image, a0, ImageRemap *, remap, a1, \
	, DOPUS_BASE_NAME)

#define FreeAppMessage(msg) \
	LP1NR(0x6fc, FreeAppMessage, DOpusAppMessage *, msg, a0, \
	, DOPUS_BASE_NAME)

#define ReplyAppMessage(msg) \
	LP1NR(0x702, ReplyAppMessage, DOpusAppMessage *, msg, a0, \
	, DOPUS_BASE_NAME)

#define SetLibraryFlags(flags, mask) \
	LP2(0x708, ULONG, SetLibraryFlags, ULONG, flags, d0, ULONG, mask, d1, \
	, DOPUS_BASE_NAME)

#define StartRefreshConfigWindow(win, state) \
	LP2NR(0x70e, StartRefreshConfigWindow, struct Window *, win, a0, long, state, d0, \
	, DOPUS_BASE_NAME)

#define EndRefreshConfigWindow(win) \
	LP1NR(0x714, EndRefreshConfigWindow, struct Window *, win, a0, \
	, DOPUS_BASE_NAME)

#define CompareListFormat(f1, f2) \
	LP2(0x71a, ULONG, CompareListFormat, ListFormat *, f1, a0, ListFormat *, f2, a1, \
	, DOPUS_BASE_NAME)

#define UpdateGadgetValue(list, msg, id) \
	LP3NR(0x720, UpdateGadgetValue, ObjectList *, list, a0, struct IntuiMessage *, msg, a1, UWORD, id, d0, \
	, DOPUS_BASE_NAME)

#define UpdateGadgetList(list) \
	LP1NR(0x726, UpdateGadgetList, ObjectList *, list, a0, \
	, DOPUS_BASE_NAME)

#define NewBitMap(w, h, d, f, b) \
	LP5(0x72c, struct BitMap *, NewBitMap, ULONG, w, d0, ULONG, h, d1, ULONG, d, d2, ULONG, f, d3, struct BitMap *, b, a0, \
	, DOPUS_BASE_NAME)

#define DisposeBitMap(b) \
	LP1NR(0x732, DisposeBitMap, struct BitMap *, b, a0, \
	, DOPUS_BASE_NAME)

#define ParseArgs(temp, args) \
	LP2(0x738, FuncArgs *, ParseArgs, char *, temp, a0, char *, args, a1, \
	, DOPUS_BASE_NAME)


#define DisposeArgs(args) \
	LP1NR(0x73e, DisposeArgs, FuncArgs *, args, a0, \
	, DOPUS_BASE_NAME)


#define SetConfigWindowLimits(window, min, max) \
	LP3NR(0x744, SetConfigWindowLimits, struct Window *, window, a0, ConfigWindow *, min, a1, ConfigWindow *, max, a2, \
	, DOPUS_BASE_NAME)

#define SetEnv(name, data, save) \
	LP3NR(0x74a, SetEnv, char *, name, a0, char *, data, a1, BOOL, save, d0, \
	, DOPUS_BASE_NAME)

#define IsListLockEmpty(list) \
	LP1(0x750, BOOL, IsListLockEmpty, struct ListLock *, list, a0, \
	, DOPUS_BASE_NAME)

#define AllocAppMessage(mem, reply, num) \
	LP3(0x756, DOpusAppMessage *, AllocAppMessage, APTR, mem, a0, struct MsgPort *, reply, a1, short, num, d0, \
	, DOPUS_BASE_NAME)

#define CheckAppMessage(msg) \
	LP1(0x75c, BOOL, CheckAppMessage, DOpusAppMessage *, msg, a0, \
	, DOPUS_BASE_NAME)

#define CopyAppMessage(msg, mem) \
	LP2(0x762, DOpusAppMessage *, CopyAppMessage, DOpusAppMessage *, msg, a0, APTR, mem, a1, \
	, DOPUS_BASE_NAME)

#define SetWBArg(msg, num, lock, name, mem) \
	LP5(0x768, BOOL, SetWBArg, DOpusAppMessage *, msg, a0, short, num, d0, BPTR, lock, d1, char *, name, a1, APTR, mem, a2, \
	, DOPUS_BASE_NAME)

#define OriginalCreateDir(name) \
	LP1(0x76e, BPTR, OriginalCreateDir, char *, name, d1, \
	, DOPUS_BASE_NAME)

#define OriginalDeleteFile(name) \
	LP1(0x774, long, OriginalDeleteFile, char *, name, d1, \
	, DOPUS_BASE_NAME)

#define OriginalSetFileDate(name, date) \
	LP2(0x77a, BOOL, OriginalSetFileDate, char *, name, d1, struct DateStamp *, date, d2, \
	, DOPUS_BASE_NAME)

#define OriginalSetComment(name, comment) \
	LP2(0x780, BOOL, OriginalSetComment, char *, name, d1, char *, comment, d2, \
	, DOPUS_BASE_NAME)

#define OriginalSetProtection(name, mask) \
	LP2(0x786, BOOL, OriginalSetProtection, char *, name, d1, ULONG, mask, d2, \
	, DOPUS_BASE_NAME)

#define OriginalRename(oldname, newname) \
	LP2(0x78c, BOOL, OriginalRename, char *, oldname, d1, char *, newname, d2, \
	, DOPUS_BASE_NAME)

#define OriginalOpen(name, access) \
	LP2(0x792, BPTR, OriginalOpen, char *, name, d1, LONG, access, d2, \
	, DOPUS_BASE_NAME)

#define OriginalClose(file) \
	LP1(0x798, BOOL, OriginalClose, BPTR, file, d1, \
	, DOPUS_BASE_NAME)

#define OriginalWrite(file, data, length) \
	LP3(0x79e, LONG, OriginalWrite, BPTR, file, d1, void *, data, d2, LONG, length, d3, \
	, DOPUS_BASE_NAME)

#define CreateTitleGadget(scr, list, zoom, offset, type, id) \
	LP6(0x7a4, struct Gadget *, CreateTitleGadget, struct Screen *, scr, a0, struct List *, list, a1, BOOL, zoom, d0, short, offset, d1, short, type, d2, UWORD, id, d3, \
	, DOPUS_BASE_NAME)

#define FindGadgetType(gad, type) \
	LP2(0x7aa, struct Gadget *, FindGadgetType, struct Gadget *, gad, a0, UWORD, type, d0, \
	, DOPUS_BASE_NAME)

#define FixTitleGadgets(win) \
	LP1NR(0x7b0, FixTitleGadgets, struct Window *, win, a0, \
	, DOPUS_BASE_NAME)

#define OriginalRelabel(dev, name) \
	LP2(0x7b6, BOOL, OriginalRelabel, char *, dev, d1, char *, name, d2, \
	, DOPUS_BASE_NAME)

#define FakeILBM(data, pal, w, h, d, flags) \
	LP6(0x7bc, ILBMHandle *, FakeILBM, UWORD *, data, a0, ULONG *, pal, a1, short, w, d0, short, h, d1, short, d, d2, ULONG, flags, d3, \
	, DOPUS_BASE_NAME)

#define IPC_SafeCommand(ipc, command, flags, data, data_free, reply, list) \
	LP7A4(0x7c2, ULONG, IPC_SafeCommand, IPCData *, ipc, a0, ULONG, command, d0, ULONG, flags, d1, APTR, data, a1, APTR, data_free, a2, struct MsgPort *, reply, a3, struct ListLock *, list, d7, \
	, DOPUS_BASE_NAME)

#define ClearFiletypeCache() \
	LP0NR(0x7c8, ClearFiletypeCache, \
	, DOPUS_BASE_NAME)

#define GetTimerBase() \
	LP0(0x7ce, struct Library *, GetTimerBase, \
	, DOPUS_BASE_NAME)

#define InitDragDBuf(drag) \
	LP1(0x7d4, BOOL, InitDragDBuf, DragInfo *, drag, a0, \
	, DOPUS_BASE_NAME)

#define FreeRexxMsgEx(msg) \
	LP1NR(0x7da, FreeRexxMsgEx, struct RexxMsg *, msg, a0, \
	, DOPUS_BASE_NAME)

#define CreateRexxMsgEx(port, extension, host) \
	LP3(0x7e0, struct RexxMsg *, CreateRexxMsgEx, struct MsgPort *, port, a0, UBYTE *, extension, a1, UBYTE *, host, d0, \
	, DOPUS_BASE_NAME)

#define SetRexxVarEx(msg, varname, value, length) \
	LP4(0x7e6, long, SetRexxVarEx, struct RexxMsg *, msg, a0, char *, varname, a1, char *, value, d0, long, length, d1, \
	, DOPUS_BASE_NAME)

#define GetRexxVarEx(msg, varname, bufpointer) \
	LP3(0x7ec, long, GetRexxVarEx, struct RexxMsg *, msg, a0, char *, varname, a1, char **, bufpointer, a2, \
	, DOPUS_BASE_NAME)

#define BuildRexxMsgEx(port, extension, host, tags) \
	LP4(0x7f2, struct RexxMsg *, BuildRexxMsgEx, struct MsgPort *, port, a0, UBYTE *, extension, a1, UBYTE *, host, d0, struct TagItem *, tags, a2, \
	, DOPUS_BASE_NAME)


#define NotifyDiskChange() \
	LP0NR(0x7f8, NotifyDiskChange, \
	, DOPUS_BASE_NAME)

#define GetDosListCopy(list, memory) \
	LP2NR(0x7fe, GetDosListCopy, struct List *, list, a0, APTR, memory, a1, \
	, DOPUS_BASE_NAME)

#define FreeDosListCopy(list) \
	LP1NR(0x804, FreeDosListCopy, struct List *, list, a0, \
	, DOPUS_BASE_NAME)

#define DateFromStringsNew(date, time, ds, method) \
	LP4(0x80a, BOOL, DateFromStringsNew, char *, date, a0, char *, time, a1, struct DateStamp *, ds, a2, ULONG, method, d0, \
	, DOPUS_BASE_NAME)

#define RemapIcon(icon, screen, free) \
	LP3(0x810, BOOL, RemapIcon, struct DiskObject *, icon, a0, struct Screen *, screen, a1, short, free, d0, \
	, DOPUS_BASE_NAME)

#define GetOriginalIcon(icon) \
	LP1(0x816, struct DiskObject *, GetOriginalIcon, struct DiskObject *, icon, a0, \
	, DOPUS_BASE_NAME)

#define CalcPercent(amount, total, utilbase) \
	LP3(0x81c, long, CalcPercent, ULONG, amount, d0, ULONG, total, d1, struct Library *, utilbase, a0, \
	, DOPUS_BASE_NAME)

#define IsDiskDevice(port) \
	LP1(0x822, BOOL, IsDiskDevice, struct MsgPort *, port, a0, \
	, DOPUS_BASE_NAME)

#define DrawDragList(rp, vp, flags) \
	LP3NR(0x828, DrawDragList, struct RastPort *, rp, a0, struct ViewPort *, vp, a1, long, flags, d0, \
	, DOPUS_BASE_NAME)

#define RemoveDragImage(drag) \
	LP1NR(0x82e, RemoveDragImage, DragInfo *, drag, a0, \
	, DOPUS_BASE_NAME)

#define SetNewIconsFlags(flags, prec) \
	LP2NR(0x834, SetNewIconsFlags, ULONG, flags, d0, short, prec, d1, \
	, DOPUS_BASE_NAME)

#define ReadBufLine(file, data, size) \
	LP3(0x83a, long, ReadBufLine, APTR, file, a0, char *, data, a1, long, size, d0, \
	, DOPUS_BASE_NAME)

#define GetLibraryFlags() \
	LP0(0x840, ULONG, GetLibraryFlags, \
	, DOPUS_BASE_NAME)

#define GetIconType(icon) \
	LP1(0x846, short, GetIconType, struct DiskObject *, icon, a0, \
	, DOPUS_BASE_NAME)

#define SetReqBackFill(hook, scr) \
	LP2NR(0x84c, SetReqBackFill, struct Hook *, hook, a0, struct Screen **, scr, a1, \
	, DOPUS_BASE_NAME)

#define LockReqBackFill(scr) \
	LP1(0x852, struct Hook *, LockReqBackFill, struct Screen *, scr, a0, \
	, DOPUS_BASE_NAME)

#define UnlockReqBackFill() \
	LP0NR(0x858, UnlockReqBackFill, \
	, DOPUS_BASE_NAME)

#define DragCustomOk(bm) \
	LP1(0x85e, BOOL, DragCustomOk, struct BitMap *, bm, a0, \
	, DOPUS_BASE_NAME)

#define WB_LaunchNew(name, scr, wait, stack, tool) \
	LP5(0x864, BOOL, WB_LaunchNew, char *, name, a0, struct Screen *, scr, a1, short, wait, d0, long, stack, d1, char *, tool, a2, \
	, DOPUS_BASE_NAME)

#define UpdatePathList() \
	LP0NR(0x86a, UpdatePathList, \
	, DOPUS_BASE_NAME)

#define UpdateMyPaths() \
	LP0NR(0x870, UpdateMyPaths, \
	, DOPUS_BASE_NAME)

#define GetPopUpImageSize(window, menu, width, height) \
	LP4NR(0x876, GetPopUpImageSize, struct Window *, window, a0, PopUpMenu *, menu, a1, short *, width, a2, short *, height, a3, \
	, DOPUS_BASE_NAME)

#define GetDeviceUnit(startup, device, unit) \
	LP3(0x87c, BOOL, GetDeviceUnit, BPTR, startup, a0, char *, device, a1, short *, unit, a2, \
	, DOPUS_BASE_NAME)

#define StripWindowMessages(port, except) \
	LP2NR(0x882, StripWindowMessages, struct MsgPort *, port, a0, struct IntuiMessage *, except, a1, \
	, DOPUS_BASE_NAME)

#define DeleteIcon(name) \
	LP1(0x888, BOOL, DeleteIcon, char *, name, a0, \
	, DOPUS_BASE_NAME)

#define MUFSLogin(window, name, password) \
	LP3NR(0x88e, MUFSLogin, struct Window *, window, a0, char *, name, a1, char *, password, a2, \
	, DOPUS_BASE_NAME)

#define UpdateEnvironment(env) \
	LP1NR(0x894, UpdateEnvironment, CFG_ENVR *, env, a0, \
	, DOPUS_BASE_NAME)

#define ConvertStartMenu(bank) \
	LP1NR(0x89a, ConvertStartMenu, Cfg_ButtonBank *, bank, a0, \
	, DOPUS_BASE_NAME)

#define GetOpusPathList() \
	LP0(0x8a0, BPTR, GetOpusPathList, \
	, DOPUS_BASE_NAME)

#define GetStatistics(id) \
	LP1(0x8a6, long, GetStatistics, long, id, d0, \
	, DOPUS_BASE_NAME)

#define SetPopUpDelay(delay) \
	LP1NR(0x8ac, SetPopUpDelay, short, delay, d0, \
	, DOPUS_BASE_NAME)

#define WB_AppWindowWindow(appwindow) \
	LP1(0x8b8, struct Window *, WB_AppWindowWindow, struct AppWindow *, appwindow, a0, \
	, DOPUS_BASE_NAME)

#define OpenEnvironment(name, data) \
	LP2(0x8be, BOOL, OpenEnvironment, char *, name, a0, struct OpenEnvironmentData *, data, a1, \
	, DOPUS_BASE_NAME)

#define PopUpNewHandle(data, callback, locale) \
	LP3(0x8c4, PopUpHandle *, PopUpNewHandle, ULONG, data, d0, REF_CALLBACK, callback, a0, struct DOpusLocale *, locale, a1, \
	, DOPUS_BASE_NAME)

#define PopUpFreeHandle(handle) \
	LP1NR(0x8ca, PopUpFreeHandle, PopUpHandle *, handle, a0, \
	, DOPUS_BASE_NAME)

#define PopUpNewItem(handle, string, id, flags) \
	LP4(0x8d0, PopUpItem *, PopUpNewItem, PopUpHandle *, handle, a0, ULONG, string, d0, ULONG, id, d1, ULONG, flags, d2, \
	, DOPUS_BASE_NAME)

#define PopUpSeparator(handle) \
	LP1NR(0x8d6, PopUpSeparator, PopUpHandle *, handle, a0, \
	, DOPUS_BASE_NAME)

#define PopUpItemSub(handle, item) \
	LP2(0x8dc, BOOL, PopUpItemSub, PopUpHandle *, handle, a0, PopUpItem *, item, a1, \
	, DOPUS_BASE_NAME)

#define PopUpEndSub(handle) \
	LP1NR(0x8e2, PopUpEndSub, PopUpHandle *, handle, a0, \
	, DOPUS_BASE_NAME)

#define PopUpSetFlags(menu, id, value, mask) \
	LP4(0x8e8, ULONG, PopUpSetFlags, PopUpMenu *, menu, a0, UWORD, id, d0, ULONG, value, d1, ULONG, mask, d2, \
	, DOPUS_BASE_NAME)

#define AddAllocBitmapPatch(task, screen) \
	LP2(0x8ee, APTR, AddAllocBitmapPatch, struct Task *, task, a0, struct Screen *, screen, a1, \
	, DOPUS_BASE_NAME)

#define RemAllocBitmapPatch(handle) \
	LP1NR(0x8f4, RemAllocBitmapPatch, APTR, handle, a0, \
	, DOPUS_BASE_NAME)

#define LoadPos(name, pos, font) \
	LP3(0x8fa, BOOL, LoadPos, char *, name, a0, struct IBox *, pos, a1, short *, font, d0, \
	, DOPUS_BASE_NAME)

#define SavePos(name, pos, font) \
	LP3(0x900, BOOL, SavePos, char *, name, a0, struct IBox *, pos, a1, short, font, d0, \
	, DOPUS_BASE_NAME)

#define SimpleRequestTags(window,title,buttons,message,...) \
({ \
	IPTR __args[] = { __VA_ARGS__ }; \
	(short) SimpleRequest(window, title, buttons, message, 0, (APTR)&__args, 0, 0); \
})

#define OpenProgressWindowTags(...) \
({ \
	IPTR __tags[] = { __VA_ARGS__ }; \
	(APTR) OpenProgressWindow((struct TagItem *)&__tags); \
})

#define SetProgressWindowTags(prog, ...) \
({ \
	IPTR __tags[] = { __VA_ARGS__ }; \
	(void) SetProgressWindow(prog, (struct TagItem *)&__tags); \
})

#define AsyncRequestTags(my_ipc,type,window,callback,data,...) \
({ \
	IPTR __tags[] = { __VA_ARGS__ }; \
	(long)AsyncRequest(my_ipc, type, window, callback, data, (struct TagItem *)&__tags); \
})

#define GetEditHookTags(type,flags,...) \
({ \
	IPTR __tags[] = { __VA_ARGS__ }; \
	(struct Hook *)GetEditHook(type, flags, (struct TagItem *)&__tags); \
})

#define BuildRexxMsgExTags(port,ext,host,...) \
({ \
	IPTR __tags[] = { __VA_ARGS__ }; \
	(struct RexxMsg *)BuildRexxMsgEx(port, ext, host, (struct TagItem *)&__tags); \
})
 	
#define GetProgressWindowTags(prog, ...) \
({ \
	IPTR __tags[] = { __VA_ARGS__ }; \
	(void) GetProgressWindow(prog, (struct TagItem *)&__tags); \
})
	
#endif /*  _INLINE_DOPUS_H  */
