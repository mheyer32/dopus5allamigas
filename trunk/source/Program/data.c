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

#include "dopus.h"

// SAS Detach information
#if defined(__amigaos3__)
long __stack=STACK_LARGE;
long __priority=0;
long __BackGroundIO=0;
char *__procname="dopus";
#endif

// os4 ifaces
#ifdef __amigaos4__
struct DOpusIFace 		*IDOpus 		= NULL;
/*struct ConfigOpusIFace	*IConfigOpus	= NULL;
struct ModuleIFace		*IModule 		= NULL;

struct SysInfoIFace		*ISysInfo 		= NULL;*/
struct muIFace			*Imu 			= NULL;


struct UtilityIFace  	*IUtility 		= NULL;
struct LocaleIFace   	*ILocale 		= NULL;
struct CommoditiesIFace	*ICommodities 	= NULL;
struct ConsoleIFace 	*IConsole 		= NULL;
struct GraphicsIFace 	*IGraphics 		= NULL;
struct CyberGfxIFace 	*ICyberGfx 		= NULL;
struct IntuitionIFace 	*IIntuition 	= NULL;
struct InputIFace		*IInput 		= NULL;
struct GadToolsIFace 	*IGadTools 		= NULL;
struct AslIFace 		*IAsl 			= NULL;
struct LayersIFace 		*ILayers 		= NULL;
struct DiskfontIFace 	*IDiskfont 		= NULL;
struct IconIFace 		*IIcon 			= NULL;
struct WorkbenchIFace 	*IWorkbench		= NULL;
struct DataTypesIFace 	*IDataTypes 	= NULL;
struct RexxSysIFace 	*IRexxSys 		= NULL;
struct NewIconIFace 	*INewIcon 		= NULL;
struct TimerIFace		*ITimer 		= NULL;
struct AmigaGuideIFace	*IAmigaGuide 	= NULL;
#endif


// bases
#if defined(__amigaos4__) || defined(__AROS__)
struct UtilityBase		*UtilityBase	= NULL;
#else
struct Library			*UtilityBase	= NULL;
#endif
struct IntuitionBase	*IntuitionBase	= NULL;
struct GfxBase			*GfxBase		= NULL;
struct Library			*DOpusBase		= NULL;
struct Library			*IconBase		= NULL;
struct Library			*DiskfontBase	= NULL;
struct Library			*LayersBase		= NULL;
struct Library			*WorkbenchBase	= NULL;
struct Library			*CxBase			= NULL;
#if defined(__amigaos3__)
struct Library			*ConfigOpusBase = NULL;
#endif
#ifdef __AROS__
struct RxsLib			*RexxSysBase	= NULL;
#elif !defined(__amigaos3__)
struct Library			*RexxSysBase	= NULL;
#endif
struct Library			*GadToolsBase	= NULL;
struct Library			*AslBase		= NULL;
struct Library			*DataTypesBase	= NULL;
#if defined(__amigaos3__) || defined(__AROS__)
struct Device			*InputBase		= NULL;
#else
struct Library			*InputBase		= NULL;
#endif

#ifdef __MORPHOS__
struct Library			*TimerBase		= NULL;
#else
struct Device			*TimerBase		= NULL;
#endif



#ifdef __MORPHOS__
struct Library  		*ConsoleDevice 	= NULL;
#else
struct Device  			*ConsoleDevice 	= NULL;
#endif
struct Library			*AmigaGuideBase	= NULL;
struct Library			*CyberGfxBase	= NULL;
struct NewIconBase		*NewIconBase	= NULL;
struct Library			*muBase			= NULL;



//-----

struct Process			*main_proc;				// Main process pointer
IPCData					main_ipc;				// Main IPC data
APTR					global_memory_pool=0;	// Global memory pool for anything to use
char					*str_space_string;		// A string of spaces
struct DOpusLocale		locale;					// Locale data
APTR					main_status=0;			// Main status window
Cfg_Environment			*environment=0;			// Environment data
GUI_Glue				*GUI=0;					// GUI data
BPTR					old_current_dir=0;		// Old current directory
struct IOStdReq			input_req;
struct IOStdReq			timer_req;
struct IOStdReq			console_req;

struct DOpusSemaphore	pub_semaphore;

long main_lister_count=0;

// Internal function definitions
Cfg_Function	*def_function_leaveout=0;
Cfg_Function	*def_function_iconinfo=0;
Cfg_Function	*def_function_format=0;
Cfg_Function	*def_function_diskcopy=0;
Cfg_Function	*def_function_select=0;
Cfg_Function	*def_function_diskinfo=0;
Cfg_Function	*def_function_devicelist=0;
Cfg_Function	*def_function_cachelist=0;
Cfg_Function	*def_function_all=0;
Cfg_Function	*def_function_rename=0;
Cfg_Function	*def_function_delete=0;
Cfg_Function	*def_function_delete_quiet=0;
Cfg_Function	*def_function_makedir=0;
Cfg_Function	*def_function_copy=0;
Cfg_Function	*def_function_move=0;
Cfg_Function	*def_function_assign=0;
Cfg_Function	*def_function_configure=0;
Cfg_Function	*def_function_cli=0;
Cfg_Function	*def_function_devicelist_full=0;
Cfg_Function	*def_function_devicelist_brief=0;
Cfg_Function	*def_function_loadtheme=0;
Cfg_Function	*def_function_savetheme=0;
Cfg_Function	*def_function_buildtheme=0;
Cfg_Filetype	*default_filetype=0;
Cfg_Filetype	*run_filetype=0;
Cfg_Filetype	*command_filetype=0;

char *config_name="configopus.module";
char *dopus_name="Directory Opus";
char register_name[]="\x9b\x90\x8f\x8a\x8c\xca\xc5\x92\x90\x9b\x8a\x93\x9a\x8c\xd0\x8d\x9a\x98\x96\x8c\x8b\x9a\x8d\xd1\x92\x90\x9b\x8a\x93\x9a";

char *string_no_owner;
char *string_no_group;
char *string_empty;

// Shortcut arrow
UWORD
	arrow_hi_data[]={
		0xffe0,0x8020,0x8fa0,0x87a0,0x8fa0,0x9ea0,0xbc20,0xb820,
		0xb820,0x8020,0xffe0,
		0x0000,0x7fc0,0x7040,0x7840,0x7040,0x6140,0x43c0,0x47c0,
		0x47c0,0x7fc0,0x0000},

	arrow_lo_data[]={
		0xfff8,0x8008,0x8fe8,0x87e8,0x8fe8,0x9f68,0xbe08,0xbc08,
		0xbc08,0x8008,0xfff8,
		0x0000,0x7ff0,0x7010,0x7810,0x7010,0x6090,0x41f0,0x43f0,
		0x43f0,0x7ff0,0x0000};

struct Image
	arrow_image[2]={
		{0,0,11,11,2,arrow_hi_data,3,0,0},
		{0,0,13,11,2,arrow_lo_data,3,0,0}};
