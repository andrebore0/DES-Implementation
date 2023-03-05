#include "des.h"

int main(int argc, char** argv)
{
	Arguments arguments;

	try
	{
		_LOG("[main()] Impostazione input.\n\n")
		setInput(argc, argv, arguments);
	}
	catch (ArgumentsException e)
	{
		std::cerr << "\nCatturata ArgumentsException: " << e.getError() << "\n\n";
		printUsageError(argv[0]);
		std::cerr << std::endl;

		return -1;
	}

	_LOG("[main()] Input impostato correttamente.\n\n")

	_LOG(
		"[main()] Input: \"" + arguments.input_string + "\"\n" +
		"[main()] Chiave: \"" + arguments.key_string + "\"\n" +
		"[main()] Tipo di input: " + std::to_string(arguments.input_type) + "\n" +
		"[main()] Funzione: " + std::to_string(arguments.program_function) + "\n\n"
	)

	des_main(arguments);

	return 0;
}

void des_main(const Arguments& arguments)
{
	/* Input parsing */
	ProgramFunction		function		{ arguments.program_function };	// questo serve a capire se criptare o decriptare
	std::string			input_string	{ arguments.input_string };		// input come string
	std::string			key_string		{ arguments.key_string };		// ...

	ui64 input{};
	ui64 key{};

	switch (arguments.input_type)
	{
	case hexadecimal:
		_LOG("[des_main()] Conversione da stringa(esadecimale) a \'ui64\'.\n\n")
		input	= stringBaseToUi64Hex(input_string);
		key		= stringBaseToUi64Hex(key_string);
		break;

	case string:
		_LOG("[des_main()] Conversione da stringa(ascii) a \'ui64\'.\n\n")
		input	= stringASCIIToUi64(input_string);
		key		= stringASCIIToUi64(key_string);
	}
	/* ------------- */

	/* Output */
	std::cout << std::hex;

	std::cout	<< "Input:\t\"" << input_string << "\" -> 0x" << input
				<< "\nChiave:\t\"" << key_string << "\" -> 0x" << key << ((isUi64Printable(key)) ? (" -> \"" + uiToASCIIString(key) + "\"") : "")
				<< "\n\n";

	std::cout << std::dec;

	ui64 result{ operateOnBlock(input, key, function) };
	/* ------ */
	std::cout << std::hex;

	std::cout << ((function) ? "Testo in chiaro: 0x" : "Testo cifrato: 0x") << result << ((isUi64Printable(result)) ? (" -> \"" + uiToASCIIString(result) + "\"\n") : "\n");
	std::cout << std::dec;
}

ui64 operateOnBlock(ui64 input, ui64 key, ProgramFunction function)
{
	std::array<ui64, rounds> keyTable{};
	key_schedule(key, keyTable);

	_LOG("[operateOnBlock()] Chiavi ottenute.\n\n")

	permute(input, des_data::initial_perm_matrix);

	_LOG(
		"[operateOnBlock()] Permutazione iniziale: \n" +
		uiBitsToString(input, 8) + " -> 0x" + ui64ToString(input, std::hex) + "\n\n"
	)

	ui32 inputLeftPart	{ static_cast<ui32>(input >> ui64_size / 2) };	// L0
	ui32 inputRightPart	{ static_cast<ui32>(input & ui32_mask) };		// R0

	if (function == decrypt)
	{
		std::ranges::reverse(keyTable);
		_LOG("[operateOnBlock()] function == decrypt, inverto \'keyTable\'.\n\n")
	}

	ui32 oldLeftPart{};
	for (int i = 0; i < rounds; ++i)
	{
		_LOG(
			"[operateOnBlock()] Round " + std::to_string(i + 1) + ": \n" +
			"\tL" + std::to_string(i) + ": " + uiBitsToString(inputLeftPart, 8) + " -> 0x" + ui64ToString(inputLeftPart, std::hex) + "\n" +
			"\tR" + std::to_string(i) + ": " + uiBitsToString(inputRightPart, 8) + " -> 0x" + ui64ToString(inputRightPart, std::hex) + "\n" +
			"\tChiave " + std::to_string(i) + ": " + uiBitsToString(keyTable.at(i), 7, 15) + " -> 0x" + ui64ToString(keyTable.at(i), std::hex) + "\n"
		)

		oldLeftPart = inputLeftPart;
		inputLeftPart = inputRightPart;

		inputRightPart = oldLeftPart ^ feistel(inputRightPart, keyTable.at(i));
		
		_LOG(
			"\tR" + std::to_string(i + 1) + " = L" + std::to_string(i) +
			" XOR feistel(R" + std::to_string(i) + ", Chiave" + std::to_string(i) + "): " +
			uiBitsToString(inputRightPart, 8) + " -> 0x" + ui64ToString(inputRightPart, std::hex) + "\n\n"
		)
	}

	ui64 output{ (static_cast<ui64>(inputRightPart) << (block_size / 2)) | inputLeftPart }; // R16 concat L16

	_LOG(
		"Output pre-permutazione: " + uiBitsToString(output, 8) + " -> 0x" + ui64ToString(output, std::hex) + "\n\n"
	)

	permute(output, des_data::final_perm_matrix);

	return output;
}

/*\
 *	permuta i bit di 'input' ed esegue eventuale compressione/espansione
 *	segue le posizioni date da 'permuteTable'
 *	{ 0 < permuteTable.size() <= (sizeof(_Ui) * byte) }
\*/
template <std::unsigned_integral _Ui, std::size_t size>
void permute(_Ui& input, const std::array<int, size>& permuteTable, int inputSize)
{
	assert( // bounds checking
		(permuteTable.size() > 0 && permuteTable.size() <= (sizeof(_Ui) * byte))
		&&
		"\'permuteTable.size()\' out of range in \'permute(_Ui&, const std::array<int, size>&, int)\'."
	);

	_Ui permutedInput	{}; // mi serve 'input' intatto per lettura
	int maxIndex		{ static_cast<int>(permuteTable.size() - 1) };

	for (int i{}; i <= maxIndex; ++i)
	{
		bit_manipulation::setBit(
			permutedInput,
			maxIndex - i,
			bit_manipulation::getBit(input, inputSize - permuteTable.at(i))
		);
	}

	input = permutedInput;
}

/*\
 *	Genera le 16 chiavi a 48-bit utilizzate nei rispettivi round partendo da una singola chiave a 64-bit
\*/
void key_schedule(ui64 key, std::array<ui64, rounds>& dst)
{
	permute(key, des_data::key_scheduler_pc_1); // 64-bit -> 56-bit
	
	_LOG(
		"[key_schedule()] Chiave permutata(PC-1):\n" +
		uiBitsToString(key, 8) + " -> 0x" + ui64ToString(key, std::hex) + "\n\n" +
		"[key_schedule()] Chiavi:\n"
	)

	ui32 leftPart	{ static_cast<ui32>(key >> key_size_PC1 / 2) };	// 28-bit
	ui32 rightPart	{ static_cast<ui32>(key & right_key_mask_PC1) };
	
	ui64 temp{};
	for (int i{}; i < rounds; ++i)
	{
		bit_manipulation::rotateBits(
			leftPart,
			des_data::key_shift_table.at(i),
			(key_size_PC1 / 2) - 1
		);
		
		bit_manipulation::rotateBits(
			rightPart,
			des_data::key_shift_table.at(i),
			(key_size_PC1 / 2) - 1
		);

		temp = leftPart;
		temp = (temp << key_size_PC1 / 2) ^ rightPart;

		permute(temp, des_data::key_scheduler_pc_2, key_size_PC1); // praticamente rimasto a 64-bit, quindi devo specificare la dimensione

		_LOG(
			"Chiave " + std::to_string(i + 1) + ": " +
			uiBitsToString(temp, 8) + " -> 0x" + ui64ToString(temp, std::hex) +
			"\n"
		)

		dst.at(i) = temp;
	}

	_LOG("\n")
}

ui32 feistel(ui32 block, ui64 key) // la chiave è a 48-bit, salvata come 64-bit
{
	ui64 blockCopy	{ block };
	ui32 output		{};

	permute(blockCopy, des_data::feistel_expansion_table, block_size / 2); // 32 -> 48

	blockCopy ^= key;

	ui64 temp{};	// contiene il valore a 6-bit estratto
	int row{};		// riga di s-box
	int col{};		// colonna di s-box
	for (int i{}; i < sbox_rounds; ++i)
	{
		output <<= byte / 2; // xxxx -> xxxx 0000
		temp = blockCopy >> ((sbox_input_size * sbox_rounds) - ((i + 1) * sbox_input_size));	// 010011 011010 101000 101101 -> 010011 011010
		temp = temp & sbox_input_mask;															// 010011 011010 -> 011010

		row = (bit_manipulation::getBit(temp, sbox_input_size - 1) << 1) | static_cast<int>(bit_manipulation::getBit(temp, 0)); // 0xxxx0 -> 00 -> 0dec
		
		col = (bit_manipulation::getBit(temp, sbox_input_size - 2) << 3) | // x1101x -> 1101 -> 13dec
			(bit_manipulation::getBit(temp, sbox_input_size - 3) << 2) |
			(bit_manipulation::getBit(temp, sbox_input_size - 4) << 1) |
			static_cast<int>(bit_manipulation::getBit(temp, sbox_input_size - 5));
		
		output |= des_data::sbox.at(i).at(row).at(col); // sbox[1][0][13] (fa 0) -> ... 0000
	}

	permute(output, des_data::feistel_p_table, block_size / 2);

	return output;
}

#ifdef _DEBUG
template <std::unsigned_integral _Ui>
std::string uiBitsToString(_Ui x, int separatorMultiple, int startPos)
{
	std::string output{ std::bitset<sizeof(_Ui)* byte>(x).to_string() };

	if (separatorMultiple %= static_cast<int>(sizeof(_Ui) * byte); separatorMultiple <= 0)
	{
		return output.substr(startPos);
	}

	for (int currentPos{ static_cast<int>(sizeof(_Ui) * byte) - separatorMultiple };
		currentPos > startPos;
		currentPos = (currentPos - separatorMultiple))
	{
		output.insert(currentPos, "\'");
	}

	return output.substr(startPos);
}
#endif // _DEBUG