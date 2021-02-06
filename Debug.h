#pragma once
#include "Chip8.h"

void printFontData(Chip8* state);
void printDisplay(Chip8* state);
void printMemory(Chip8* state, int size);
void printRegisters(Chip8* state);
void printPC(Chip8* state);
void printIndexRegister(Chip8* state);
void printStack(Chip8* state);