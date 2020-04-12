#pragma once

#include <SFML/Graphics.hpp>

#include "Air.h"
#include "Ground.h"
#include "Sun.h"
#include "PlantsManager.h"

class World {
private:

	int 				m_mode;

	Air 				m_air;
	Ground 				m_ground;
	Sun 				m_sun;
	PlantsManager 		m_plants;

	sf::Clock 			m_deltaClock;
	sf::RenderWindow 	m_window;

public:

	World ();
	~World ();

	bool exists () { return m_window.isOpen(); }

	void update ();
	void draw ();

private:

	void updateImGUI ();

};