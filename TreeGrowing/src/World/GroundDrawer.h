#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Air.h"

class GroundDrawer {
private:
	
	sf::VertexArray m_surface;
	sf::VertexArray m_soil;
	std::vector<sf::CircleShape> m_minerals;
	unsigned int m_mineralsNumber;

public:

	GroundDrawer ();
	
	void generate_mesh (sf::RenderWindow &window);
	void generate_minerals (sf::RenderWindow &window);

	void update_color (Air &air);
	void update_minerals (float minerals);
	void draw (sf::RenderWindow &window);

private:

	sf::Vector2f generate_point (float x_start, float x_end, float x_range, 
								 float y_start, float y_end, float y_range);
};