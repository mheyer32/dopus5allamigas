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

#define IFFP_IFF_H
#include <iffp/ilbm.h>

#define ID_DPAN MAKE_ID('D','P','A','N')
#define ID_DLTA MAKE_ID('D','L','T','A')

typedef struct {
	UWORD version;
	UWORD nframes;
	unsigned char framespersecond;
	char pad;
	UWORD flags;
} DPAnimChunk;

typedef struct {
	UBYTE operation;
	UBYTE mask;
	UWORD w,h;
	WORD x,y;
	ULONG abstime;
	ULONG reltime;
	UBYTE interleave;
	UBYTE pad0;
	ULONG bits;
	UBYTE pad[16];
} AnimHdr;

#define ANIMF_LONG	1
#define ANIMF_XOR	2

typedef struct
{
	struct MinNode		node;

	AnimHdr			header;			// ANIM header
	unsigned char		*delta;			// DLTA data
} ANIMFrame;

typedef struct
{
	DPAnimChunk		header;			// DeluxePaint anim header

	struct MinList		frames;			// Frame list (for ANIMs)
	ANIMFrame		*current;		// Current frame
	unsigned short		frame_count;		// Number of frames
} ANIMHandle;

typedef struct
{
	APTR			memory;			// Memory handle

	BitMapHeader		header;			// ILBM header
	ULONG			mode_id;		// Mode ID
	ULONG			flags;			// Flags

	union
	{
		struct
		{
			unsigned char	*data;		// BODY data
			unsigned long	size;		// BODY size
		} body;

		struct
		{
			struct BitMap	*bitmap;	// Displayable bitmap
		} bitmap;

		struct
		{
			unsigned short	**planes;	// Image plane data (not chip memory)
		} planes;
	} image;

	ULONG			*palette;		// Image palette

	ANIMHandle		*anim;			// Animation data
} ILBMHandle;

#define ILBMF_GET_BODY		(1<<0)			// Get BODY
#define ILBMF_GET_BITMAP	(1<<1)			// Get Bitmap
#define ILBMF_GET_PLANES	(1<<2)			// Get plane data
#define ILBMF_NO_ANIM		(1<<3)			// Specifically don't want an animation
#define ILBMF_ANIM_ONE_ONLY	(1<<4)			// Get maximum of one animation frame
#define ILBMF_NO_PALETTE	(1<<5)			// Don't bother about palette
#define ILBMF_NO_24BIT		(1<<6)			// Don't support 24 bit

#define ILBMF_GOT_BODY		(1<<0)			// Got BODY
#define ILBMF_GOT_BITMAP	(1<<1)			// Got Bitmap
#define ILBMF_GOT_PLANES	(1<<2)			// Got plane data
#define ILBMF_IS_ANIM		(1<<3)			// Is an animation

#define ILBMF_GOT_HEADER	(1<<4)			// Got header
#define ILBMF_GOT_PALETTE	(1<<5)			// Got palette
#define ILBMF_GOT_MODE		(1<<6)			// Got mode ID
#define ILBMF_IS_ANIM_BRUSH	(1<<7)			// Is an anim brush
#define ILBMF_CHIP_PLANES	(1<<8)			// Planes are in chip


typedef struct {
	unsigned char		*sourceptr;		// Source data
	unsigned char		**destplanes;		// Destination planes
	unsigned short		imagebpr;		// Bytes-per-row in source
	unsigned short		imageheight;		// Image height
	unsigned short		imagedepth;		// Image depth
	unsigned short		destbpr;		// Bytes-per-row in destination
	unsigned short		destheight;		// Destination height
	unsigned short		destdepth;		// Destination depth
	char			masking;		// Image masking
	char			compression;		// Compression type
	unsigned long		offset;			// Offset in destination
} RLEinfo;


ILBMHandle *ReadILBM(char *name,ULONG flags);
void FreeILBM(ILBMHandle *ilbm);
void DecodeILBM(
	char *source,
	unsigned short width,
	unsigned short height,
	unsigned short depth,
	struct BitMap *dest,
	unsigned long flags,
	char comp);
void DecodeRLE(RLEinfo *rle);
ILBMHandle *FakeILBM(
	USHORT *imagedata,
	ULONG *palette,
	short width,
	short height,
	short depth,
	ULONG flags);

#define DIF_MASK	(1<<0)
#define DIF_WRITEPIX	(1<<6)
