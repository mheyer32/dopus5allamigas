/*-----------------------------------------------------------------------*
 * 8SVX.H  Definitions for 8-bit sampled voice (VOX).   2/10/86
 *
 * By Jerry Morrison and Steve Hayes, Electronic Arts.
 * This software is in the public domain.
 * 
 * Modified for use with iffparse.library 05/91 - CAS_CBM
 *
 * This version for the Commodore-Amiga computer.
 *----------------------------------------------------------------------*/
#ifndef EIGHTSVX_H
#define EIGHTSVX_H

#ifndef COMPILER_H
#include "iffp/compiler.h"
#endif

#include "iffp/iff.h"

#define ID_8SVX      MAKE_ID('8', 'S', 'V', 'X')
#define ID_VHDR      MAKE_ID('V', 'H', 'D', 'R')

#define ID_ATAK      MAKE_ID('A', 'T', 'A', 'K')
#define ID_RLSE      MAKE_ID('R', 'L', 'S', 'E')

/* defined in iffp/iff.h
#define ID_NAME      MAKE_ID('N', 'A', 'M', 'E')
#define ID_Copyright MAKE_ID('(', 'c', ')', ' ')
#define ID_AUTH      MAKE_ID('A', 'U', 'T', 'H')
#define ID_ANNO      MAKE_ID('A', 'N', 'N', 'O')
#define ID_BODY      MAKE_ID('B', 'O', 'D', 'Y')
*/

/* ---------- Voice8Header ---------------------------------------------*/
typedef LONG Fixed;	/* A fixed-point value, 16 bits to the left of
			 * the point and 16 to the right. A Fixed is a
			 * number of 2**16ths, i.e. 65536ths. */
#define Unity 0x10000L	/* Unity = Fixed 1.0 = maximum volume */

/* sCompression: Choice of compression algorithm applied to the samples. */
#define sCmpNone       0	/* not compressed */
#define sCmpFibDelta   1	/* Fibonacci-delta encoding (Appendix C) */
				/* Could be more kinds in the future. */
typedef struct {
    ULONG oneShotHiSamples,	/* # samples in the high octave 1-shot part */
          repeatHiSamples,	/* # samples in the high octave repeat part */
          samplesPerHiCycle;	/* # samples/cycle in high octave, else 0 */
    UWORD samplesPerSec;	/* data sampling rate */
    UBYTE ctOctave,		/* # of octaves of waveforms */
          sCompression;		/* data compression technique used */
    Fixed volume;		/* playback nominal volume from 0 to Unity
				 * (full volume). Map this value into
				 * the output hardware's dynamic range.
				 */
    } Voice8Header;

/* ---------- NAME -----------------------------------------------------*/
/* NAME chunk contains a CHAR[], the voice's name. */

/* ---------- Copyright ------------------------------------------------*/
/* "(c) " chunk contains a CHAR[], the FORM's copyright notice. */

/* ---------- AUTH -----------------------------------------------------*/
/* AUTH chunk contains a CHAR[], the author's name. */

/* ---------- ANNO -----------------------------------------------------*/
/* ANNO chunk contains a CHAR[], the author's text annotations. */

/* ---------- Envelope ATAK & RLSE -------------------------------------*/
typedef struct {
    UWORD duration;	/* segment duration in milliseconds, > 0 */
    Fixed dest;		/* destination volume factor */
    } EGPoint;

/* ATAK and RLSE chunks contain an EGPoint[], piecewise-linear envelope. */

/* The envelope defines a function of time returning Fixed values.
 * It's used to scale the nominal volume specified in the Voice8Header.
 */

/* ---------- BODY -----------------------------------------------------*/
/* BODY chunk contains a BYTE[], array of audio data samples. */
/* (8-bit signed numbers, -128 through 127.) */


/* ---------- 8SVX Writer Support Routines -----------------------------*/

/* Just call this macro to write a VHDR chunk. */
#define PutVHDR(iff, vHdr)  \
    PutCk(iff, ID_VHDR, sizeof(Voice8Header), (BYTE *)vHdr)

#endif
