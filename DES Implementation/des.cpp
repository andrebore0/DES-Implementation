#include "des.h"

int main(int argc, char** argv)
{
#ifndef _DEBUG

	setArguments(argc, argv);

#endif

	return des_main();
}

Status des_main()
{
	/* Input parsing */
#ifndef _DEBUG

	std::string function	{ g_arguments.at(0) };	// questo serve a capire se criptare o decriptare
	std::string input_str	{ g_arguments.at(1) };	// input come string
	std::string key_str		{ g_arguments.at(2) };	// ...

#else

	std::string input_str;
	std::string key_str;

	std::cout	<< "Debug: argomenti ignorati.\n"
				<< "Inserire input: ";
	std::getline(std::cin >> std::ws, input_str);

	std::cout	<< "Inserire chiave: ";
	std::getline(std::cin >> std::ws, key_str);

#endif // _DEBUG

	ui64 input	{ stringToULL(input_str) };		// conversione in intero senza segno
	ui64 key	{ stringToULL(key_str) };		// numero intero = operazioni logiche bitwise
	/* ------------- */

	/* Output */
#ifndef _DEBUG
	
	ui64 result{ (function == "-crypt") ? des_crypt(input, key) : des_decrypt(input, key) };

	if (result == error_generic)
	{
		std::cout << "Not implemented yet." << std::endl;
	}
	else
	{
		std::cout << "DES " << function.substr(1, function.length() - 1) << " di \'" << input_str << "\' usando la chiave \'" << key << "\': " << result << std::endl;
	}

#else

	std::cout	<< "\nInput:\t\"" << input_str << "\" -> " << input
				<< "\nChiave:\t\"" << key_str << "\" -> " << key
				<< std::endl;

	ui64 digest		{ des_crypt(input, key) };
	ui64 decrypt	{ des_decrypt(digest, key) };

	std::cout	<< "\nDigest:\t" << digest
				<< "\nDigest decriptato:\t" << decrypt;

#endif // _DEBUG
	/* ------ */

	return ok;
}

ui64 des_decrypt(ui64 input, ui64 key)
{
	// TODO
	return static_cast<ui64>(error_generic);
}

ui64 des_crypt(ui64 input, ui64 key)
{
	permute(input, INITIAL_PERM_MATRIX);	// -> void	initial_permutation	(ull& input)
	key_scheduler(key);			// -> void	key_compress		(ull& key)

	for (int i = 0; i < rounds; ++i) // left part
	{
		do_round();
	}

	return static_cast<ui64>(error_generic);
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