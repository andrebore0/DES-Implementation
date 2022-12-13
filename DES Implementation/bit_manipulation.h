#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

#include <iostream>
#include <cassert>
#include <stdint.h>

typedef std::uint8_t	ui8;	// intero a 8-bit senza segno
typedef std::uint16_t	ui16;	// intero a 16-bit senza segno
typedef std::uint32_t	ui32;	// intero a 32-bit senza segno
typedef std::uint64_t	ui64;	// intero a 64-bit senza segno

enum Sizes // evito "numeri magici"
{
	byte = 8,
	ui8_size = sizeof(ui8) * byte,
	ui16_size = sizeof(ui16) * byte,
	ui32_size = sizeof(ui32) * byte,
	ui64_size = sizeof(ui64) * byte
};

namespace bit_manipulation
{
	template <typename T>
	concept UnsignedInteger = std::is_unsigned_v<T>; // definisce un numero intero unsigned

	/*\
	 *	ritorna il bit di 'src' nella posizione indicata da 'pos'
	 *	{ 0 <= pos < sizeof(ui64) }
	\*/
	bool getBit(ui64 src, int pos) // non c'è necessità di fare template qui, ritorna sempre 0 o 1.
	{
		assert( // mi assicuro che la posizione sia valida
			(pos >= 0 && pos < ui64_size)
			&&
			"\'pos\' out of range in \'getBit(bit_manipulation::ui64, int)\'."
		);

		return (src >> pos) & 1u; // bit shifiting e AND per isolare il bit
	}

	/*\
	 *	imposta il bit alla posizione 'pos' di 'src' a 'bitState'
	 *	{ 0 <= pos < sizeof(T) * byte }
	\*/
	template <UnsignedInteger T>
	void setBit(T& dst, int pos, bool bitState) // qui serve usare un template per mantenere la lunghezza dell'argomento
	{
		assert(
			(pos >= 0 && pos < (sizeof(T) * byte))
			&&
			"\'pos\' out of range in \'setBit(T&, int, bool)\'."
		);

		const T mask{ static_cast<T>(1Ui64 << pos) };

		// OR bitwise "accende" i bit "accesi" nella maschera
		// AND bitwise "spegne" i bit "spenti" nella maschera
		// implementati nella riga successiva con l'operatore ternario
		dst = (bitState) ? (dst | mask) : (dst & ~mask);
	}

	template <UnsignedInteger T>
	void circularShift(T& dst, int pos, int leftBound = (sizeof(T) * byte) - 1, bool shiftLeft = true)
	{
		assert(
			(pos >= 0 && pos <= leftBound)
			&&
			"\'pos\' out of range in \'circularShift(T&, int, bool, int)\'."
		);

		int temp{};

		if (shiftLeft)
		{
			for (int i{}; i < pos; ++i)
			{
				temp = getBit(dst, leftBound);

				dst <<= 1;

				if (leftBound != (sizeof(T) * byte) - 1)
				{
					setBit(dst, leftBound + 1, 0);
				}
				
				setBit(dst, 0, temp);
			}
		}
		else
		{
			for (int i{}; i < pos; ++i)
			{
				temp = getBit(dst, 0);

				dst >>= 1;

				setBit(dst, leftBound, temp);
			}
		}
	}
}

#endif // BIT_MANIPULATION_H