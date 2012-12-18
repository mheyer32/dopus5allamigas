/* 8svxapp.h
 * - definition of EightSVXInfo structure
 * - inclusion of includes needed by modules and application
 * - application-specific definitions
 */
#ifndef EIGHTSVXAPP_H
#define EIGHTSVXAPP_H

#include "iffp/8svx.h"

#include <devices/audio.h>

#define MAXOCT 16

struct EightSVXInfo {
	/* general parse.c related */
	struct  ParseInfo ParseInfo;

	/* For convenient access to VHDR, Name, and sample.
	 * Other chunks will be accessible through FindProp()
         *  (or findchunk() if the chunks have been copied)
	 */
	/* 8SVX */
	Voice8Header	Vhdr;		

	BYTE		*sample;
	ULONG		samplebytes;

	BYTE		*osamps[MAXOCT];
	ULONG		osizes[MAXOCT];
	BYTE		*rsamps[MAXOCT];
	ULONG		rsizes[MAXOCT];
	ULONG		spcycs[MAXOCT];

	UBYTE		name[80];

	ULONG		Reserved[8];	/* must be 0 for now */

	/* Applications may add variables here */
	};

/* referenced by modules */
extern struct Library *IFFParseBase;

#endif
