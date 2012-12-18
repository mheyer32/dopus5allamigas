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
#include "replace.h"

#ifdef FULL_REPLACE

ConfigWindow
	replace_window={
		{POS_CENTER,POS_CENTER,41,6},
		{0,0,34,50}};

USHORT
	replace_labels[]={
		MSG_SKIP,
		MSG_REPLACE,
		0};

struct TagItem
	replace_layout[]={
		{GTCustom_LayoutRel,GAD_REPLACE_LAYOUT},
		{TAG_DONE}},

	replace_option_tags[]={
		{GTCustom_LocaleLabels,(ULONG)replace_labels},
		{TAG_MORE,(ULONG)replace_layout}},

	replace_size[]={
		{GTNM_Border,TRUE},
		{TAG_MORE,(ULONG)replace_layout}},

	replace_date[]={
		{GTTX_Border,TRUE},
		{TAG_MORE,(ULONG)replace_layout}};

ObjectDef
	replace_objects[]={

		// Replace layout area
		{OD_AREA,
			0,
			{0,0,SIZE_MAXIMUM,SIZE_MAX_LESS-1},
			{3,3,-3,-12},
			0,
			AREAFLAG_RECESSED|AREAFLAG_ERASE,
			GAD_REPLACE_LAYOUT,
			0},

		// Size title
		{OD_TEXT,
			TEXTPEN,
			{6,0,0,0},
			{4,4,0,0},
			MSG_SIZE,
			0,
			0,
			replace_layout},

		// Date title
		{OD_TEXT,
			TEXTPEN,
			{18,0,0,0},
			{16,4,0,0},
			MSG_DATE,
			0,
			0,
			replace_layout},

		// Old size
		{OD_GADGET,
			NUMBER_KIND,
			{6,1,12,1},
			{4,4,4,6},
			MSG_OLD,
			PLACETEXT_LEFT,
			GAD_REPLACE_OLD_SIZE,
			replace_size},

		// Old date
		{OD_GADGET,
			TEXT_KIND,
			{18,1,22,1},
			{16,4,4,6},
			0,
			0,
			GAD_REPLACE_OLD_DATE,
			replace_date},

		// New size
		{OD_GADGET,
			NUMBER_KIND,
			{6,2,12,1},
			{4,12,4,6},
			MSG_NEW,
			PLACETEXT_LEFT,
			GAD_REPLACE_NEW_SIZE,
			replace_size},

		// New date
		{OD_GADGET,
			TEXT_KIND,
			{18,2,22,1},
			{16,12,4,6},
			0,
			0,
			GAD_REPLACE_NEW_DATE,
			replace_date},

		// Option title
		{OD_TEXT,
			TEXTPEN,
			{17,3,0,0},
			{16,25,0,1},
			MSG_REPLACE_OPTION,
			TEXTFLAG_RIGHT_JUSTIFY,
			0,
			replace_layout},

		// Option
		{OD_GADGET,
			MX_KIND,
			{18,3,1,1},
			{16,24,7,1},
			MSG_REPLACE_OPTION_KEY,
			PLACETEXT_RIGHT,
			GAD_REPLACE_OPTION,
			replace_option_tags},

		// Ok
		{OD_GADGET,
			BUTTON_KIND,
			{0,POS_RIGHT_JUSTIFY,12,1},
			{3,-3,4,6},
			MSG_OK_BUTTON,
			BUTTONFLAG_OKAY_BUTTON,
			GAD_REPLACE_OK,
			0},

		// All
		{OD_GADGET,
			BUTTON_KIND,
			{POS_CENTER,POS_RIGHT_JUSTIFY,12,1},
			{0,-3,4,6},
			MSG_ALL_BUTTON,
			0,
			GAD_REPLACE_ALL,
			0},

		// Abort
		{OD_GADGET,
			BUTTON_KIND,
			{POS_RIGHT_JUSTIFY,POS_RIGHT_JUSTIFY,12,1},
			{-3,-3,4,6},
			MSG_ABORT_BUTTON,
			BUTTONFLAG_CANCEL_BUTTON,
			GAD_REPLACE_ABORT,
			0},

		{OD_END}};

#endif
