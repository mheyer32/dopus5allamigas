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

#include "modules_lib.h"

int __saveds __UserLibInit(void);
void __saveds __UserLibCleanup(void);

struct Library *DOpusBase;
struct Library *IconBase;
struct Library *LocaleBase;
struct Library *UtilityBase;
struct Library *LayersBase;
struct Library *WorkbenchBase;
struct Library *IFFParseBase;
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
	IFFParseBase=0;
	GadToolsBase=0;
	DiskfontBase=0;
	AslBase=0;
	locale=0;

	// DOS
	DOSBase=(struct DosLibrary *)OpenLibrary("dos.library",0);

	// Other libraries we want
	if (!(DOpusBase=OpenLibrary("dopus5.library",41)) ||
		!(IntuitionBase=(struct IntuitionBase *)OpenLibrary("intuition.library",37)) ||
		!(GfxBase=(struct GfxBase *)OpenLibrary("graphics.library",37)) ||
		!(IconBase=OpenLibrary("icon.library",37)) ||
		!(LayersBase=OpenLibrary("layers.library",37)) ||
		!(GadToolsBase=OpenLibrary("gadtools.library",37)) ||
		!(AslBase=OpenLibrary("asl.library",37)) ||
		!(DiskfontBase=OpenLibrary("diskfont.library",37)) ||
		!(IFFParseBase=OpenLibrary("iffparse.library",0)) ||
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
	CloseLibrary((struct Library *)IntuitionBase);
	CloseLibrary((struct Library *)GfxBase);
	CloseLibrary(IconBase);
	CloseLibrary(LayersBase);
	CloseLibrary(UtilityBase);
	CloseLibrary(IFFParseBase);
	CloseLibrary(WorkbenchBase);
	CloseLibrary(DiskfontBase);
	CloseLibrary(AslBase);
	CloseLibrary((struct Library *)DOSBase);
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
