#ifndef _DEBUG

#include "release_input_handling.h"

Status setArguments(int argc, char** argv)
{
	if (argc < EXPECTED_ARGUMENTS || (toLowerCase(argv[1]) != "-crypt" && toLowerCase(argv[1]) != "-decrypt"))
	{
		print_usageError((argv[0]) ? argv[0] : "");
		return error_arguments;
	}

	g_argumentCount = argc;

	g_arguments.at(0) = toLowerCase(argv[1]);
	g_arguments.at(1) = argv[2];
	g_arguments.at(2) = argv[3];
}

void print_usageError(const char* argv_zero)
{
	if (argv_zero)
	{
		std::string arg0 = argv_zero;

		std::ranges::reverse(arg0); // reverse della directory

		auto pos = std::distance(arg0.begin(), std::ranges::find(arg0, '\\')); // trova il primo '\'

		arg0 = arg0.substr(0, pos); // substringa che va dal nome del programma al primo '\' trovato

		std::ranges::reverse(arg0); // ora il nome al contrario torna "dritto"

		std::cout << "Utilizzo: " << arg0 << " <input> <chiave> -crypt|-decrypt";
	}
	else
	{
		std::cout << "Utilizzo: <nome_programma> <input> <chiave> -crypt|-decrypt";
	}
}

#endif