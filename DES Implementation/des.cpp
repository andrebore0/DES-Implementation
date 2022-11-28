#include "des.h"

ull stringToULL(std::string& str)
{
	for (; str.length() > 8;) // trimming
	{
		str.pop_back();
	}

	for (; str.length() < 8;) // padding
	{
		str += '\0';
	}

	ull temp{};

	for (int i = 0; i < byte; ++i) // (string)input -> (unsigned long long)input
	{
		temp <<= byte; // 0x00001234 -> 0x12340000
		temp ^= str[i]; // input char estratto nel byte liberato
	}

	return temp;
}

ull des_crypt(ull input, ull key)
{
	key_compress(key);									// -> void					key_compress		(ull& key)
	initial_permutation(input);							// -> void					initial_permutation	(ull& input)
	
	std::tuple<ui, ui> inputParts = divideInput(input);	// -> std::tuple<ui, ui>	divideInput			(ull input)

	ui leftKeyPart{ std::get<0>(inputParts) };
	ui rightKeyPart{ std::get<1>(inputParts) };

	ui right{ rightKeyPart };
	for (int i = 0; i < 16; ++i) // left part
	{
		do_round();
	}

	ui left{ leftKeyPart };
	for (int i = 0; i < 16; ++i) // right part
	{
		do_round();
	}
}

ull des_decrypt(ull input, ull key)
{

}

int main(int argc, char** argv)
{
#ifndef _DEBUG
	std::string input_str{ argv[1] };	// input come string
	std::string key_str{ argv[2] };		// ...
#else
	std::string input_str;
	std::string key_str;

	std::cout	<< "Debug: argomenti ignorati.\n"
				<< "Inserire input: ";
	std::getline(std::cin >> std::ws, input_str);

	std::cout	<< "Inserire chiave: ";
	std::getline(std::cin >> std::ws, key_str);
#endif // _DEBUG

	ull input	{ stringToULL(input_str) };	// conversione in intero senza segno
	ull key		{ stringToULL(key_str) };	// numero intero = operazioni logiche bitwise

#ifdef _DEBUG
	std::cout	<< "\nInput:\t\"" << input_str << "\" -> " << input
				<< "\nChiave:\t\"" << key_str << "\" -> " << key
				<< std::endl;
#endif // _DEBUG

	ull result{ des_crypt(input, key) };

	return 0;
}