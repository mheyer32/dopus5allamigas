#include "config_lib.h"

#define LIB_VER 68

int __saveds __UserLibInit(void);
void __saveds __UserLibCleanup(void);
char *_ProgramName="configopus.module";

char *version="$VER: configopus.module 68.11 (08.11.99)";

struct DosLibrary *DOSBase=0;
struct Library *DOpusBase=0;
struct IntuitionBase *IntuitionBase=0;
struct GfxBase *GfxBase=0;
struct Library *LayersBase=0;
struct Library *DiskfontBase=0;
struct Library *GadToolsBase=0;
struct Library *WorkbenchBase=0;
struct Library *IconBase=0;
struct Library *AslBase=0;
struct Library *CxBase=0;
struct Library *UtilityBase=0;
struct Library *LocaleBase=0;
struct DOpusLocale *locale=0;

// Initialise libraries we need
__saveds __UserLibInit()
{
	// DOS
	DOSBase=(struct DosLibrary *)OpenLibrary("dos.library",0);

	// Other libraries we want
	if (!(DOpusBase=OpenLibrary("dopus5.library",LIB_VER)) ||
		!(IntuitionBase=(struct IntuitionBase *)OpenLibrary("intuition.library",37)) ||
		!(GfxBase=(struct GfxBase *)OpenLibrary("graphics.library",37)) ||
		!(LayersBase=OpenLibrary("layers.library",37)) ||
		!(GadToolsBase=OpenLibrary("gadtools.library",37)) ||
		!(DiskfontBase=OpenLibrary("diskfont.library",37)) ||
		!(WorkbenchBase=OpenLibrary("workbench.library",37)) ||
		!(IconBase=OpenLibrary("icon.library",37)) ||
		!(AslBase=OpenLibrary("asl.library",37)) ||
		!(CxBase=OpenLibrary("commodities.library",37)) ||
		!(UtilityBase=OpenLibrary("utility.library",37))) return 1;

	// Allocate and open locale data
	if (!(locale=AllocVec(sizeof(struct DOpusLocale),MEMF_CLEAR)))
		return 1;
	init_locale_data(locale);

	if (LocaleBase=OpenLibrary("locale.library",38))
	{
		locale->li_LocaleBase=LocaleBase;
		locale->li_Catalog=OpenCatalogA(0,"configopus.catalog",0);
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
			CloseCatalog(locale->li_Catalog);
			CloseLibrary(LocaleBase);
		}
		FreeVec(locale);
	}

	// Close libraries
	CloseLibrary(DOpusBase);
	CloseLibrary((struct Library *)IntuitionBase);
	CloseLibrary((struct Library *)GfxBase);
	CloseLibrary(LayersBase);
	CloseLibrary(GadToolsBase);
	CloseLibrary(DiskfontBase);
	CloseLibrary(WorkbenchBase);
	CloseLibrary(IconBase);
	CloseLibrary(AslBase);
	CloseLibrary(CxBase);
	CloseLibrary(UtilityBase);
	CloseLibrary((struct Library *)DOSBase);
}

/*
libdata *init_libs(void)
{
	libdata *data;

	// Allocate library data
	if (!(data=AllocVec(sizeof(libdata),MEMF_CLEAR)))
		return 0;

	// Get libraries we need
	if (!(data->DOSBase=OpenLibrary("dos.library",0)) ||
		!(data->DOpusBase=OpenLibrary("dopus5.library",40)) ||
		!(data->IntuitionBase=OpenLibrary("intuition.library",37)) ||
		!(data->GfxBase=OpenLibrary("graphics.library",37)) ||
		!(data->LayersBase=OpenLibrary("layers.library",37)) ||
		!(data->GadToolsBase=OpenLibrary("gadtools.library",37)) ||
		!(data->DiskfontBase=OpenLibrary("diskfont.library",37)) ||
		!(data->WorkbenchBase=OpenLibrary("workbench.library",37)) ||
		!(data->IconBase=OpenLibrary("icon.library",37)) ||
		!(data->AslBase=OpenLibrary("asl.library",37)) ||
		!(data->CxBase=OpenLibrary("commodities.library",37)) ||
		!(data->UtilityBase=OpenLibrary("utility.library",37)))
	{
		free_libs(data);
		return 0;
	}

	// Open locale data
	init_locale_data(&data->locale);
	if (data->LocaleBase=OpenLibrary("locale.library",38))
	{
		data->locale.li_LocaleBase=LocaleBase;
		data->locale.li_Catalog=OpenCatalogA(NULL,"ConfigOpus.catalog",0);
	}

	return data;
}

void free_libs(libdata *data)
{
	if (data)
	{
		// Free locale stuff
		if (data->LocaleBase)
		{
			CloseCatalog(data->locale.li_Catalog);
			CloseLibrary(data->LocaleBase);
		}

		// Close libraries
		if (data->DOpusBase) CloseLibrary(data->DOpusBase);
		if (data->IntuitionBase) CloseLibrary(data->IntuitionBase);
		if (data->GfxBase) CloseLibrary(data->GfxBase);
		if (data->LayersBase) CloseLibrary(data->LayersBase);
		if (data->GadToolsBase) CloseLibrary(data->GadToolsBase);
		if (data->DiskfontBase) CloseLibrary(data->DiskfontBase);
		if (data->WorkbenchBase) CloseLibrary(data->WorkbenchBase);
		if (data->IconBase) CloseLibrary(data->IconBase);
		if (data->AslBase) CloseLibrary(data->AslBase);
		if (data->CxBase) CloseLibrary(data->CxBase);
		if (data->UtilityBase) CloseLibrary(data->UtilityBase);
		if (data->DOSBase) CloseLibrary(data->DOSBase);

		// Free data
		FreeVec(data);
	}
}
*/

void __stdargs _XCEXIT(long poo) {}
void __stdargs _CXFERR(int code) {}

void L_Config_removed(void);
void L_Config_removed(void){}
