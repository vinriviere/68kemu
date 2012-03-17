/*
  asm.S
  Written in 2010-2012 by Vincent Riviere <vincent.riviere@freesbee.fr>

  This file is part of:
  68Kemu - A CPU emulator for Atari TOS computers
  http://vincent.riviere.free.fr/soft/68kemu/

  To the extent possible under law, the author(s) have dedicated all copyright
  and related and neighboring rights to this software to the public domain
  worldwide. This software is distributed without any warranty.

  You should have received a copy of the CC0 Public Domain Dedication along
  with this software.
  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

/*
  This file contains code which will run on the emulated CPU.
*/

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
