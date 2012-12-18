

	XDEF _L_AnimDecodeRIFFXor
	XDEF _L_AnimDecodeRIFFSet

	XREF KPrintF

delta		equ		a0
plane		equ		a1
rowbytes	equ		d0
sourcebytes	equ		d1

ch			equ		d2
data		equ		a2
opcount		equ		d3
column		equ		d4
scratch		equ		d5

	section text,code

_L_AnimDecodeRIFFXor:

	; Save registers
	movem.l	a0-a2/d1-d5,-(sp)

	; Loop through image columns
	moveq	#0,column
x_columnloop:

	; Get pointer to delta column
	move.l	plane,data
	add.l	column,data

	; Number of operations in this column
	move.b	(delta)+,opcount

	; Perform operations
x_oploop:

	; Get delta code
	move.b	(delta)+,ch
	bne	x_oprun

	; Repeated byte - get count
	move.b	(delta)+,ch
	beq		x_opend

	; Get byte to repeat
	move.b	(delta)+,scratch

	; Repeat loop
x_oprepeatloop:
	eor.b	scratch,(data)
	add.w	rowbytes,data
	dbne	ch,x_oprepeatloop

	; Finished repeat; do next operation
	dbne	opcount,x_oploop
	bra	x_opfinish


	; Run
x_oprun:

	; If high bit is not set, it means skip
	btst	#7,ch
	bne	x_opdorun

	; Increment data
	move.w	rowbytes,scratch
	mulu.w	ch,scratch
	add.l	scratch,data

	; Do next operation
	dbne	opcount,x_oploop
	bra	x_opend

	; Need to do run
x_opdorun:

	; Clear high bit
	bclr	#7,ch
	tst.b	ch
	beq	x_opend

	; Run loop
x_oprunloop:
	move.b	(delta)+,scratch
	eor.b	scratch,(data)
	add.w	rowbytes,data
	dbne	ch,x_oprunloop

	; End of run; do next operation
x_opend:
	dbne	opcount,x_oploop


	; End of column; do next
x_opfinish:
	addq	#1,column
	cmp.w	column,sourcebytes
	beq	x_columnloop

	; Restore registers and return
	movem.l	(sp)+,a0-a2/d1-d5
	moveq	#0,d0
	rts




_L_AnimDecodeRIFFSet:

	; Save registers
	movem.l	a0-a2/d1-d5,-(sp)

	; Loop through image columns
	moveq	#0,column
s_columnloop:

	; Get pointer to delta column
	move.l	plane,data
	add.l	column,data

	; Number of operations in this column
	move.b	(delta)+,opcount
	beq	s_opfinish

	; Perform operations
s_oploop:

	; Get delta code
	move.b	(delta)+,ch
	bne	s_oprun

	; Repeated byte - get count
	move.b	(delta)+,ch
	beq	s_opend

	; Get byte to repeat
	move.b	(delta)+,scratch

	; Repeat loop
s_oprepeatloop:
	move.b	scratch,(data)
	add.w	rowbytes,data
	dbne	ch,s_oprepeatloop

	; Finished repeat; do next operation
	dbne	opcount,s_oploop
	bra	s_opfinish


	; Run
s_oprun:

	; If high bit is not set, it means skip
	btst	#7,ch
	beq	s_opdorun

	; Increment data
	move.w	rowbytes,scratch
	mulu.w	ch,scratch
	add.w	scratch,data

	; Do next operation
	dbne	opcount,s_oploop
	bra	s_opfinish

	; Need to do run
s_opdorun:

	; Clear high bit
	bclr	#7,ch
	tst.b	ch
	beq	s_opend

	; Run loop
s_oprunloop:
	move.b	(delta)+,(data)
	add.w	rowbytes,data
	dbne	ch,s_oprunloop

	; End of run; do next operation
s_opend:
	dbne	opcount,s_oploop


	; End of column; do next
s_opfinish:
	addq	#1,column

	cmp.w	column,sourcebytes
	bne	s_columnloop

	; Restore registers and return
	movem.l	(sp)+,a0-a2/d1-d5
	moveq	#0,d0
	rts


printdebug:
	movem.l a0/a1,-(sp)
	lea.l	debug_str,a0
	move.l	d7,-(sp)
	move.l	d6,-(sp)
	move.l	sp,a1
	jsr	KPrintF
	add.w	#8,sp
	movem.l (sp)+,a0/a1
	rts
	
debug_str:
	dc.b	'%ld %ld',10,0

	end
