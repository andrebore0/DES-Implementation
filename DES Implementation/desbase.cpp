#include "desbase.h"

namespace desbase
{
	int getBit(ull src, int pos) // primo bit nella posizione 0
	{
		assert((pos < ULL_SIZE || pos >= 0) && "\'pos\' out of range in \'getBit(ull, int)\'.");

		return ((src << ((ULL_SIZE - 1) - pos)) >> (ULL_SIZE - 1));
	}

	void setBit(ui& dst, int pos, bool bitState) // 32bit
	{
		assert((pos < ULL_SIZE || pos >= 0) && "\'pos\' out of range in \'setBit(ui&, int, bool)\'.");

		const ui mask = static_cast<ui>(1) << pos; // shifto il bit attivo nella posizione che mi serve

		// OR bitwise "accende" i bit "accesi" nella maschera
		// AND bitwise "spegne" i bit "spenti" nella maschera
		// implementati nella riga successiva con l'operatore ternario
		dst = (bitState) ? (dst ^ mask) : (dst & ~mask);
	}

	void setBit(ull& dst, int pos, bool bitState) // 64bit
	{
		assert((pos < ULL_SIZE || pos >= 0) && "\'pos\' out of range in \'setBit(ull&, int, bool)\'.");

		const ull mask = static_cast<ull>(1) << pos; // shifto il bit attivo nella posizione che mi serve

		// OR bitwise "accende" i bit "accesi" nella maschera
		// AND bitwise "spegne" i bit "spenti" nella maschera
		// implementati nella riga successiva con l'operatore ternario
		dst = (bitState) ? (dst ^ mask) : (dst & ~mask);
	}
}