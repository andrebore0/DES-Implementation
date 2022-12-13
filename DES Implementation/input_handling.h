#ifndef _DEBUG
#ifndef _INPUT_HANDLING_
#define _INPUT_HANDLING_

#include <iostream>
#include <string>
#include <algorithm>
#include <ranges>
#include "arguments.h"

constexpr int EXPECTED_ARGUMENTS{ 4 };

bool		setArguments		(int argc, char** argv);
void		print_usageError	(const char* argv_zero);
std::string	toLowerCase			(std::string str);

#endif // _INPUT_HANDLING_
#endif // _DEBUG
