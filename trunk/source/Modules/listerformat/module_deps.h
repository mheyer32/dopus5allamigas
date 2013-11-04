#ifndef _MODULE_DEPS_H
#define _MODULE_DEPS_H

#include <dopus/common.h>
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


#define userlibname "listerformat.module"
#define textsegmentname "$VER: listerformat.module "LIB_STRING


#endif

