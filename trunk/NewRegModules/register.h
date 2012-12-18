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
#include "register.strings"
#include "modules_lib.h"

typedef struct _rego_data
{
	char			serial_number[20];
	char			name[40];
	char			company[40];
	char			address1[40];
	char			address2[40];
	char			address3[40];
	struct DateStamp	install_date;
	struct DateStamp	harddrive_date;
	short			pirate;
	short			pirate_count;
	long			checksum;
} rego_data;

enum
{
	GAD_TEXT_DISPLAY,
	GAD_SERIAL_OKAY,
	GAD_DEUTSCH,
	GAD_ENGLISH,
};

extern ConfigWindow serial_window;
extern ObjectDef serial_objects[];

extern char *message0,*message1;
