#include "bit_manipulation.h"

bool bit_manipulation::getBit(ui64 src, std::size_t pos)
{
	assert( // mi assicuro che la posizione sia valida
		(pos < ui64_size)
		&&
		"\'pos\' out of range in \'getBit(bit_manipulation::ui64, int)\'."
	);

	return (src >> pos) & static_cast<ui64>(1); // bit shifiting e AND per isolare il bit
}

/*\
 *	Le altre definizioni si trovano nel file "bit_manipulation.h".
 *	I template sono gestiti in maniera strana per ora, quindi non posso separare dichiarazione e definizione.
\*/