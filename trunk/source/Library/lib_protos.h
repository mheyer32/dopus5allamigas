/***************************************************************************

 codesets.library - Amiga shared library for handling different codesets
 Copyright (C) 2001-2005 by Alfonso [alfie] Ranieri <alforan@tin.it>.
 Copyright (C) 2005-2009 by codesets.library Open Source Team

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 codesets.library project: http://sourceforge.net/projects/codesetslib/

 $Id: lib_protos.h 220 2009-12-08 15:28:34Z thboeckel $

***************************************************************************/

#ifndef _LIB_PROTOS_H
#define _LIB_PROTOS_H

#include <SDI/SDI_lib.h>

/* init.c */
ULONG freeBase(struct LibraryHeader* lib);
ULONG initBase(struct LibraryHeader* lib);

/* utils.c */
#if defined(__amigaos4__)
  #define HAVE_ALLOCVECPOOLED 1
  #define HAVE_FREEVECPOOLED  1
  #define HAVE_GETHEAD        1
  #define HAVE_GETTAIL        1
  #define HAVE_GETPRED        1
  #define HAVE_GETSUCC        1
#elif defined(__MORPHOS__)
  #define HAVE_ALLOCVECPOOLED 1
  #define HAVE_FREEVECPOOLED  1
  #define HAVE_GETHEAD        1
  #define HAVE_GETTAIL        1
  #define HAVE_GETPRED        1
  #define HAVE_GETSUCC        1
#elif defined(__AROS__)
  #define HAVE_ALLOCVECPOOLED 1
  #define HAVE_FREEVECPOOLED  1
  #define HAVE_GETHEAD        1
  #define HAVE_GETTAIL        1
  #define HAVE_GETPRED        1
  #define HAVE_GETSUCC        1
#endif

#if defined(HAVE_ALLOCVECPOOLED)
#define allocVecPooled(pool,size) AllocVecPooled(pool,size)
#else
APTR allocVecPooled(APTR pool, ULONG size);
#endif
#if defined(HAVE_FREEVECPOOLED)
#define freeVecPooled(pool,mem)   FreeVecPooled(pool,mem)
#else
void freeVecPooled(APTR pool, APTR mem);
#endif
APTR reallocVecPooled(APTR pool, APTR mem, ULONG oldSize, ULONG newSize);
APTR allocArbitrateVecPooled(ULONG size);
void freeArbitrateVecPooled(APTR mem);
APTR reallocArbitrateVecPooled(APTR mem, ULONG oldSize, ULONG newSize);
#if !defined(HAVE_GETHEAD)
struct Node *GetHead(struct List *list);
#endif
#if !defined(HAVE_GETPRED)
struct Node *GetPred(struct Node *node);
#endif
#if !defined(HAVE_GETSUCC)
struct Node *GetSucc(struct Node *node);
#endif
#if !defined(HAVE_GETTAIL)
struct Node *GetTail(struct List *list);
#endif


#endif /* _LIB_PROTOS_H */
