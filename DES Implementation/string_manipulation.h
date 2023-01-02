#ifndef _STRING_MANIPULATION_H_
#define _STRING_MANIPULATION_H_

#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cstring>
#include "bit_manipulation.h"

#ifndef _MSC_VER // _strcmpi non è standard, è implementata in MSVC++ ma non in g++
#define _strcmpi compareStringCase
#endif

std::string	ui64ToString		(ui64 input, std::ios_base& (*ui64_format)(std::ios_base&) = std::dec);
ui64		stringToUi64		(const std::string& str, std::ios_base& (*string_format)(std::ios_base&));
bool		compareStringCase	(std::string_view str1, std::string_view str2);
std::string	toLowerCase			(std::string str);
ui64		asciiToUi64			(std::string& str);

template <bit_manipulation::UnsignedInteger _Ui>
bool		isUi64Printable		(_Ui input)
{
	for (std::size_t i{}; i < sizeof(_Ui); ++i)
	{
		if (!std::isprint(static_cast<unsigned char>(input & ui8_mask)))
		{
			return false;
		}

		input >>= 8;
	}

	return true;
}

template <bit_manipulation::UnsignedInteger _Ui>
std::string	uiToASCIIString		(_Ui x)
{
	std::string output{ "" };

	for (int i{}; i < sizeof(_Ui); ++i)
	{
		char temp = bit_manipulation::getByte(x, i);

		output += temp;
	}

	return output;
}

#endif // _STRING_MANIPULATION_H_