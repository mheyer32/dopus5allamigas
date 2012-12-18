#include "config_lib.h"
#include "config_environment.h"

// ftp environment window dimensions
ConfigWindow
	ftp_environment_window={
		{POS_CENTER,POS_CENTER,66,14},
		{0,0,36,64}};

// Tags for gadgets
static struct TagItem

	// Option lister
	ftp_lister_taglist[]={
		{DLV_ShowSelected,0},
		{DLV_NoScroller,1},
		{DLV_TopJustify,1},
		{TAG_END,0}},



	// Relative to area tags[]={
	ftp_relative_taglist[]={
		{GTCustom_LayoutRel,GAD_ENVIRONMENT_EDIT_AREA},
		{TAG_END,0}},


	// string gadget for 4 chars
	ftp_timeout_field[]={
		{GTIN_MaxChars,4},
		{TAG_MORE,(ULONG)ftp_relative_taglist}},


// Flags objects
ObjectDef
	ftp_environment_objects[]={

		// ftp item lister
		{OD_GADGET,
			MY_LISTVIEW_KIND,
			{0,0,16,13},
			{2,2,4,52},
			0,
			LISTVIEWFLAG_CURSOR_KEYS,
			GAD_ENVIRONMENT_ITEM_LISTER,
			ftp_lister_taglist},

		// Edit area
		{OD_AREA,
			0,
			{16,0,SIZE_MAXIMUM,13},
			{8,2,-2,52},
			0,
			AREAFLAG_RECESSED|AREAFLAG_ERASE,
			GAD_ENVIRONMENT_EDIT_AREA,
			0},

		// Save
		{OD_GADGET,
			BUTTON_KIND,
			{0,POS_RIGHT_JUSTIFY,16,1},
			{2,-2,4,6},
			MSG_SAVE,
			BUTTONFLAG_OKAY_BUTTON,
			GAD_ENVIRONMENT_SAVE,
			0},

		// Use
		{OD_GADGET,
			BUTTON_KIND,
			{POS_CENTER,POS_RIGHT_JUSTIFY,16,1},
			{2,-2,4,6},
			MSG_USE,
			0,
			GAD_ENVIRONMENT_USE,
			0},

		// Cancel
		{OD_GADGET,
			BUTTON_KIND,
			{POS_RIGHT_JUSTIFY,POS_RIGHT_JUSTIFY,16,1},
			{-2,-2,4,6},
			MSG_CANCEL,
			BUTTONFLAG_CANCEL_BUTTON,
			GAD_ENVIRONMENT_CANCEL,
			0},

		{OD_END}},

	ftp_connection[]={

		// Connection title
		{OD_TEXT,
			TEXTPEN,
			{2,2,0,1},
			{4,0,0,0},
			MSG_FTP_OPTIONS_CONNECTION,
			0,
			0,
			ftp_relative_taglist},

		// Enable Retry
		{OD_GADGET,
			CHECKBOX_KIND,
			{12,3,0,1},
			{4,4,26,6},
			MSG_FTP_OPTIONS_ENABLE_RETRY,
			PLACETEXT_RIGHT,
			GAD_FTP_OPTIONS_ENABLE_RETRY,
			ftp_relative_taglist},

		// Retry Count
		{OD_GADGET,
			STRING_KIND,	
			{12,4,SIZE_MAX_LESS-2,1},
			{30,12,-34,6},
			MSG_FTP_OPTIONS_RETRY_COUNT,
			PLACETEXT_LEFT,
			GAD_FTP_OPTIONS_RETRY_COUNT,
			ftp_timeout_field},

		// Retry Time
		{OD_GADGET,
			STRING_KIND,	
			{12,5,SIZE_MAX_LESS-2,1},
			{30,20,-34,6},
			MSG_FTP_OPTIONS_RETRY_DELAY,
			PLACETEXT_LEFT,
			GAD_FTP_OPTIONS_RETRY_DELAY,
			ftp_timeout_field},

		// Retry on lost connect
		{OD_GADGET,
			CHECKBOX_KIND,
			{12,6,0,1},
			{4,28,26,6},
			MSG_FTP_OPTIONS_ENABLE_RETRY_LOST,
			PLACETEXT_RIGHT,
			GAD_FTP_OPTIONS_ENABLE_RETRY_LOST,
			ftp_relative_taglist},
		{OD_END}};

