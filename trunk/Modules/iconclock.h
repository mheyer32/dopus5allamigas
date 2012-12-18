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

#define CATCOMP_NUMBERS
#include "iconclock.strings"
#include "modules_lib.h"

#define ENV_ICONCLOCK		"dopus/Icon Clock"
#define NAME_ICONCLOCK		"Icon Clock"

#define CLOCK_WIDTH	48
#define CLOCK_HEIGHT	17

#define NUMERAL_WIDTH	8
#define NUMERAL_HEIGHT	13
#define COLON_WIDTH	6
#define COLON_HEIGHT	13

typedef struct
{
	struct SignalSemaphore	sem;
	IPCData			*ipc;
} IconClockSemaphore;

typedef struct
{
	ULONG			a4;
	struct Library		*library;
	struct Library		*module;

	IPCData			*ipc;
	struct MsgPort		*notify_port;
	APTR			notify_req;

	struct DiskObject	clock_icon;
	struct Image		clock_image;

	struct RastPort		clock_rp;
	struct BitMap		clock_bm;

	struct AppIcon		*appicon;
	struct MsgPort		*app_port;

	long			icon_x;
	long			icon_y;
	char			buffer[256];

	IconClockSemaphore	sem;

	TimerHandle		*timer;
	long			day;
	char			date_buffer[20];

	struct Screen		*screen;
	short			pen;
	long			colour;

	IPCData			*main_ipc;

	struct Window		*about;
} iconclock_data;

void icon_clock(void);
ULONG __asm iconclock_startup(
	register __a0 IPCData *,
	register __a1 iconclock_data *);
void iconclock_cleanup(iconclock_data *);
void iconclock_show(iconclock_data *);
void read_parse_set(char **,long *);
void iconclock_init(iconclock_data *,struct Screen *);

extern USHORT __chip numeral_data[10][13],colon_data[3][13];
void iconclock_info(iconclock_data *);
