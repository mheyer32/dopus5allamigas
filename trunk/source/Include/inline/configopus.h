#ifndef _INLINE_CONFIGOPUS_H
#define _INLINE_CONFIGOPUS_H

#ifndef CLIB_CONFIGOPUS_PROTOS_H
#define CLIB_CONFIGOPUS_PROTOS_H
#endif

#ifndef __INLINE_MACROS_H
#include <inline/macros.h>
#endif

//
// functions ConfigEditFunction(), ConfigEnvironment(), ConfigMenu() and ShowPaletteBox() implemented in 68k assember
// because of problems with a4 and/or a5 registers used as arguments, which make 68k gcc inlines works wrong.
//

#include <exec/types.h>

#ifndef CONFIGOPUS_BASE_NAME
#define CONFIGOPUS_BASE_NAME ConfigOpusBase
#endif

#define Config_Settings(env, screen, ipc, mainipc, name) \
	LP5(0x1e, int, Config_Settings, Cfg_Environment *, env, a0, struct Screen *, screen, a1, IPCData *, ipc, a2, IPCData *, mainipc, a3, char *, name, d0, \
	, CONFIGOPUS_BASE_NAME)

#define Config_Buttons(bank, ipc, owner, screen, cmdlist) \
	LP5(0x30, int, Config_Buttons, ButtonsStartup *, bank, a0, IPCData *, ipc, a1, IPCData *, owner, a2, struct Screen *, screen, a3, ULONG, cmdlist, d0, \
	, CONFIGOPUS_BASE_NAME)

#define ConvertConfig(name, screen, owner) \
	LP3(0x36, BOOL, ConvertConfig, char *, name, a0, struct Screen *, screen, a1, IPCData *, owner, a2, \
	, CONFIGOPUS_BASE_NAME)

#define Config_Filetypes(screen, ipc, owner, cmdlist, name) \
	LP5(0x3c, short, Config_Filetypes, struct Screen *, screen, a0, IPCData *, ipc, a1, IPCData *, owner, a2, ULONG, cmdlist, d0, char *, name, a3, \
	, CONFIGOPUS_BASE_NAME)

#define Config_ListerButtons(name, ipc, owner, screen, bank, cmdlist, init) \
	LP7A4(0x42, ULONG, Config_ListerButtons, char *, name, a0, IPCData *, ipc, a1, IPCData *, owner, a2, struct Screen *, screen, a3, Cfg_ButtonBank *, bank, d7, ULONG, cmdlist, d0, LONG, init, d1, \
	, CONFIGOPUS_BASE_NAME)

#define Config_Menus(ipc, owner, screen, menu, cmdlist, type, name) \
	LP7(0x4e, ULONG, Config_Menus, IPCData *, ipc, a0, IPCData *, owner, a1, struct Screen *, screen, a2, Cfg_ButtonBank *, menu, a3, ULONG, cmdlist, d0, ULONG, type, d1, char *, name, d2, \
	, CONFIGOPUS_BASE_NAME)

#define EditFiletype(type, window, ipc, dopus, flags) \
	LP5(0x54, Cfg_Filetype *, EditFiletype, Cfg_Filetype *, type, a0, struct Window *, window, a1, IPCData *, ipc, a2, IPCData *, dopus, a3, ULONG, flags, d0, \
	, CONFIGOPUS_BASE_NAME)

#define FunctionExportASCII(name, button, func, type) \
	LP4(0x66, BOOL, FunctionExportASCII, char *, name, a0, Cfg_Button *, button, a1, Cfg_Function *, func, a2, ULONG, type, d0, \
	, CONFIGOPUS_BASE_NAME)

#endif /*  _INLINE_CONFIGOPUS_H  */
