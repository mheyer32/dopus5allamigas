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

// varargs OpenWindowTags
struct Window *__stdargs OpenWindowTags(
	struct NewWindow *nw,
	Tag tag1,...)
{
	return OpenWindowTagList(nw,(struct TagItem *)&tag1);
}

// varargs AllocAslRequestTags
APTR __stdargs AllocAslRequestTags(
	unsigned long type,
	Tag tag1,...)
{
	return AllocAslRequest(type,(struct TagItem *)&tag1);
}

// varargs AslRequestTags
BOOL __stdargs AslRequestTags(
	APTR req,
	Tag tag1,...)
{
	return AslRequest(req,(struct TagItem *)&tag1);
}

// varargs GT_SetGadgetAttrs
void __stdargs L_GT_SetGadgetAttrs(
	struct Gadget *gad,
	struct Window *win,
	Tag tag1,...)
{
	GT_SetGadgetAttrsA(gad,win,0,(struct TagItem *)&tag1);
}

// varargs CreateGadget
struct Gadget *__stdargs CreateGadget(
	ULONG kind,
	struct Gadget *previous,
	struct NewGadget *newgad,
	Tag tag,...)
{
	return CreateGadgetA(kind,previous,newgad,(struct TagItem *)&tag);
}

// varargs SetGadgetAttrs
void __stdargs L_SetGadgetAttrs(
	struct Gadget *gad,
	struct Window *win,
	Tag tag,...)
{
	SetGadgetAttrsA(gad,win,0,(struct TagItem *)&tag);
}

// varargs NewObject
APTR __stdargs NewObject(struct IClass *class,UBYTE *classid,Tag tag,...)
{
	return NewObjectA(class,classid,(struct TagItem *)&tag);
}



// varargs dt stuff
ULONG __stdargs GetDTAttrs(Object *o,ULONG data,...)
{
    return GetDTAttrsA(o,(struct TagItem *)&data);
}

ULONG __stdargs SetDTAttrs(Object *o,struct Window *w,struct Requester *r,ULONG data,...)
{
    return SetDTAttrsA(o,0,0,(struct TagItem *)&data);
}

Object *__stdargs NewDTObject(APTR name,Tag tag1,...)
{
	return NewDTObjectA(name,(struct TagItem *)&tag1);
}
