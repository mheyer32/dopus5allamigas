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
#include "font.strings"
#include "modules_lib.h"

typedef struct
{
	struct Screen		*screen;
	struct Window		*window;
	IPCData			*ipc;

	ConfigWindow		win_dims;
	NewConfigWindow		new_win;
	ObjectList		*list;

	struct TextAttr		attr;
	struct TextFont		*font;

	Point			window_pos;
	char			pos_valid;

	char			font_name[256];
	short			font_size;

	char			title[80];
} font_data;

BOOL font_open(font_data *data,BOOL);
void font_close(font_data *data);
void font_free(font_data *data);

extern ConfigWindow font_window;
extern ObjectDef font_objects[];

enum
{
	GAD_FONT_LAYOUT,

	GAD_font_DEVICES,
	GAD_font_NAME,
	GAD_font_FFS,
	GAD_font_INTERNATIONAL,
	GAD_font_CACHING,
	GAD_font_TRASHCAN,
	GAD_font_INSTALL,
	GAD_font_VERIFY,
	GAD_font_STATUS,
	GAD_font_font,
	GAD_font_QUICK_font,
	GAD_font_CANCEL,
};

extern unsigned long bootblock_20[22];
