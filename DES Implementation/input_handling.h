#ifndef _INPUT_HANDLING_
#define _INPUT_HANDLING_

#include <iostream>
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
	crypt,
	decrypt
};

enum InputType
{
	input_type_undefined = -1,
	hexadecimal,
	decimal,
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

void				setInput				(int argc, char** argv, Arguments& dst);
void				print_usageError		(const char* argv_zero);
void				getInputManually		(Arguments& dst);
InputType			checkInputType			(std::string_view str);
ProgramFunction		checkProgramFunction	(std::string_view str);


#endif // _INPUT_HANDLING_