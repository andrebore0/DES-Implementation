#include "bitmanipulation.h"

namespace bitmanipulation
{
	bool getBit(ui64 src, int pos) // estrae un bit da un numero intero(max 64-bit)
	{
		assert(
			(pos - 1) < sizeof(ui64) || (pos - 1) >= 0
			&&
			"\'pos\' out of range in \'getBit(auto, int)\'."
		);

		return static_cast<bool>(src << ((sizeof(ui64) - 1) - (pos - 1))) >> ((sizeof(ui64) - 1));
	}

	void setBit(auto& dst, int pos, bool bitState) // setta un bit
	{
		assert(
			(pos < sizeof(dst) || pos >= 0)
			&&
			"\'pos\' out of range in \'setBit(auto&, int, bool)\'."
		);

		constexpr auto mask{
			(sizeof(dst) == sizeof(ui64)) ? 1Ui64 << pos :
			(sizeof(dst) == sizeof(ui32)) ? 1Ui32 << pos :
			(sizeof(dst) == sizeof(ui16)) ? 1Ui16 << pos :
			(sizeof(dst) == sizeof(ui8)) ? 1Ui8 << pos : UINT64_MAX
		};

		std::cout << sizeof(mask) << '\n';

		assert(
			mask != UINT64_MAX
			&&
			"fatal error: (\'mask\' == \'UINT64_MAX\') in \'void setBit(auto& dst, int pos, bool bitState)\'"
		);

		// OR bitwise "accende" i bit "accesi" nella maschera
		// AND bitwise "spegne" i bit "spenti" nella maschera
		// implementati nella riga successiva con l'operatore ternario
		dst = (bitState) ? (dst ^ mask) : (dst & ~mask);
	}
}