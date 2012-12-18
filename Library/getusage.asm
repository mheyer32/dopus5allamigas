
* Get CPU usage as a percentage
* getusage() routine takes no arguments, returns value from 0 to 100 in d0

	XDEF _GetCPUUsage

	section code

_GetCPUUsage:
	movem.l d1-d3/a6,-(sp)
	move.l 4,a6
	move.l 280(a6),d0
	move.l 284(a6),d1
	move.l oldidl,d3
	move.l d0,oldidl
	sub.l d3,d0
	move.l olddisp,d3
	move.l d1,olddisp
	sub.l d1,d3
	move.l d0,d1
	sub.l d3,d1
	sub.l d3,d0
	neg.l d3
	bsr getpcent
	movem.l (sp)+,d1-d3/a6
	rts

getpcent:
	lsl.l #1,d3
	move.l d3,d1
	lsl.l #2,d3
	add.l d1,d3
	lsl.l #2,d3
	move.l d3,d1
	lsl.l #3,d3
	move.l d3,d2
	lsl.l #1,d3
	add.l d2,d3
	add.l d1,d3
	move.l d0,d1
	move.l d3,d0
	bsr div32
	rts

* 32-bit division routines

div32:
	tst.l d1
	beq div8
	swap d1
	move.w d1,d2
	bne.s div1
	swap d0
	swap d1
	swap d2
	move.w d0,d2
	beq.s div2
	divu d1,d2
	move.w d2,d0
div2
	swap d0
	move.w d0,d2
	divu d1,d2
	move.w d2,d0
	swap d2
	move.w d2,d1
	bra div8
div1
	moveq #$10,d3
	cmpi.w #$80,d1
	bcc.s div3
	rol.l #8,d1
	subq.w #8,d3
div3
	cmpi.w #$800,d1
	bcc.s div4
	rol.l #4,d1
	subq.w #4,d3
div4
	cmpi.w #$2000,d1
	bcc.s div5
	rol.l #2,d1
	subq.w #2,d3
div5
	tst.w d1
	bmi.s div6
	rol.l #1,d1
	subq.w #1,d3
div6
	move.w d0,d2
	lsr.l d3,d0
	swap d2
	clr.w d2
	lsr.l d3,d2
	swap d3
	divu d1,d0
	move.w d0,d3
	move.w d2,d0
	move.w d3,d2
	swap d1
	mulu d1,d2
	sub.l d2,d0
	bcc.s div7
	subq.w #1,d3
	add.l d1,d0
div7
	moveq #0,d1
	move.w d3,d1
	swap d3
	rol.l d3,d0
	swap d0
	exg d1,d0
div8
	rts

	section data

oldidl
	dc.l 0
olddisp
	dc.l 0

	end
