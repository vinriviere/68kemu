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
