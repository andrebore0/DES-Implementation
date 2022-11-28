#ifndef DESBASE_H
#define DESBASE_H

#include <iostream>
#include <cassert>

typedef unsigned int		ui;		// 32-bit unsigned integer
typedef unsigned long long	ull;	// 64-bit unsigned integer

namespace desbase
{
	constexpr int UI_SIZE	= sizeof(ui) * 8;
	constexpr int ULL_SIZE	= sizeof(ull) * 8;

	int		getBit(ull src, int pos);
	void	setBit(ui& dst, int pos, bool bitState);
	void	setBit(ull& dst, int pos, bool bitState);
}

#endif // DESBASE_H