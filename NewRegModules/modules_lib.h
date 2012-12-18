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
#include "dopuspragmas.h"
#include "dopus_config.h"
#include "modules.h"

#define VALID_QUALIFIERS (IEQUALIFIER_LCOMMAND|IEQUALIFIER_RCOMMAND|\
                         IEQUALIFIER_CONTROL|IEQUALIFIER_LSHIFT|\
                         IEQUALIFIER_RSHIFT|IEQUALIFIER_LALT|IEQUALIFIER_RALT)

extern struct Library *DOpusBase;
extern struct Library *IconBase;
extern struct Library *LayersBase;
extern struct Library *UtilityBase;
extern struct Library *WorkbenchBase;
extern struct Library *GadToolsBase;
extern struct Library *IFFParseBase;
extern struct Library *DiskfontBase;
extern struct Library *AslBase;
extern struct DOpusLocale *locale;
extern ModuleInfo module_info;

void init_locale_data(struct DOpusLocale *);
void KPrintF __ARGS((char *,...));
void lsprintf __ARGS((char *,...));

/*
int __asm __saveds L_Module_Entry(
	register __a0 struct List *files,
	register __a1 struct Screen *screen,
	register __a2 IPCData *ipc,
	register __d0 ULONG id,
	register __d1 ULONG data);
*/

ModuleInfo *__asm __saveds L_Module_Identify(register __d0 int num);

// Function flags
#define FUNCF_NEED_SOURCE		(1<<0)	// Needs a source directory
#define FUNCF_NEED_DEST			(1<<1)	// Needs a destination directory
#define FUNCF_NEED_FILES		(1<<2)	// Needs some files to work with
#define FUNCF_NEED_DIRS			(1<<3)	// Needs some files to work with
#define FUNCF_NEED_ENTRIES	(FUNCF_NEED_FILES|FUNCF_NEED_DIRS)
#define FUNCF_CAN_DO_ICONS		(1<<6)	// Function can do icons
#define FUNCF_SINGLE_SOURCE		(1<<8)	// Only a single source needed
#define FUNCF_SINGLE_DEST		(1<<9)	// Only a single destination needed
#define FUNCF_NO_LOOP_SOURCE		(1<<10)	// Don't loop through sources
#define FUNCF_WANT_DEST			(1<<11)	// Want destinations, don't need them
#define FUNCF_WANT_SOURCE		(1<<12)	// Want source, don't need it
#define FUNCF_CREATE_SOURCE		(1<<13)	// Can create our own source

ULONG __asm __saveds function_external_hook(
	register __d0 ULONG command,
	register __a0 struct _FunctionHandle *handle,
	register __a1 APTR packet);

#define EXT_FUNC(name)	unsigned long __asm (*name)(register __d0 ULONG,register __a0 struct _FunctionHandle *,register __a1 APTR)
#define TYPE_EXT(var)	(unsigned long (*)())var
