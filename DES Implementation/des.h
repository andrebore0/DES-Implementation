#ifndef DES_H
#define DES_H

#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include "Timer.h"
#include "desbase.h"

enum sizes
{
	byte = 8,
	word = 16
};

namespace des_matrix
{
	int keyCompressor[56] = {
	1 , 2 , 3 , 4 , 5 , 6 , 7 , 9 ,
	10, 11, 12, 13, 14, 15, 17, 18,
	19, 20, 21, 22, 23, 25, 26, 27,
	28, 29, 30, 31, 33, 34, 35, 36,
	37, 38, 39, 41, 42, 43, 44, 45,
	46, 47, 49, 50, 51, 52, 53, 54,
	55, 57, 58, 59, 60, 61, 62, 63,
	};
}

#endif // DES_H