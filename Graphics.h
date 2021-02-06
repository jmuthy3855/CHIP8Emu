#pragma once
#include <SFML/Graphics.hpp>
#include "Chip8.h"

void drawFrame(unsigned char display[][DISPLAY_COLS], sf::RenderWindow& window, int flag);