#include "../include/Fluid.h"

// Primary Constructor
Fluid::Fluid(float density, int dim_x, int dim_y) {
	_density = density;

	_dim_x = dim_x + 2;	// Add an extra 2 for the edges
	_dim_y = dim_y + 2;

	_n_cells = _dim_x * _dim_y;	// Calculate total "cell" count

	// Prepare current velocity arrays
	_x_vel = new float[_n_cells];
	_y_vel = new float[_n_cells];

	// Prepare next velocity arrays
	_n_x_vel = new float[_n_cells];
	_n_y_vel = new float[_n_cells];
}

// Setup Display
void Fluid::setup_display(sf::RenderWindow& window) {
	sf::Vector2u window_dim = window.getSize();

	// Foolishly undoing the edge adds to get visibility correct
	cell_w = window_dim.x / float(_dim_x - 2);
	cell_h = window_dim.y / float(_dim_y - 2);

	cell.setSize(sf::Vector2f(cell_w, cell_h));
	cell.setOutlineThickness(1);
	cell.setOutlineColor(sf::Color(50, 10, 10));
	cell.setFillColor(sf::Color::Black);
}

// Draws the "cell" grid
void Fluid::draw(sf::RenderWindow& window) {
	// Loop through all "visible" cells
	for (int y = 1; y < _dim_y - 1; ++y) {
		for (int x = 1; x < _dim_x - 1; ++x) {
			cell.setPosition((x - 1) * cell_w, (y - 1) * cell_h);
			window.draw(cell);
		}
	}
}

// Converts a coordinate to 1D array index
int Fluid::to_index(int x, int y) {
	return (y * _dim_x + x);
}