/* 
 *
 * ilbm.h:	Definitions for IFFParse ILBM reader.
 *
 * 5/92
 * 39.1 - 7/92 - added setcolors, interface change for loadcmap
 * 39.5 - 11/92 - get rid of BytesPerRow macro which duplicated RowBytes
 *                AND conflicted with a system structure member name.
 *		  Changed "BitsPerRow" macro to "RowBits" to match.
 *                Also unconditionalized extern of GfxBase and IntuitionBase
 */

#ifndef IFFP_ILBM_H
#define IFFP_ILBM_H

#ifndef IFFP_IFF_H
#include "iffp/iff.h"
#endif

#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef GRAPHICS_VIDEOCONTROL_H
#include <graphics/videocontrol.h>
#endif

#ifndef NO_PROTOS
#include <clib/graphics_protos.h>
#include <clib/intuition_protos.h>
#include <clib/alib_protos.h>
#endif

extern struct Library *IntuitionBase;
extern struct Library *GfxBase;

#ifndef NO_SAS_PRAGMAS
#include <pragmas/intuition_pragmas.h>
#include <pragmas/graphics_pragmas.h>
#endif

/*  IFF types we may encounter  */
#define	ID_ILBM		MAKE_ID('I','L','B','M')

/* ILBM Chunk ID's we may encounter
 * (see iffp/iff.h for some other generic chunks)
 */
#define	ID_BMHD		MAKE_ID('B','M','H','D')
#define	ID_CMAP		MAKE_ID('C','M','A','P')
#define	ID_CRNG		MAKE_ID('C','R','N','G')
#define	ID_CCRT		MAKE_ID('C','C','R','T')
#define	ID_GRAB		MAKE_ID('G','R','A','B')
#define	ID_SPRT		MAKE_ID('S','P','R','T')
#define	ID_DEST		MAKE_ID('D','E','S','T')
#define	ID_CAMG		MAKE_ID('C','A','M','G')

/* Use this constant instead of sizeof(ColorRegister).
 * ONLY VALID FOR size of color register AS STORED in ILBM.CMAP
 */
#define sizeofColorRegister  3


typedef WORD Color4;   /* Amiga RAM version of a color-register,
          * with 4 bits each RGB in low 12 bits.*/

typedef struct {
	ULONG	r;
	ULONG	g;
	ULONG	b;
	} Color32;

/* Maximum number of bitplanes storable in BitMap structure */
#define MAXAMDEPTH 8

/* Use ViewPort->ColorMap.Count instead 
#define MAXAMCOLORREG 32
*/

/* Maximum planes this code can save */
#define MAXSAVEDEPTH 24

/* Convert image width to even number of BytesPerRow for ILBM save.
 * Do NOT use this macro to determine the actual number of bytes per row
 * in an Amiga BitMap.  Use BitMap->BytesPerRow for scan-line modulo.
 * Use your screen or viewport width to determine width. Or under
 * V39, use GetBitMapAttr().
 */
#define RowBytes(w)	((((w) + 15) >> 4) << 1)
#define RowBits(w)	((((w) + 15) >> 4) << 4)

/* Flags that should be masked out of old 16-bit CAMG before save or use.
 * Note that 32-bit mode id (non-zero high word) bits should not be twiddled
 */
#define BADFLAGS  (SPRITES|VP_HIDE|GENLOCK_AUDIO|GENLOCK_VIDEO)
#define OLDCAMGMASK  (~BADFLAGS)


/*  Masking techniques  */
#define	mskNone			0
#define	mskHasMask		1
#define	mskHasTransparentColor	2
#define	mskLasso		3

/* We plan to define this value, to mean that the BMHD.transparentColor
 * variable contains a count of alpha channel planes which are stored
 * in the BODY AFTER the image planes.  As always, the count of
 * masking/alpha planes is not included in BMHD.nPlanes.
 * If you have any comments or input, contact Chris Ludwig (CATS US).
 */
#define	mskHasAlpha		4


/*  Compression techniques  */
#define	cmpNone			0
#define	cmpByteRun1		1



/* ---------- BitMapHeader ---------------------------------------------*/
/*  Required Bitmap header (BMHD) structure describes an ILBM */
typedef struct {
	UWORD	w, h;		/* Width, height in pixels */
	WORD	x, y;		/* x, y position for this bitmap  */
	UBYTE	nPlanes;	/* # of planes (not including mask) */
	UBYTE	masking;	/* a masking technique listed above */
	UBYTE	compression;	/* cmpNone or cmpByteRun1 */
	UBYTE	flags;		/* as defined or approved by Commodore */
	UWORD	transparentColor;
	UBYTE	xAspect, yAspect;
	WORD	pageWidth, pageHeight;
} BitMapHeader;

/* BMHD flags */

/* Advisory that 8 significant bits-per-gun have been stored in CMAP
 * i.e. that the CMAP is definitely not 4-bit values shifted left.
 * This bit will disable nibble examination by color loading routine.
 */
#define BMHDB_CMAPOK	7
#define BMHDF_CMAPOK	(1 << BMHDB_CMAPOK)


/* ---------- ColorRegister --------------------------------------------*/
/* A CMAP chunk is a packed array of ColorRegisters (3 bytes each). */
typedef struct {
    UBYTE red, green, blue;   /* MUST be UBYTEs so ">> 4" won't sign extend.*/
    } ColorRegister;

/* ---------- Point2D --------------------------------------------------*/
/* A Point2D is stored in a GRAB chunk. */
typedef struct {
    WORD x, y;      /* coordinates (pixels) */
    } Point2D;

/* ---------- DestMerge ------------------------------------------------*/
/* A DestMerge is stored in a DEST chunk. */
typedef struct {
    UBYTE depth;   /* # bitplanes in the original source */
    UBYTE pad1;      /* UNUSED; for consistency store 0 here */
    UWORD planePick;   /* how to scatter source bitplanes into destination */
    UWORD planeOnOff;   /* default bitplane data for planePick */
    UWORD planeMask;   /* selects which bitplanes to store into */
    } DestMerge;

/* ---------- SpritePrecedence -----------------------------------------*/
/* A SpritePrecedence is stored in a SPRT chunk. */
typedef UWORD SpritePrecedence;

/* ---------- Camg Amiga Viewport Mode Display ID ----------------------*/
/* The CAMG chunk is used to store the Amiga display mode in which
 * an ILBM is meant to be displayed.  This is very important, especially
 * for special display modes such as HAM and HALFBRITE where the
 * pixels are interpreted differently.
 * Under V37 and higher, store a 32-bit Amiga DisplayID (aka. ModeID)
 * in the ULONG ViewModes CAMG variable (from GetVPModeID(viewport)).
 * Pre-V37, instead store the 16-bit viewport->Modes.
 * See the current IFF manual for information on screening for bad CAMG
 * chunks when interpreting a CAMG as a 32-bit DisplayID or 16-bit ViewMode.
 * The chunk's content is declared as a ULONG.
 */
typedef struct {
   ULONG ViewModes;
   } CamgChunk;

/* ---------- CRange cycling chunk -------------------------------------*/
#define RNG_NORATE  36   /* Dpaint uses this rate to mean non-active */
/* A CRange is store in a CRNG chunk. */
typedef struct {
    WORD  pad1;              /* reserved for future use; store 0 here */
    WORD  rate;      /* 60/sec=16384, 30/sec=8192, 1/sec=16384/60=273 */
    WORD  active;     /* bit0 set = active, bit 1 set = reverse */
    UBYTE low, high;   /* lower and upper color registers selected */
    } CRange;

/* ---------- Ccrt (Graphicraft) cycling chunk -------------------------*/
/* A Ccrt is stored in a CCRT chunk. */
typedef struct {
   WORD  direction;  /* 0=don't cycle, 1=forward, -1=backwards */
   UBYTE start;      /* range lower */
   UBYTE end;        /* range upper */
   LONG  seconds;    /* seconds between cycling */
   LONG  microseconds; /* msecs between cycling */
   WORD  pad;        /* future exp - store 0 here */
   } CcrtChunk;

/* If you are writing all of your chunks by hand,
 * you can use these macros for these simple chunks.
 */
#define putbmhd(iff, bmHdr)  \
    PutCk(iff, ID_BMHD, sizeof(BitMapHeader), (BYTE *)bmHdr)
#define putgrab(iff, point2D)  \
    PutCk(iff, ID_GRAB, sizeof(Point2D), (BYTE *)point2D)
#define putdest(iff, destMerge)  \
    PutCk(iff, ID_DEST, sizeof(DestMerge), (BYTE *)destMerge)
#define putsprt(iff, spritePrec)  \
    PutCk(iff, ID_SPRT, sizeof(SpritePrecedence), (BYTE *)spritePrec)
#define putcamg(iff, camg)  \
    PutCk(iff, ID_CAMG, sizeof(CamgChunk),(BYTE *)camg)
#define putcrng(iff, crng)  \
    PutCk(iff, ID_CRNG, sizeof(CRange),(BYTE *)crng)
#define putccrt(iff, ccrt)  \
    PutCk(iff, ID_CCRT, sizeof(CcrtChunk),(BYTE *)ccrt)

#ifndef NO_PROTOS
/* unpacker.c */
BOOL unpackrow(BYTE **pSource, BYTE **pDest, WORD srcBytes0, WORD dstBytes0);

/* packer.c */
LONG packrow(BYTE **pSource, BYTE **pDest, LONG rowSize);

/* ilbmr.c  ILBM reader routines */
LONG loadbody(struct IFFHandle *iff, struct BitMap *bitmap,
		BitMapHeader *bmhd);
LONG loadbody2(struct IFFHandle *iff, struct BitMap *bitmap, 
		BYTE *mask, BitMapHeader *bmhd, 
		BYTE *buffer, ULONG bufsize);
LONG loadcmap(struct ILBMInfo *ilbm);
LONG getcolors(struct ILBMInfo *ilbm);
LONG setcolors(struct ILBMInfo *ilbm, struct ViewPort *vp);
void freecolors(struct ILBMInfo *ilbm);
LONG alloccolortable(struct ILBMInfo *ilbm);
ULONG getcamg(struct ILBMInfo *ilbm);

/* ilbmw.c  ILBM writer routines */
long initbmhd(BitMapHeader *bmhd, struct BitMap *bitmap,
              WORD masking, WORD compression, WORD transparentColor,
              WORD width, WORD height, WORD pageWidth, WORD pageHeight,
              ULONG modeid);
long putcmap(struct IFFHandle *iff,APTR colortable,UWORD ncolors,UWORD bitspergun);
long putbody(struct IFFHandle *iff, struct BitMap *bitmap,
		BYTE *mask, BitMapHeader *bmHdr,
		BYTE *buffer, LONG bufsize);

/* getdisplay.c (used to load a display) */
LONG showilbm(struct ILBMInfo *ilbm, UBYTE *filename);
BOOL unshowilbm(struct ILBMInfo *ilbm);
LONG createdisplay(struct ILBMInfo *);
BOOL deletedisplay(struct ILBMInfo *);
LONG getdisplay(struct ILBMInfo *);
BOOL freedisplay(struct ILBMInfo *);

/* getbitmap.c (used if just loading brush or bitmap) */
LONG createbrush(struct ILBMInfo *);
void deletebrush(struct ILBMInfo *);
LONG getbitmap(struct ILBMInfo *);
void freebitmap(struct ILBMInfo *);

/* screen.c (opens 1.3 or 2.0 screen) */
struct Screen *openidscreen(struct ILBMInfo *,SHORT,SHORT,SHORT,ULONG);
struct Window *opendisplay(struct ILBMInfo *,SHORT,SHORT,SHORT,ULONG);
ULONG  modefallback(ULONG, SHORT, SHORT, SHORT);
void clipit(SHORT wide, SHORT high, struct Rectangle *spos,
	struct Rectangle *dclip, struct Rectangle *txto,
	struct Rectangle *stdo,struct Rectangle *maxo,
	struct Rectangle * uclip);
BOOL closedisplay(struct ILBMInfo *ilbm);

/* loadilbm.c */
LONG loadbrush(struct ILBMInfo *ilbm, UBYTE *filename);
void unloadbrush(struct ILBMInfo *ilbm);

LONG queryilbm(struct ILBMInfo *ilbm, UBYTE *filename);

LONG loadilbm(struct ILBMInfo *ilbm, UBYTE *filename);
void unloadilbm(struct ILBMInfo *ilbm);

/* saveilbm.c */
LONG screensave(struct ILBMInfo *ilbm,
			struct Screen *scr,
			struct Chunk *chunklist1, struct Chunk *chunklist2,
			UBYTE *filename);

LONG saveilbm(struct ILBMInfo *ilbm,
		struct BitMap *bitmap, ULONG modeid,
		WORD width, WORD height, WORD pagewidth, WORD pageheight,
		APTR colortable, UWORD count, UWORD bitspergun,
                WORD masking, WORD transparentColor,
		struct Chunk *chunklist1, struct Chunk *chunklist2,
		UBYTE *filename);


/* screendump.c (print screen or brush) */
int screendump(struct Screen *scr,
     UWORD srcx, UWORD srcy, UWORD srcw, UWORD srch,
     LONG destcols, UWORD special);

/* bmprintc.c (write C source for ILBM) */
void BMPrintCRep(struct BitMap *bm, FILE *fp, UBYTE *name, UBYTE *fmt);  

#endif /* NO_PROTOS */

#endif /* IFFP_ILBM_H */
