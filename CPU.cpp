#include "CPU.h"
#include "Debug.h"

/* file scope variables that represent parts of the current instruction being executed */
static unsigned short int curr_instr; 
static unsigned int opcode;
static unsigned int X;
static unsigned int Y;
static unsigned int N;
static unsigned int NN;
static unsigned int NNN;
static Chip8* state;
static Instruction opcode_zero[2];
static Instruction opcode_eight[9];
static Instruction opcode_EX[2];
static Instruction opcode_FX[9];

void load_instruction_table() {
	opcode_zero[0] = &opcode_00E0;
	opcode_zero[1] = &opcode_00EE;

	opcode_eight[0] = &opcode_8XY0;
	opcode_eight[1] = &opcode_8XY1;
	opcode_eight[2] = &opcode_8XY2;
	opcode_eight[3] = &opcode_8XY3;
	opcode_eight[4] = &opcode_8XY4;
	opcode_eight[5] = &opcode_8XY5;
	opcode_eight[6] = &opcode_8XY6;
	opcode_eight[7] = &opcode_8XY7;
	opcode_eight[8] = &opcode_8XYE;

	opcode_EX[0] = &opcode_EX9E;
	opcode_EX[1] = &opcode_EXA1;

	opcode_FX[0] = &opcode_FX0A;
	opcode_FX[1] = &opcode_FX29;
	opcode_FX[2] = &opcode_FX1E;
	opcode_FX[3] = &opcode_FX15;
	opcode_FX[4] = &opcode_FX55;
	opcode_FX[5] = &opcode_FX07;
	opcode_FX[6] = &opcode_FX65;
	opcode_FX[7] = &opcode_FX18;
	opcode_FX[8] = &opcode_FX33;
}

/* allows CPU to access chip8 components(register, stack, program counter, etc). only needs to be called once before emulation loop starts */
void connect_chip8(Chip8* input) {
	state = input;
}

unsigned short int fetch() {

	/*
	combine the 2 bytes into an instruction
	1. first left shift the first byte by 8
	2. then bitwise OR with the second byte

	*/
	curr_instr = state->memory[state->PC] << 8 | state->memory[state->PC + 1]; //check this...right shifting by 8 only works assuming memory[PC) treated as 2 bytes
	state->PC += 2;
	return curr_instr; // just for convenience if needed later
}

/* extract parts of the instruction */
void decode() {
	opcode = (curr_instr & 0xF000) >> 12; //11110000 00000000 will extract the first 4 bits, BUT HAVE TO RIGHT SHIFT...
	X = (curr_instr & 0x0F00) >> 8; //00001111 00000000 will extract the second 4 bits, first reg 
	Y = (curr_instr & 0x00F0) >> 4; //0000 0000 1111 0000 you get the idea....third nibble, second reg
	N = curr_instr & 0x000F; //fourth nibble, 4 bit number
	NN = (Y << 4) | N; //third and fourth nibble, an 8 bit number
	NNN = (X << 8 | Y << 4) | N; //second, third, fourth nibble. 12 bit memory address
}

/* execute the current instruction, based off the file scope variable values */
void execute() {
	//a better way/more compact way to do this would be to use a function pointer table

	switch (opcode) {
		case 0x0: 
		{
			//std::cout << ((N & 2) >> 1) << std::endl;
			/*
			switch (NN) {
				case 0xE0:
				{
					opcode_00E0();
					break;
				}
				case 0xEE:
				{
					opcode_00EE();
					break;
				}
				default:
				{
					std::cout << "Opcode error with 0x0" << std::endl;
				}
			}
			*/
			

			opcode_zero[(N & 2) >> 1]();
			break;
		}
		case 0x1:
		{
			opcode_1NNN();
			break;
		}
		case 0x2:
		{
			opcode_2NNN();
			break;
		}
		case 0x3:
		{
			opcode_3XNN();
			break;
		}
		case 0x4:
		{
			opcode_4XNN();
			break;
		}
		case 0x5:
		{
			opcode_5XY0();
			break;
		}
		case 0x6: 
		{
			opcode_6XNN();
			break;
		}
		case 0x7:
		{
			opcode_7XNN();
			break;
		}
		case 0x8:
		{
			/*
			switch (N) {

				case 0x0:
				{
					opcode_8XY0();
					break;
				}
				case 0x1:
				{
					opcode_8XY1();
					break;
				}
				case 0x2:
				{
					opcode_8XY2();
					break;
				}
				case 0x3:
				{
					opcode_8XY3();
					break;
				}
				case 0x4:
				{
					opcode_8XY4();
					break;
				}
				case 0x5:
				{
					opcode_8XY5();
					break;
				}
				case 0x6:
				{
					opcode_8XY6();
					break;
				}
				case 0x7:
				{
					opcode_8XY7();
					break;
				}
				case 0xE:
				{
					opcode_8XYE();
					break;
				}
				default:
				{
					std::cout << "Opcode error for 0x8" << std::endl;
				}
			}
			*/
			//std::cout << (N % 9) + 3 * (N & (1 << 3)) << std::endl;

			opcode_eight[(N % 9) + 3 * ((N & (1 << 3)) >> 3)]();
			break;
		}
		case 0x9:
		{
			opcode_9XY0();
			break;
		}
		case 0xA:
		{
			opcode_ANNN();
			break;
		}
		case 0xB:
		{
			opcode_BNNN();
			break;
		}
		case 0xC:
		{
			opcode_CXNN();
			break;
		}
		case 0xD: 
		{
			opcode_DXYN();
			break;
		}
		case 0xE:
		{

			/*
			switch (NN) {
				case 0x9E:
				{
					opcode_EX9E();
					break;
				}
				case 0xA1:
				{
					opcode_EXA1();
					break;
				}
				default:
				{
					std::cout << "Opcode error 0xE" << std::endl;
				}
			}
			*/

			opcode_EX[N & 1]();
			break;
		}
		case 0xF:
		{
			/* 
			switch (NN) {
				case 0x07:
				{
					opcode_FX07();
					break;
				}
				case 0x15:
				{
					opcode_FX15();
					break;
				}
				case 0x18:
				{
					opcode_FX18();
					break;
				}
				case 0x29:
				{
					opcode_FX29();
					break;
				}
				case 0x33:
				{
					opcode_FX33();
					break;
				}
				case 0x0A:
				{
					opcode_FX0A();
					break;
				}
				case 0x1E:
				{
					opcode_FX1E();
					break;
				}
				case 0x55:
				{
					opcode_FX55();
					break;
				}
				case 0x65:
				{
					opcode_FX65();
					break;
				}
				default:
				{
					std::cout << "Opcode error for 0xF" << std::endl;
				}
			}
			*/
			
			//i found this 0-8 mapping via magic
			//well sort of. 0x55 skips every other bit position. NN & 0x55 gives some unique numbers, but it's really just coincidence that modding 9 after that gives the 0-8 mapping. 
			opcode_FX[(NN & 0x55) % 9]();
			break;
		}
		default:
		{
			std::cout << "Unknown opcode" << std::endl;
		}
	}
	
}

/*Chip 8 instructions*/

//clear the screen
void opcode_00E0() {
	memset(state->display, 0, sizeof(state->display[0][0]) * DISPLAY_ROWS * DISPLAY_COLS); //clear the display array
	state->draw_flag = 2;
}

//pop from stack
void opcode_00EE() {
	state->PC = state->stack[state->stack_index--]; //could just do stack_index--...
}

//jump to PC given by NNN
void opcode_1NNN() {
	state->PC = NNN;
}

//call subroutine at NNN, push current PC to stack
void opcode_2NNN() {
	state->stack[++state->stack_index] = state->PC; //push current PC to stack
	state->PC = NNN; //jump to NNN
}

//skip one 2-byte instruction if VX == NN
void opcode_3XNN() {
	if (state->V[X] == NN) {
		state->PC += 2;
	}
}

//skip one 2-byte instruction if VX != NN
void opcode_4XNN() {
	if (state->V[X] != NN) {
		state->PC += 2;
	}
}

//skip one 2-byte instruction if VX == VY
void opcode_5XY0() {
	if (state->V[X] == state->V[Y]) {
		state->PC += 2;
	}
}

//set register X to NN
void opcode_6XNN() {
	state->V[X] = NN;
}

//add NN to register X
void opcode_7XNN() {
	//7XNN, add NN to VX
	state->V[X] = (state->V[X] + NN);
}

//set VX to VY
void opcode_8XY0() {
	state->V[X] = state->V[Y];
}

//bitwise logical AND of VX and VY, stored in VX
void opcode_8XY1() {
	state->V[X] = state->V[X] | state->V[Y];
}

//bitwise logical AND of VX and VY, stored in VX
void opcode_8XY2() {
	state->V[X] = state->V[X] & state->V[Y];
}

//bitwise XOR of VX and VY, stored in VX
void opcode_8XY3() {
	state->V[X] = state->V[X] ^ state->V[Y];
}

//add NN to register X(same as 7XNN), but carry flag is affected
void opcode_8XY4() {
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
void opcode_8XY5() {
	if (state->V[X] > state->V[Y]) {
		state->V[15] = 1;
	}
	else {
		state->V[15] = 0;
	}

	state->V[X] = state->V[X] - state->V[Y]; //% 256;
}

//shift to the right by 1 bit
void opcode_8XY6() {
	int bit = state->V[X] & 1; //get LSB
	state->V[X] = state->V[X] >> 1;

	state->V[15] = bit;
}

//store VY-VX in VX, carry flag is set in both cases
void opcode_8XY7() {
	if (state->V[Y] > state->V[X]) {
		state->V[15] = 1;
	}
	else {
		state->V[15] = 0; //set carry flag before subtraction
	}

	state->V[X] = state->V[Y] - state->V[X];
}

//left shift by 1 bit
void opcode_8XYE() {
	unsigned char bit = (state->V[X] & (1 << 7)) >> 7; //get MSB

	state->V[X] = state->V[X] << 1;
	state->V[15] = bit;
}

// skip instruction if VX != VY
void opcode_9XY0() {
	if (state->V[X] != state->V[Y]) {
		state->PC += 2;
	}
}


//set index register to NNN
void opcode_ANNN() {
	state->index_reg = NNN;
}

//jump with offset
void opcode_BNNN() {
	state->PC = NNN + state->V[0];
}

//random number generator
void opcode_CXNN() {
	unsigned int rdm = (rand() % 255) & NN;
	state->V[X] = rdm;
}


//draw sprite to screen
void opcode_DXYN() {
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

			/* this is just XOR */
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
void opcode_EX9E() {
	if (sf::Keyboard::isKeyPressed(state->keyboardMap[state->V[X]])) {
		state->PC += 2; //skip instruction 
	}
}

//skip instruction if value in VX is NOT pressed
void opcode_EXA1() {
	if (!sf::Keyboard::isKeyPressed(state->keyboardMap[state->V[X]])) {
		state->PC += 2; //skip instruction 
	}
}

//set VX to delay_timer
void opcode_FX07() {
	state->V[X] = state->delay_timer;
}

//set delay timer to value in VX
void opcode_FX15() {
	state->delay_timer = state->V[X];
}

//set sound timer to value in VX
void opcode_FX18() {
	state->sound_timer = state->V[X];
}

//font character
void opcode_FX29() {
	state->index_reg = 0x50 + (5 * state->V[X]);
}

//store digits into memory
void opcode_FX33() {
	//storing digits into memory
	int orig = state->V[X]; //use original value, or could use bit shifting to not use orig?
	int offset = 2;

	while (offset >= 0) { 
		state->memory[state->index_reg + offset--] = orig % 10;
		orig /= 10;
		//offset--;
	}
}

//wait till any key is pressed
void opcode_FX0A() {
	int key = -1;

	//goes through the keys, checking if any of them are pressed(it finds the earliest key that is pressed in the keyboard array)
	for (int i = 0; i <= 0xF; i++) {
		if (sf::Keyboard::isKeyPressed(state->keyboardMap[i])) {
			key = i;
			break; 
		}
	}

	if (key != -1) {
		state->V[X] = key; //puts hexadecimal value of pressed key into V[X]...?
	}
	else {
		state->PC -= 2; //decrement PC so it executes this instruction again until a key is pressed
	}
}

// adds V[X] to index reg, sets overflow flag
void opcode_FX1E() {
	if (state->V[X] + state->index_reg >= 4096) { //this might be 4095..
		state->V[15] = 1;
	}

	state->index_reg += state->V[X];
}

//storing memory(store registers to memory)
void opcode_FX55() {
	for (int i = 0; i <= X; i++) {
		state->memory[state->index_reg + i] = state->V[i];
	}
}

//loading memory into registers
void opcode_FX65() {
	for (int i = 0; i <= X; i++) {
		state->V[i] = state->memory[state->index_reg + i];
	}
}











