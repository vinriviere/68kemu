/*
  m68kinl.h
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

#ifndef __INC_M68KINL_H__
#define __INC_M68KINL_H__

INLINE unsigned int m68k_read_memory_8(unsigned int address)
{
	return *(unsigned char*)address;
}

INLINE unsigned int m68k_read_memory_16(unsigned int address)
{
	return *(unsigned short*)address;
}

INLINE unsigned int m68k_read_memory_32(unsigned int address)
{
	return *(unsigned long*)address;
}

INLINE unsigned int m68k_read_disassembler_8(unsigned int address)
{
	return *(unsigned char*)address;
}

INLINE unsigned int m68k_read_disassembler_16 (unsigned int address)
{
	return *(unsigned short*)address;
}

INLINE unsigned int m68k_read_disassembler_32 (unsigned int address)
{
	return *(unsigned long*)address;
}

INLINE void m68k_write_memory_8(unsigned int address, unsigned int value)
{
	*(unsigned char*)address = (char)value;
}

INLINE void m68k_write_memory_16(unsigned int address, unsigned int value)
{
	*(unsigned short*)address = (short)value;
}

INLINE void m68k_write_memory_32(unsigned int address, unsigned int value)
{
	*(unsigned long*)address = (long)value;
}

#endif /* __INC_M68KINL_H__ */
