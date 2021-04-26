#pragma once
#include "Chip8.h"

void connect_chip8(Chip8* input_state); //"connects" the CPU to the main Chip8 object/state via a pointer

unsigned short int fetch(); //fetch the instruction at the current PC
void decode(); // decode instruction(extract opcode, regs, etc.)
void execute(); //execute the current instruction

void opcode_00E0();
void opcode_00EE();

void opcode_1NNN();

void opcode_2NNN();

void opcode_3XNN();

void opcode_4XNN();

void opcode_5XY0();

void opcode_6XNN();

void opcode_7XNN();

void opcode_8XY0();
void opcode_8XY1();
void opcode_8XY2();
void opcode_8XY3();
void opcode_8XY4();
void opcode_8XY5();
void opcode_8XY6();
void opcode_8XY7();
void opcode_8XYE();

void opcode_9XY0();

void opcode_ANNN();

void opcode_BNNN();

void opcode_CXNN();

void opcode_DXYN();

void opcode_EX9E();
void opcode_EXA1();

void opcode_FX07();
void opcode_FX15();
void opcode_FX18();
void opcode_FX29();
void opcode_FX33();
void opcode_FX0A();
void opcode_FX1E();
void opcode_FX55();
void opcode_FX65();