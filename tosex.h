#ifndef __INCLUDE_TOSEX_H__
#define __INCLUDE_TOSEX_H__

static __inline__
long SuperInquire()
{
	register long retvalue __asm__("d0");

	__asm__ volatile
	(
		"move.l #1,-(%%sp)\n\t"
		"move.w #0x20,-(%%sp)\n\t"
		"trap #1\n\t"
		"addq.l #6,%%sp"
		: "=r"(retvalue)				/* outputs */
	:								/* inputs  */
	: "d1", "d2", "a0", "a1", "a2"	/* clobbered regs */
	);

	return retvalue;
}

static __inline__
void* SuperFromUser()
{
	register long retvalue __asm__("d0");

	__asm__ volatile
	(
		"clr.l -(%%sp)\n\t"
		"move.w #0x20,-(%%sp)\n\t"
		"trap #1\n\t"
		"addq.l #6,%%sp"
		: "=r"(retvalue)				/* outputs */
	:								/* inputs  */
	: "d1", "d2", "a0", "a1", "a2"	/* clobbered regs */
	);

	return (void*)retvalue;
}

static  __inline__
void SuperToUser(void* ssp)
{
	register long spbackup;

	__asm__ volatile
	(
		"move.l sp,%0\n\t"
		"move.l %1,-(%%sp)\n\t"
		"move.w #0x20,-(%%sp)\n\t"
		"trap #1\n\t"
		"move.l %0,sp"
	: "=&r"(spbackup)						/* outputs */
	: "g"(ssp)								/* inputs  */
	: "d0", "d1", "d2", "a0", "a1", "a2"	/* clobbered regs */
	);
}

#endif /* __INCLUDE_TOSEX_H__ */
