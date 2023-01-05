#ifndef _BIT_MANIPULATION_H_
#define _BIT_MANIPULATION_H_

#include <iostream>
#include <stdint.h>
#include <concepts> // per ::std::unsigned_integral

#if !defined (_DEBUG) && !defined (NDEBUG)
#define NDEBUG
#endif

#include <cassert> // NDEBUG serve qui.

typedef std::uint8_t	ui8;	// intero a 8-bit senza segno
typedef std::uint16_t	ui16;	// intero a 16-bit senza segno
typedef std::uint32_t	ui32;	// intero a 32-bit senza segno
typedef std::uint64_t	ui64;	// intero a 64-bit senza segno

enum Sizes : ui64
{
	byte = 8,

	ui8_size	= byte,
	ui16_size	= 2 * ui8_size,
	ui32_size	= 2 * ui16_size,
	ui64_size	= 2 * ui32_size,

	ui8_mask	= 0xFF,
	ui16_mask	= 0xFFFF,
	ui32_mask	= 0xFFFF'FFFF,
	ui64_mask	= 0xFFFF'FFFF'FFFF'FFFF
};

namespace bit_manipulation
{
	/*\
	 *	ritorna il bit di 'src' nella posizione indicata da 'pos'
	 *	{ 0 <= pos < ui64_size }
	\*/
	bool getBit(ui64 src, std::size_t pos); // non c'è necessità di usare template qui, ritorna sempre 0 o 1.

	/*\
	 *	ritorna il byte di 'src' nella posizione indicata da 'pos'
	 *	{ 0 <= pos <= sizeof(_Ui) }
	\*/
	template <std::unsigned_integral _Ui>
	ui8 getByte(_Ui src, std::size_t pos)
	{
		assert(
			(pos <= sizeof(_Ui))
			&&
			"\'pos\' out of range in \'getByte(_Ui, std::size_t)\'."
		);

		return (src >> (sizeof(_Ui) * byte) - (byte * (pos + 1))) & ui8_mask;
	}

	/*\
	 *	imposta il bit alla posizione 'pos' di 'src' a 'bitState'
	 *	{ 0 <= pos < sizeof(_Ui) * byte }
	\*/
	template <std::unsigned_integral _Ui>
	void setBit(_Ui& dst, std::size_t pos, bool bitState) // qui serve usare un template per mantenere la lunghezza dell'argomento
	{
		assert(
			(pos < (sizeof(_Ui) * byte))
			&&
			"\'pos\' out of range in \'setBit(_Ui&, int, bool)\'."
		);

		const _Ui mask{ static_cast<_Ui>(static_cast<ui64>(1) << pos) };

		// OR bitwise "accende" i bit "accesi" nella maschera
		// AND bitwise "spegne" i bit "spenti" nella maschera
		// implementati nella riga successiva con l'operatore ternario
		dst = (bitState) ? (dst | mask) : (dst & ~mask);
	}

	/*\
	 *	esegue lo shift dei bit di 'dst' di 'pos' posizioni.
	 *	oltre il limite 'leftBound' i bit ruotano e tornano all'inzio.
	 *	la direzione dipende da 'shiftLeft', di default a 'true'.
	 *	{ 0 <= pos < sizeof(_Ui) * byte }
	\*/
	template <std::unsigned_integral _Ui>
	void rotateBits(_Ui& dst, std::size_t pos, std::size_t leftBound = (sizeof(_Ui) * byte) - 1, bool shiftLeft = true)
	{
		assert( // mi assicuro che leftBound non sia più grande di quanto possibile dal tipo
			(leftBound < (sizeof(_Ui) * byte))
			&&
			"\'leftBound\' greater than (\'sizeof(_Ui)\' * \'byte\') in \'rotateBits(_Ui&, std::size_t, std::size_t, bool)\'"
		);

		const _Ui _UiMask{ static_cast<_Ui>((static_cast<_Ui>(1u) << leftBound + 1) - 1) }; // maschera di dimensione 'leftbound'

		pos %= leftBound + 1; // assicuro ('pos' <= 'leftBound')

		dst = (shiftLeft) ?
			(dst << pos) | (dst >> (leftBound + 1 - pos)) :
			(dst >> pos) | (dst << (leftBound + 1 - pos));

		dst &= _UiMask; // uso la maschera per tenere solo i bit dentro il range
	}
}

#endif // _BIT_MANIPULATION_H_