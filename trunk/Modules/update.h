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
#include "update.strings"
#include "modules_lib.h"

#define UPDATEF_DONE_PATHS	(1<<0)
#define UPDATEF_DONE_LEFTOUTS	(1<<1)
#define UPDATEF_DONE_GROUPS	(1<<2)
#define UPDATEF_DONE_STORAGE	(1<<3)
#define UPDATEF_DONE_FILETYPES	(1<<4)
#define UPDATEF_DONE_POSITION	(1<<5)
#define UPDATEF_DONE_PATH_KEYS	(1<<6)
#define UPDATEF_DONE_COMMANDS	(1<<7)
#define UPDATEF_DONE_DESKTOP	(1<<8)
#define UPDATEF_DONE_THEMES 	(1<<9)

struct Window *open_status(struct Screen *);
BOOL update_do_leftouts(struct List *,APTR);
BOOL update_groups(void);
short update_convert_leftouts(APTR file,APTR memory,struct List *list);
BOOL update_storage(void);
void update_filetypes(void);
void update_envarc(void);
void update_envarc_do(char *path);
APTR read_position_info(struct List *list);
void update_do_pathkeys(struct List *list);
