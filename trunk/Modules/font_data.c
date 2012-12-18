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

#include "font.h"

ModuleInfo
	module_info={
		1,
		"font.module",
		"font.catalog",
		0,
		1,
		{0,"ViewFont",MSG_VIEWFONT_DESC,0,0}};

ConfigWindow
	font_window={
		{POS_CENTER,POS_CENTER,40,9},
		{0,0,44,67}};


struct TagItem

	font_layout_tags[]={
		{GTCustom_LayoutRel,GAD_FONT_LAYOUT},
		{TAG_DONE}};


ObjectDef

	font_objects[]={

		// Background area
		{OD_AREA,
			0,
			{0,0,SIZE_MAXIMUM,SIZE_MAX_LESS-1},
			{2,2,-2,-10},
			0,
			AREAFLAG_RECESSED|AREAFLAG_ERASE,
			GAD_FONT_LAYOUT,
			0},

		// Print
		{OD_GADGET,
			BUTTON_KIND,
			{POS_CENTER,POS_RIGHT_JUSTIFY,12,1},
			{0,-2,12,6},
			MSG_FONT_PRINT,
			0,
			GAD_FONT_PRINT,
			0},

		{OD_END}};

