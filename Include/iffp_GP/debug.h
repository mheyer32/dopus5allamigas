/*
 * mydebug.h - #include this file sometime after stdio.h
 * Set MYDEBUG to 1 to turn on debugging, 0 to turn off debugging
 */
#ifndef MYDEBUG_H
#define MYDEBUG_H

#define MYDEBUG	0

#if MYDEBUG
/*
 * MYDEBUG User Options
 */

/* Set to 1 to turn second level D2(bug()) statements */
#define DEBUGLEVEL2	1

/* Set to a non-zero # of ticks if a delay is wanted after each debug message */
#define DEBUGDELAY		0

/* Always non-zero for the DDx macros */
#define DDEBUGDELAY		50

/* Set to 1 for serial debugging (link with debug.lib) */
#define KDEBUG		0

/* Set to 1 for parallel debugging (link with ddebug.lib) */
#define DDEBUG		0

#endif /* MYDEBUG */


/* Prototypes for Delay, kprintf, dprintf. Or use proto/dos.h or functions.h. */
#include <clib/dos_protos.h>
void kprintf(UBYTE *fmt,...);
void dprintf(UBYTE *fmt,...);

/*
 * D(bug()), D2(bug()), DQ((bug()) only generate code if MYDEBUG is non-zero
 *
 * Use D(bug()) for general debugging, D2(bug()) for extra debugging that
 * you usually won't need to see, DD(bug()) for debugging statements that
 * you always want followed by a delay, and DQ(bug()) for debugging that
 * you'll NEVER want a delay after (ie. debugging inside a Forbid, Disable,
 * Task, or Interrupt)
 *
 * Some example uses (all are used the same):
 * D(bug("about to do xyz. variable = $%lx\n",myvariable)); 
 * D2(bug("v1=$%lx v2=$%lx v3=$%lx\n",v1,v2,v3)); 
 * DQ(bug("in subtask: variable = $%lx\n",myvariable));
 * DD(bug("About to do xxx\n"));
 *
 * Set MYDEBUG above to 1 when debugging is desired and recompile the modules
 *  you wish to debug.  Set to 0 and recompile to turn off debugging.
 *
 * User options set above:
 * Set DEBUGDELAY to a non-zero # of ticks (ex. 50) when a delay is desired.
 * Set DEBUGLEVEL2 nonzero to turn on second level (D2) debugging statements
 * Set KDEBUG to 1 and link with debug.lib for serial debugging.
 * Set DDEBUG to 1 and link with ddebug.lib for parallel debugging.
 */


/* 
 * Debugging function automaticaly set to printf, kprintf, or dprintf
 */

#if KDEBUG
#define bug kprintf
#elif DDEBUG
#define bug dprintf
#else	/* else changes all bug's to printf's */
#define bug printf
#endif

/*
 * Debugging macros
 */

/* D(bug( 	delays DEBUGDELAY if DEBUGDELAY is > 0
 * DD(bug(	always delays DDEBUGDELAY
 * DQ(bug(      (debug quick) never uses Delay.  Use in forbids,disables,ints
 * The similar macros with "2" in their names are second level debugging
 */
#if MYDEBUG    /* Turn on first level debugging */
#define D(x)  (x); if(DEBUGDELAY>0) Delay(DEBUGDELAY)
#define DD(x) (x); Delay(DDEBUGDELAY)
#define DQ(x) (x)
#if DEBUGLEVEL2 /* Turn on second level debugging */
#define D2(x)  (x); if(DEBUGDELAY>0) Delay(DEBUGDELAY)
#define DD2(x) (x); Delay(DDEBUGDELAY)
#define DQ2(x) (x)
#else  /* Second level debugging turned off */
#define D2(x) ;
#define DD2(x) ;
#define DQ2(x) ;
#endif /* DEBUGLEVEL2 */
#else  /* First level debugging turned off */
#define D(x) ;
#define DQ(x) ;
#define D2(x) ;
#define DD(x) ;
#endif


#endif /* MYDEBUG_H */

