/*----------------------------------------------------------------------*
 * SMUS.H  Definitions for Simple MUSical score.   2/12/86
 *
 * By Jerry Morrison and Steve Hayes, Electronic Arts.
 * This software is in the public domain.
 *
 * Modified for use with iffparse.library 05/91 - CAS_CBM
 *
 * This version for the Commodore-Amiga computer.
 *----------------------------------------------------------------------*/
#ifndef SMUS_H
#define SMUS_H

#ifndef COMPILER_H
#include "iffp/compiler.h"
#endif

#include "iffp/iff.h"

#define ID_SMUS      MAKE_ID('S', 'M', 'U', 'S')
#define ID_SHDR      MAKE_ID('S', 'H', 'D', 'R')

/* Now defined in iffp/iff.h as generic chunks
#define ID_NAME      MAKE_ID('N', 'A', 'M', 'E')
#define ID_Copyright MAKE_ID('(', 'c', ')', ' ')
#define ID_AUTH      MAKE_ID('A', 'U', 'T', 'H')
#define ID_ANNO      MAKE_ID('A', 'N', 'N', 'O')
*/

#define ID_INS1      MAKE_ID('I', 'N', 'S', '1')
#define ID_TRAK      MAKE_ID('T', 'R', 'A', 'K')

/* ---------- SScoreHeader ---------------------------------------------*/
typedef struct {
    UWORD tempo;	/* tempo, 128ths quarter note/minute */
    UBYTE volume;	/* playback volume 0 through 127 */
    UBYTE ctTrack;	/* count of tracks in the score */
    } SScoreHeader;

/* ---------- NAME -----------------------------------------------------*/
/* NAME chunk contains a CHAR[], the musical score's name. */

/* ---------- Copyright (c) --------------------------------------------*/
/* "(c) " chunk contains a CHAR[], the FORM's copyright notice. */

/* ---------- AUTH -----------------------------------------------------*/
/* AUTH chunk contains a CHAR[], the name of the score's author. */

/* ---------- ANNO -----------------------------------------------------*/
/* ANNO chunk contains a CHAR[], the author's text annotations. */

/* ---------- INS1 -----------------------------------------------------*/
/* Constants for the RefInstrument's "type" field. */
#define INS1_Name  0	/* just use the name; ignore data1, data2 */
#define INS1_MIDI  1	/* <data1, data2> = MIDI <channel, preset> */

typedef struct {
    UBYTE iRegister;	/* set this instrument register number */
    UBYTE type;		/* instrument reference type (see above) */
    UBYTE data1, data2;	/* depends on the "type" field */
    char name[60];	/* instrument name */
    } RefInstrument;

/* ---------- TRAK -----------------------------------------------------*/
/* TRAK chunk contains an SEvent[]. */

/* SEvent: Simple musical event. */
typedef struct {
    UBYTE sID;		/* SEvent type code */
    UBYTE data;		/* sID-dependent data */
    } SEvent;

/* SEvent type codes "sID". */
#define SID_FirstNote     0
#define SID_LastNote    127	/* sIDs in the range SID_FirstNote through
				 * SID_LastNote (sign bit = 0) are notes. The
				 * sID is the MIDI tone number (pitch). */
#define SID_Rest        128	/* a rest; same data format as a note. */

#define SID_Instrument  129	/* set instrument number for this track. */
#define SID_TimeSig     130	/* set time signature for this track. */
#define SID_KeySig	131	/* set key signature for this track. */
#define SID_Dynamic	132	/* set volume for this track. */
#define SID_MIDI_Chnl	133	/* set MIDI channel number (sequencers) */
#define SID_MIDI_Preset	134	/* set MIDI preset number (sequencers) */
#define SID_Clef        135     /* inline clef change. 
                                 * 0=Treble, 1=Bass, 2=Alto, 3=Tenor. */
#define SID_Tempo       136     /* Inline tempo change in beats per minute.*/

/* SID values 144 through 159: reserved for Instant Music SEvents. */

/* The remaining sID values up through 254: reserved for future
 * standardization. */
#define SID_Mark        255	/* SID reserved for an end-mark in RAM. */

/* ---------- SEvent FirstNote..LastNote or Rest -----------------------*/
typedef struct {
    unsigned tone     :8,	/* MIDI tone number 0 to 127; 128 = rest */
             chord    :1,	/* 1 = a chorded note */
             tieOut   :1,	/* 1 = tied to the next note or chord */
             nTuplet  :2,	/* 0 = none, 1 = triplet, 2 = quintuplet,
				 * 3 = septuplet */
             dot      :1,	/* dotted note; multiply duration by 3/2 */
             division :3;	/* basic note duration is 2**-division:
				 * 0 = whole note, 1 = half note, 2 = quarter
				 * note, ... 7 = 128th note */
    } SNote;

/* Warning: An SNote is supposed to be a 16-bit entity.
 * Some C compilers will not pack bit fields into anything smaller
 * than an int. So avoid the actual use of this type unless you are certain
 * that the compiler packs it into a 16-bit word.
 */

/* You may get better object code by masking, ORing, and shifting using the
 * following definitions rather than the bit-packed fields, above. */
#define noteChord  (1<<7)	/* note is chorded to next note */

#define noteTieOut (1<<6)	/* note/chord is tied to next note/chord */

#define noteNShift 4			/* shift count for nTuplet field */
#define noteN3     (1<<noteNShift)	/* note is a triplet */
#define noteN5     (2<<noteNShift)	/* note is a quintuplet */
#define noteN7     (3<<noteNShift)	/* note is a septuplet */
#define noteNMask  noteN7		/* bit mask for the nTuplet field */

#define noteDot    (1<<3)		/* note is dotted */

#define noteDShift 0			/* shift count for division field */
#define noteD1     (0<<noteDShift)	/* whole note division */
#define noteD2     (1<<noteDShift)	/* half note division */
#define noteD4     (2<<noteDShift)	/* quarter note division */
#define noteD8     (3<<noteDShift) 	/* eighth note division */
#define noteD16    (4<<noteDShift) 	/* sixteenth note division */
#define noteD32    (5<<noteDShift) 	/* thirty-secondth note division */
#define noteD64    (6<<noteDShift) 	/* sixty-fourth note division */
#define noteD128   (7<<noteDShift) 	/* 1/128 note division */
#define noteDMask  noteD128		/* bit mask for the division field */

#define noteDurMask 0x3F		/* bit mask for all duration fields
					 * division, nTuplet, dot */

/* Field access: */
#define IsChord(snote)	(((UWORD)snote) & noteChord)
#define IsTied(snote) 	(((UWORD)snote) & noteTieOut)
#define NTuplet(snote) 	((((UWORD)snote) & noteNMask) >> noteNShift)
#define IsDot(snote) 	(((UWORD)snote) & noteDot)
#define Division(snote) ((((UWORD)snote) & noteDMask) >> noteDShift)

/* ---------- TimeSig SEvent -------------------------------------------*/
typedef struct {
    unsigned type     :8,	/* = SID_TimeSig */
             timeNSig :5,	/* time signature "numerator" timeNSig + 1 */
             timeDSig :3;	/* time signature "denominator" is
				 * 2**timeDSig: 0 = whole note, 1 = half
				 * note, 2 = quarter note, ...
				 * 7 = 128th note */
    } STimeSig;

#define timeNMask  0xF8		/* bit mask for timeNSig field */
#define timeNShift 3		/* shift count for timeNSig field */

#define timeDMask  0x07		/*  bit mask for timeDSig field */

/* Field access: */
#define TimeNSig(sTime)  ((((UWORD)sTime) & timeNMask) >> timeNShift)
#define TimeDSig(sTime)   (((UWORD)sTime) & timeDMask)

/* ---------- KeySig SEvent --------------------------------------------*/
/* "data" value 0 = Cmaj; 1 through 7 = G,D,A,E,B,F#,C#;
 * 8 through 14 = F,Bb,Eb,Ab,Db,Gb,Cb.					*/

/* ---------- Dynamic SEvent -------------------------------------------*/
/* "data" value is a MIDI key velocity 0..127. */


/* ---------- SMUS Writer Support Routines -----------------------------*/

/* Just call this to write a SHDR chunk. */
#define PutSHDR(iff, ssHdr)  \
    PutCk(iff, ID_SHDR, sizeof(SScoreHeader), (BYTE *)ssHdr)

#endif
