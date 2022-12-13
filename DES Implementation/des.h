#ifndef DES_H
#define DES_H

#include <iostream>
#include <string>
#include <array>
#include <map>
#include <intrin.h>
#include "bit_manipulation.h"
#include "input_handling.h"

#define PLACEHOLDER 1

enum Status
{
	error_generic = -1,
	ok,
#ifndef _DEBUG
	error_arguments
#endif
};

enum Des_info
{
	block_size_bits = 64,
	input_size = block_size_bits / (sizeof(char) * byte), // valido sia per input che per chiave
	rounds = 16,

	key_size_PC1 = 56,
	right_key_mask_PC1 = 0x0FFF'FFFF
};

namespace des_data // tutte le matrici e i dati generali sono qui
{
	std::map<int, int> key_shift_table
	{
		{ 0 , 1  },	// 1
		{ 1 , 2  },	// 1
		{ 2 , 4  },	// 2
		{ 3 , 6  },	// 2
		{ 4 , 8  },	// 2
		{ 5 , 10 },	// 2
		{ 6 , 12 },	// 2
		{ 7 , 14 },	// 2
		{ 8 , 15 },	// 1
		{ 9 , 17 },	// 2
		{ 10, 19 },	// 2
		{ 11, 21 },	// 2
		{ 12, 23 },	// 2
		{ 13, 25 },	// 2
		{ 14, 27 },	// 2
		{ 15, 28 }	// 1
	};

	constexpr std::array INITIAL_PERM_MATRIX // 64
	{
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9 , 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7
	};

	constexpr std::array FINAL_PERM_MATRIX // 64
	{
		PLACEHOLDER
	};

	constexpr std::array KEY_SCHEDULER_PC_1 // 56
	{
		57, 49, 41, 33, 25, 17, 9 , 1 ,
		58, 50, 42, 34, 26, 18, 10, 2 ,
		59, 51, 43, 35, 27, 19, 11, 3 ,
		60, 52, 44, 36, 63, 55, 47, 39,
		31, 23, 15, 7 , 62, 54, 46, 38,
		30, 22, 14, 6 , 61, 53, 45, 37,
		29, 21, 13, 5 , 28, 20, 12, 4
	};
}

/* Forward Declarations / Firme */
Status		des_main			();
ui64		des_decrypt			(ui64 input, ui64 key);
ui64		des_crypt			(ui64 input, ui64 key);
ui64		stringToULL			(std::string& str);

template <bit_manipulation::UnsignedInteger T, std::size_t size>
void		permute				(T& input, const std::array<int, size>& matrix);

void		key_schedule(ui64 key, std::array<ui64, 16>& dst);
void		do_round			();

#ifdef _DEBUG
template <bit_manipulation::UnsignedInteger T>
void		printBits			(T input, std::string str = "bits", int startPos = 0, int separatorPos = 8);
#endif // _DEBUG
/* ---------------------------- */
#endif // DES_H