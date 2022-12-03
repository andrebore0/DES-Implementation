#include "des.h"

int main(int argc, char** argv)
{
#ifndef _DEBUG
	if (argc <= 3 || (toLowerCase(argv[1]) != "\\crypt" && toLowerCase(argv[1]) != "\\decrypt"))
	{
		print_usageError((argv[0]) ? argv[0] : "");
		return -1;
	}

	std::string function{ argv[1] };	// questo serve a capire se criptare o decriptare
	std::string input_str{ argv[2] };	// input come string
	std::string key_str{ argv[3] };		// ...
#else
	std::string input_str;
	std::string key_str;

	std::cout	<< "Debug: argomenti ignorati.\n"
				<< "Inserire input: ";
	std::getline(std::cin >> std::ws, input_str);

	std::cout	<< "Inserire chiave: ";
	std::getline(std::cin >> std::ws, key_str);
#endif // _DEBUG

	ui64 input	{ stringToULL(input_str) };	// conversione in intero senza segno
	ui64 key	{ stringToULL(key_str) };	// numero intero = operazioni logiche bitwise

#ifdef _DEBUG
	std::cout	<< "\nInput:\t\"" << input_str << "\" -> " << input
				<< "\nChiave:\t\"" << key_str << "\" -> " << key
				<< std::endl;

#endif // _DEBUG

	//ull result{ des_crypt(input, key) };

	return 0;
}

ui64 des_decrypt(ui64 input, ui64 key)
{
	// TODO
	return -1;
}

ui64 des_crypt(ui64 input, ui64 key)
{
	permute(input, INITIAL_PERM_MATRIX);	// -> void	initial_permutation	(ull& input)
	key_scheduler(key);			// -> void	key_compress		(ull& key)

	for (int i = 0; i < rounds; ++i) // left part
	{
		do_round();
	}

	return -1;
}

ui64 stringToULL(std::string& str)
{
	for (; str.length() > input_size;) // trimming
	{
		str.pop_back();
	}

	for (; str.length() < input_size;) // padding
	{
		str += '\0';
	}

	ui64 temp{};

	for (int i = 0; i < input_size; ++i) // (string)input -> (unsigned long long)input
	{
		temp <<= BYTE;	// 0x00001234 -> 0x12340000
		temp ^= str[i];	// input char estratto nel byte liberato
	}

	return temp;
}

std::string toLowerCase(std::string str) // idk
{
	constexpr auto CASEMASK{ 0b00100000 };

	for (char& elem : str)
	{
		elem = ((elem >= 'A' && elem <= 'Z') || (elem >= 'a' && elem <= 'z')) ? (elem | CASEMASK) : elem;
	}

	return str;
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

template <std::size_t size>
void permute(ui64& input, const std::array<int, size>& matrix)
{
	
	ui64 inputCopy{ input };
}

void key_scheduler(ui64& key)
{
	// dividi input
	ui32 keyLeft{ static_cast<ui32>(key >> (sizeof(ui64) >> 1)) }; // quick hack: ((int)a >> 1) == ((int)a / 2)
	//ui32 keyRight{ key >> static_cast<ui32>(sizeof(ui64) >> 1) };

}

void do_round()
{

}