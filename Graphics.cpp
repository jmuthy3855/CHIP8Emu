#include "Graphics.h"


void drawFrame(unsigned char display[][DISPLAY_COLS], sf::RenderWindow& window, int flag) {
	window.clear(sf::Color::Black);

	//flag 1 means draw, flag 2 means clear screen, which is done above, so just skip and display
	if (flag == 1) {
		sf::RectangleShape* rec_ptr = new sf::RectangleShape(sf::Vector2f(SCALE_FACTOR, SCALE_FACTOR));
		//the bounds for this loop(and size of rectangle) should be scaled relative to each other, maybe use some constants for
		//the height/width of window, and determine the dims of the rectangle using that
		for (int y = 0; y < DISPLAY_ROWS * SCALE_FACTOR; y += SCALE_FACTOR) {
			for (int x = 0; x < DISPLAY_COLS * SCALE_FACTOR; x += SCALE_FACTOR) {

				if (display[y / SCALE_FACTOR][x / SCALE_FACTOR] == 1) {
					(*rec_ptr).setFillColor(sf::Color::Green);
				}
				else {
					(*rec_ptr).setFillColor(sf::Color::Black);
				}


				rec_ptr->setPosition(x, y);
				window.draw(*rec_ptr);
			}
		}

		delete rec_ptr;
	}

	window.display();
}