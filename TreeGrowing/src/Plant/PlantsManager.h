#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Seed.h"
#include "Plant/Plant.h"
#include "World/Air.h"
#include "World/Ground.h"
#include "World/Sun.h"

class PlantsManager {
private:

    std::vector<Plant> 			m_plants;
    Seed 						m_seed;

    std::vector<std::string> 	m_types;
    std::string 				m_current_type;

public:
    
    PlantsManager ();

    void setup (sf::RenderWindow &window);

    inline void click () { m_seed.click(); }
    inline int getPlantsCount() { return m_plants.size(); }

	void updateImGUI ();
    void update (Air &air, Ground &ground, Sun &sun, sf::Vector2f mousePosition);
    void draw (sf::RenderWindow &window);

};