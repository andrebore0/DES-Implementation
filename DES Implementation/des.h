#ifndef DES_H
#define DES_H

#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <algorithm>
#include <ranges>
#include "Timer.h"
#include "bitmanipulation.h"

#define placeholder 1

enum Des_info
{
	rounds = 16,
	input_size = 64 / BYTE, // 64 / sizeof(char)
	key_size = 64 / BYTE // 64 / sizeof(char)
};

constexpr std::array KEYCOMPRESS_MATRIX{ // 56
	1 , 2 , 3 , 4 , 5 , 6 , 7 , 9 ,
	10, 11, 12, 13, 14, 15, 17, 18,
	19, 20, 21, 22, 23, 25, 26, 27,
	28, 29, 30, 31, 33, 34, 35, 36,
	37, 38, 39, 41, 42, 43, 44, 45,
	46, 47, 49, 50, 51, 52, 53, 54,
	55, 57, 58, 59, 60, 61, 62, 63,
};

const std::array INITIAL_PERM_MATRIX{ // 64
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9 , 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

const std::array FINAL_PERM_MATRIX{ // 64
	placeholder
};

/* Forward Declarations / Firme */
ui64		des_decrypt(ui64 input, ui64 key);
ui64		des_crypt(ui64 input, ui64 key);
ui64		stringToULL(std::string& str);
std::string	toLowerCase(std::string str);
void		print_usageError(const char* argv_zero);

template <std::size_t size>
void		permute(ui64& input, const std::array<int, size>& matrix);

void		key_scheduler(ui64& key);
void		do_round();
/* ---------------------------- */

#endif // DES_H