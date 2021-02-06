#include "Chip8.h"
#include "CPU.h"


void Chip8::setKeyboardMap() {
	//array index is chip 8 key, element is the respective keyboard key
	keyboardMap[0x0] = sf::Keyboard::X;
	keyboardMap[0x1] = sf::Keyboard::Num1; //not numpad1
	keyboardMap[0x2] = sf::Keyboard::Num2;
	keyboardMap[0x3] = sf::Keyboard::Num3;
	keyboardMap[0x4] = sf::Keyboard::Q;
	keyboardMap[0x5] = sf::Keyboard::W;
	keyboardMap[0x6] = sf::Keyboard::E;
	keyboardMap[0x7] = sf::Keyboard::A;
	keyboardMap[0x8] = sf::Keyboard::S;
	keyboardMap[0x9] = sf::Keyboard::D;
	keyboardMap[0xA] = sf::Keyboard::Z;
	keyboardMap[0xB] = sf::Keyboard::C;
	keyboardMap[0xC] = sf::Keyboard::Num4;
	keyboardMap[0xD] = sf::Keyboard::R;
	keyboardMap[0xE] = sf::Keyboard::F;
	keyboardMap[0xF] = sf::Keyboard::V;
}

int Chip8::loadROM(const char* filename) {
	// Open the file as a stream of binary and move the file pointer to the end
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open()) {
		// Get size of file and allocate a buffer to hold the contents
		//tellg will tell us the position we're currently at, so that's why we move the file pointer to the end of the file to determine the size we need
		std::streampos size = file.tellg();
		char* buffer = new char[size]; //this is dynamically allocated using the new keyword that's why it's freed later

		// Go back to the beginning of the file and fill the buffer
		file.seekg(0, std::ios::beg); //jump to beginning of file
		file.read(buffer, size); //read file into buffer
		file.close();

		std::cout << "size of file: " << std::dec << size << std::endl;

		// Load the ROM contents into memory starting at 0x200
		for (long i = 0; i < size; ++i) {
			memory[START_ADDRESS + i] = buffer[i];
		}

		// Free the buffer
		delete[] buffer;
		return size;
	}
	else {
		std::cout << "Could not open the ROM" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Chip8::setFont() {
	unsigned char font[80] = { 0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80 }; // F

	for (int i = 0x50; i <= 0x9F; i++) {
		memory[i] = font[i - 0x50];
	}


}

void Chip8::emulateCPUCycle(Chip8* state) {
	unsigned short int instr = fetch(state);
	decodeAndExecute(state, instr);
}