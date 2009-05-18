#ifndef PROTO_OPENURL_H
#define PROTO_OPENURL_H

/*
**	$Id$
**	Includes Release 50.1
**
**	Prototype/inline/pragma header file combo
**
**	(C) Copyright 2003-2007 Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #ifndef __USE_BASETYPE__
  extern struct Library * OpenURLBase;
 #else
  extern struct Library * OpenURLBase;
 #endif /* __USE_BASETYPE__ */
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/openurl.h>
 #ifdef __USE_INLINE__
  #include <inline4/openurl.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_OPENURL_PROTOS_H
  #define CLIB_OPENURL_PROTOS_H 1
 #endif /* CLIB_OPENURL_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  extern struct OpenURLIFace *IOpenURL;
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_OPENURL_PROTOS_H
  #include <clib/openurl_protos.h>
 #endif /* CLIB_OPENURL_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/openurl.h>
  #else
   #include <ppcinline/openurl.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/openurl_protos.h>
  #endif /* __PPC__ */
 #else
  #include <pragmas/openurl_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_OPENURL_H */
