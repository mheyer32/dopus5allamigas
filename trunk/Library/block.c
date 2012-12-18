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

#include "dopuslib.h"

// Block window input

typedef struct
{
	struct Window	*bi_Window;
	struct Gadget	*bi_Gadgets;
	LONG		bi_GadgetPos;
	ULONG		bi_IDCMP;
	ULONG		bi_Flags;
} BlockInfo;

#define BIF_BLOCKED	(1<<30)

#define BWIF_KEYS	(1<<0)
#define BWIF_SIZE	(1<<1)
#define BWIF_CLOSE	(1<<2)
#define BWIF_BUSY	(1<<3)
#define BWIF_MENUS	(1<<4)

void BlockWindowInput(struct Window *,BlockInfo *,ULONG);
void FreeWindowInput(BlockInfo *);


// Block window input
void __asm __saveds L_BlockWindowInput(
	register __a0 struct Window *window,
	register __a1 BlockInfo *block,
	register __d0 ULONG flags)
{
	ULONG idcmp=0;
	struct Gadget *gad;

	// Input already blocked?
	if (block->bi_Window==window && block->bi_Flags&BIF_BLOCKED)
		return;

	// Set window pointer
	block->bi_Window=window;

	// Save flags
	block->bi_IDCMP=window->IDCMPFlags;
	block->bi_Flags=flags|BIF_BLOCKED;

	// RMBTrap?
	if (window->Flags&WFLG_RMBTRAP) block->bi_Flags|=BWIF_MENUS;
	else
	{
		// Set RMBTRAP
		window->Flags|=WFLG_RMBTRAP;
		block->bi_Flags&=~BWIF_MENUS;
	}

	// Set our flags
	if (window->IDCMPFlags&IDCMP_REFRESHWINDOW) idcmp|=IDCMP_REFRESHWINDOW;
	if (flags&BWIF_KEYS) idcmp|=IDCMP_RAWKEY;
	if (flags&BWIF_SIZE)
	{
		if (window->IDCMPFlags&IDCMP_NEWSIZE) idcmp|=IDCMP_NEWSIZE;
		if (window->IDCMPFlags&IDCMP_CHANGEWINDOW) idcmp|=IDCMP_CHANGEWINDOW;
	}
	if (flags&BWIF_CLOSE) idcmp|=IDCMP_CLOSEWINDOW;
	if (window->IDCMPFlags&IDCMP_GADGETUP) idcmp|=IDCMP_GADGETUP;
	ModifyIDCMP(window,idcmp);

	// Go through window gadgets
	for (gad=window->FirstGadget;
		gad;
		gad=gad->NextGadget)
	{
		// System gadget?
		if (gad->GadgetType&GTYP_SYSTYPEMASK)
		{
			// Close gadget?
			if ((gad->GadgetType&GTYP_SYSTYPEMASK)==GTYP_CLOSE)
			{
				// Remove close gadget?
				if (!(flags&BWIF_CLOSE)) gad->Flags|=GFLG_DISABLED;
			}

			// Size gadget?
			else
			if ((gad->GadgetType&GTYP_SYSTYPEMASK)==GTYP_SIZING ||
				(gad->GadgetType&GTYP_SYSTYPEMASK)==GTYP_WZOOM)
			{
				// Remove sizing?
				if (!(flags&BWIF_SIZE)) gad->Flags|=GFLG_DISABLED;
			}
		}
	}

	// Set busy pointer?
	if (flags&BWIF_BUSY) L_SetBusyPointer(window);
}


// Free window input
void __asm __saveds L_FreeWindowInput(
	register __a0 BlockInfo *block)
{
	struct Gadget *gad;

	// Input blocked?
	if (!block->bi_Window || !(block->bi_Flags&BIF_BLOCKED))
		return;

	// Restore IDCMP flags
	ModifyIDCMP(block->bi_Window,block->bi_IDCMP);

	// RMBTrap?
	if (!(block->bi_Flags&BWIF_MENUS))
		block->bi_Window->Flags&=~WFLG_RMBTRAP;

	// Go through window gadgets
	for (gad=block->bi_Window->FirstGadget;
		gad;
		gad=gad->NextGadget)
	{
		// System gadget?
		if (gad->GadgetType&GTYP_SYSTYPEMASK)
		{
			// Check gadget is enabled
			gad->Flags&=~GFLG_DISABLED;
		}
	}

	// Clear pointer?
	if (block->bi_Flags&BWIF_BUSY) ClearPointer(block->bi_Window);

	// Clear window pointer and flags
	block->bi_Window=0;
	block->bi_Flags=0;
}
