/* AmigaOS includes */

#ifndef _AMIGA_H
#define _AMIGA_H

// Temporary defines
#undef __chip
#define __chip

// End Temporary defines

#define __ARGS(x) x

#include <SDI/SDI_compiler.h>
#include <SDI/SDI_lib.h>
#include <SDI/SDI_stdarg.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
#include <proto/timer.h>
#include <proto/diskfont.h>
#include <proto/input.h>
#include <proto/datatypes.h>
#include <proto/layers.h>
#include <proto/rexxsyslib.h>
#if defined(__MORPHOS__) || defined(__AROS__)
#include <cybergraphx/cybergraphics.h>
#else
#include <cybergraphics/cybergraphics.h>
#endif
#include <proto/cybergraphics.h>	


#include <exec/execbase.h>
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

#include <stddef.h>


#if defined(__MORPHOS__) || defined(__amigaos3__)
#include <intuition/intuitionbase.h>
#include <clib/alib_protos.h>
#endif

#ifdef __AROS__
#include <proto/alib.h>
#endif

#ifdef __amigaos4__
#include <exec/emulation.h>		// necessary 68k emul-based parts
#include <dos/stdio.h>			// for #define Flush(x) FFlush(x)
#define REG68K_d0 REG68K_D0		// make macros work for all builds
#define REG68K_d1 REG68K_D1
#define REG68K_a0 REG68K_A0
#define REG68K_a1 REG68K_A1
#define REG68K_a2 REG68K_A2
#define REG68K_a3 REG68K_A3
#define REG68K_a4 REG68K_A4
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

#if defined(__MORPHOS__)
#define getreg(x) x
#define putreg(x,y) x = y
#else
#define getreg(x) 0
#define putreg(x,y)
#endif

#endif
