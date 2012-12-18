
_LVORawDoFmt equ -$20a

VIEW_FILE_SIZE       equ 0
VIEW_MAX_LINE_LENGTH equ 4
VIEW_TAB_SIZE        equ 8
VIEW_TEXT_BUFFER     equ 12

	section code

	XDEF _countlines

_countlines:
	movem.l d2-d5/a2,-(sp) ; save registers

	move.l VIEW_FILE_SIZE(a0),d1
	move.l VIEW_MAX_LINE_LENGTH(a0),d2
	move.l VIEW_TEXT_BUFFER(a0),a0

* D1 = viewsize
* D2 = maximum line length
* A0 = buffer
* ---
* D0 = number of lines
* D3 = number of characters counted
* D5 = earliest position to wordwrap from
* A1 = last white space character (for wordwrap)

	moveq #0,d0
	moveq #0,d3
	move.l d2,d5
	sub.l #10,d5
	move.l #0,a1
loop:
	addq #1,d3
	cmp.l d2,d3
	bne skip1
	cmp.l #0,a1
	beq nolastspace
	move.l a0,a2	
	sub.l a1,a2
	cmp.l d5,a2
	bge nolastspace
	add.l a2,d1
	move.l a1,a0
nolastspace:
	move.b #10,(a0)
	addq #1,d0
	moveq #0,d3
	sub.l a1,a1
	bra skip3
skip1:
	cmpi.b #10,(a0)
	bne skip2
	sub.l a1,a1
	addq #1,d0
	moveq #0,d3
	bra skip3
skip2:
	cmpi.b #9,(a0)
	bne skip3
	move.b #32,(a0)
skip3:
	cmpi.b #32,(a0)
	bne notspace
	move.l a0,a1
notspace:
	subq.l #1,d1
	cmpi.l #0,d1
	beq endcountlines
	addq.l #1,a0
	bra loop
endcountlines:
	cmpi.b #10,(a0)
	beq lastlf
	addq #1,d0
lastlf:
	movem.l (sp)+,d2-d5/a2
	rts

	XDEF _smartcountlines

_smartcountlines:
	movem.l d2-d7/a2,-(sp)

	move.l VIEW_FILE_SIZE(a0),d1
	move.l d1,d7
	move.l VIEW_MAX_LINE_LENGTH(a0),d2
	move.l VIEW_TEXT_BUFFER(a0),a0

	moveq #0,d0
	moveq #0,d3
	moveq #0,d4
	move.l d2,d5
	sub.l #10,d5
	moveq #0,d6
	move.l #0,a1
aloop:
	addq #1,d3
	cmp.l d2,d3
	bne askip1
	cmp.l #0,a1
	beq nolastspace1
	move.l a0,a2	
	sub.l a1,a2
	cmp.l d5,a2
	bge nolastspace1
	add.l a2,d1
	move.l a1,a0
nolastspace1:
	move.b #10,(a0)
	sub.l a1,a1
	addq #1,d0
	moveq #0,d3
	bra askip2
askip1:
	cmpi.b #-33,(a0)
	blt aokay
	cmpi.b #-1,(a0)
	ble aishex
	cmpi.b #9,(a0)
	blt aishex
	cmpi.b #14,(a0)
	blt aokay
	cmpi.b #32,(a0)
	blt aishex
	cmpi.b #128,(a0)
	blt aokay
	cmpi.b #160,(a0)
	bge aokay
aishex:
	cmpi.l #6,d7
	blt nomorecheck
	addq #1,d4
	cmpi.l #6,d4
	bge nomorecheck
	cmpi.b #27,(a0)
	bne aokay1
	moveq #1,d6
	bra aokay1
nomorecheck:
	move.l #-1,d0
	movem.l (sp)+,d2-d7/a2
	rts
aokay:
	moveq #0,d4
	cmpi.b #1,d6
	bne aokay1
	cmpi.b #'[',(a0)
	beq isansi
	moveq #0,d6
	bra aokay1
isansi:
	move.l #-2,d0
	movem.l (sp)+,d2-d7/a2
	rts
aokay1:
	cmpi.b #10,(a0)
	bne askip2
	sub.l a1,a1
	addq #1,d0
	moveq #0,d3
askip2:
	cmpi.b #32,(a0)
	bne notspace1
	move.l a0,a1
notspace1:
	subq.l #1,d1
	cmpi.l #0,d1
	beq endsmartcount
	addq.l #1,a0
	bra aloop
endsmartcount:
	cmpi.b #10,(a0)
	beq lastlf1
	addq #1,d0
lastlf1:
	movem.l (sp)+,d2-d7/a2
	rts

	XDEF _ansicountlines

tabsize:
	dc.l 0

_ansicountlines:
	movem.l d2-d7/a2,-(sp)

	move.l VIEW_TAB_SIZE(a0),d0
	move.l d0,tabsize
	move.l VIEW_FILE_SIZE(a0),d1
	move.l VIEW_MAX_LINE_LENGTH(a0),d2
	move.l VIEW_TEXT_BUFFER(a0),a0

	moveq #0,d0
	moveq #0,d3
	move.l d2,d5
	sub.l #10,d5
	moveq #0,d6
	move.l tabsize,d7
	move.l #0,a1

nloop:
	cmpi.b #32,(a0)
	bge notillegal
	cmpi.b #0,(a0)
	blt notillegal
	cmpi.b #9,(a0)
	beq notillegal
	cmpi.b #10,(a0)
	beq notillegal
	cmpi.b #27,(a0)
	beq notillegal

	move.b #' ',(a0)
	bra nottab

notillegal:
	cmpi.b #27,(a0)
	bne notescape
	moveq #1,d6
	bra nnotspace
notescape:
	cmpi.b #1,d6
	bne notansi
	cmpi.b #';',(a0)
	beq nnotspace
	cmpi.b #'[',(a0)
	beq nnotspace
	cmpi.b #'0',(a0)
	blt endansi
	cmpi.b #'9',(a0)
	ble nnotspace
endansi:
	moveq #0,d6
	bra nnotspace

notansi:
	cmpi.b #9,(a0)
	bne nottab
	add.l d7,d3
	move.l tabsize,d7
	bra notnexttab
nottab:
	addq #1,d3
	subq #1,d7
	cmpi.b #0,d7
	bgt notnexttab
	move.l tabsize,d7
notnexttab:
	cmp.l d2,d3
	blt nskip1
	cmp.l #0,a1
	beq nnolastspace
	move.l a0,a2	
	sub.l a1,a2
	cmp.l d5,a2
	bge nnolastspace
	add.l a2,d1
	move.l a1,a0
nnolastspace:
	move.b #10,(a0)
	addq #1,d0
	moveq #0,d3
	moveq #0,d6
	move.l tabsize,d7
	sub.l a1,a1
	bra nskip2
nskip1:
	cmpi.b #10,(a0)
	bne nskip2
	sub.l a1,a1
	addq #1,d0
	moveq #0,d3
	moveq #0,d6
	move.l tabsize,d7
nskip2:
	cmpi.b #32,(a0)
	beq isspace
	cmpi.b #9,(a0)
	bne nnotspace
isspace:
	move.l a0,a1
nnotspace:
	addq.l #1,a0
	subq.l #1,d1
	cmpi.l #0,d1
	bgt nloop
	movem.l (sp)+,d2-d7/a2
	rts

	XDEF _removetabs

_removetabs:
	move.l VIEW_FILE_SIZE(a0),d1
	move.l VIEW_TEXT_BUFFER(a0),a0

	moveq #0,d0
rloop:
	cmpi.b #9,(a0)
	bne rskip
	move.b #' ',(a0)
rskip:
	addq.l #1,a0
	subq.l #1,d1
	cmpi.l #0,d1
	bgt rloop
	rts

	XDEF @filteroff

@filteroff:
	btst.b #1,$bfe001
	bne alreadyon
	bset.b #1,$bfe001
	moveq.l #1,d0
	rts
alreadyon:
	moveq.l #0,d0
	rts

	XDEF @filteron

@filteron:
	bclr.b #1,$bfe001
	rts

	end
