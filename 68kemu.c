#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <m68k.h>
#include <m68kcpu.h>
#include <mint/osbind.h>
#include <mint/basepage.h>
#include "tosex.h"

static void* old_ssp_real;

static void* BothSuperFromUser(void* new_ssp_emu)
{
	unsigned short sr;
	void* old_ssp_emu;

	// Switch the real CPU to supervisor mode
	old_ssp_real = (void *)SuperFromUser();

	// Switch the emulated CPU to supervisor mode
	if (new_ssp_emu == NULL)
		new_ssp_emu = (void*)m68k_get_reg(NULL, M68K_REG_SP);

	sr = (unsigned short)m68k_get_reg(NULL, M68K_REG_SR);
	sr |= 0x2000;
	m68k_set_reg(M68K_REG_SR, sr);

	old_ssp_emu = (void*)m68k_get_reg(NULL, M68K_REG_SP);
	m68k_set_reg(M68K_REG_SP, (int)new_ssp_emu);
	m68k_set_reg(M68K_REG_D0, (int)old_ssp_emu);
	
	return old_ssp_emu;
}

static void BothSuperToUser(void* old_ssp_emu)
{
	unsigned short sr;

	// Switch the real CPU to user mode
	SuperToUser(old_ssp_real);

	m68k_set_reg(M68K_REG_SP, (int)old_ssp_emu);

	sr = (unsigned short)m68k_get_reg(NULL, M68K_REG_SR);
	sr &= ~0x2000;
	m68k_set_reg(M68K_REG_SR, sr);

	m68k_set_reg(M68K_REG_D0, (int)0);
}

void m68ki_hook_trap1()
{
	unsigned short* sp = (unsigned short *)m68k_get_reg(NULL, M68K_REG_SP);
	unsigned short num = *sp;

	//printf("GEMDOS(0x%02x)\n", num);

	if (num == 0x20)
	{
		void* param = *(void**)(sp + 1);
		//printf("Super(0x%08lx)\n", (long)param);
		
		if (param != (void*)1)
		{
			long current_super = SuperInquire();
			if (current_super)
			{
				BothSuperToUser(param);
				return;
			}
			else /* current user */
			{
				BothSuperFromUser(param);
				return;
			}
		}
	}

	// Standard block
	{
		register long reg_d0 __asm__("d0");

		__asm__ volatile
		(
			"move.l	sp,a3\n\t"
			"move.l	%1,sp\n\t"
			"trap	#1\n\t"
			"move.l	a3,sp"
		: "=r"(reg_d0)			/* outputs */
		: "g"(sp)
		: "d1", "d2", "a0", "a1", "a2", "a3", "memory"    /* clobbered regs */
		);
		
		m68k_set_reg(M68K_REG_D0, (int)reg_d0);
	}
}

void m68ki_hook_trap2()
{
	void* sp = (void*)m68k_get_reg(NULL, M68K_REG_SP);
	unsigned long ad0 = (unsigned long)m68k_get_reg(NULL, M68K_REG_D0);
	unsigned long ad1 = (unsigned long)m68k_get_reg(NULL, M68K_REG_D1);

	//printf("GEM\n");
	__asm__ volatile
	(
		"move.l	sp,a3\n\t"
		"move.l	%1,d0\n\t"
		"move.l	%2,d1\n\t"
		"move.l	%0,sp\n\t"
		"trap	#2\n\t"
		"move.l	a3,sp"
	: 			/* outputs */
	: "g"(sp), "g"(ad0), "g"(ad1)
	: "d0", "d1", "d2", "a0", "a1", "a2", "a3", "memory"    /* clobbered regs */
	);
}

void m68ki_hook_trap13()
{
	unsigned short* sp = (unsigned short *)m68k_get_reg(NULL, M68K_REG_SP);
	//unsigned short num = *sp;
	register long reg_d0 __asm__("d0");

	//printf("BIOS(0x%02x)\n", num);

	__asm__ volatile
	(
		"move.l	sp,a3\n\t"
		"move.l	%1,sp\n\t"
		"trap	#13\n\t"
		"move.l	a3,sp"
	: "=r"(reg_d0)			/* outputs */
	: "g"(sp)
	: "d1", "d2", "a0", "a1", "a2", "a3", "memory"    /* clobbered regs */
	);
	
	m68k_set_reg(M68K_REG_D0, (int)reg_d0);
}

typedef void VOIDFUNC(void);
/*
VOIDFUNC* nextCallback = NULL;

// This callback is called from the real CPU
void generic_callback(void)
{
	if (nextCallback == NULL)
		abort();

	// TODO
}
*/

typedef unsigned long SUPEXEC_CALLBACK_TYPE(void);
typedef unsigned long SUPEXEC_TYPE(SUPEXEC_CALLBACK_TYPE* f);
/*
static unsigned long RunEmulatedFunction(SUPEXEC_TYPE* f, SUPEXEC_CALLBACK_TYPE* param)
{
	return f(param);
}
*/
//unsigned long SupexecImpl(SUPEXEC_CALLBACK_TYPE* f);
void SupexecImpl(void);

/*
// This function is run on the emulated CPU
unsigned long SupexecImpl(SUPEXEC_CALLBACK_TYPE* f)
{
	long from_super = SuperInquire();
	void* old_ssp;
	unsigned long ret;

	if (!from_super)
		old_ssp = SuperFromUser();

	ret = f();

	if (!from_super)
		SuperToUser(old_ssp);
		
	return ret;
}
*/
void m68ki_hook_trap14()
{
	unsigned char* sp = (unsigned char *)m68k_get_reg(NULL, M68K_REG_SP);
	unsigned short num = *(unsigned short*)sp;
	register long reg_d0 __asm__("d0");

	//printf("XBIOS(0x%02x)\n", num);

	if (num == 0x26)
	{
		//SUPEXEC_CALLBACK_TYPE* pCallback = *(SUPEXEC_CALLBACK_TYPE**)(sp + 2);
		//unsigned long ret;
		unsigned long* sp;
		void* pc;

		//printf("Supexec(0x%08lx)\n", (unsigned long)pCallback);
		//ret = RunEmulatedFunction(SupexecImpl, pCallback);
		//m68k_set_reg(M68K_REG_D0, (int)ret);
		pc = (void*)m68k_get_reg(NULL, M68K_REG_PC);
		//printf("*pc = 0x%04x\n", *(((unsigned short*)pc)-1));
		//return;
		sp = (unsigned long*)m68k_get_reg(NULL, M68K_REG_SP);
		*--sp = (unsigned long)pc;
		m68k_set_reg(M68K_REG_SP, (int)sp);
		m68k_set_reg(M68K_REG_PC, (int)SupexecImpl);
		return;
	}
	
	__asm__ volatile
	(
		"move.l	sp,a3\n\t"
		"move.l	%1,sp\n\t"
		"trap	#14\n\t"
		"move.l	a3,sp"
	: "=r"(reg_d0)			/* outputs */
	: "g"(sp)
	: "d1", "d2", "a0", "a1", "a2", "a3", "memory"    /* clobbered regs */
	);
	
	//nextCallback = NULL;
	
	m68k_set_reg(M68K_REG_D0, (int)reg_d0);
}

static int int_ack_callback_vector = M68K_INT_ACK_AUTOVECTOR;

// Exception vector callback
int int_ack_callback(int int_level)
{
	return int_ack_callback_vector;
}

unsigned char systack[64*1024];

void buildCommandTail(char tail[128], char* argv[], int argc)
{
	int i;
	
	tail[1] = '\0';
	for (i = 0; i < argc; ++i)
	{
		if (i > 0)
			strcat(tail + 1, " ");
			
		strcat(tail + 1, argv[i]);
	}
	
	tail[0] = (char)strlen(tail + 1);
}

int main(int argc, char* argv[])
{
	BASEPAGE* bp;
	unsigned long* pStack;

	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <program.tos> [arguments...]\n", argv[0]);
		return 1;
	}

	char tail[128];
	buildCommandTail(tail, argv + 2, argc - 2);
	bp = (BASEPAGE*)Pexec(PE_LOAD, argv[1], tail, NULL);
	if ((long)bp < 0)
	{
		fprintf(stderr, "error: cannot load %s.\n", argv[1]);
		return 1;
	}

	m68k_set_cpu_type(M68K_CPU_TYPE_68020);
	m68k_pulse_reset(); // Patched
	//m68k_set_int_ack_callback(int_ack_callback);
	
	pStack = (unsigned long*)bp->p_hitpa;
	*--pStack = (unsigned long)bp;
	*--pStack = (unsigned long)0;
	
	m68k_set_reg(M68K_REG_SP, (int)(systack + 1));
	m68k_set_reg(M68K_REG_SR, 0x0300);
	m68k_set_reg(M68K_REG_SP, (int)pStack);
	m68k_set_reg(M68K_REG_PC, (int)bp->p_tbase);

	for (;;)
	{
		m68k_execute(10000);
	}
	
	return 0;
}
