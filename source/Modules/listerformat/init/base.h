/***************************************************************************

 codesets.library - Amiga shared library for handling different codesets
 Copyright (C) 2001-2005 by Alfonso [alfie] Ranieri <alforan@tin.it>.
 Copyright (C) 2005-2007 by codesets.library Open Source Team

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 codesets.library project: http://sourceforge.net/projects/codesetslib/

 $Id: base.h 220 2009-12-08 15:28:34Z thboeckel $

***************************************************************************/

/***************************************************************************/
#ifndef _BASE_H
#define _BASE_H

#include <dopus/common.h>

struct LibraryHeader
{
  struct Library          libBase;
  UWORD                   initialized;
  struct Library          *sysBase;
  BPTR                    segList;
  struct SignalSemaphore  libSem;
};

/***************************************************************************/

#if defined(__MORPHOS__)
#define __TEXTSEGMENT__ __attribute__((section(".text")))
#else
#define __TEXTSEGMENT__
#endif

/***************************************************************************/


#endif

