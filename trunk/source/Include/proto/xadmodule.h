#ifndef PROTO_XADMODULE_H
#define PROTO_XADMODULE_H

/*
**	$Id$
**	Includes Release 50.1
**
**	Prototype/inline/pragma header file combo
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_XADMASTER_H
#include <libraries/xadmaster.h>
#endif

#include <libraries/module.h>

/****************************************************************************/

#ifndef __NOLIBBASE__
 #ifndef __USE_BASETYPE__
  extern struct Library * XADModuleBase;
 #else
  extern struct Library * XADModuleBase;
 #endif /* __USE_BASETYPE__ */
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/xadmodule.h>
 #ifdef __USE_INLINE__
  #include <inline4/xadmodule.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_XADMODULE_PROTOS_H
  #define CLIB_XADMODULE_PROTOS_H 1
 #endif /* CLIB_XADMODULE_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  extern struct XADModuleIFace *IXADModule;
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_XADMODULE_PROTOS_H
  #include <clib/xadmodule_protos.h>
 #endif /* CLIB_XADMODULE_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/xadmodule.h>
  #else /* __PPC__ */
   #include <ppcinline/xadmodule.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/xadmodule_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/xadmodule_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_XADMODULE_H */
