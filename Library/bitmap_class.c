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

BOOL __asm bitmap_remap(
	register __a0 Class *cl,
	register __a2 Object *obj,
	register __a1 struct TagItem *attrs);

// Get class base
Class *__asm L_ObtainDTClass(register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;

	// Get data
	data=(struct LibData *)libbase->ml_UserData;

	// Return class pointer
	return data->dt_class;
}


// Datatypes dispatcher
ULONG __asm __saveds dt_dispatch(
	register __a0 Class *cl,
	register __a2 Object *obj,
	register __a1 Msg msg)
{
	ULONG retval;

	// Look at method
	switch (msg->MethodID)
	{
		// New
		case OM_NEW:

KPrintF("OM_NEW - super %s\n",cl->cl_Super->cl_ID);
			// Pass to super class
			if (retval=DoSuperMethodA(cl,obj,msg))
			{
				// Fix things for remapping
				if (!bitmap_remap(cl,(Object *)retval,((struct opSet *)msg)->ops_AttrList))
				{
KPrintF("remap failed\n");
					CoerceMethod(cl,(Object *)retval,OM_DISPOSE);
					return 0;
				}
			}
else KPrintF("foo!\n");
			break;

		// Dispose
		case OM_DISPOSE:
KPrintF("OM_DISPOSE\n");

			// Clear bitmap pointer
			SetDTAttrs(obj,0,0,PDTA_BitMap,0,TAG_DONE);

		// Super class handles everything else
		default:
if (msg->MethodID!=OM_DISPOSE) KPrintF("method %lx\n",msg->MethodID);
			retval=DoSuperMethodA(cl,obj,msg);
			break;
	}

	return retval;
}


// Setup for remapping
BOOL __asm bitmap_remap(
	register __a0 Class *cl,
	register __a2 Object *obj,
	register __a1 struct TagItem *attrs)
{
	struct BitMap *source_bm;
	ULONG *palette=0;
	short depth,ncolors,i,p;
    struct ColorRegister *cmap;
    long *cregs;

	// Get bitmap and palette
	if ((GetDTAttrs(obj,PDTA_SourceBitMap,&source_bm,TAG_DONE))!=1 || !source_bm)
		return 0;
	GetDTAttrs(obj,PDTA_Palette,&palette,TAG_DONE);

	// Get depth
	depth=GetBitMapAttr(source_bm,BMA_DEPTH);
	ncolors=1<<depth;

	// Set number of colours
	SetDTAttrs(obj,0,0,PDTA_NumColors,ncolors,TAG_DONE);

	// Got a palette?
	if (palette)
	{
		// Get palette fields
		GetDTAttrs(obj,
			PDTA_ColorRegisters,&cmap,
			PDTA_CRegs,&cregs,
			TAG_DONE);

		// Go through colours
		for (i=0,p=0;i<ncolors;i++,p+=3)
		{
			// Set master colour table
			cmap->red=(palette[p+0]>>24)&0xff;
			cmap->green=(palette[p+1]>>24)&0xff;
			cmap->blue=(palette[p+2]>>24)&0xff;

			// Set remapping table
			cregs[p+0]=palette[p+0];
			cregs[p+1]=palette[p+1];
			cregs[p+2]=palette[p+2];
		}
	}

	// Set bitmap pointer
	SetDTAttrs(obj,0,0,PDTA_BitMap,source_bm,TAG_DONE);
	return 1;
}


// Patch OpenLibrary()
struct Library *__asm L_WB_OpenLibrary(
	register __a1 char *name,
	register __d0 long version,
	register __a6 struct Library *exec)
{
	struct MyLibrary *libbase;
	struct LibData *data;
	short a;

	// Open library
	if (!(libbase=(struct MyLibrary *)FindName(&((struct ExecBase *)exec)->LibList,"dopus5.library")))
		return 0;

	// Get data pointer
	data=(struct LibData *)libbase->ml_UserData;

	// Get length of name
	a=strlen(name);

	// Long enough?
	if (a>=14)
	{
		// Looking for bitmap datatype?
		if (strcmp(name+a-14,"dopus.datatype")==0)
			name="dopus5.library";
	}

	// Call old routine
	return ((struct Library *__asm (*)
		(register __a1 char *,
		register __d0 long,
		register __a6 struct Library *))
			data->wb_data.old_function[WB_PATCH_OPENLIBRARY])
		(name,version,exec);
}




/*
// Remap an image
Object *__saveds __asm L_RemapBitmap(
	register __a0 struct BitMap *source_bm,
	register __a1 ULONG *palette,
	register __a2 struct Screen *screen,
	register __a6 struct MyLibrary *libbase)
{
	struct LibData *data;
	struct DataType *type;
	struct DataTypeHeader *header;
	Object *obj;

	// Get data
	data=(struct LibData *)libbase->ml_UserData;

	// Got class?
	if (!data->dt_class) return 0;

	// Allocate fake datatype
	if (!(type=AllocVec(sizeof(struct DataType)+sizeof(struct DataTypeHeader),MEMF_CLEAR)))
		return 0;
	header=(struct DataTypeHeader *)(type+1);

	// Fill out fake datatype
	type->dtn_Header=header;
	NewList(&type->dtn_ToolList);

	// Fill out fake header
	header->dth_Name="dopus";
	header->dth_BaseName="dopus";
	header->dth_GroupID=GID_PICTURE;
	header->dth_ID=MAKE_ID('L','O','V','E');

	// Do new method
	obj=
		NewDTObject(0,
			DTA_SourceType,DTST_RAM,
			DTA_GroupID,GID_PICTURE,
			DTA_DataType,type,
			PDTA_SourceBitMap,source_bm,
			PDTA_Palette,palette,
			PDTA_Screen,screen,
			OBP_Precision,PRECISION_IMAGE,
			TAG_END);

	// Free data
	FreeVec(type);

	return obj;
}
*/
