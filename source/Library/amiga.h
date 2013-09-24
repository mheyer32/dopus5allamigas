/* AmigaOS includes */

#ifndef _AMIGA_H
#define _AMIGA_H

// Temporary defines
#undef __chip
#define __chip

// End Temporary defines

#define __ARGS(x) x

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <SDI/SDI_compiler.h>
#include <SDI/SDI_lib.h>
#include <SDI/SDI_stdarg.h>

//*** #include "debug_lib.h"

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/wb.h>
#include <proto/icon.h>
#include <proto/iffparse.h>
#include <proto/locale.h>
#include <proto/commodities.h>
#include <proto/asl.h>
#include <proto/gadtools.h>
#include <proto/console.h>
#include <proto/utility.h>
#include <proto/datatypes.h>
#include <proto/layers.h>
#include <proto/rexxsyslib.h>

#include <exec/memory.h>
#include <exec/resident.h>
#include <dos/dostags.h>
#include <dos/filehandler.h>
#include <devices/trackdisk.h>
#include <graphics/gfxmacros.h>
#include <intuition/gadgetclass.h>
#include <intuition/imageclass.h>
#include <intuition/icclass.h>
#include <intuition/sghooks.h>
#include <workbench/startup.h>
#include <workbench/icon.h>
#include <prefs/wbpattern.h>
#include <prefs/prefhdr.h>
#include <prefs/font.h>
#include <datatypes/animationclass.h>
#include <datatypes/textclass.h>

#ifdef __amigaos3__
#include <clib/alib_protos.h>
#endif

#ifdef __AROS__
#include <intuition/cghooks.h>
#include <graphics/gfxbase.h>
#endif


// for os4 replace external (non L_) calls on internal (L_ ones)

#ifdef __amigaos4__

#define GetSemaphore	L_GetSemaphore
#define FreeSemaphore	L_FreeSemaphore
#define GetDosPathList	L_GetDosPathList
#define FindPubScreen	L_FindPubScreen
#define AllocMemH		L_AllocMemH
#define FreeMemH		L_FreeMemH
#define AllocTimer		L_AllocTimer
#define StartTimer		L_StartTimer
#define CheckTimer		L_CheckTimer
#define FreeTimer		L_FreeTimer
#define IPC_Reply		L_IPC_Reply
#define IPC_Free		L_IPC_Free
#define IPC_Command		L_IPC_Command
#define GetString		L_GetString
#define SetWindowID		L_SetWindowID
#define DrawBox			L_DrawBox
#define Att_NewList		L_Att_NewList
#define Att_RemList		L_Att_RemList
#define Att_NewNode		L_Att_NewNode
#define Att_RemList		L_Att_RemList
#define OpenClipBoard	L_OpenClipBoard
#define ReadClipString	L_ReadClipString
#define WriteClipString	L_WriteClipString
#define CloseClipBoard	L_CloseClipBoard
#define CopyLocalEnv	L_CopyLocalEnv
#define GetDeviceUnit	L_GetDeviceUnit
#define BuildKeyString	L_BuildKeyString
#define DeviceFromHandler(par1,par2)	L_DeviceFromHandler(par1,par2,dopuslibbase_global)
#define WB_Install_Patch()				L_WB_Install_Patch(dopuslibbase_global)
#define UpdateMyPaths()					L_UpdateMyPaths(dopuslibbase_global)
#define SendNotifyMsg(par1,par2,par3,par4,par5,par6)		L_SendNotifyMsg(par1,par2,par3,par4,par5,par6,dopuslibbase_global)
#define DoSimpleRequest(par1,par2)		L_DoSimpleRequest(par1,par2,dopuslibbase_global)
 
#endif

/* Long word alignement (mainly used to get
 * FIB or DISK_INFO as auto variables)
 */
#define D_S(type,name) char a_##name[sizeof(type)+3]; \
                       type *name = (type *)((LONG)(a_##name+3) & ~3);

// no need for old functions
#undef UDivMod32
#define UDivMod32(x,y)( ((ULONG) x) / ((ULONG) y) )
#undef SDivMod32
#define SDivMod32(x,y) ( ((LONG) x) / ((LONG) y) )
#undef UMult32
#define UMult32(x,y) ( ((ULONG) x) * ((ULONG) y) )

/* Replacement functions for functions not available in some SDKs/GCCs */
#if !defined(__MORPHOS__) && !defined(__AROS__)
#undef stccpy
int stccpy(char *p, const char *q, int n);
#endif

/* dummy replacements for SASC getreg() & putreg() functions */

#if defined(__MORPHOS__)
#define getreg(x) x
#define putreg(x,y) x = y
#else
#define getreg(x) 0
#define putreg(x,y)
#endif


#endif /* _AMIGA_H */
