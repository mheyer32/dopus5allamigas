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

#ifndef DOPUS_DATA
#define DOPUS_DATA


// Library bases
/*#ifndef __amigaos4__
extern struct ExecBase			*SysBase;
#endif*/

extern struct IntuitionBase		*IntuitionBase;
extern struct GfxBase			*GfxBase;

#if defined(__amigaos4__) || defined(__AROS__)
extern struct UtilityBase		*UtilityBase;
#else
extern struct Library			*UtilityBase;
#endif

extern struct Library			*DOpusBase;
extern struct Library			*IconBase;
extern struct Library			*DiskfontBase;
extern struct Library			*LayersBase;
extern struct Library			*WorkbenchBase;
extern struct Library			*CxBase;
extern struct Library			*GadToolsBase;
extern struct Library			*IFFParseBase;
extern struct Library			*AslBase;
extern struct Library			*DataTypesBase;
#if defined(__amigaos3__) || defined(__AROS__)
extern struct Device			*InputBase;
#else
extern struct Library			*InputBase;
#endif

#ifdef __MORPHOS__
extern struct Library			*TimerBase;
#else
extern struct Device			*TimerBase;
#endif

#ifdef __AROS__
extern struct RxsLib			*RexxSysBase;
#elif !defined(__amigaos3__)
extern struct Library			*RexxSysBase;
#endif

extern struct Library			*AmigaGuideBase;
extern struct Library			*CyberGfxBase;

// ----

extern struct Process			*main_proc;			// Main process pointer
extern struct MsgPort			*arexx_port;			// ARexx port
extern IPCData					main_ipc;			// Main IPC data
extern APTR						global_memory_pool;		// Global memory pool for anything to use
extern char						*str_space_string;		// A string of spaces
extern struct DOpusLocale		locale;				// Locale data
extern APTR						main_status;			// Main status window
extern Cfg_Environment			*environment;			// Environment data
extern GUI_Glue					*GUI;				// GUI data
extern BPTR						old_current_dir;		// Old current directory
extern struct IOStdReq			input_req;
extern struct IOStdReq			timer_req;
extern struct IOStdReq			console_req;

extern struct DOpusSemaphore		pub_semaphore;

extern long				main_lister_count;

// Internal function definitions
extern Cfg_Function	*def_function_leaveout;
extern Cfg_Function	*def_function_iconinfo;
extern Cfg_Function	*def_function_format;
extern Cfg_Function	*def_function_diskcopy;
extern Cfg_Function	*def_function_select;
extern Cfg_Function	*def_function_diskinfo;
extern Cfg_Function	*def_function_devicelist;
extern Cfg_Function	*def_function_devicelist_full;
extern Cfg_Function	*def_function_devicelist_brief;
extern Cfg_Function	*def_function_cachelist;
extern Cfg_Function	*def_function_all;
extern Cfg_Function	*def_function_rename;
extern Cfg_Function	*def_function_delete;
extern Cfg_Function	*def_function_delete_quiet;
extern Cfg_Function	*def_function_makedir;
extern Cfg_Function	*def_function_copy;
extern Cfg_Function	*def_function_move;
extern Cfg_Function	*def_function_assign;
extern Cfg_Function	*def_function_configure;
extern Cfg_Function	*def_function_cli;
extern Cfg_Function	*def_function_loadtheme;
extern Cfg_Function	*def_function_savetheme;
extern Cfg_Function	*def_function_buildtheme;
extern Cfg_Filetype	*default_filetype;
extern Cfg_Filetype	*run_filetype;
extern Cfg_Filetype	*command_filetype;

extern char *config_name;
extern char *dopus_name;

extern char *string_no_owner;
extern char *string_no_group;
extern char *string_empty;

extern UWORD arrow_hi_data[11][2],arrow_lo_data[11][2];
extern struct Image arrow_image[2];
extern UWORD small_arrow[7],big_arrow[11];
extern UWORD moon_big_data[8][2][13],moon_small_data[8][2][9];
extern UWORD command_arrow[7],parent_arrow[6];

#ifdef __amigaos3__
extern UWORD *command_arrow_chip;
extern UWORD *parent_arrow_chip;
#endif

#endif
