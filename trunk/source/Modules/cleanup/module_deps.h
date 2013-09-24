#ifndef _MODULE_DEPS_H
#define _MODULE_DEPS_H

#include "amiga.h"
#include "base.h"
#include <proto/dopus5.h>
#include <proto/module.h>

		
extern struct DOpusLocale *locale;
extern ModuleInfo module_info;


#define VALID_QUALIFIERS (IEQUALIFIER_LCOMMAND|IEQUALIFIER_RCOMMAND|\
                         IEQUALIFIER_CONTROL|IEQUALIFIER_LSHIFT|\
                         IEQUALIFIER_RSHIFT|IEQUALIFIER_LALT|IEQUALIFIER_RALT)

extern struct Library *IconBase;
extern struct Library *LayersBase;
#ifdef __AROS__
extern struct UtilityBase *UtilityBase;
#else
extern struct Library *UtilityBase;
#endif
extern struct Library *WorkbenchBase;
extern struct Library *GadToolsBase;
extern struct Library *DiskfontBase;
extern struct Library *AslBase;

void init_locale_data(struct DOpusLocale *);

#if defined(__amigaos3__)
extern ULONG GlobalStuffChar;
#define DOPUS_RAWFMTFUNC (APTR)&GlobalStuffChar
#else
#define DOPUS_RAWFMTFUNC NULL
#endif
 
void KPrintF __ARGS((char *,...));

#define lsprintf(buf,fmt,...) \
	({ \
		IPTR args[] = { __VA_ARGS__ }; \
		RawDoFmt(fmt, &args, DOPUS_RAWFMTFUNC, buf); \
	})
 
  


#define LIB_VERSION    68
#define LIB_REVISION   10
#define DATE       "05.05.2013"
#define COPYRIGHT  "Copyright (c) 2012-2013 dopus5 Open Source Team"

// set the LIB_REV_STRING
#define REV_STRING STR(LIB_VERSION) "." STR(LIB_REVISION)

#define userlibname "cleanup.module"
#define textsegmentname "$VER: cleanup.module 68.10 (05.05.2013)"

#endif

