#pragma once

#include <string>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>


#define DISPLAY_ROWS 32
#define DISPLAY_COLS 64
#define SCALE_FACTOR 30
#define START_ADDRESS 0x200

class Chip8 {

public:
	unsigned char memory[4096];
	unsigned char display[DISPLAY_ROWS][DISPLAY_COLS]; //not sure about this one
	unsigned short int PC;
	unsigned short int index_reg;
	unsigned short int stack[16];
	unsigned int stack_index; //self explanatory, keep track of stack index(index that stack will write to next, so write to index, then increment by 1)
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned char V[16]; //might be better to call this V[16], there are the 16 registers. registers go from 0 to 15, VF is the flag register
	//const unsigned int START_ADDRESS;
	sf::Keyboard::Key keyboardMap[16]; //maps chip 8 key to keyboard key
	int draw_flag; //0 -> don't draw 1-> draw 2-> clear screen


	void setKeyboardMap(); //set keyboard mapping
	int loadROM(const char* filename); //load ROM into memory
	void setFont(); //sets font and loads it into memory
	void emulateCPUCycle(); //emulates 1 chip 8 cycle

	Chip8() {
		//initialize various array variables
		memset(memory, 0, 4096);
		memset(display, 0, sizeof(display[0][0]) * DISPLAY_ROWS * DISPLAY_COLS);
		memset(stack, 0, 16);
		memset(V, 0, 16);

		//initialize other vars, which will be changed by ROMs before being used
		PC = START_ADDRESS;
		index_reg = 0;
		stack_index = 0;
		delay_timer = 0;
		sound_timer = 0;
		draw_flag = 0;

		//set keyboard mapping and font
		setKeyboardMap();
		setFont();
	}

};

