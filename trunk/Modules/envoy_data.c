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

#include "envoy.h"

ModuleInfo
	module_info={
		1,
		"envoy.module",
		"envoy.catalog",
		0,
		1,
		{0,"NetSet",MSG_ENVOY_DESC,FUNCF_NEED_ENTRIES|FUNCF_NO_ARGS,0}};

ConfigWindow
	_envoy_window={
		{POS_CENTER,POS_CENTER,42,5},
		{0,0,8,49}};

struct TagItem
	_envoy_layout_tags[]={
		{GTCustom_LayoutRel,ENVOY_LAYOUT},
		{TAG_END}},

	_envoy_field_tags[]={
		{GTST_MaxChars,32},
		{TAG_MORE,(ULONG)_envoy_layout_tags}};

ObjectDef
	_envoy_objects[]={

		// Layout area
		{OD_AREA,
			0,
			{0,0,SIZE_MAXIMUM,SIZE_MAX_LESS-1},
			{2,2,-2,-10},
			0,
			AREAFLAG_RECESSED|AREAFLAG_ERASE,
			ENVOY_LAYOUT,
			0},

		// Owner folder gadget
		{OD_GADGET,
			FILE_BUTTON_KIND,
			{11,0,0,1},
			{4,4,28,6},
			MSG_ENVOY_OWNER,
			PLACETEXT_LEFT,
			GAD_ENVOY_OWNER,
			_envoy_layout_tags},

		// Owner field
		{OD_GADGET,
			STRING_KIND,
			{11,0,SIZE_MAXIMUM,1},
			{32,4,-8,6},
			0,
			0,
			GAD_ENVOY_OWNER_FIELD,
			_envoy_field_tags},

		// Group folder gadget
		{OD_GADGET,
			FILE_BUTTON_KIND,
			{11,1,0,1},
			{4,11,28,6},
			MSG_ENVOY_GROUP,
			PLACETEXT_LEFT,
			GAD_ENVOY_GROUP,
			_envoy_layout_tags},

		// Group field
		{OD_GADGET,
			STRING_KIND,
			{11,1,SIZE_MAXIMUM,1},
			{32,11,-8,6},
			0,
			0,
			GAD_ENVOY_GROUP_FIELD,
			_envoy_field_tags},

		// Group bits title
		{OD_TEXT,
			TEXTPEN,
			{10,2,0,1},
			{2,21,0,0},
			MSG_ENVOY_GROUP_BITS,
			TEXTFLAG_RIGHT_JUSTIFY,
			0,
			_envoy_layout_tags},

		// Group bits
		{OD_GADGET,
			BUTTON_KIND,
			{11,2,2,1},
			{4,18,4,6},
			(ULONG)"r",
			TEXTFLAG_TEXT_STRING|BUTTONFLAG_TOGGLE_SELECT,
			GAD_ENVOY_GROUP_READ,
			_envoy_layout_tags},

		{OD_GADGET,
			BUTTON_KIND,
			{13,2,2,1},
			{8,18,4,6},
			(ULONG)"w",
			TEXTFLAG_TEXT_STRING|BUTTONFLAG_TOGGLE_SELECT,
			GAD_ENVOY_GROUP_WRITE,
			_envoy_layout_tags},

		{OD_GADGET,
			BUTTON_KIND,
			{15,2,2,1},
			{12,18,4,6},
			(ULONG)"e",
			TEXTFLAG_TEXT_STRING|BUTTONFLAG_TOGGLE_SELECT,
			GAD_ENVOY_GROUP_EXECUTE,
			_envoy_layout_tags},

		{OD_GADGET,
			BUTTON_KIND,
			{17,2,2,1},
			{16,18,4,6},
			(ULONG)"d",
			TEXTFLAG_TEXT_STRING|BUTTONFLAG_TOGGLE_SELECT,
			GAD_ENVOY_GROUP_DELETE,
			_envoy_layout_tags},

		// Other bits title
		{OD_TEXT,
			TEXTPEN,
			{10,3,0,1},
			{2,28,0,0},
			MSG_ENVOY_OTHER_BITS,
			TEXTFLAG_RIGHT_JUSTIFY,
			0,
			_envoy_layout_tags},

		// Other bits
		{OD_GADGET,
			BUTTON_KIND,
			{11,3,2,1},
			{4,25,4,6},
			(ULONG)"r",
			TEXTFLAG_TEXT_STRING|BUTTONFLAG_TOGGLE_SELECT,
			GAD_ENVOY_OTHER_READ,
			_envoy_layout_tags},

		{OD_GADGET,
			BUTTON_KIND,
			{13,3,2,1},
			{8,25,4,6},
			(ULONG)"w",
			TEXTFLAG_TEXT_STRING|BUTTONFLAG_TOGGLE_SELECT,
			GAD_ENVOY_OTHER_WRITE,
			_envoy_layout_tags},

		{OD_GADGET,
			BUTTON_KIND,
			{15,3,2,1},
			{12,25,4,6},
			(ULONG)"e",
			TEXTFLAG_TEXT_STRING|BUTTONFLAG_TOGGLE_SELECT,
			GAD_ENVOY_OTHER_EXECUTE,
			_envoy_layout_tags},

		{OD_GADGET,
			BUTTON_KIND,
			{17,3,2,1},
			{16,25,4,6},
			(ULONG)"d",
			TEXTFLAG_TEXT_STRING|BUTTONFLAG_TOGGLE_SELECT,
			GAD_ENVOY_OTHER_DELETE,
			_envoy_layout_tags},

		// Ok
		{OD_GADGET,
			BUTTON_KIND,
			{0,POS_RIGHT_JUSTIFY,12,1},
			{2,-2,12,6},
			MSG_OK,
			BUTTONFLAG_OKAY_BUTTON,
			GAD_ENVOY_OK,
			0},

		// Cancel
		{OD_GADGET,
			BUTTON_KIND,
			{POS_RIGHT_JUSTIFY,POS_RIGHT_JUSTIFY,12,1},
			{-2,-2,12,6},
			MSG_CANCEL,
			BUTTONFLAG_CANCEL_BUTTON,
			GAD_ENVOY_CANCEL,
			0},

		{OD_END}};
