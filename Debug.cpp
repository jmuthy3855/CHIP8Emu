#include "Debug.h"
#include <iostream>

/* most of the debug functions are just print functions and are pretty self explanatory */
void printFontData(Chip8* state) {
	for (int i = 0x50; i <= 0x9F; i++) {
		std::cout << std::hex << (0xFF & state->memory[i]) << std::endl;
	}
}

void printDisplay(Chip8* state) {
	for (int i = 0; i < DISPLAY_ROWS; i++) {

		for (int j = 0; j < DISPLAY_COLS; j++) {
			std::cout << (int)state->display[i][j];
		}

		std::cout << std::endl;
	}
}

void printMemory(Chip8* state, int size) {
	for (int i = START_ADDRESS; i < size + START_ADDRESS; i++) {
		std::cout << std::hex << (int)state->memory[i] << std::endl;
	}
}

void printRegisters(Chip8* state) {
	std::cout << "Register contents: " << std::endl;

	for (int i = 0; i < 16; i++) {
		std::cout << "Register " << std::dec << i << ":" << std::hex << (int)state->V[i] << std::endl;
	}
}

void printPC(Chip8* state) {
	std::cout << "Program Counter: " << std::hex << state->PC << std::endl;
}

void printIndexRegister(Chip8* state) {
	std::cout << "Index Register: " << std::hex << state->index_reg << std::endl;
	std::cout << "Memory contents at address in IR: " << std::hex << (int)state->memory[state->index_reg] << std::endl;
}

//prints top most value first
void printStack(Chip8* state) {
	std::cout << "Stack contents: " << std::endl;

	for (int i = state->stack_index; i >= 0; i--) {
		std::cout << "index " << std::dec << i << ": " << std::hex << state->stack[i] << std::endl;
	}
}

/* prints instruction table indices */
void print_indices() {
	
	unsigned int indices_8[] = { 0x07, 0x0A, 0x15, 0x18, 0x1E, 0x29, 0x33, 0x55, 0x65 };
	//(indices_8[i] % 9) + 3 * ((indices_8[i] & (1 << 3)) >> 3)
	//0.0791789x + 0.744868

	for (int i = 0; i < 9; i++) {
		std::cout << "hex: " << std::hex << indices_8[i] << std::endl;
		std::cout << std::dec << (indices_8[i] & 0x55) % 9 << std::endl;
	}

}
