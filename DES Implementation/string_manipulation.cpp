#include "string_manipulation.h"

std::string ui64ToString(ui64 input, std::ios_base& (*ui64_format)(std::ios_base&))
{
	return (std::ostringstream{} << ui64_format << input).str();
}

ui64 stringToUi64(const std::string& str, std::ios_base& (*string_format)(std::ios_base&))
{
	ui64 output{};
	static_cast<std::istringstream>(str) >> string_format >> output;

	return output;
}

bool compareStringCase(std::string_view str1, std::string_view str2)
{
	return strcmp(toLowerCase(str1.data()).c_str(), toLowerCase(str2.data()).c_str());
}

std::string toLowerCase(std::string str)
{
	std::ranges::for_each(str, [](unsigned char c) { return std::tolower(c); });

	return str;
}

ui64 asciiToUi64(std::string& str)
{
	while (str.length() > ui64_size / byte) // trimming
	{
		str.pop_back();
	}

	while (str.length() < ui64_size / byte) // padding
	{
		str += '\0';
	}

	ui64 temp{};

	for (int i{}; i < ui64_size / byte; ++i) // (string)input -> (unsigned long long)input
	{
		temp <<= byte;	// 0x00001234 -> 0x12340000
		temp |= str[i];	// input char estratto nel byte liberato
	}

	return temp;
}