#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

#include "Leaf/Leaf.h"
#include "Plant/PlantShape.h"

#include "Resources.h"

class LeavesManager {
private:

	std::vector<Leaf> 				m_leaves;
	sf::Vector2f				 	m_origin;
	std::shared_ptr<Resources> 		m_required;
	std::shared_ptr<Resources> 		m_eatrate;
	std::shared_ptr<Resources> 		m_max_resources;

	float				m_growingRate; // 50 / 33 = 1.5 листьев на 1 рост
	std::string			m_type;
	sf::ConvexShape 	m_mesh;

public:

	LeavesManager (sf::Vector2f origin, std::string type);

	Resources collect (Air &air, Sun &sun);
	void feed (Resources &resources);
	void grow (Resources &resources, float growth, PlantShape &shape);

	void generatePosition (PlantShape &shape);

	void update (float growth);
	void draw (sf::RenderWindow &window);

private:

	void loadFromFile (std::string file);

};