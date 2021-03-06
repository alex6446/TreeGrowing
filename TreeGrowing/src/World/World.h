#pragma once

#include <SFML/Graphics.hpp>

#include "World/Air.h"
#include "World/Ground.h"
#include "World/Sun.h"
#include "Plant/PlantsManager.h"

class World {
private:

	Air 				m_air;
	Ground 				m_ground;
	Sun 				m_sun;
	PlantsManager 		m_plants;

	sf::Clock 			m_deltaClock;
	sf::RenderWindow 	m_window;

public:

	World ();
	~World ();

	inline bool exists () { return m_window.isOpen(); }

	void update ();
	void draw ();

private:

	void updateImGUI ();

    void setupWindow ();
    void setupImGUI ();

};