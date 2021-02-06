#pragma once
#include "Chip8.h"

unsigned short int fetch(Chip8* state); //fetch the instruction at the current PC
void decodeAndExecute(Chip8* state, unsigned short int instruction); //decode and execute the instruction arg

void opcode_00E0(Chip8* state);
void opcode_00EE(Chip8* state);

void opcode_1NNN(Chip8* state, unsigned int NNN);

void opcode_2NNN(Chip8* state, unsigned int NNN);

void opcode_3XNN(Chip8* state, unsigned int X, unsigned int NN);

void opcode_4XNN(Chip8* state, unsigned int X, unsigned int NN);

void opcode_5XY0(Chip8* state, unsigned int X, unsigned int Y);

void opcode_6XNN(Chip8* state, unsigned int X, unsigned int NN);

void opcode_7XNN(Chip8* state, unsigned int X, unsigned int NN);

void opcode_8XY0(Chip8* state, unsigned int X, unsigned int Y);
void opcode_8XY1(Chip8* state, unsigned int X, unsigned int Y);
void opcode_8XY2(Chip8* state, unsigned int X, unsigned int Y);
void opcode_8XY3(Chip8* state, unsigned int X, unsigned int Y);
void opcode_8XY4(Chip8* state, unsigned int X, unsigned int Y);
void opcode_8XY5(Chip8* state, unsigned int X, unsigned int Y);
void opcode_8XY6(Chip8* state, unsigned int X);
void opcode_8XY7(Chip8* state, unsigned int X, unsigned int Y);
void opcode_8XYE(Chip8* state, unsigned int X);

void opcode_9XY0(Chip8* state, unsigned int X, unsigned int Y);

void opcode_ANNN(Chip8* state, unsigned int NNN);

void opcode_BNNN(Chip8* state, unsigned int NNN);

void opcode_CXNN(Chip8* state, unsigned int X, unsigned int NN);

void opcode_DXYN(Chip8* state, unsigned int X, unsigned int Y, unsigned int N);

void opcode_EX9E(Chip8* state, unsigned int X);
void opcode_EXA1(Chip8* state, unsigned int X);

void opcode_FX07(Chip8* state, unsigned int X);
void opcode_FX15(Chip8* state, unsigned int X);
void opcode_FX18(Chip8* state, unsigned int X);
void opcode_FX29(Chip8* state, unsigned int X);
void opcode_FX33(Chip8* state, unsigned int X);
void opcode_FX0A(Chip8* state, unsigned int X);
void opcode_FX1E(Chip8* state, unsigned int X);
void opcode_FX55(Chip8* state, unsigned int X);
void opcode_FX65(Chip8* state, unsigned int X);