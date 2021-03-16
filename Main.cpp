#include "Chip8.h"
#include "Debug.h"
#include "CPU.h"
#include "Graphics.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>


int main(void) {
	Chip8* emulator = new Chip8(); //why can't i do Chip8 *emulator()?
	int ROM_size = emulator->Chip8::loadROM("Tetris.ch8"); //should be a cmd line arg or part of UI
	int instruction_count = 0;
	srand(time(NULL)); //initialize seed for RNG

	connect_chip8(emulator); //allows CPU to access chip 8 state
	load_instruction_table();
	print_indices();

	std::cout << "ROM SIZE: " << std::dec << ROM_size << " bytes\n";

	sf::RenderWindow window(sf::VideoMode(DISPLAY_COLS * SCALE_FACTOR, DISPLAY_ROWS * SCALE_FACTOR), "Chip 8 Actual");
	window.setFramerateLimit(60);

	float cycle_delay = 1.5;
	auto lastCycleTime = std::chrono::high_resolution_clock::now();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		if (dt > cycle_delay) {
			lastCycleTime = currentTime;

			emulator->emulateCPUCycle();
			instruction_count++;

			if (instruction_count % 8 == 0 && emulator->delay_timer > 0) {
				--emulator->delay_timer;
			}

			if (instruction_count % 8 == 0 && emulator->sound_timer > 0) {
				--emulator->sound_timer;
			}
			
			if (emulator->draw_flag >= 1) {
				drawFrame(emulator->display, window, emulator->draw_flag);
				emulator->draw_flag = 0;
			}
		}
		

	}

	delete emulator; //use smart pointer?
}