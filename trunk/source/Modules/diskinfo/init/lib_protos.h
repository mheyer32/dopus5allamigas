
#ifndef _LIB_PROTOS_H
#define _LIB_PROTOS_H

#include <dopus/common.h>
#include <proto/dopus5.h>
#include <proto/module.h>

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

// protos:


LIBPROTO(L_Module_Entry, int, 	REG(a0, char *args),
								REG(a1, struct Screen *screen),
								REG(a2, IPCData *ipc),
								REG(a3, IPCData *main_ipc),
								REG(d0, ULONG mod_id),
								REG(d1, EXT_FUNC(func_callback)));
	
LIBPROTO(L_Module_Identify, ModuleInfo *, REG(d0, int num));


#endif /* _LIB_PROTOS_H */

