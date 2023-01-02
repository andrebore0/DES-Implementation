#include "input_handling.h"

void setInput(int argc, char** argv, Arguments& dst) // imposto gli argomenti da qui
{
	if (argc <= 1)
	{
		getInputManually(dst);
		return;
	}
	else if (argc > 1 && argc < EXPECTED_ARGUMENTS)
	{
		throw ArgumentsException{ "Numero di argomenti insufficiente." };
	}
	
	std::string program_function_str = argv[1];
	std::string input_type_str = argv[2];

	dst.input_type			= checkInputType(input_type_str.substr(1, input_type_str.length() - 1));
	dst.program_function	= checkProgramFunction(program_function_str.substr(1, program_function_str.length() - 1));
	
	if (dst.input_type == input_type_undefined || dst.program_function == program_function_undefined)
	{
		throw ArgumentsException{ "\'program_funcion\' o \'input_type\' non sono stati impostati correttamente." };
	}
	
	dst.input_string	= argv[3];
	dst.key_string		= argv[4];
}

void getInputManually(Arguments& dst)
{
	/* Tipo di input */
	std::cout << "Tipi di input accettati: (hex|hexadecimal|h) | (dec|decimal|d) | (str|string|s)\n\n";
	std::cout << "Inserire tipo di input: ";
	std::string input_type_str;
	std::getline(std::cin >> std::ws, input_type_str);

	while (
		_strcmpi(input_type_str.c_str(), "hex") && _strcmpi(input_type_str.c_str(), "hexadecimal") && _strcmpi(input_type_str.c_str(), "h") &&
		_strcmpi(input_type_str.c_str(), "dec") && _strcmpi(input_type_str.c_str(), "decimal") && _strcmpi(input_type_str.c_str(), "d") &&
		_strcmpi(input_type_str.c_str(), "str") && _strcmpi(input_type_str.c_str(), "string") && _strcmpi(input_type_str.c_str(), "s")
	)
	{
		std::cout << "Errore:\nTipi di input accettati: (hex|hexadecimal|h) | (dec|decimal|d) | (str|string|s)\n\n";

		std::cout << "Inserire tipo di input: ";
		std::getline(std::cin >> std::ws, input_type_str);
	}
	/* ------------- */

	/* Tipo di funzione */
	std::cout << "Tipi di funzione accettati: (crypt|c) | (decrypt|d)\n\n";
	std::cout << "Inserire tipo di funzione: ";
	std::string program_function_str;
	std::getline(std::cin >> std::ws, program_function_str);

	while (
		_strcmpi(program_function_str.c_str(), "crypt") && _strcmpi(program_function_str.c_str(), "c") &&
		_strcmpi(program_function_str.c_str(), "decrypt") && _strcmpi(program_function_str.c_str(), "d")
		)
	{
		std::cout << "Errore:\nTipi di funzione accettati: (crypt|c) | (decrypt|d)\n\n";

		std::cout << "Inserire tipo di funzione: ";
		std::getline(std::cin >> std::ws, program_function_str);
	}
	/* ---------------- */

	/* Imposto argomenti */
	dst.input_type			= checkInputType(input_type_str);
	dst.program_function	= checkProgramFunction(program_function_str);
	/* ----------------- */

	/* Input */
	std::cout << "Inserire input: ";
	std::getline(std::cin >> std::ws, dst.input_string);

	std::cout << "Inserire chiave: ";
	std::getline(std::cin >> std::ws, dst.key_string);
	/* ----- */
}

InputType checkInputType(std::string_view str)
{
	if (!_strcmpi(str.data(), "hex") ||
		!_strcmpi(str.data(), "hexadecimal") ||
		!_strcmpi(str.data(), "h"))
	{
		return hexadecimal;
	}
	if (!_strcmpi(str.data(), "dec") ||
		!_strcmpi(str.data(), "decimal") ||
		!_strcmpi(str.data(), "d"))
	{
		return decimal;
	}
	if (!_strcmpi(str.data(), "str") ||
		!_strcmpi(str.data(), "string") ||
		!_strcmpi(str.data(), "s"))
	{
		return string;
	}

	return input_type_undefined; // possibile solo se chiamata da 'setInput()'
}

ProgramFunction checkProgramFunction(std::string_view str)
{
	if (!_strcmpi(str.data(), "crypt") ||
		!_strcmpi(str.data(), "c"))
	{
		return crypt;
	}
	if (!_strcmpi(str.data(), "decrypt") ||
		!_strcmpi(str.data(), "d"))
	{
		return decrypt;
	}

	return program_function_undefined; // possibile solo se chiamata da 'setInput()'
}

void print_usageError(const char* argv_zero) // stampa il messaggio di errore
{
	if (argv_zero)
	{
		std::string arg0 = argv_zero;

		std::ranges::reverse(arg0); // 'C:\abc.exe' -> 'exe.cba\:C'

		auto pos = std::distance(arg0.begin(), std::ranges::find(arg0, '\\')); // trova il primo '\'

		arg0 = arg0.substr(0, pos); // 'exe.cba\:C' -> 'exe.cba'

		std::ranges::reverse(arg0); // 'exe.cba' -> 'abc.exe'

		std::cout << "Utilizzo: " << arg0 << " (-crypt|-decrypt) (-hex|-dec|-str) <input> <chiave>";
	}
	else
	{
		std::cout << "Utilizzo: <nome_programma> (-crypt|-decrypt) (-hex|-dec|-str) <input> <chiave>";
	}
}