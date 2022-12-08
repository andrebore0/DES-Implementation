#ifndef _DEBUG
#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

#include <string>

struct arguments_container_t
{
	std::string program_function;
	std::string input_string;
	std::string key_string;
};

extern arguments_container_t	g_arguments;
extern int			g_argumentCount;

#endif // _ARGUMENTS_H_
#endif // _DEBUG
