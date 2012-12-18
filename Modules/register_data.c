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

#ifndef SOLD_VERSION

ConfigWindow
	serial_window={
		{POS_CENTER,POS_CENTER,50,7},
		{0,0,0,57}};

struct TagItem
	serial_layout[]={
		{GTCustom_LayoutRel,GAD_SERIAL_LAYOUT},
		{TAG_DONE}},

	serial_serial_tags[]={
		{GTST_MaxChars,20},
		{TAG_MORE,(ULONG)serial_layout}},

	serial_tags[]={
		{GTST_MaxChars,40},
		{TAG_MORE,(ULONG)serial_layout}};

ObjectDef
	serial_objects[]={

		// Layout
		{OD_AREA,
			0,
			{0,0,SIZE_MAXIMUM,SIZE_MAX_LESS-1},
			{3,3,-3,-12},
			0,
			AREAFLAG_RECESSED|AREAFLAG_ERASE,
			GAD_SERIAL_LAYOUT,
			0},

		// Serial #
		{OD_GADGET,
			STRING_KIND,
			{12,0,SIZE_MAXIMUM,1},
			{4,3,-4,4},
			MSG_SERIAL_SERIAL_NUMBER,
			PLACETEXT_LEFT,
			GAD_SERIAL_SERIAL,
			serial_serial_tags},

		// Name
		{OD_GADGET,
			STRING_KIND,
			{12,1,SIZE_MAXIMUM,1},
			{4,9,-4,4},
			MSG_SERIAL_NAME,
			PLACETEXT_LEFT,
			GAD_SERIAL_NAME,
			serial_tags},

		// Company
		{OD_GADGET,
			STRING_KIND,
			{12,2,SIZE_MAXIMUM,1},
			{4,15,-4,4},
			MSG_SERIAL_COMPANY,
			PLACETEXT_LEFT,
			GAD_SERIAL_COMPANY,
			serial_tags},

		// Address #1
		{OD_GADGET,
			STRING_KIND,
			{12,3,SIZE_MAXIMUM,1},
			{4,21,-4,4},
			MSG_SERIAL_ADDRESS1,
			PLACETEXT_LEFT,
			GAD_SERIAL_ADDRESS1,
			serial_tags},

		// Address #2
		{OD_GADGET,
			STRING_KIND,
			{12,4,SIZE_MAXIMUM,1},
			{4,27,-4,4},
			MSG_SERIAL_ADDRESS2,
			PLACETEXT_LEFT,
			GAD_SERIAL_ADDRESS2,
			serial_tags},

		// City, State
		{OD_GADGET,
			STRING_KIND,
			{12,5,SIZE_MAXIMUM,1},
			{4,33,-4,4},
			MSG_SERIAL_ADDRESS3,
			PLACETEXT_LEFT,
			GAD_SERIAL_ADDRESS3,
			serial_tags},

		// Register
		{OD_GADGET,
			BUTTON_KIND,
			{0,POS_RIGHT_JUSTIFY,12,1},
			{3,-3,4,6},
			MSG_OK_BUTTON,
			BUTTONFLAG_OKAY_BUTTON,
			GAD_SERIAL_OKAY,
			0},

		// Run
		{OD_GADGET,
			BUTTON_KIND,
			{POS_CENTER,POS_RIGHT_JUSTIFY,12,1},
			{0,-3,4,6},
			MSG_RUN_BUTTON,
			0,
			GAD_SERIAL_RUN,
			0},

		// Cancel
		{OD_GADGET,
			BUTTON_KIND,
			{POS_RIGHT_JUSTIFY,POS_RIGHT_JUSTIFY,12,1},
			{-3,-3,4,6},
			MSG_CANCEL_BUTTON,
			BUTTONFLAG_CANCEL_BUTTON,
			GAD_SERIAL_CANCEL,
			0},

		{OD_END}};


#else

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

		// Ok
		{OD_GADGET,
			BUTTON_KIND,
			{POS_CENTER,POS_RIGHT_JUSTIFY,14,1},
			{0,-4,4,6},
			MSG_OK,
			BUTTONFLAG_OKAY_BUTTON,
			GAD_SERIAL_OKAY,
			0},

		{OD_END}};

char
	*message0=
		"\vLicence Conditions: Directory Opus 5.5 for MACD11 CD-ROM\n\n"

		"Congratulations on your purchase of MACD11 CD-ROM and "
		"welcome to this special version of Directory Opus 5.5.\n\n"

		"This Directory Opus 5.5 is a fully working commercial product, "
		"and is (c) Copyright 1995-99 Jonathan Potter & GP Software. "
		"It has been licenced exclusively for purchasers of this MACD11 CD-ROM "
		"in Poland ONLY.\n\n"

		"It is prohibited by law to copy, sell, reproduce or distribute this "
		"software in any manner whatsoever apart from on the original "
		"MACD11 CD-ROM. The original purchaser of the MACD11 CD-ROM "
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
			"\a\x10""mailto: greg@gpsoft.com.au";

#endif
