

	SECTION	code

	XDEF _L_Seed
	XDEF _L_Random
	XDEF _L_BtoCStr
	XDEF _L_DivideU
	
rand
	ds.l 2

_L_Seed:
	move.l d0,d1
	not.l d1
	movem.l d0/d1,rand
longrnd:
  movem.l d2-d3,-(sp) 
	movem.l rand,d0/d1
	andi.b #$0e,d0
	ori.b #$20,d0
	move.l d0,d2
	move.l d1,d3
	add.l d2,d2 
	addx.l d3,d3
	add.l d2,d0
	addx.l d3,d1
	swap d3
	swap d2
	move.w d2,d3
	clr.w d2
	add.l d2,d0
	addx.l d3,d1
	movem.l d0/d1,rand
	move.l d1,d0
	movem.l (sp)+,d2-d3
	rts

_L_Random:
	move.w d2,-(sp)
	move.w d0,d2
	beq.s skip
	bsr.s longrnd
	clr.w d0
	swap d0
	divu.w d2,d0
	clr.w d0
	swap d0
skip:
	move.w (sp)+,d2
	rts

_L_BtoCStr:
	subq.l #1,d0
	move.l a0,d1
	lsl.l #2,d1
	move.l d1,a0
	moveq.l #0,d1
	move.b (a0)+,d1
	cmp.l d0,d1
	ble conloop
	move.l d0,d1
conloop:
	move.b (a0)+,(a1)+
	dbeq d1,conloop
	move.b #0,(a1)
	rts

_L_DivideU:
	* num = d0
	* div = d1
	* rem = a0
	* utilitybase = a1
	jsr -$9c(a1)
	move.l d1,(a0)
	rts

	END
