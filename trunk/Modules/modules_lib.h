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

#include "dopuslib:dopusbase.h"
#include "dopuslib:dopuspragmas.h"
#include "dopusprog:dopus_config.h"
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
extern struct Library *DiskfontBase;
extern struct Library *AslBase;
extern struct Library *RexxSysBase;
extern struct DOpusLocale *locale;
extern ModuleInfo module_info;

void init_locale_data(struct DOpusLocale *);
void KPrintF __ARGS((char *,...));
void lsprintf __ARGS((char *,...));
