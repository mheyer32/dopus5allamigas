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
#include "newdiskinfo.strings"
#include "modules_lib.h"

#include <libraries/mathffp.h>
#include <clib/mathffp_protos.h>
#include <clib/mathtrans_protos.h>
#include <pragmas/mathffp_pragmas.h>
#include <pragmas/mathtrans_pragmas.h>

extern ConfigWindow diskinfo_win;
extern ObjectDef diskinfo_objects[];

#define AREAVERTEX	190

enum
{
	USEDPEN,
	FREEPEN,
	USEDSHADOWPEN,
	FREESHADOWPEN,
};

typedef struct
{
	NewConfigWindow		new_win;
	struct Window		*window;
	ObjectList		*objlist;

	unsigned short		pens[4];
	short			pen_alloc[4];

	struct InfoData		info;

	char			buffer[1024];
	char			path[256];
	char			decimal_sep;
	char			pad;
	char			title[128];
	char			volume[40];

	struct Library		*maths;
	struct Library		*maths1;

	struct TmpRas		tmpras;
	PLANEPTR		rasbuf;
	struct AreaInfo		areainfo;

	unsigned char		__aligned areabuf[AREAVERTEX*5];
} diskinfo_data;

enum
{
	DISKINFO_LAYOUT,
	GAD_OK,
	GAD_CANCEL,
	GAD_NAME,
	GAD_HANDLER,
	GAD_TYPE,
	GAD_STATE,
	GAD_USED_KEY,
	GAD_FREE_KEY,
	GAD_USED,
	GAD_FREE,
	GAD_CAPACITY,
	GAD_ERRORS,
	GAD_USED_MB,
	GAD_FREE_MB,
	GAD_CAPACITY_MB,
	GAD_GRAPH,
};

extern short diskinfo_colours[4][3];
extern ULONG disktype_lookup[];

BOOL diskinfo_info(diskinfo_data *);
void get_dostype_string(ULONG,char *);
void diskinfo_show_space(diskinfo_data *,unsigned long,short,short);
void diskinfo_show_graph(diskinfo_data *,struct Rectangle *,long,long);

#define MathBase		(data->maths)
#define MathTransBase		(data->maths1)
