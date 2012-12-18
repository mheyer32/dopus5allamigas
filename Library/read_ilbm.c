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
#include <cybergraphics/cybergraphics.h>
#include <proto/cybergraphics.h>

// Read an ILBM image
ILBMHandle *__asm __saveds L_ReadILBM(
	register __a0 char *name,
	register __d0 ULONG flags)
{
	struct _IFFHandle *iff;
	ILBMHandle *ilbm;
	unsigned char *body=0;
	unsigned long body_size=0;
	ULONG chunk,chunksize;
	BOOL fail=0;

	// Allocate new ILBM handle
	if (!(ilbm=AllocVec(sizeof(ILBMHandle),MEMF_CLEAR)) ||
		!(ilbm->memory=L_NewMemHandle(1024,sizeof(ANIMHandle)+sizeof(ANIMFrame),MEMF_CLEAR)))
	{
		FreeVec(ilbm);
		return 0;
	}

	// Try to open file
	if (!(iff=L_IFFOpen(name,IFF_READ,ID_ILBM)))
	{
		// Not ILBM; is it ANIM?
		if (iff=L_IFFOpen(name,IFF_READ,ID_ANIM))
		{
			// Allocate anim data
			if (!(flags&ILBMF_NO_ANIM))
			{
				if (ilbm->anim=L_AllocMemH(ilbm->memory,sizeof(ANIMHandle)))
					NewList((struct List *)&ilbm->anim->frames);
				ilbm->flags|=ILBMF_IS_ANIM;
			}
		}

		// Not ILBM or ANIM
		else
		{
			L_FreeILBM(ilbm);
			return 0;
		}
	}

	// Parse IFF file
	while (!fail && (chunk=L_IFFNextChunk(iff,0)))
	{
		// Get chunk size
		chunksize=L_IFFChunkSize(iff);

		// Look at chunk type
		switch (chunk)
		{
			// Bitmap header
			case ID_BMHD:

				// Read header
				if ((L_IFFReadChunkBytes(iff,&ilbm->header,sizeof(BitMapHeader)))==
					sizeof(BitMapHeader))
				{
					ilbm->flags|=ILBMF_GOT_HEADER;
					if ((flags&ILBMF_NO_24BIT) &&
						ilbm->header.nPlanes>8)
					{
						ilbm->flags&=~ILBMF_GOT_HEADER;
						fail=1;
					}
				}
				break;


			// Mode ID
			case ID_CAMG:

				// Read mode
				L_IFFReadChunkBytes(iff,&ilbm->mode_id,sizeof(ULONG));
				ilbm->flags|=ILBMF_GOT_MODE;
				break;


			// DPAnimChunk
			case ID_DPAN:

				// Do we have animation data?
				if (ilbm->flags&ILBMF_IS_ANIM)
				{
					// Read header
					if ((L_IFFReadChunkBytes(iff,&ilbm->anim->header,sizeof(DPAnimChunk))!=
						sizeof(DPAnimChunk))) ilbm->flags&=~ILBMF_IS_ANIM;
				}
				break;


			// Anim frame
			case ID_ANHD:

				// Do we have animation data?
				if (ilbm->flags&ILBMF_IS_ANIM)
				{
					// If we haven't had a body yet, ignore this chunk (DPaintV animbrush)
					if (!(ilbm->flags&ILBMF_GOT_BODY))
						break;

					// See if we're allowed this one
					if (!(flags&ILBMF_ANIM_ONE_ONLY) ||
						ilbm->anim->frame_count<1)
					{
						// Create a new frame
						if (ilbm->anim->current=L_AllocMemH(ilbm->memory,sizeof(ANIMFrame)))
						{
							// Read frame header
							L_IFFReadChunkBytes(iff,&ilbm->anim->current->header,sizeof(AnimHdr));

							// Add to list
							AddTail(
								(struct List *)&ilbm->anim->frames,
								(struct Node *)ilbm->anim->current);
						}
					}
				}
				break;


			// Delta
			case ID_DLTA:

				// Do we have animation data and a valid frame?
				if (ilbm->flags&ILBMF_IS_ANIM && ilbm->anim->current)
				{
					// Allocate delta memory
					if (ilbm->anim->current->delta=L_AllocMemH(ilbm->memory,chunksize))
					{
						// Read delta
						L_IFFReadChunkBytes(iff,ilbm->anim->current->delta,chunksize);

						// Increment frame count
						++ilbm->anim->frame_count;
					}

					// Abandon frame
					else
					{
						Remove((struct Node *)ilbm->anim->current);
						L_FreeMemH(ilbm->anim->current);
					}

					// Clear current frame pointer
					ilbm->anim->current=0;
				}
				break;


			// Body
			case ID_BODY:

				// Allocate body data
				if (body=L_AllocMemH(ilbm->memory,chunksize))
				{
					// Read body
					if ((body_size=L_IFFReadChunkBytes(iff,body,chunksize))==chunksize)
						ilbm->flags|=ILBMF_GOT_BODY;
				}
				break;


			// Palette
			case ID_CMAP:

				// Do we want a palette?
				if (!(flags&ILBMF_NO_PALETTE))
				{
					// Allocate palette data
					if (ilbm->palette=L_AllocMemH(ilbm->memory,(chunksize+2)*sizeof(ULONG)))
					{
						char *temp;

						// Get temporary buffer
						if (temp=L_AllocMemH(ilbm->memory,chunksize))
						{
							short entry;
							unsigned char *ptr;

							// Read palette
							L_IFFReadChunkBytes(iff,temp,chunksize);

							// Initialise palette
							ilbm->palette[0]=(chunksize/3)<<16;

							// Fill out palette
							ptr=(unsigned char *)temp;
							for (entry=1;entry<=chunksize;entry++,ptr++)
							{
								unsigned char val;

								// 8 bit palette?
								if (ilbm->header.flags&BMHDF_CMAPOK ||
									ilbm->header.nPlanes>6)
								{
									val=*ptr;
								}

								// 4 bit left justified
								else
								{
									val=((*ptr)>>4)&0xf;
									val|=(val<<4);
								}

								// Convert to 32 bit left justified
								ilbm->palette[entry]=
									(((ULONG)val)<<24)|
									(((ULONG)val)<<16)|
									(((ULONG)val)<<8)|
									(((ULONG)val));
							}

							// Free temporary buffer
							L_FreeMemH(temp);
							ilbm->flags|=ILBMF_GOT_PALETTE;
						}

						// No palette
						else
						{
							L_FreeMemH(ilbm->palette);
							ilbm->palette=0;
						}
					}
				}
				break;
		}
	}


	// Finished parsing file
	L_IFFClose(iff);

	// See what we've got
	if (!(ilbm->flags&ILBMF_GOT_HEADER) ||
		!(ilbm->flags&ILBMF_GOT_BODY))
	{
		// Without a header or a body we must fail
		L_FreeILBM(ilbm);
		return 0;
	}


	// See what the customer wants
	if (flags&ILBMF_GET_BODY)
	{
		// Only wants a body
		ilbm->image.body.data=body;
		ilbm->image.body.size=body_size;
	}

	// Don't want body
	else
	{
		// Clear body flag
		ilbm->flags&=~ILBMF_GOT_BODY;

		// Wants bitmap
		if (flags&ILBMF_GET_BITMAP)
		{
			// Create a bitmap
			if (ilbm->image.bitmap.bitmap=L_NewBitMap(
				ilbm->header.w,
				ilbm->header.h,
				ilbm->header.nPlanes,
				BMF_CLEAR|BMF_DISPLAYABLE,0))
			{
				// Set flag to say we got bitmap
				ilbm->flags|=ILBMF_GOT_BITMAP;

				// Decode body
				L_DecodeILBM(
					body,
					ilbm->header.w,
					ilbm->header.h,
					ilbm->header.nPlanes,
					ilbm->image.bitmap.bitmap,
					(ilbm->header.masking==1)?DIF_MASK:0,
					ilbm->header.compression);
			}
		}

		// Wants planes
		else
		if (flags&ILBMF_GET_PLANES)
		{
			// Allocate space for plane pointers
			if (ilbm->image.planes.planes=L_AllocMemH(ilbm->memory,ilbm->header.nPlanes*sizeof(unsigned short *)))
			{
				short plane;
				struct BitMap fake;
				unsigned long planesize;

				// Initialise fake bitmap
				InitBitMap(&fake,ilbm->header.nPlanes,ilbm->header.w,ilbm->header.h);
				planesize=RASSIZE(ilbm->header.w,ilbm->header.h);

				// Small enough for chip?
				if (planesize*ilbm->header.nPlanes<=16384) ilbm->flags|=ILBMF_CHIP_PLANES;

				// Allocate planes
				for (plane=0;plane<ilbm->header.nPlanes;plane++)
				{
					// Allocate chip memory if we're allowed to
					if (!(ilbm->flags&ILBMF_CHIP_PLANES) ||
						!(ilbm->image.planes.planes[plane]=AllocVec(planesize,MEMF_CHIP)))
					{
						// Allocate from normal memory
						if (ilbm->image.planes.planes[plane]=AllocVec(planesize,0))
						{
							// Did we end up with chip memory anyway?
							if (plane==0 && (TypeOfMem(ilbm->image.planes.planes[plane])&MEMF_CHIP))
							{
								// Allocate all chip memory from now on
								ilbm->flags|=ILBMF_CHIP_PLANES;
							}

							// Otherwise, clear chip flag
							else ilbm->flags&=~ILBMF_CHIP_PLANES;
						}
						else break;
					}
				}

				// Did we fail to get all planes?
				if (plane<ilbm->header.nPlanes)
				{
					// Free what we did get
					for (;plane>=0;plane--)
					{
						FreeVec(ilbm->image.planes.planes[plane]);
					}

					// Free plane pointers
					L_FreeMemH(ilbm->image.planes.planes);
					ilbm->image.planes.planes=0;
				}

				// Successful
				else
				{
					// Set plane pointers in fake bitmap
					for (plane=0;plane<ilbm->header.nPlanes;plane++)
						fake.Planes[plane]=(PLANEPTR)ilbm->image.planes.planes[plane];

					// Decode body
					L_DecodeILBM(
						body,
						ilbm->header.w,
						ilbm->header.h,
						ilbm->header.nPlanes,
						&fake,
						(ilbm->header.masking==1)?DIF_MASK:0,
						ilbm->header.compression);

					// Set flag to say we've got planes
					ilbm->flags|=ILBMF_GOT_PLANES;
				}
			}
		}
	}


	// Do we need to free the body?
	if (!(flags&ILBMF_GET_BODY))
	{
		L_FreeMemH(body);
	}


	// Are we an animation?
	if (ilbm->flags&ILBMF_IS_ANIM)
	{
		// Initialise current frame
		ilbm->anim->current=(ANIMFrame *)ilbm->anim->frames.mlh_Head;

		// Are we an anim brush?
		if (ilbm->anim->current->header.interleave==1)
			ilbm->flags|=ILBMF_IS_ANIM_BRUSH;
	}


	// Return ILBM handle
	return ilbm;
}


// Free an ILBM image
void __asm __saveds L_FreeILBM(register __a0 ILBMHandle *ilbm)
{
	// Valid?
	if (ilbm)
	{
		// Do we have a bitmap?
		if (ilbm->flags&ILBMF_GOT_BITMAP)
		{
			// Free bitmap
			L_DisposeBitMap(ilbm->image.bitmap.bitmap);
		}

		// Or do we got planes?
		else
		if (ilbm->flags&ILBMF_GOT_PLANES)
		{
			short plane;

			// Free planes
			for (plane=0;plane<ilbm->header.nPlanes;plane++)
				FreeVec(ilbm->image.planes.planes[plane]);
		}

		// Free handle memory
		L_FreeMemHandle(ilbm->memory);
		FreeVec(ilbm);
	}
}


// Decode an IFF body
void __asm __saveds L_DecodeILBM(
	register __a0 char *source,
	register __d0 unsigned short width,
	register __d1 unsigned short height,
	register __d2 unsigned short planes,
	register __a1 struct BitMap *dest,
	register __d3 unsigned long flags,
	register __d4 char comp)
{
	register short bpr;
	unsigned short plane,row;
	unsigned short dest_rows,dest_depth,bufsize=0;
	unsigned long bmoffset=0;
	struct RastPort rp,temprp;
	struct BitMap *tempbm=0;
	UBYTE *buffer=0;

	// Check valid source and destination
	if (!source || !dest) return;

	// Masking?
	if (flags&DIF_MASK) ++planes;

	// Get bytes per row for source
	bpr=((width+15)>>4)<<1;

	// Under 39?
	if (GfxBase->LibNode.lib_Version>=39)
	{
		// Get bitmap info
		dest_rows=GetBitMapAttr(dest,BMA_HEIGHT);
		dest_depth=GetBitMapAttr(dest,BMA_DEPTH);
	}

	// Normal
	else
	{
		dest_rows=dest->Rows;
		dest_depth=dest->Depth;
	}

	// Check height doesn't exceed destination bitmap
	if (height>dest_rows) height=dest_rows;

	// Allocate temporary bitmap if WritePixel needed
	if (flags&DIF_WRITEPIX)
	{
		// Cybergraphics, 24bit?
		if (CyberGfxBase && planes==24)
			buffer=AllocVec((bufsize=bpr*24),0);

		// Otherwise
		else
		if ((CyberGfxBase || (tempbm=L_NewBitMap(width,1,dest_depth,0,0))))
			buffer=AllocVec((bufsize=bpr<<3),0);

		// Got buffer?
		if (buffer)
		{
			// Set up dummy rastport
			InitRastPort(&rp);
			rp.BitMap=dest;

			// Set up temporary rastport
			if (tempbm)
			{
				InitRastPort(&temprp);
				temprp.BitMap=tempbm;
			}
		}
		else flags&=~DIF_WRITEPIX;
	}

	// Run-length encoding?
	if (comp==1)
	{
		// Go through image rows
		for (row=0;row<height;row++)
		{
			// Write pixel?
			if (flags&DIF_WRITEPIX)
			{
				short col;

				// Clear buffer
				for (col=0;col<bufsize;col++)
					buffer[col]=0;
			}

			// Go through planes
			for (plane=0;plane<planes;plane++)
			{
				// Check this plane is ok to decode into
				if (plane<dest_depth && (flags&DIF_WRITEPIX || dest->Planes[plane]))
				{
					register char *ptr;
					register short copy,col,count;
					short pnum=0;

					// Get destination pointer
					if (flags&DIF_WRITEPIX)
					{
						// 24 bit?
						if (planes==24)
						{
							// Get start
							if (plane<8)
							{
								ptr=buffer;
								pnum=plane;
							}
							else
							if (plane<16)
							{
								ptr=buffer+1;
								pnum=plane-8;
							}
							else
							{
								ptr=buffer+2;
								pnum=plane-16;
							}
						}
						else ptr=buffer;
					}
					else ptr=(char *)(dest->Planes[plane]+bmoffset);

					// Go through columns
					for (col=0;col<bpr;)
					{
						// >=0 bytes copied
						if ((count=*source++)>=0)
						{
							copy=count+1;
							col+=copy;
							if (flags&DIF_WRITEPIX)
							{
								while (copy--)
								{
									register unsigned char val;
									register short a;

									// Get value
									val=*source++;

									// 24 bit?
									if (planes==24)
									{
										// 8 pixels in value
										for (a=0;a<8;a++,ptr+=3)
											if (val&(1<<(7-a))) *ptr|=1<<pnum;
									}

									// 8 pixels in value
									else
									for (a=0;a<8;a++,ptr++)
										if (val&(1<<(7-a))) *ptr|=1<<plane;
								}
							}
							else
							while (copy--) *ptr++=*source++;
						}

						// -128<0 byte run
						else
						if (count!=-128)
						{
							copy=1-count;
							col+=copy;
							if (flags&DIF_WRITEPIX)
							{
								register unsigned char val;

								// Get value
								val=*source;

								while (copy--)
								{
									register short a;

									// 24 bit?
									if (planes==24)
									{
										// 8 pixels in value
										for (a=0;a<8;a++,ptr+=3)
											if (val&(1<<(7-a))) *ptr|=1<<pnum;
									}

									// 8 pixels in value
									else
									for (a=0;a<8;a++,++ptr)
										if (val&(1<<(7-a))) *ptr|=1<<plane;
								}
							}
							else
							while (copy--) *ptr++=*source;
							++source;
						}
					}
				}

				// Destination invalid
				else
				{
					register short col,copy,count;

					for (col=0;col<bpr;)
					{
						if ((count=*source++)>=0)
						{
							copy=count+1;
							col+=copy;
							source+=copy;
						}
						else
						if (count!=-128)
						{
							copy=1-count;
							col+=copy;
							++source;
						}
					}
				}
			}

			// Writepixel?
			if (flags&DIF_WRITEPIX)
			{
				// CyberGfx?
				if (CyberGfxBase)
				{
					// Write pixel array
					WritePixelArray(buffer,0,0,width,&rp,0,row,width,1,(planes==24)?RECTFMT_RGB:RECTFMT_LUT8);
				}

				// Write to bitmap
				else WritePixelLine8(&rp,0,row,width,buffer,&temprp);
			}

			// Increment bitmap offset
			else bmoffset+=dest->BytesPerRow;
		}
	}

	// No encoding
	else
	if (comp==0)
	{
		for (row=0;row<height;row++)
		{
			for (plane=0;plane<planes;plane++)
			{
				if (plane<dest_depth)
					CopyMem(source,(char *)dest->Planes[plane]+bmoffset,bpr);
				source+=bpr;
			}
			bmoffset+=dest->BytesPerRow;
		}
	}

	// Free buffers, etc
	if (tempbm) L_DisposeBitMap(tempbm);
	if (buffer) FreeVec(buffer);
}


/*
// Decode an IFF body
void __asm __saveds L_DecodeILBM(
	register __a0 unsigned char *source,
	register __d0 unsigned short width,
	register __d1 unsigned short height,
	register __d2 unsigned short depth,
	register __a1 struct BitMap *dest,
	register __d3 char mask,
	register __d4 char comp)
{
	RLEinfo picinfo;

	// Check valid source and destination
	if (!source || !dest) return;

	// Fill out RLEinfo structure
	picinfo.sourceptr=source;
	picinfo.destplanes=dest->Planes;
	picinfo.imagebpr=((width+15)/16)*2;
	picinfo.imageheight=height;
	picinfo.imagedepth=depth;
	picinfo.destbpr=dest->BytesPerRow;
	picinfo.destheight=dest->Rows;
	picinfo.destdepth=dest->Depth;
	picinfo.masking=mask;
	picinfo.compression=comp;
	picinfo.offset=0;

	// Decode it
	L_DecodeRLE(&picinfo);
}
*/


// Do RLE decoding
void __asm __saveds L_DecodeRLE(register __a0 RLEinfo *rle)
{
	register char *source;
	register short bpr;
	unsigned short plane,row,planes,depth,height,destbpr;
	unsigned long bmoffset;
	PLANEPTR *planeptrs;

	planes=rle->imagedepth;
	if (rle->masking==1) ++planes;
	source=rle->sourceptr;
	bpr=rle->imagebpr;
	destbpr=rle->destbpr;

	// Get height to do
	if (rle->imageheight>rle->destheight) height=rle->destheight;
	else height=rle->imageheight;

	// Get depth to do
	depth=rle->destdepth;

	// Get plane pointers
	planeptrs=rle->destplanes;

	// Look at compression type
	switch (rle->compression)
	{
		// Run-length encoding
		case 1:

			// Start offset in this bitmap
			bmoffset=rle->offset;

			// Go through image rows
			for (row=0;row<height;row++)
			{
				// Go through planes
				for (plane=0;plane<planes;plane++)
				{
					// Check this plane is ok to decode into
					if (plane<depth && planeptrs[plane])
					{
						register char *dest;
						register short copy,col,count;

						// Get destination pointer
						dest=(char *)(planeptrs[plane]+bmoffset);

						// Go through columns
						for (col=0;col<bpr;)
						{
							// >=0 bytes copied
							if ((count=*source++)>=0)
							{
								copy=count+1;
								col+=copy;
								while (copy--) *dest++=*source++;
							}

							// -128<0 byte run
							else
							if (count!=-128)
							{
								copy=1-count;
								col+=copy;
								while (copy--) *dest++=*source;
								++source;
							}
						}
					}

					// Destination invalid
					else
					{
						register short col,copy,count;

						for (col=0;col<bpr;)
						{
							if ((count=*source++)>=0)
							{
								copy=count+1;
								col+=copy;
								source+=copy;
							}
							else
							if (count!=-128)
							{
								copy=1-count;
								col+=copy;
								++source;
							}
						}
					}
				}
				bmoffset+=destbpr;
			}
			break;

		// No encoding
		case 0:
			bmoffset=rle->offset;
			for (row=0;row<rle->imageheight;row++)
			{
				if (row>=height) break;
				for (plane=0;plane<planes;plane++)
				{
					if (plane<depth)
						CopyMem(source,(char *)planeptrs[plane]+bmoffset,bpr);
					source+=bpr;
				}
				bmoffset+=destbpr;
			}
			break;
	}
}


// Fake an ILBM structure from data
ILBMHandle *__asm __saveds L_FakeILBM(
	register __a0 USHORT *imagedata,
	register __a1 ULONG *palette,
	register __d0 short width,
	register __d1 short height,
	register __d2 short depth,
	register __d3 ULONG flags)
{
	ILBMHandle *ilbm;

	// Allocate new ILBM handle
	if (!(ilbm=AllocVec(sizeof(ILBMHandle),MEMF_CLEAR)) ||
		!(ilbm->memory=L_NewMemHandle(1024,sizeof(ANIMHandle)+sizeof(ANIMFrame),MEMF_CLEAR)))
	{
		FreeVec(ilbm);
		return 0;
	}

	// Bitmap header
	ilbm->header.w=width;
	ilbm->header.h=height;
	ilbm->header.nPlanes=depth;
	ilbm->flags|=ILBMF_GOT_HEADER;

	// Do we want a palette?
	if (!(flags&ILBMF_NO_PALETTE))
	{
		// Palette?
		if (palette)
		{
			long chunksize;

			// Get size
			chunksize=(palette[0]>>16)*3;

			// Allocate palette data
			if (ilbm->palette=L_AllocMemH(ilbm->memory,(chunksize+2)*sizeof(ULONG)))
			{
				// Copy palette
				CopyMem((char *)palette,(char *)ilbm->palette,(chunksize+2)*sizeof(ULONG));
				ilbm->flags|=ILBMF_GOT_PALETTE;
			}
		}
	}

	// Allocate space for plane pointers
	if (ilbm->image.planes.planes=L_AllocMemH(ilbm->memory,depth*sizeof(unsigned short *)))
	{
		short plane;
		unsigned long planesize;

		// Get size of bitplane
		planesize=RASSIZE(width,height);

		// Set flag for chip memory
		ilbm->flags|=ILBMF_CHIP_PLANES;

		// Allocate planes
		for (plane=0;plane<depth;plane++)
		{
			// Allocate plane
			if (!(ilbm->image.planes.planes[plane]=AllocVec(planesize,MEMF_CHIP)))
				break;
		}

		// Did we fail to get all planes?
		if (plane<depth)
		{
			// Free what we did get
			for (;plane>=0;plane--)
			{
				FreeVec(ilbm->image.planes.planes[plane]);
			}

			// Free plane pointers
			L_FreeMemH(ilbm->image.planes.planes);
			ilbm->image.planes.planes=0;
		}

		// Successful
		else
		{
			// Fill in bitmap
			for (plane=0;plane<ilbm->header.nPlanes;plane++)
			{
				// Copy to bitplane
				CopyMem(
					((char *)imagedata)+(planesize*plane),
					(char *)ilbm->image.planes.planes[plane],
					planesize);
			}

			// Set flag to say we've got planes
			ilbm->flags|=ILBMF_GOT_PLANES;
		}
	}

	// Return ILBM handle
	return ilbm;
}
