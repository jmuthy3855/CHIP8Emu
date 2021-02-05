#include "CPU.h"
#include "Debug.h"

unsigned short int fetch(Chip8* state) {

	/*
	combine the 2 bytes into an instruction
	1. first left shift the first byte by 8
	2. then bitwise OR with the second byte
	EX: first byte: 00110011
	second byte: 11101010

	left shift by 8:
	00110011 00000000
	bitwise OR with 11101010:
	00110011 11101010
	*/
	unsigned short int instruction = state->memory[state->PC] << 8 | state->memory[state->PC + 1]; //check this...right shifting by 8 only works assuming memory[PC) treated as 2 bytes
	state->PC += 2;
	return instruction;
}

void decodeAndExecute(Chip8* state, unsigned short int instruction) {
	unsigned int opcode = (instruction & 0xF000) >> 12; //11110000 00000000 will extract the first 4 bits, BUT HAVE TO RIGHT SHIFT...
	unsigned int X = (instruction & 0x0F00) >> 8; //00001111 00000000 will extract the second 4 bits, first reg 
	unsigned int Y = (instruction & 0x00F0) >> 4; //0000 0000 1111 0000 you get the idea....third nibble, second reg
	unsigned int N = instruction & 0x000F; //fourth nibble, 4 bit number
	unsigned int NN = (Y << 4) | N; //third and fourth nibble, an 8 bit number
	unsigned int NNN = (X << 8 | Y << 4) | N; //second, third, fourth nibble. 12 bit memory address

	if (opcode == 0x0) {
		if (NN == 0xE0) {
			opcode_00E0(state);
		}
		else {
			opcode_00EE(state);
		}
	}
	else if (opcode == 0x1) {
		opcode_1NNN(state, NNN);
	}
	else if (opcode == 0x2) {
		opcode_2NNN(state, NNN);
	}
	else if (opcode == 0x3) {
		opcode_3XNN(state, X, NN);
	}
	else if (opcode == 0x4) {
		opcode_4XNN(state, X, NN);
	}
	else if (opcode == 0x5) {
		opcode_5XY0(state, X, Y);
	}
	else if (opcode == 0x6) {
		opcode_6XNN(state, X, NN);
	}
	else if (opcode == 0x7) {
		opcode_7XNN(state, X, NN);
	}
	else if (opcode == 0x8) {
		if (N == 0x0) {
			opcode_8XY0(state, X, Y);
		}
		else if (N == 0x1) {
			opcode_8XY1(state, X, Y);
		}
		else if (N == 0x2) {
			opcode_8XY2(state, X, Y);
		}
		else if (N == 0x3) {
			opcode_8XY3(state, X, Y);
		}
		else if (N == 0x4) {
			opcode_8XY4(state, X, Y);
		}
		else if (N == 0x5) {
			opcode_8XY5(state, X, Y);
		}
		else if (N == 0x6) {
			opcode_8XY6(state, X);
		}
		else if (N == 0x7) {
			opcode_8XY7(state, X, Y);
		}
		else if (N == 0xE) {
			opcode_8XYE(state, X);
		}
		else {
			std::cout << "Unknown 8-prefix Opcode: " << std::hex << opcode << std::endl;
		}
	}
	else if (opcode == 0x9) {
		opcode_9XY0(state, X, Y);
	}
	else if (opcode == 0xA) {
		opcode_ANNN(state, NNN);
	}
	else if (opcode == 0xB) {
		opcode_BNNN(state, NNN);
	}
	else if (opcode == 0xC) {
		opcode_CXNN(state, X, NN);
	}
	else if (opcode == 0xD) {
		opcode_DXYN(state, X, Y, N);
	}
	else if (opcode == 0xE) {
		if (NN == 0x9E) {
			opcode_EX9E(state, X);
		}
		else if (NN == 0xA1) {
			opcode_EXA1(state, X);
		}
		else {
			std::cout << "Unknown E-prefix Opcode: " << std::hex << opcode << std::endl;
		}
	}
	else if (opcode == 0xF) {
		if (NN == 0x07) {
			opcode_FX07(state, X);
		}
		else if (NN == 0x15) {
			opcode_FX15(state, X);
		}
		else if (NN == 0x18) {
			opcode_FX18(state, X);
		}
		else if (NN == 0x29) {
			opcode_FX29(state, X);
		}
		else if (NN == 0x33) {
			opcode_FX33(state, X);
		}
		else if (NN == 0x0A) {
			opcode_FX0A(state, X);
		}
		else if (NN == 0x1E) {
			opcode_FX1E(state, X);
		}
		else if (NN == 0x55) {
			opcode_FX55(state, X);
		}
		else if (NN == 0x65) {
			opcode_FX65(state, X);
		}
		else {
			std::cout << "Unknown F-prefix Opcode: " << std::hex << opcode << std::endl;
		}
	}
	else {
		std::cout << "Unknown Opcode: " << std::hex << opcode << std::endl;
	}

}

/*Chip 8 instructions*/

//clear the screen
void opcode_00E0(Chip8* state) {
	memset(state->display, 0, sizeof(state->display[0][0]) * DISPLAY_ROWS * DISPLAY_COLS); //clear the display array
	state->draw_flag = 2;
	//drawFrame();
	//window.clear(sf::Color::Black); //clear the actual display
	//window.display(); //no need to draw points array
}

//pop from stack
void opcode_00EE(Chip8* state) {
	state->PC = state->stack[state->stack_index--]; //could just do stack_index--...
	//state->PC -= 2;
	//stack_index--;
}

//jump to PC given by NNN
void opcode_1NNN(Chip8* state, unsigned int NNN) {
	state->PC = NNN;
}

//call subroutine at NNN, push current PC to stack
void opcode_2NNN(Chip8* state, unsigned int NNN) {
	//2NNN call subroutine at NNN, but push current PC to stack
		//stack_index++; //move stack_index to next free location
		//printPC();
		//std::cout << "pushing on to stack " << std::endl;
	state->stack[++state->stack_index] = state->PC; //push current PC to stack
	state->PC = NNN; //jump to NNN
	//printPC();
	//std::cout << "stack index: " << std::dec << stack_index << std::endl;
	//printStack();
}

//skip one 2-byte instruction if VX == NN
void opcode_3XNN(Chip8* state, unsigned int X, unsigned int NN) {
	if (state->V[X] == NN) {
		state->PC += 2;
	}
}

//skip one 2-byte instruction if VX != NN
void opcode_4XNN(Chip8* state, unsigned int X, unsigned int NN) {
	if (state->V[X] != NN) {
		state->PC += 2;
	}
}

//skip one 2-byte instruction if VX == VY
void opcode_5XY0(Chip8* state, unsigned int X, unsigned int Y) {
	if (state->V[X] == state->V[Y]) {
		state->PC += 2;
	}
}

//set register X to NN
void opcode_6XNN(Chip8* state, unsigned int X, unsigned int NN) {
	state->V[X] = NN;
}

//add NN to register X
void opcode_7XNN(Chip8* state, unsigned int X, unsigned int NN) {
	//7XNN, add NN to VX
	state->V[X] = (state->V[X] + NN);// % 256;
}

//set VX to VY
void opcode_8XY0(Chip8* state, unsigned int X, unsigned int Y) {
	state->V[X] = state->V[Y];
}

//bitwise logical AND of VX and VY, stored in VX
void opcode_8XY1(Chip8* state, unsigned int X, unsigned int Y) {
	state->V[X] = state->V[X] | state->V[Y];
}

//bitwise logical AND of VX and VY, stored in VX
void opcode_8XY2(Chip8* state, unsigned int X, unsigned int Y) {
	state->V[X] = state->V[X] & state->V[Y];
}

//bitwise XOR of VX and VY, stored in VX
void opcode_8XY3(Chip8* state, unsigned int X, unsigned int Y) {
	state->V[X] = state->V[X] ^ state->V[Y];
}

//add NN to register X(same as 7XNN), but carry flag is affected
void opcode_8XY4(Chip8* state, unsigned int X, unsigned int Y) {
	int x = state->V[X]; //store in integers, because if result overflows it's not very easy to tell
	int y = state->V[Y];
	state->V[X] = state->V[X] + state->V[Y];

	if (x + y > 255) {
		state->V[15] = 1;
		//V[X] = V[X] % 256; //if value overflowed, take modulo of value
	}
	else {
		state->V[15] = 0;
	}
}

//store VX-VY in VX, carry flag is set in both cases
void opcode_8XY5(Chip8* state, unsigned int X, unsigned int Y) {
	if (state->V[X] > state->V[Y]) {
		state->V[15] = 1;
	}
	else {
		state->V[15] = 0;
	}

	state->V[X] = state->V[X] - state->V[Y]; //% 256;
}

//shift to the right by 1 bit
void opcode_8XY6(Chip8* state, unsigned int X) {
	int bit = state->V[X] & 1; //get LSB
	state->V[X] = state->V[X] >> 1;

	state->V[15] = bit;
}

//store VY-VX in VX, carry flag is set in both cases
void opcode_8XY7(Chip8* state, unsigned int X, unsigned int Y) {
	if (state->V[Y] > state->V[X]) {
		state->V[15] = 1;
	}
	else {
		state->V[15] = 0; //set carry flag before subtraction
	}

	state->V[X] = state->V[Y] - state->V[X];
}

//left shift by 1 bit
void opcode_8XYE(Chip8* state, unsigned int X) {
	unsigned char bit = (state->V[X] & (1 << 7)) >> 7; //get MSB

	state->V[X] = state->V[X] << 1;
	state->V[15] = bit;
}

// skip instruction if VX != VY
void opcode_9XY0(Chip8* state, unsigned int X, unsigned int Y) {
	if (state->V[X] != state->V[Y]) {
		state->PC += 2;
	}
}


//set index register to NNN
void opcode_ANNN(Chip8* state, unsigned int NNN) {
	state->index_reg = NNN;
}

//jump with offset
void opcode_BNNN(Chip8* state, unsigned int NNN) {
	state->PC = NNN + state->V[0];
}

//random number generator
void opcode_CXNN(Chip8* state, unsigned int X, unsigned int NN) {
	unsigned int rdm = (rand() % 255) & NN;
	//std::cout << "random number: " << std::dec << rdm << std::endl;
	state->V[X] = rdm;
}


//draw sprite to screen
void opcode_DXYN(Chip8* state, unsigned int X, unsigned int Y, unsigned int N) {
	//DXYN, draw to the screen. REMEMBER, Y -> ROWS(VERTICAL), X -> COLS(HORIZONTAL)
	state->draw_flag = 1;
	unsigned int x_coord = state->V[X] % DISPLAY_COLS; //handle "wrapping" of pixels if going out of bounds
	unsigned int y_coord = state->V[Y] % DISPLAY_ROWS;
	unsigned int x_orig = x_coord;

	state->V[15] = 0; //setting VF to 0...

	for (int i = 0; i < N; i++) {

		if (y_coord >= DISPLAY_ROWS) { //stop if you reach bottom of screen
			break;
		}

		unsigned int sprite_byte = state->memory[state->index_reg + i]; //get one byte at mem address stored in index_reg, offset by 1 after every iteration
		x_coord = x_orig;
		
		for (int j = 0; j < 8; j++) {

			if (x_coord >= DISPLAY_COLS) { //stop if you reach right edge
				break;
			}

			unsigned int bit = (sprite_byte & (1 << (7 - j))) >> (7 - j); //get the bit...but do i start from most significant or least significiant end? MSB

			if (bit == 1 && state->display[y_coord][x_coord] == 1) {
				state->display[y_coord][x_coord] = 0; //turn off pixel
				state->V[15] = 1; //set VF to 1
			}
			else if (bit == 1 && state->display[y_coord][x_coord] == 0) { //this can be restructured
				state->display[y_coord][x_coord] = 1;
			}

			x_coord += 1;
		}

		y_coord += 1;
	}

}

//skip instruction if value in VX is pressed
void opcode_EX9E(Chip8* state, unsigned int X) {
	if (sf::Keyboard::isKeyPressed(state->keyboardMap[state->V[X]])) {
		state->PC += 2; //skip instruction 
	}
}

//skip instruction if value in VX is NOT pressed
void opcode_EXA1(Chip8* state, unsigned int X) {
	if (!sf::Keyboard::isKeyPressed(state->keyboardMap[state->V[X]])) {
		state->PC += 2; //skip instruction 
	}
}

//set VX to delay_timer
void opcode_FX07(Chip8* state, unsigned int X) {
	state->V[X] = state->delay_timer;
}

//set delay timer to value in VX
void opcode_FX15(Chip8* state, unsigned int X) {
	state->delay_timer = state->V[X];
}

//set sound timer to value in VX
void opcode_FX18(Chip8* state, unsigned int X) {
	state->sound_timer = state->V[X];
}

//font character
void opcode_FX29(Chip8* state, unsigned int X) {
	//std::cout << "Drawing character " << std::hex << (int)state->V[X] << " to the screen" << std::endl;
	state->index_reg = 0x50 + (5 * state->V[X]);
}

//store digits into memory
void opcode_FX33(Chip8* state, unsigned int X) {
	//storing digits into memory
	int orig = state->V[X]; //use original value, or could use bit shifting to not use orig?
	int offset = 2;
	//std::cout << "val before store: " << std::dec << orig << std::endl;
	//std::cout << "register used: " << std::dec << X << std::endl;

	while (offset >= 0) { //potential infinite loop here....
		state->memory[state->index_reg + offset--] = orig % 10;
		orig /= 10;
		//offset--;
	}
}

//wait till any key is pressed
void opcode_FX0A(Chip8* state, unsigned int X) {
	int key = -1;
	//std::cout << "checking for key press" << std::endl;
	//goes through the keys, checking if any of them are pressed(it finds the earliest key that is pressed in the keyboard array)
	for (int i = 0; i <= 0xF; i++) {
		if (sf::Keyboard::isKeyPressed(state->keyboardMap[i])) {
			key = i;
			break; //this break will break out of the for loop, not the switch case
		}
	}

	if (key != -1) {
		state->V[X] = key; //puts hexadecimal value of pressed key into V[X]...?
	}
	else {
		state->PC -= 2; //decrement PC so it executes this instruction again until a key is pressed
	}
}

void opcode_FX1E(Chip8* state, unsigned int X) {
	if (state->V[X] + state->index_reg >= 4096) { //this might be 4095..
		state->V[15] = 1;
	}

	state->index_reg += state->V[X];
}

//storing memory(store registers to memory)
void opcode_FX55(Chip8* state, unsigned int X) {
	
			//std::cout << "storing memory, X is " << std::dec << X << std::endl;
	for (int i = 0; i <= X; i++) {
		state->memory[state->index_reg + i] = state->V[i];
	}
}

//loading memory into registers
void opcode_FX65(Chip8* state, unsigned int X) {
	
			//std::cout << "loading memory, X is " << std::dec << X << std::endl;
	for (int i = 0; i <= X; i++) {
		state->V[i] = state->memory[state->index_reg + i];
	}
}











