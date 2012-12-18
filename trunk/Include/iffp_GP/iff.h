/* 
 *
 * iff.h:	General Definitions for IFFParse modules
 *
 * 10/20/91
 * 39.5 - 11/92 - allow a conditional USE_AMIGA_IO define to cause
 *   inclusion of Amiga-specific prototypes rather than standard C
 *   stdlib.h and stdio.h (you must change makefile also - see notes below)
 *   Added include of exec/libraries.h
 */

#ifndef IFFP_IFF_H
#define IFFP_IFF_H

#include "iffp/compiler.h"

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_MEMORY_H
#include <exec/memory.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#include <string.h>

/* If you define this, change your link to use Amiga startup code
 * like astartup.obj, and to link with library amiga.lib first
 */
#ifdef USE_AMIGA_IO
#include <clib/alib_stdio_protos.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef MYDEBUG_H
#include "iffp/debug.h"
#endif

#ifndef NO_PROTOS
#include <clib/exec_protos.h>
#include <clib/utility_protos.h>
#include <clib/iffparse_protos.h>
#endif
#ifndef NO_SAS_PRAGMAS
extern struct Library *SysBase;
#include <pragmas/exec_pragmas.h>
extern struct Library *IFFParseBase;
#include <pragmas/iffparse_pragmas.h>
extern struct Library *DOSBase;
#include <pragmas/dos_pragmas.h>
#endif

#ifndef MAX
#define	MAX(a,b)	((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define	MIN(a,b)	((a) < (b) ? (a) : (b))
#endif
#ifndef ABS
#define	ABS(x)		((x) < 0 ? -(x) : (x))
#endif

/* Locale stuff */
#ifndef LOCALESTR_IFFP_H
#define CATCOMP_NUMBERS
#include "iffp/iffpstrings.h"
#endif

#ifndef CATCOMP_ARRAY
struct CatCompArrayType
{
    LONG   cca_ID;
    STRPTR cca_Str;
};
extern struct  CatCompArrayType CatCompArray[];
#endif

#define SI(i)  GetString(i)


#define CkErr(expression)  {if (!error) error = (expression);}
#define ChunkMoreBytes(cn)	(cn->cn_Size - cn->cn_Scan)
#define IS_ODD(a)		(a & 1)

#define IFF_OKAY	0L
#define	CLIENT_ERROR	1L
#define NOFILE          5L

#define message printf

/* Generic Chunk ID's we may encounter */
#define	ID_ANNO		MAKE_ID('A','N','N','O')
#define	ID_AUTH		MAKE_ID('A','U','T','H')
#define	ID_CHRS		MAKE_ID('C','H','R','S')
#define	ID_Copyright	MAKE_ID('(','c',')',' ')
#define	ID_CSET		MAKE_ID('C','S','E','T')
#define	ID_FVER		MAKE_ID('F','V','E','R')
#define	ID_NAME		MAKE_ID('N','A','M','E')
#define ID_TEXT		MAKE_ID('T','E','X','T')
#define ID_BODY		MAKE_ID('B','O','D','Y')


/* Used to keep track of allocated IFFHandle, and whether file is
 * clipboard or not, filename, copied chunks, etc.
 * This structure is included in the beginning of every
 * form-specific info structure used by the example modules.
 */
struct ParseInfo {
	/* general parse.c related */
	struct  IFFHandle *iff;		/* to be alloc'd with AllocIFF */
	UBYTE	*filename;		/* current filename of this ui */
	LONG	*propchks;		/* properties to get */
	LONG	*collectchks;		/* properties to collect */
	LONG	*stopchks;		/* stop on these (like BODY) */
	BOOL    opened;			/* this iff has been opened */
	BOOL	clipboard;		/* file is clipboard */
	BOOL	hunt;			/* we are parsing a complex file */
	BOOL	Reserved1;		/* must be zero for now */		

	/* for copychunks.c - for read/modify/write programs
	 * and programs that need to keep parsed chunk info
	 * around after closing file.
	 * Deallocated by freechunklist();
	 */
	struct Chunk *copiedchunks;

	/* application may hang its own list of new chunks here
	 * just to keep it with the frame.
	 */
	struct Chunk *newchunks;

	ULONG	Reserved[8];
	};


/*
 * Used by some modules to save or pass a singly linked list of chunks
 */
struct Chunk {
	struct  Chunk *ch_Next;
	long	ch_Type;
	long	ch_ID;
        long    ch_Size;
        void    *ch_Data;
};


#ifndef NO_PROTOS
/* parse.c */
LONG openifile(struct ParseInfo *pi,UBYTE *filename, ULONG iffopenmode);
void closeifile(struct ParseInfo *pi);
LONG parseifile(struct ParseInfo *pi,LONG groupid,LONG grouptype,
	LONG *propchks,LONG *collectchks,LONG *stopchks);
LONG getcontext(struct IFFHandle *iff);
LONG nextcontext(struct IFFHandle *iff);
LONG currentchunkis(struct IFFHandle *iff, LONG type, LONG id);
LONG contextis(struct IFFHandle *iff, LONG type, LONG id);
UBYTE *findpropdata(struct IFFHandle *iff, LONG type, LONG id);
void initiffasstdio(struct IFFHandle *iff);
LONG chkcnt(LONG *taggedarray);
long PutCk(struct IFFHandle *iff, long id, long size, void *data);

/* iffpstrings.c */
UBYTE *openScreenErr(ULONG errorcode);
UBYTE *IFFerr(LONG error);
void OpenStrings(void);
void CloseStrings(void);
UBYTE *GetString(ULONG id);

/* copychunks.c */
struct Chunk *copychunks(struct IFFHandle *iff,
                 LONG *propchks, LONG *collectchks, ULONG memtype);
void freechunklist(struct Chunk *first);
struct Chunk *findchunk(struct Chunk *first, long type, long id);
long writechunklist(struct IFFHandle *iff, struct Chunk *first);
#endif /* NO_PROTOS */

#endif /* IFFP_IFF_H */
