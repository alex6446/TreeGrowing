#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "PlantShape.h"

class PlantDrawer {
private:

	PlantShape 	m_plant;
	int 	 	m_shapes;
	int 		m_current;
	float 		m_step;
	sf::Vector2f 	m_scale_factor;

	std::string	m_type;

public:

	PlantDrawer (sf::Vector2f positoin, std::string type);

	inline PlantShape& getShape () { return m_plant; }

	bool update (float growth);
	void draw (sf::RenderWindow &window);

};