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
#include "show.strings"
#include "modules_lib.h"
#include "dopuslib:read_ilbm.h"

typedef struct
{
	ILBMHandle		*ilbm;
	struct Screen		*display_screen;
	struct Window		*display_window;
	ULONG			error;
	IPCData			*ipc;
	char			*file;

	TimerHandle		*timer;

	struct BitMap		*double_bm;
	BOOL			anim_ok;

	struct BitMap		*anim_bm[2];
	short			anim_bitmap;

	unsigned long		frame_speed;
	unsigned long		original_speed;
	unsigned long		frame_secs;
	unsigned long		frame_micros;

	BOOL			anim_playing;
	unsigned short		frame_num;
	unsigned short		frame_count;
	ANIMFrame		*last_frame;

	struct Preferences	prefs;

	struct Library		*dt_base;

	short			width;
	short			height;
	short			depth;
	ULONG			modeid;

	APTR			dt_object;
	struct dtFrameBox	framebox;
	struct FrameInfo	frameinfo;
	struct gpLayout		layout;
	ULONG			*cregs;
	struct BitMap		*dt_bm;

	short			pic_ok;
	char			*picture_type;

	BOOL			active;

	ULONG			numcolours;

	struct BitMap		*scr_bm;
} show_data;

#define DataTypesBase	(data->dt_base)

struct Screen *__stdargs my_OpenScreenTags(Tag tag,...);
struct Window *__stdargs my_OpenWindowTags(Tag tag,...);

void show_free(show_data *data);
BOOL show_help(show_data *data);
void show_next_frame(show_data *data);
short show_print(show_data *data,struct Window *help_window,ObjectList *list);

void do_riff(unsigned char *delta,struct BitMap *bitmap,unsigned short xor,unsigned short sourcewidth,unsigned short size);
void decode_riff_xor(unsigned char *delta,char *plane,unsigned short rowbytes,unsigned short sourcebytes);
void decode_riff_set(unsigned char *delta,char *plane,unsigned short rowbytes,unsigned short sourcebytes);

void do_riff_7(unsigned char *delta,struct BitMap *bitmap,unsigned short sourcewidth,unsigned short size);
void decode_riff7_short(unsigned short *delta,unsigned char *opcode,unsigned char *plane,unsigned short rowbytes,unsigned short sourcebytes);
void decode_riff7_long(unsigned long *delta,unsigned char *opcode,unsigned char *plane,unsigned short rowbytes,unsigned short sourcebytes);

BOOL show_get_dtpic(show_data *data,struct Node *node);

extern ConfigWindow
	picture_info_window,
	anim_info_window;
extern ObjectDef
	picture_info_objects[],
	anim_info_objects[],
	show_info_objects[],
	print_objects[];

enum
{
	GAD_dummy,

	GAD_INFO_AREA,
	GAD_INFO_FILE,
	GAD_INFO_IMAGE_SIZE,
	GAD_INFO_COLOURS,
	GAD_INFO_MODE,
	GAD_INFO_FRAME,
	GAD_INFO_ANIM,
	GAD_OK,

	GAD_PRINT_AREA,
	GAD_PRINT_ASPECT,
	GAD_PRINT_IMAGE,
	GAD_PRINT_SHADE,
	GAD_PRINT_PLACEMENT,
	GAD_PRINT_FORM_FEED,
	GAD_PRINT_PRINT_TITLE,
	GAD_PRINT,

	GAD_INFO_TYPE,
};
