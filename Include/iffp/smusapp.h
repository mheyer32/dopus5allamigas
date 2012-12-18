/* smusapp.h
 * - definition of SMUSInfo structure
 * - inclusion of includes needed by modules and application
 * - application-specific definitions
 */
#ifndef SMUSAPP_H
#define SMUSAPP_H

#include "iffp/smus.h"
#include "iffp/8svx.h"
#include "iffp/8svxapp.h"

#include <devices/audio.h>

/* Structure currently defined for max of 16 tracks, 16 instruments */

#define MAXTRACKS 16
#define MAXINS    16

struct SMUSInfo {
	/* general parse.c related */
	struct  ParseInfo ParseInfo;

	/* For convenient access to SHDR and tracks.
	 * Other chunks will be accessible through FindProp()
         *  (or findchunk() if the chunks have been copied)
	 */
	SScoreHeader		Shdr;

	SEvent			*traks[MAXTRACKS];
	ULONG			tbytes[MAXTRACKS];

	UBYTE			insids[MAXINS];
	ULONG			insflags[MAXINS];
		
	struct EightSVXInfo 	*esvxs[MAXINS];

	UBYTE           	name[80];

	ULONG			Reserved[8];	/* must be 0 for now */

	/* Applications may add variables here */
	};

/* referenced by modules */
extern struct Library *IFFParseBase;

#endif
