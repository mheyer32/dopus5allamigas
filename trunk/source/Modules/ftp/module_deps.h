#ifndef _MODULE_DEPS_H
#define _MODULE_DEPS_H

#include "amiga.h"
#include "base.h"
#include <proto/dopus5.h>
#include <proto/module.h>

		
extern struct DOpusLocale *locale;
#ifdef __AROS__
typedef struct
{
	ULONG		ver;		// Module version
	char		*name;		// Module name
	char		*locale_name;	// Catalog name
	ULONG		flags;		// Module flags
	ULONG		function_count;	// Number of functions in module
	ModuleFunction	function[7];	// All the module functions
} ModuleInfo_7;
extern ModuleInfo_7 module_info;
#else
extern ModuleInfo module_info;
#endif



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
void LSprintf(char *buffer, char *string, APTR data);

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

#define userlibname "ftp.module"
#define textsegmentname "$VER: ftp.module 68.10 (05.05.2013)"

#endif

