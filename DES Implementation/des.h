#ifndef DES_H
#define DES_H

#include <iostream>
#include <string>
#include "des_defs.h"
#include "string_manipulation.h"
#include "input_handling.h"

#ifdef _DEBUG

#include <bitset>
#include <vector>

std::vector<std::string> debug_logs{};
#define _LOG(x) std::cout << x;
#define _PRINTLOGS() std::ranges::for_each(debug_logs, [](std::string_view x){ std::cout << x; });

#else

#define _LOG(x) ;
#define _PRINTLOGS() ;

#endif

/* Forward Declarations / Firme */
Status		des_main			(const Arguments& arguments);
ui64		des_operate			(ui64 input, ui64 key, ProgramFunction f);

template <bit_manipulation::UnsignedInteger _Ui, std::size_t size>
void		permute				(_Ui& input, const std::array<int, size>& matrix, int inputSize = sizeof(_Ui) * byte);

void		key_schedule		(ui64 key, std::array<ui64, rounds>& dst);
ui32		feistel				(ui32 block, ui64 key);

template <bit_manipulation::UnsignedInteger _Ui>
std::string uiBitsToString		(_Ui x, int separatorMultiple = 0, int startPos = 0);
/* ---------------------------- */
#endif // DES_H