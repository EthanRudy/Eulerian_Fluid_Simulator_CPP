#include "../include/Fluid.h"
/*
	Paper Used: http://www.georgebit.com/images/articles/programming/euler/downloads/Liviu-George_Bitiusca_-_Eulerian_Fluid_Simulator.pdf
*/

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1090), "Test Window");
	Fluid fluid(0, 160, 90);
	fluid.setup_display(window);

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed()) {
				window.close();
			}
		}

		window.clear(sf::Color::White);

		// Draw stuff
		fluid.draw(window);

		window.display();
	}
}