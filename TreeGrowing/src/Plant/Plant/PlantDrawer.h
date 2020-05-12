#pragma once

#include <SFML/Graphics.hpp>
#include "PlantShape.h"

class PlantDrawer {
private:

	PlantShape 	m_tree;
	int 	 	m_shapes;
	int 		m_current;
	float 		m_step;
	std::string	m_path;

public:

	PlantDrawer (sf::Vector2f positoin);

	PlantShape& getShape () { return m_tree; }

	bool update (float growth);
	void draw (sf::RenderWindow &window);

};