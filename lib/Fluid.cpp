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

	for (int y = 0; y < _dim_y; ++y) {
		for (int x = 0; x < _dim_x; ++x) {
			int index = to_index(x, y);

			_x_vel[index] = 0;
			_y_vel[index] = 0;
		}
	}
}

// Draws the "cell" grid
void Fluid::draw(sf::RenderWindow& window) {
	// Loop through all "visible" cells
	for (int y = 1; y < _dim_y - 1; ++y) {
		for (int x = 1; x < _dim_x - 1; ++x) {
			cell.setPosition((x - 1) * cell_w, (y - 1) * cell_h);

			int index = to_index(x, y);

			window.draw(cell);
		}
	}
}

// Converts a coordinate to 1D array index
int Fluid::to_index(int x, int y) {
	return (y * _dim_x + x);
}

// Converts a screen coordinate to a grid coordinate
sf::Vector2i Fluid::screen_to_grid(int x, int y) {
	return sf::Vector2i(x / cell_w, y / cell_h);
}

// Adds velocity to a specified location
void Fluid::add_vel(int x, int y, int vel_x, int vel_y) {
	if (vel_x == 0 && vel_y == 0) { return; }// Avoid unnecessary math when mouse is static


	sf::Vector2i grid_pos = screen_to_grid(x, y);
	clamp(grid_pos, 1, _dim_x - 2, 1, _dim_y - 2);

	int grid_index = to_index(grid_pos.x, grid_pos.y);

	//std::cout << grid_pos.x << ", " << grid_pos.y << "\n";

	// Add the velocites
	_x_vel[grid_index] += vel_x;
	_y_vel[grid_index] += vel_y;
}

// Clamps a vector
void Fluid::clamp(sf::Vector2i& vec, int x_min, int x_max, int y_min, int y_max) {
	if (vec.x < x_min) {
		vec.x = x_min;
	}
	else if (vec.x > x_max) {
		vec.x = x_max;
	}

	if (vec.y < y_min) {
		vec.y = y_min;
	}
	else if (vec.y > y_max) {
		vec.y = y_max;
	}
}