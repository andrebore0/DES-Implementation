#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

#include <iostream>
#include <cassert>
#include <stdint.h>

typedef std::uint8_t	ui8;	// intero a 8-bit senza segno
typedef std::uint16_t	ui16;	// intero a 16-bit senza segno
typedef std::uint32_t	ui32;	// intero a 32-bit senza segno
typedef std::uint64_t	ui64;	// intero a 64-bit senza segno

namespace bitmanipulation
{
	bool	getBit(ui64 src, int pos);
	void	setBit(auto& dst, int pos, bool bitState);
}

#endif // BIT_MANIPULATION_H