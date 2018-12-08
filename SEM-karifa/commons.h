/*
 * commons.h
 *
 * Created: 2017. 10. 04. 21:15:34
 *  Author: Balazs
 */ 


#ifndef COMMONS_H_
#define COMMONS_H_

#include <stdint.h>

// Alap típusok definiálása.
typedef uint8_t			byte;
typedef int8_t			sbyte;
typedef uint16_t		word;
typedef uint32_t		dword;

// Regiszter kezelõ függvények.
static inline dword bv(byte bit)
{
	return 1 << bit;
}

static inline void bit_set(volatile byte *reg, byte bit)
{
	*reg |= bv(bit);
}

static inline void bit_clr(volatile byte *reg, byte bit)
{
	*reg &= ~bv(bit);
}

static inline void bit_tgl(volatile byte *reg, byte bit)
{
	*reg ^= bv(bit);
}

static inline dword bit_get(volatile byte *reg, byte bit)
{
	return *reg & bv(bit);
}

static inline void bit_wrt(byte val,volatile  byte *reg, byte bit)
{
	val ? bit_set(reg, bit) : bit_clr(reg, bit);
}

// NOP: No Operation.
static inline void _nop()
{
	asm volatile ("nop");
}


#endif /* COMMONS_H_ */