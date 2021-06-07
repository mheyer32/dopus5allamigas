/*
!! For 68k build only !!

 That file have 7 functions which use a4 and/or a5 registers as arguments which can cause problems with 68k gcc's inline
macroses.

 3 function from dopus5 itself (SimpleRequest, SelectionList and WB_LaunchNotify)
 4 functions from configopus module (ConfigEditFunction, ConfigEnvironment, ConfigMenu and ShowPaletteBox).

 The reassons to create them like this, is that there is not possible by fd2pragma generate "right" inlines
 for such functions where a5 and a6 used as arguments at the same time.

 We tryed all of possible gcc-68k-inlines started from SPECIAL 40 to SPECIAL 47. Even if in some cases inlines
 still generates, they still didn't works in end.

 Because of that we need to create those functions on pure assembler, so they will works as they intended to.

 All the other 68k inlines generated with SPECIAL 43 (the best and clean look) via usage of inline/macros.h from 68k
gcc.

 It is worth to try to create necessary macroses to put it inside of inline/macros.h, but currently we go that way.

*/

asm(".text                    \n\
     .even                    \n\
.globl _SimpleRequest         \n\
_SimpleRequest:               \n\
      moveml a2-a6,sp@-       \n\
      moveal _DOpusBase,a6    \n\
      moveml sp@(24),a0-a5    \n\
      moveml sp@(48),d0/d1    \n\
      jsr a6@(-156:W)         \n\
      moveml sp@+,a2-a6       \n\
      rts                     \n\
      ");

asm(".text                       \n\
     .even                       \n\
.globl _SelectionList            \n\
_SelectionList:                  \n\
      moveml d2-d4/a2-a6,sp@-    \n\
      moveal _DOpusBase,a6       \n\
      moveml sp@(36),a0-a3       \n\
      moveml sp@(52),d0-d4/a4/a5 \n\
      jsr a6@(-162:W)            \n\
      moveml sp@+,d2-d4/a2-a6    \n\
      rts                        \n\
      ");

asm(".text                       \n\
     .even                       \n\
.globl _WB_LaunchNotify          \n\
_WB_LaunchNotify:                \n\
      moveml d2/a2-a6,sp@-       \n\
      moveal _DOpusBase,a6       \n\
      moveml sp@(24),a0-a1       \n\
      moveml sp@(32),d0-d1/a2-a4 \n\
      movel  sp@(52),d2          \n\
      jsr a6@(-2226:W)           \n\
      moveml sp@+,d2/a2-a6  	 \n\
      rts                        \n\
      ");

asm(".text                       \n\
     .even                       \n\
.globl _Config_EditFunction      \n\
_Config_EditFunction:            \n\
      moveml a2/a3/a4/a6,sp@-    \n\
      moveal _ConfigOpusBase,a6  \n\
      moveml sp@(20),a0-a4       \n\
      moveml sp@(40),d0          \n\
      jsr a6@(-90:W)             \n\
      moveml sp@+,a2/a3/a4/a6    \n\
      rts                        \n\
      ");

asm(".text                       \n\
     .even                       \n\
.globl _Config_Environment       \n\
_Config_Environment:             \n\
      moveml d2/a2-a6,sp@-       \n\
      moveal _ConfigOpusBase,a6  \n\
      moveml sp@(28),a0-a4       \n\
      moveml sp@(48),d0/a5       \n\
      moveml sp@(56),d1/d2       \n\
      jsr a6@(-36:W)             \n\
      moveml sp@+,d2/a2-a6       \n\
      rts                        \n\
      ");

asm(".text                       \n\
     .even                       \n\
.globl _Config_Menu              \n\
_Config_Menu:                    \n\
      moveml d2/d3/a2-a6,sp@-    \n\
      moveal _ConfigOpusBase,a6  \n\
      moveml sp@(32),a0-a5       \n\
      moveml sp@(56),d0-d3       \n\
      jsr a6@(-72:W)             \n\
      moveml sp@+,d2/d3/a2-a6    \n\
      rts                        \n\
      ");

asm(".text                       \n\
     .even                       \n\
.globl _ShowPaletteBox           \n\
_ShowPaletteBox:                 \n\
      moveml a2-a6,sp@-          \n\
      moveal _ConfigOpusBase,a6  \n\
      moveml sp@(24),a0-a5       \n\
      moveml sp@(48),d0          \n\
      jsr a6@(-96:W)             \n\
      moveml sp@+,a2-a6          \n\
      rts                        \n\
      ");
