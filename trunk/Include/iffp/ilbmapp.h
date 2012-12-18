
/* ilbmapp.h
 * - definition of ILBMInfo structure
 * - inclusion of includes needed by modules and application
 * - application-specific definitions
 *
 * 07/03/91 - added ilbm->stags for screen.c
 * 07/92 - added 32-bit-per-gun variables
 * 09/92 - flags for bestfit and usermodeid
 */
#ifndef ILBMAPP_H
#define ILBMAPP_H

#include "iffp/ilbm.h"

struct ILBMInfo {
	/* general parse.c related */
	struct  ParseInfo ParseInfo;

	/* The following variables are for
	 * programs using the ILBM-related modules.
	 * They may be removed or replaced for
	 * programs parsing other forms.
	 */
	/* ILBM */
	BitMapHeader Bmhd;		/* filled in by load and save ops */
	ULONG	camg;			/* filled in by load and save ops */
	Color4	*colortable;		/* allocated by getcolors */
	ULONG	ctabsize;		/* size of colortable in bytes */
	USHORT	ncolors;		/* number of color registers loaded */
	USHORT  Reserved1;

	/* for getbitmap.c */
	struct BitMap *brbitmap;	/* for loaded brushes only */

	/* for screen.c */
	struct Screen *scr;		/* screen of loaded display   */
	struct Window *win;		/* window of loaded display   */
	struct ViewPort *vp;		/* viewport of loaded display */
	struct RastPort	*srp;		/* screen's rastport */
	struct RastPort *wrp;		/* window's rastport */
	BOOL TBState;			/* state of titlebar hiddenness */

	/* caller preferences */
	struct NewWindow *windef;	/* definition for window */
	UBYTE *stitle;		/* screen title */
	LONG stype;		/* additional screen types */
	WORD ucliptype;		/* overscan display clip type */
	BOOL EHB;		/* default to EHB for 6-plane/NoCAMG */
	BOOL Video;		/* Max Video Display Clip (non-adjustable) */
	BOOL Autoscroll;	/* Enable Autoscroll of screens */
	BOOL Notransb;		/* Borders not transparent to genlock */
	ULONG *stags;		/* Additional screen tags for 2.0 screens  */
	ULONG IFFPFlags;	/* For CBM-designated use by IFFP modules  */
	VOID  *IFFPData;	/* For CBM-designated use by IFFP modules  */
	ULONG UserFlags;	/* For use by applications for any purpose */
	VOID  *UserData;	/* For use by applications for any purpose */
	/* --- New --- */
	WORD  *colorrecord;	/* Passed to LoadRGB32 (ncolors,firstreg,table) */
	Color32 *colortable32;	/* 32-bit-per-gun representation of colors      */
	ULONG crecsize;		/* Bytes allocated including extra WORDs        */

	ULONG usermodeid;
	ULONG Reserved[7];
	/* -------------------------------- */
	/* Application-specific variables may go here - but this may move!!!
	 * If this moves, you will have to recompile all of your modules.
	 * If you want something that won't move, use the UserData above.
 	 */
	};

/* Flags for IFFPFlags */

/* Don't allocate or use a 32-bit-per-gun Color Table under V39 or above */
#define IFFPB_NOCOLOR32	0
#define IFFPF_NOCOLOR32	(1L << IFFPB_NOCOLOR32)
/* Force use of ilbm->usermodeid if mode is available */
#define IFFPB_USERMODE	1
#define IFFPF_USERMODE	(1L << IFFPB_USERMODE)
/* Force use of BestFit() under V39 only */
#define IFFPB_BESTFIT	2
#define IFFPF_BESTFIT	(1L << IFFPB_BESTFIT)
/* Disable centering */
#define IFFPB_NOCENTER	3
#define IFFPF_NOCENTER	(1L << IFFPB_NOCENTER)

/* Disable auto 4->8 bit CMAP conversion on apparently shifted 4-bit guns */
#define IFFPB_CMAPOK	7
#define IFFPF_CMAPOK	(1L << IFFPB_CMAPOK)

/* referenced by modules */

extern struct Library *IFFParseBase;

/* protos for application module(s) */

#endif
