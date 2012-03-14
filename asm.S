	.cpu 68000

// 0(sp).l = ret pc
// 4(sp).w = 0x26
// 6(sp).l = callback
        .global _SupexecImpl
_SupexecImpl:
        movem.l  d3-d7/a3-a6,-(sp)

        move.l  #1,-(sp)
        move.w  #0x20,-(sp)
        trap    #1
        addq.l  #6,sp
        
        move.w  d0,d3
        jbne    super
      
        move.l  sp,a3
        clr.l   -(sp)
        move.w  #0x20,-(sp)
        trap    #1
        move.l  a3,sp

        move.l  d0,a3           // old_ssp
super:
        move.l  42(sp),a0
        movem.l d3/a3,-(sp)
/*
	move.l	a0,-(sp)
	move.l	#format,-(sp)
	jbsr	_printf
	addq.l	#8,sp
*/
        jsr     (a0)
        movem.l (sp)+,d3/a3

        tst.w   d3
        jbne    endf

        movem.l d0/a4,-(sp)
		move.l	sp,a4
        move.l  a3,-(sp)
        move.w  #0x20,-(sp)
        trap    #1
		move.l	a4,sp
        movem.l (sp)+,d0/a4

endf:
        movem.l  (sp)+,d3-d7/a3-a6
        rts
/*
format:
	.asciz "a0 = 0x%08lx\n"
*/
