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

#ifndef _DOPUS_MODULES
#define _DOPUS_MODULES

#include "dopusbase.h"
#include "modules_pragmas.h"

typedef struct
{
	ULONG	id;
	char	*name;
	ULONG	desc;
	ULONG	flags;
	ULONG	data;
} ModuleFunction;

typedef struct
{
	ULONG		ver;
	char		*name;
	char		*locale_name;
	ULONG		flags;
	ULONG		function_count;
	ModuleFunction	function[1];
} ModuleInfo;

ModuleInfo	*Module_Identify(int);
int		Module_Entry(struct List *,struct Screen *,IPCData *,IPCData *,ULONG,ULONG);

// Callback commands
enum
{
	EXTCMD_GET_SOURCE,	// Get current source path
	EXTCMD_NEXT_SOURCE,	// Get next source path
	EXTCMD_UNLOCK_SOURCE,	// Unlock source paths
	EXTCMD_GET_ENTRY,	// Get entry
	EXTCMD_END_ENTRY,	// End entry
	EXTCMD_RELOAD_ENTRY,	// Reload entry
	EXTCMD_OPEN_PROGRESS,	// Open progress indicator
	EXTCMD_UPDATE_PROGRESS,	// Update progress indicator
	EXTCMD_CLOSE_PROGRESS,	// Close progress indicator
	EXTCMD_CHECK_ABORT,	// Check abort status
	EXTCMD_ENTRY_COUNT,	// Get entry count
	EXTCMD_GET_WINDOW,	// Get window handle
	EXTCMD_GET_DEST,	// Get next destination
	EXTCMD_END_SOURCE,	// Cleanup current source path
	EXTCMD_END_DEST,	// Cleanup current destination path
	EXTCMD_ADD_CHANGE,	// Add a change to a lister
	EXTCMD_ADD_FILE,	// Add a file to a lister
	EXTCMD_GET_HELP,	// Get help on a topic
};

struct progress_packet
{
	struct _PathNode	*path;
	char			*name;
	ULONG			count;
};

struct endentry_packet
{
	struct _FunctionEntry	*entry;
	BOOL			deselect;
};

struct addchange_packet
{
	struct _PathNode	*path;
	USHORT			change;
	APTR			data;
};

struct addfile_packet
{
	struct _PathNode	*path;
	struct FileInfoBlock	*fib;
};

#endif
