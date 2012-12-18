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


//#define BACKFILL

struct backfill_hook
{
	struct Hook		hook;
	struct Library		*GfxBase;
	USHORT			dither[2];
	struct RastPort		rp;
	short			shinepen;
	short			shadowpen;
};

#ifdef BACKFILL
void __asm _req_backfill(register __a0 struct backfill_hook *hook,register __a1 struct BackFillInfo *info,register __a2 struct RastPort *rp);
#else
void _req_backfill(struct Window *window);
#endif

void _layout_add_gad_image(APTR *memory,struct Gadget *,struct Image *);
void __stdargs L_GT_SetGadgetAttrs(struct Gadget *gad,struct Window *win,ULONG tag1,...);
void __stdargs L_SetGadgetAttrs(struct Gadget *gad,struct Window *win,Tag tag,...);

APTR alloc_object_memory(APTR *memory,long size);

void layout_resize(struct Window *window);

#include "boopsi.h"
