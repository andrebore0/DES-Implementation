#ifndef _INPUT_HANDLING_
#define _INPUT_HANDLING_

#include <iostream>
#include <array>
#include <algorithm>
#include <ranges>
#include <string>
#include <string_view>
#include "string_manipulation.h"

class ArgumentsException
{
private:
	std::string m_error{};

public:
	ArgumentsException(std::string_view error) : m_error{error}
	{
	}

	const std::string& getError() const
	{
		return m_error;
	}
};

enum ProgramFunction
{
	program_function_undefined = -1,
	encrypt,
	decrypt
};

enum InputType
{
	input_type_undefined = -1,
	hexadecimal,
	string
};

struct Arguments
{
	ProgramFunction	program_function	{ program_function_undefined };	// argv[1]
	InputType		input_type			{ input_type_undefined };		// argv[2]

	std::string		input_string		{};	// argv[3]
	std::string		key_string			{};	// argv[4]
};

constexpr int EXPECTED_ARGUMENTS{ 5 };

namespace accepted_input
{
	constexpr std::array<std::string_view, 3> HEX{ "h", "hex", "hexadecimal" };
	constexpr std::array<std::string_view, 3> STR{ "s", "str", "string" };

	constexpr std::array<std::string_view, 2> ENCRYPT{ "e", "encrypt" };
	constexpr std::array<std::string_view, 2> DECRYPT{ "d", "decrypt" };
}

void				setInput				(int argc, char** argv, Arguments& dst);
void				printUsageError			(const char* argv_zero);
void				getInputManually		(Arguments& dst);
InputType			checkInputType			(std::string_view str);
ProgramFunction		checkProgramFunction	(std::string_view str);

std::vector<ui64>	inputToBlocks			(std::string input, InputType type);

#endif // _INPUT_HANDLING_