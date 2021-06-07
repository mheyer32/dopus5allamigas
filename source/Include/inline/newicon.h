#ifndef _INLINE_NEWICON_H
#define _INLINE_NEWICON_H

#ifndef CLIB_NEWICON_PROTOS_H
	#define CLIB_NEWICON_PROTOS_H
#endif

#ifndef EXEC_TYPES_H
	#include <exec/types.h>
#endif
#ifndef LIBRARIES_NEWICON_H
	#include <libraries/newicon.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NEWICON_BASE_NAME
	#define NEWICON_BASE_NAME NewIconBase
#endif

#define GetNewDiskObject(name)                                                                                 \
	({                                                                                                         \
		UBYTE *_GetNewDiskObject_name = (name);                                                                \
		({                                                                                                     \
			register char *_GetNewDiskObject__bn __asm("a6") = (char *)(NEWICON_BASE_NAME);                    \
			((struct NewDiskObject * (*)(char *__asm("a6"), UBYTE *__asm("a0")))(_GetNewDiskObject__bn - 30))( \
				_GetNewDiskObject__bn, _GetNewDiskObject_name);                                                \
		});                                                                                                    \
	})

#define PutNewDiskObject(name, newdiskobj)                                                        \
	({                                                                                            \
		UBYTE *_PutNewDiskObject_name = (name);                                                   \
		struct NewDiskObject *_PutNewDiskObject_newdiskobj = (newdiskobj);                        \
		({                                                                                        \
			register char *_PutNewDiskObject__bn __asm("a6") = (char *)(NEWICON_BASE_NAME);       \
			((BOOL(*)(char *__asm("a6"), UBYTE *__asm("a0"), struct NewDiskObject *__asm("a1")))( \
				_PutNewDiskObject__bn - 36))(                                                     \
				_PutNewDiskObject__bn, _PutNewDiskObject_name, _PutNewDiskObject_newdiskobj);     \
		});                                                                                       \
	})

#define FreeNewDiskObject(newdiskobj)                                                                        \
	({                                                                                                       \
		struct NewDiskObject *_FreeNewDiskObject_newdiskobj = (newdiskobj);                                  \
		({                                                                                                   \
			register char *_FreeNewDiskObject__bn __asm("a6") = (char *)(NEWICON_BASE_NAME);                 \
			((void (*)(char *__asm("a6"), struct NewDiskObject *__asm("a0")))(_FreeNewDiskObject__bn - 42))( \
				_FreeNewDiskObject__bn, _FreeNewDiskObject_newdiskobj);                                      \
		});                                                                                                  \
	})

#define RemapChunkyImage(chunkyimage, screen)                                                                      \
	({                                                                                                             \
		struct ChunkyImage *_RemapChunkyImage_chunkyimage = (chunkyimage);                                         \
		struct Screen *_RemapChunkyImage_screen = (screen);                                                        \
		({                                                                                                         \
			register char *_RemapChunkyImage__bn __asm("a6") = (char *)(NEWICON_BASE_NAME);                        \
			((struct Image * (*)(char *__asm("a6"), struct ChunkyImage *__asm("a0"), struct Screen *__asm("a1")))( \
				_RemapChunkyImage__bn - 66))(                                                                      \
				_RemapChunkyImage__bn, _RemapChunkyImage_chunkyimage, _RemapChunkyImage_screen);                   \
		});                                                                                                        \
	})

#define FreeRemappedImage(image, screen)                                                          \
	({                                                                                            \
		struct Image *_FreeRemappedImage_image = (image);                                         \
		struct Screen *_FreeRemappedImage_screen = (screen);                                      \
		({                                                                                        \
			register char *_FreeRemappedImage__bn __asm("a6") = (char *)(NEWICON_BASE_NAME);      \
			((VOID(*)(char *__asm("a6"), struct Image *__asm("a0"), struct Screen *__asm("a1")))( \
				_FreeRemappedImage__bn - 72))(                                                    \
				_FreeRemappedImage__bn, _FreeRemappedImage_image, _FreeRemappedImage_screen);     \
		});                                                                                       \
	})

#define GetDefNewDiskObject(def_type)                                                                           \
	({                                                                                                          \
		LONG _GetDefNewDiskObject_def_type = (def_type);                                                        \
		({                                                                                                      \
			register char *_GetDefNewDiskObject__bn __asm("a6") = (char *)(NEWICON_BASE_NAME);                  \
			((struct NewDiskObject * (*)(char *__asm("a6"), LONG __asm("d0")))(_GetDefNewDiskObject__bn - 78))( \
				_GetDefNewDiskObject__bn, _GetDefNewDiskObject_def_type);                                       \
		});                                                                                                     \
	})

#ifdef __cplusplus
}
#endif
#endif /*  _INLINE_NEWICON_H  */
