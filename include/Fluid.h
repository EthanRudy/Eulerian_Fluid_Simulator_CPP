#ifndef FLUID_H
#define FLUID_H

#include <SFML/Graphics.hpp>
#include <iostream>

/*
	Note:
		- Unlike my previous version, I won't be using a cell class to have an actual grid
			I am instead opting to use the more efficient 1D array of just raw data and raw
			dogging it
*/

class Fluid {
public:
	// Primary Constructor
	Fluid(float density, int dim_x, int dim_y);

	// One-time setup for window dimensions and stuff
	// Saves repeated arithmetic and didn't want it in the constructor
	void setup_display(sf::RenderWindow& window);

	// Draws the "cell" grid
	void draw(sf::RenderWindow& window);

	// Adds velocity to a specified location
	void add_vel(int x, int y, int vel_x, int vel_y);
protected:
private:

	///////////////////////////
	///// Fluid Variables /////
	///////////////////////////

	// Density Constant
	float _density;

	// "Cell" grid Dimensions
	int _dim_x;
	int _dim_y;

	// Total number of cells, used primarily for looping
	int _n_cells;

	// Current Velocities
	float* _x_vel;
	float* _y_vel;

	// Next (calculated and replaced Velocities)
	float* _n_x_vel;
	float* _n_y_vel;
	

	////////////////////////////
	///// Render Variables /////
	////////////////////////////

	float cell_w;
	float cell_h;

	sf::RectangleShape cell;
	
	///////////////////
	///// Helpers /////
	///////////////////

	// Converts a coordinate to 1D array index
	int to_index(int x, int y);

	// Converts a screen coordinate to a grid coordinate
	sf::Vector2i screen_to_grid(int x, int y);

	// Clamps a vector
	void clamp(sf::Vector2i& vec, int x_min, int x_max, int y_min, int y_max);
};

#endif // FLUID_H