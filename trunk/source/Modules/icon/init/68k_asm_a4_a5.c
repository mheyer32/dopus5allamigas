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
	  