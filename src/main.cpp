#include "../include/Fluid.h"

/*
	Paper Used: http://www.georgebit.com/images/articles/programming/euler/downloads/Liviu-George_Bitiusca_-_Eulerian_Fluid_Simulator.pdf
*/

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1090), "Test Window");

	Fluid fluid(0, 160, 90);
	fluid.setup_display(window);

	bool clicked = false;
	sf::Vector2i mouse_pos;
	sf::Vector2i pre_mouse_pos;
	sf::Vector2i window_pos;

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed()) {
				window.close();
			}

			if (e.type == sf::Event::MouseButtonPressed) {
				if (!clicked) { 
					clicked = true; 
				}
			}
			else if (e.type == sf::Event::MouseButtonReleased && clicked) {
				clicked = false;
			}
		}

		if (clicked) {
			mouse_pos = sf::Mouse::getPosition();
			window_pos = window.getPosition();

			float mouse_x = mouse_pos.x - window_pos.x - 8;
			float mouse_y = mouse_pos.y - window_pos.y - 32;

			float mouse_vel_x = mouse_pos.x - pre_mouse_pos.x;
			float mouse_vel_y = mouse_pos.y - pre_mouse_pos.y;

			fluid.add_vel(mouse_x, mouse_y, mouse_vel_x, mouse_vel_y);
		}

		pre_mouse_pos = mouse_pos;

		window.clear(sf::Color::White);

		// Draw stuff
		fluid.draw(window);

		window.display();
	}
}