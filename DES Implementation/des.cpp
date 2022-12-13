#include "des.h"
#include "intrin.h"

int main(int argc, char** argv)
{
#ifndef _DEBUG
	if (!setArguments(argc, argv))
	{
		return error_arguments;
	}
#endif

	ui64 key{ 0b00010011'00110100'01010111'01111001'10011011'10111100'11011111'11110001 };

	std::array<ui64, 16> x{};

	key_schedule(key, x);

	//return des_main();
	return 0;
}

Status des_main()
{
	/* Input parsing */
#ifndef _DEBUG
	
	std::string function	{ g_arguments.program_function };	// questo serve a capire se criptare o decriptare
	std::string input_str	{ g_arguments.input_string };		// input come string
	std::string key_str		{ g_arguments.key_string };			// ...

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

	if (result == 0)
	{
		std::cout << "Not implemented yet." << std::endl;
	}
	else
	{
		std::cout << "DES " << function.substr(1, function.length() - 1) << " di \'" << input_str << "\' usando la chiave \'" << key << "\': " << result << std::endl;
	}

#else

	std::cout	<< "\nInput:\t\"" << input_str << "\" -> 0x" << std::hex << input
				<< "\nChiave:\t\"" << key_str << "\" -> 0x" << std::hex << key
				<< std::endl;

	ui64 digest		{ des_crypt(input, key) };
	ui64 decrypt	{ des_decrypt(digest, key) };

	std::cout	<< "\nInput criptato -> 0x" << std::hex << digest
				<< "\nInput decriptato -> 0x" << std::hex << decrypt;

#endif // _DEBUG
	/* ------ */

	return ok;
}

ui64 des_decrypt(ui64 input, ui64 key)
{
	// TODO
	return 0;
}

ui64 des_crypt(ui64 input, ui64 key)
{
	permute(input, des_data::INITIAL_PERM_MATRIX);
	//key_scheduler(key , 0);

	for (int i{}; i < rounds; ++i) // left part
	{
		do_round();
	}

	return 0;
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

	for (int i{}; i < input_size; ++i) // (string)input -> (unsigned long long)input
	{
		temp <<= byte;	// 0x00001234 -> 0x12340000
		temp ^= str[i];	// input char estratto nel byte liberato
	}

	return temp;
}

/*\
 *	permuta i bit di 'input' ed esegue eventuale compressione
 *	segue le posizioni date da 'permuteTable'
 *	{ 0 < matrix.size() < sizeof(T) * byte }
\*/
template <bit_manipulation::UnsignedInteger T, std::size_t size>
void permute(T& input, const std::array<int, size>& permuteTable)
{
	assert( // bounds checking
		(permuteTable.size() > 0 && permuteTable.size() <= (sizeof(T) * byte))
		&&
		"\'sizeof(matrix)\' out of bounds in \'permute(T&, const std::array<int, size>&)\'."
	);

	T permutedInput	{}; // mi serve 'input' intatto per lettura
	int maxIndex	{ (sizeof(T) * byte) - 1 };

	for (int i{}; i < permuteTable.size(); ++i)
	{
		bit_manipulation::setBit(
			permutedInput,
			maxIndex - i,
			bit_manipulation::getBit(input, maxIndex - (permuteTable.at(i) - 1))
		);
	}

	// la differenza tra le dimensioni mi dirà di quanti bit "comprimere"
	input = permutedInput >> ((sizeof(T) * byte) - permuteTable.size());
}


/*\
 *	Genera le 16 chiavi a 48-bit utilizzate nei rispettivi round partendo da una singola chiave a 64-bit
\*/
void key_schedule(ui64 key, std::array<ui64, 16>& dst) 
{
	permute(key, des_data::KEY_SCHEDULER_PC_1); // 64-bit -> 56-bit permutata

	printBits(key, "permuted PC-1", 8);

	ui32 leftPart	{ static_cast<ui32>(key >> key_size_PC1 / 2) };
	ui32 rightPart	{ static_cast<ui32>(key & right_key_mask_PC1) };

	std::cout << std::endl;

	printBits(leftPart, "C0", 4, 7);
	printBits(rightPart, "D0", 4, 7);

	for (int i{}; i < rounds; ++i)
	{
		dst.at(i) = 1;
	}

}

void do_round()
{

}

/*\
 *	Stampa i bit di un numero.
 *	È possibile definire la formattazione del numero e una stringa grazie ai 3 paramtetri finali.
\*/
#ifdef _DEBUG
template <bit_manipulation::UnsignedInteger T>
void printBits(T input, std::string str, int startPos, int separatorPos)
{
	int Tsize = (sizeof(T) * byte);

	std::cout << str << ": ";
	for (int i{ (Tsize - 1) - startPos }; i >= 0; --i)
	{
		if ((i + 1) % separatorPos == 0 && i != (Tsize - 1) - startPos)
		{
			std::cout << '\'';
		}

		std::cout << bit_manipulation::getBit(input, i);
	}
	std::cout << std::endl;
}
#endif // _DEBUG