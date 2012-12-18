
	section code

	xdef _backdrop_pattern_rotate

_backdrop_pattern_rotate:
	move.l d2,-(sp)
	cmp.w #8,d0
	bgt.s go_right

	moveq #16,d1
left_loop:
	move.w (a0),d2
	rol.w d0,d2
	move.w d2,(a0)+
	dbf d1,left_loop

	move.l (sp)+,d2
	rts

go_right:
	move.w #16,d1
	sub.w d0,d1

	moveq #16,d0
right_loop:
	move.w (a0),d2
	ror.w d1,d2
	move.w d2,(a0)+
	dbf d0,right_loop

	move.l (sp)+,d2
	rts

	end
