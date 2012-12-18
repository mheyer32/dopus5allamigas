/*-----------------------------------------------------------------------*
 * FTXT.H  Definitions for formatted text
 *
 * This version for the Commodore-Amiga computer.
 *----------------------------------------------------------------------*/
#ifndef FTXT_H
#define FTXT_H

#ifndef COMPILER_H
#include "iffp/compiler.h"
#endif

#include "iffp/iff.h"


#define ID_FTXT      MAKE_ID('F','T','X','T')
#define ID_CHRS      MAKE_ID('C','H','R','S')
#define ID_FONS      MAKE_ID('F','O','N','S')

/* defined in iffp/iff.h
#define ID_NAME      MAKE_ID('N', 'A', 'M', 'E')
#define ID_Copyright MAKE_ID('(', 'c', ')', ' ')
#define ID_AUTH      MAKE_ID('A', 'U', 'T', 'H')
#define ID_ANNO      MAKE_ID('A', 'N', 'N', 'O')
#define ID_BODY      MAKE_ID('B', 'O', 'D', 'Y')
*/

/* ---------- FontSpecifier (FONS) ---------------------------------------------*/

/* Note - for convenience, this structure is defined with a name array
 * of Amiga MAXFONTPATH size.  The size of actual FONS chunks will
 * depend oon the length of the name stored in the chunk
 */

typedef struct {

	UBYTE id;       /* 0 through 9 is a font id number referenced by an SGR
			control sequence selective parameter of 10 through 19.
			Other values are reserved for future standardization.   */

	UBYTE pad1;     	/* reserved for future use; store 0 here        */

	UBYTE proportional;     /* proportional font? 0 = unknown, 1 = no, 2 = yes      */

	UBYTE serif;            /* serif font? 0 = unknown, 1 = no, 2 = yes     */

	char name[256];    	/* A NULL-terminated string naming the preferred font.   */

	} FontSpecifier;


#endif
