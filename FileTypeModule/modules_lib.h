#include "dopuslib:dopusbase.h"
#include "dopuslib:dopuspragmas.h"
#include "dopusprog:dopus_config.h"
#include "modules.h"

#define VALID_QUALIFIERS (IEQUALIFIER_LCOMMAND|IEQUALIFIER_RCOMMAND|\
                         IEQUALIFIER_CONTROL|IEQUALIFIER_LSHIFT|\
                         IEQUALIFIER_RSHIFT|IEQUALIFIER_LALT|IEQUALIFIER_RALT)

extern struct Library *DOSBase;
extern struct Library *DOpusBase;
extern struct Library *IntuitionBase;
extern struct Library *GfxBase;
extern struct Library *IconBase;
extern struct Library *LayersBase;
extern struct Library *UtilityBase;
extern struct Library *WorkbenchBase;
extern struct Library *GadToolsBase;
extern struct Library *DiskfontBase;
extern struct Library *AslBase;
extern struct DOpusLocale *locale;
extern ModuleInfo module_info;

void init_locale_data(struct DOpusLocale *);
void KPrintF __ARGS((char *,...));
void lsprintf __ARGS((char *,...));
