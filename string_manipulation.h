#ifndef _STRING_MANIPULATION_H_
#define _STRING_MANIPULATION_H_

#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cstring>
#include "bit_manipulation.h"

std::string	hexUi64ToString		(ui64 input);
ui64		stringBaseToUi64Hex		(const std::string& str);
std::string	toLowerCase			(std::string_view str);
bool		compareString		(std::string_view str, std::string_view possibleValue, bool checkCase = true);

template <std::size_t size>
bool		compareString		(std::string_view str, std::array<std::string_view, size> possibleValues, bool checkCase = true)
{
	auto isEqual{ [str, checkCase](std::string_view value) { return compareString(str, value, checkCase); } };

	return std::ranges::any_of(possibleValues, isEqual);
}

ui64		stringASCIIToUi64			(std::string& str);

template <std::unsigned_integral _Ui>
bool		isUi64Printable		(_Ui input)
{
	for (std::size_t i{}; i < sizeof(_Ui); ++i)
	{
		if (!std::isprint(static_cast<unsigned char>(input & ui8_mask)) && (input & ui8_mask) != 0)
		{
			return false;
		}

		input >>= 8;
	}

	return true;
}

template <std::unsigned_integral _Ui>
std::string	uiToASCIIString		(_Ui input)
{
	std::string output{ "" };

	for (int i{}; i < sizeof(_Ui); ++i)
	{
		char temp = bit_manipulation::getByte(input, i);

		output += temp;
	}

	return output;
}

#endif // _STRING_MANIPULATION_H_