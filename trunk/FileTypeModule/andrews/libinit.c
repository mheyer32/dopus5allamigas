#include "modules_lib.h"

int __saveds __UserLibInit(void);
void __saveds __UserLibCleanup(void);

struct Library *DOSBase;
struct Library *DOpusBase;
struct Library *IntuitionBase;
struct Library *GfxBase;
struct Library *IconBase;
struct Library *LocaleBase;
struct Library *UtilityBase;
struct Library *LayersBase;
struct Library *WorkbenchBase;
struct Library *GadToolsBase;
struct Library *AslBase;
struct Library *DiskfontBase;
struct DOpusLocale *locale;

// Initialise libraries we need
__saveds __UserLibInit()
{
	// Initialise
	DOpusBase=0;
	IntuitionBase=0;
	GfxBase=0;
	IconBase=0;
	LocaleBase=0;
	UtilityBase=0;
	LayersBase=0;
	WorkbenchBase=0;
	GadToolsBase=0;
	DiskfontBase=0;
	AslBase=0;
	locale=0;

	// DOS
	DOSBase=OpenLibrary("dos.library",0);

	// Other libraries we want
	if (!(DOpusBase=OpenLibrary("dopus5.library",41)) ||
		!(IntuitionBase=OpenLibrary("intuition.library",37)) ||
		!(GfxBase=OpenLibrary("graphics.library",37)) ||
		!(IconBase=OpenLibrary("icon.library",37)) ||
		!(LayersBase=OpenLibrary("layers.library",37)) ||
		!(GadToolsBase=OpenLibrary("gadtools.library",37)) ||
		!(AslBase=OpenLibrary("asl.library",37)) ||
		!(DiskfontBase=OpenLibrary("diskfont.library",37)) ||
		!(UtilityBase=OpenLibrary("utility.library",37))) return 1;

	// Unnecessary libraries
	WorkbenchBase=OpenLibrary("workbench.library",0);

	// Allocate and open locale data
	if (!(locale=AllocVec(sizeof(struct DOpusLocale),MEMF_CLEAR)))
		return 1;
	init_locale_data(locale);

	if (LocaleBase=OpenLibrary("locale.library",38))
	{
		locale->li_LocaleBase=LocaleBase;
		if (module_info.locale_name) locale->li_Catalog=OpenCatalogA(NULL,module_info.locale_name,0);
		locale->li_Locale=OpenLocale(0);
	}

	// Succeeded
	return 0;
}


// Clean up
void __saveds __UserLibCleanup()
{
	// Free locale stuff
	if (locale)
	{
		if (LocaleBase)
		{
			CloseLocale(locale->li_Locale);
			CloseCatalog(locale->li_Catalog);
			CloseLibrary(LocaleBase);
		}
		FreeVec(locale);
	}

	// Close libraries
	CloseLibrary(DOpusBase);
	CloseLibrary(IntuitionBase);
	CloseLibrary(GfxBase);
	CloseLibrary(IconBase);
	CloseLibrary(LayersBase);
	CloseLibrary(UtilityBase);
	CloseLibrary(WorkbenchBase);
	CloseLibrary(DiskfontBase);
	CloseLibrary(AslBase);
	CloseLibrary(DOSBase);
}

ModuleInfo *__asm __saveds L_Module_Identify(register __d0 int num)
{
	// Return module information
	if (num==-1) return &module_info;

	// Valid function number?
	if (num>module_info.function_count || !(module_info.function[num].desc)) return 0;

	// Return function description
	return (ModuleInfo *)GetString(locale,module_info.function[num].desc);
}
