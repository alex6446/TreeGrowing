#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Plant/Plant/PlantShape.h"

class LeafDrawer {
private:

	sf::ConvexShape 	m_leaf;
	float 				m_scale;
    bool 				m_active;
    bool 				m_falling;
    bool 				m_growing;
    float 				m_step;
	sf::Vector2f 		m_origin;
	
	std::string 		m_type;
	int 				m_mesh_start;
	int 				m_mesh_end;
	float 				m_angle_range;
	sf::Vector2f 		m_scale_factor;
	int 				m_leaves_direction;

public:

	LeafDrawer (
		float scale, 
		sf::Vector2f origin,
		std::string type,
		sf::ConvexShape &leaf
	);

	void generatePosition (PlantShape &shape);

	void setScale (float growth, float square);
	void scalePosition (float growth);
	inline bool isActive () { return m_active; }

	void update (bool dead, float growth, float square);
	void draw (sf::RenderWindow &window);
	
};
