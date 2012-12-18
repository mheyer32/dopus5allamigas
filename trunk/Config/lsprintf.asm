_LVORawDoFmt equ -$20a

	XDEF _lsprintf
	XDEF _SwapMem

	section text,code

_lsprintf:
	movem.l a2/a3/a6,-(sp)
	move.l 4*4(sp),a3
	move.l 5*4(sp),a0
	lea.l 6*4(sp),a1
	lea.l stuffChar(pc),a2
	move.l 4,a6
	jsr _LVORawDoFmt(a6)
	movem.l (sp)+,a2/a3/a6
	rts

stuffChar:
	move.b d0,(a3)+
	rts

_SwapMem:
	move.b (a0),d1
	move.b (a1),(a0)+
	move.b d1,(a1)+
	subq.l #1,d0
	bne.s _SwapMem
	rts

	end
