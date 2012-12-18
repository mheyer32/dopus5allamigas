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

#include "register.h"

ModuleInfo
	module_info={
		1,
		"register.module",
		"register.catalog",
		0,
		0,{0}};

ConfigWindow
	serial_window={
		{POS_CENTER,POS_CENTER,60,17},
		{0,0,8,14}};

struct TagItem
	listview_tags[]={
		{DLV_ReadOnly,TRUE},
		{TAG_DONE}};

ObjectDef
	serial_objects[]={

		// Text display
		{OD_GADGET,
			MY_LISTVIEW_KIND,
			{0,0,SIZE_MAXIMUM,SIZE_MAX_LESS-1},
			{4,4,-4,-14},
			0,
			0,
			GAD_TEXT_DISPLAY,
			listview_tags},

/*
		// Deutsch
		{OD_GADGET,
			BUTTON_KIND,
			{0,POS_RIGHT_JUSTIFY,14,1},
			{4,-4,4,6},
			MSG_DEUTSCH,
			0,
			GAD_DEUTSCH,
			0},

		// English
		{OD_GADGET,
			BUTTON_KIND,
			{POS_CENTER,POS_RIGHT_JUSTIFY,14,1},
			{0,-4,4,6},
			MSG_ENGLISH,
			0,
			GAD_ENGLISH,
			0},
*/

		// Ok
		{OD_GADGET,
			BUTTON_KIND,
			{POS_CENTER,POS_RIGHT_JUSTIFY,14,1},
			{0,-4,4,6},
			MSG_OK_BUTTON,
			BUTTONFLAG_OKAY_BUTTON,
			GAD_SERIAL_OKAY,
			0},

		{OD_END}};


char
	*message0=
		"Directory Opus 5.5 Aminet 31 & Aminet Set 8 Licence\n\n"

		"Congratulations on purchasing Aminet 31 or Set 8 and "
		"welcome to this special version of Directory Opus 5.5.\n\n"

		"Unlike most of the other software included on Aminet 31 & Set 8, "
		"Directory Opus 5.5 is a fully working commercial product, "
		"and is (c) Copyright 1995-99 Jonathan Potter & GP Software. "
		"It has been licenced exclusively for purchasers of this CD.\n\n"

		"It is prohibited by law to copy, sell, reproduce or distribute this "
		"software in any manner whatsoever apart from on the original "
		"Aminet 31 or Set 8 CD. The original purchaser of the Aminet 31 or Set 8 CD "
		"is granted a single user licence to install this version of the "
		"program on their hard disk for their personal use only.\n\n"

		"The latest full version of Directory Opus, Magellan II, has many more features "
		"than 5.5. If you like the program as much as we do, we recommend that "
		"you upgrade as soon as possible. Contact us for a special discount "
		"on the upgrade to the latest version.\n\n"

			"\a\x10""GP Software\n"
			"\a\x10""PO Box 570\n"
			"\a\x10""Ashgrove, QLD\n"
			"\a\x10""Australia 4060\n"
			"\a\x10""Ph/Fax: +61 7 33661402\n"
			"\a\x10""web   : www.gpsoft.com.au\n"
			"\a\x10""mailto: greg@gpsoft.com.au\0\0\0\0\0\0";

