
	XDEF _get_a4
	XDEF _set_a4

	section text,code

_get_a4:
	move.l a4,d0
	rts

_set_a4:
	move.l d0,a4
	rts

	end
