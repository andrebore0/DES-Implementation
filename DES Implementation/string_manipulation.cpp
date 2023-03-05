#include "string_manipulation.h"

std::string hexUi64ToString(ui64 input)
{
	return (std::ostringstream{} << std::hex << input).str();
}

ui64 stringBaseToUi64Hex(const std::string& str)
{
	ui64 output{};
	static_cast<std::istringstream>(str) >> std::hex >> output;

	return output;
}

std::string toLowerCase(std::string_view str)
{
	std::string output;

	std::ranges::transform(
		str, // da str
		std::back_inserter(output), // a output
		[](unsigned char c) { return std::tolower(c); } // ogni char convertito in minuscolo
	);

	return output;
}

bool compareString(std::string_view str, std::string_view possibleValue, bool checkCase)
{
	return (checkCase) ? str == possibleValue : toLowerCase(str) == toLowerCase(possibleValue);
}

ui64 stringASCIIToUi64(std::string& str)
{
	while (str.length() > ui64_size / byte) // trimming
	{
		str.pop_back();
	}

	ui64 temp{};

	for (int i{}; i < ui64_size / byte; ++i) // (string)input -> (unsigned long long)input
	{
		temp <<= byte;	// 0x00001234 -> 0x12340000
		temp |= (i < str.length()) ? str[i] : '\0';	// input char estratto nel byte liberato
	}

	return temp;
}