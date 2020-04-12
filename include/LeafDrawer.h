#pragma once

#include <SFML/Graphics.hpp>

#include "PlantShape.h"

class LeafDrawer {
private:

	sf::ConvexShape 	m_leaf;
	float 				m_scale;
    bool 				m_active;
    bool 				m_falling;
    bool 				m_growing;
    float 				m_step;
	sf::Vector2f 		m_origin;

public:

	LeafDrawer (
		float scale, 
		sf::Vector2f origin
	);

	void generatePosition (PlantShape &shape);

	void setScale (float growth, float square);
	void scalePosition (float growth);
	bool isActive () { return m_active; }

	void update (bool dead, float growth, float square);
	void draw (sf::RenderWindow &window);

private:

	void loadFromFile (std::string file);

};
