
_LVORawDoFmt equ -$20a

	XDEF _lsprintf
	XDEF _L_LSprintf
	XDEF @LSprintf
	XDEF _LSprintf

	section text,code

_lsprintf:
_L_LSprintf:
	movem.l a2/a3/a6,-(sp)
	move.l 4*4(sp),a3
	move.l 5*4(sp),a0
	lea.l 6*4(sp),a1
	lea.l stuffChar(pc),a2
	move.l 4,a6
	jsr _LVORawDoFmt(a6)
	movem.l (sp)+,a2/a3/a6
	rts

@LSprintf:
_LSprintf:
	movem.l a2/a3/a6,-(sp)
	lea.l stuffChar(pc),a2
	move.l 4,a6
	jsr _LVORawDoFmt(a6)
	movem.l (sp)+,a2/a3/a6
	rts

stuffChar:
	move.b d0,(a3)+
	rts

	end
