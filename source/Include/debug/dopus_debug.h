#ifndef DOPUS_DEBUG
#define DOPUS_DEBUG

#if defined(__AROS__)

#include <aros/debug.h>

#else

#if defined(__amigaos3__) || defined(__MORPHOS__)
#include <clib/debug_protos.h>
#endif

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#if defined(__amigaos4__)
  #define bug(fmt, args...)  {DebugPrintF("[%s:%ld %s] ", __FILE__, __LINE__, __FUNCTION__); DebugPrintF(fmt, ##args);}
  #define kprintf DebugPrintF
  #define KPrintF DebugPrintF
#elif defined(__amigaos3__)
  #define bug(fmt, args...)  {kprintf("[%s:%ld] ", __FILE__, __LINE__); kprintf(fmt, ##args);}
#elif defined(__MORPHOS__)
  #define bug(fmt, args...)  {kprintf("[%s:%ld %s] ", __FILE__, __LINE__, __FUNCTION__); kprintf(fmt, ##args);}
#endif

#endif

#endif /* DOPUS_DEBUG */
