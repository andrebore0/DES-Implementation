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
	
	std::string program_function_str	= argv[1];
	std::string input_type_str			= argv[2];

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

	while (!compareString(input_type_str, accepted_input::HEX, false) &&
		!compareString(input_type_str, accepted_input::DEC, false) &&
		!compareString(input_type_str, accepted_input::STR, false))
	{
		std::cout << "Errore:\nTipi di input accettati: (hex|hexadecimal|h) | (dec|decimal|d) | (str|string|s)\n\n";

		std::cout << "Inserire tipo di input: ";
		std::getline(std::cin >> std::ws, input_type_str);
	}
	/* ------------- */

	/* Tipo di funzione */
	std::cout << "Tipi di funzione accettati: (encrypt|e) | (decrypt|d)\n\n";
	std::cout << "Inserire tipo di funzione: ";
	std::string program_function_str;
	std::getline(std::cin >> std::ws, program_function_str);

	while (!compareString(program_function_str, accepted_input::ENCRYPT, false) &&
		!compareString(program_function_str, accepted_input::DECRYPT, false))
	{
		std::cout << "Errore:\nTipi di funzione accettati: (encrypt|e) | (decrypt|d)\n\n";

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
	if (compareString(str, accepted_input::HEX, false))
	{
		return hexadecimal;
	}
	if (compareString(str, accepted_input::DEC, false))
	{
		return decimal;
	}
	if (compareString(str, accepted_input::STR, false))
	{
		return string;
	}

	return input_type_undefined; // possibile solo se chiamata da 'setInput()'
}

ProgramFunction checkProgramFunction(std::string_view str)
{
	if (compareString(str, accepted_input::ENCRYPT, false))
	{
		return encrypt;
	}
	if (compareString(str, accepted_input::DECRYPT, false))
	{
		return decrypt;
	}

	return program_function_undefined; // possibile solo se chiamata da 'setInput()'
}

void printUsageError(const char* argv_zero) // stampa il messaggio di errore
{
	if (argv_zero)
	{
		std::string arg0 = argv_zero;

		std::ranges::reverse(arg0); // 'C:\abc.exe' -> 'exe.cba\:C'

		auto pos = std::distance(arg0.begin(), std::ranges::find(arg0, '\\')); // trova il primo '\'

		arg0 = arg0.substr(0, pos); // 'exe.cba\:C' -> 'exe.cba'

		std::ranges::reverse(arg0); // 'exe.cba' -> 'abc.exe'

		std::cout << "Utilizzo: " << arg0 << " (-encrypt|-decrypt) (-hex|-dec|-str) <input> <chiave>";
	}
	else
	{
		std::cout << "Utilizzo: <nome_programma> (-encrypt|-decrypt) (-hex|-dec|-str) <input> <chiave>";
	}
}

std::vector<ui64> inputToBlocks(std::string input, InputType type)
{
	return std::vector<ui64>();
}