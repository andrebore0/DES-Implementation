#include "input_handling.h"

bool setArguments(int argc, char** argv)
{
	if (argc < EXPECTED_ARGUMENTS)
	{
		print_usageError(argv[0]);
		return false;
	}
	else if (
		g_arguments.program_function = toLowerCase(argv[1]); // standard C++17
		g_arguments.program_function != "-crypt" && g_arguments.program_function != "-decrypt"
	)
	{
		print_usageError(argv[0]);
		return false;
	}

	g_argumentCount = argc;

	g_arguments.input_string = argv[2];
	g_arguments.key_string = argv[3];

	return true;
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

std::string toLowerCase(std::string str)
{
	constexpr char CASEMASK{ 0b00100000 };

	for (char& elem : str)
	{
		elem = ((elem >= 'A' && elem <= 'Z') || (elem >= 'a' && elem <= 'z')) ? (elem | CASEMASK) : elem;
	}

	return str;
}

