#pragma once

#include <SFML/Graphics.hpp>

#include "GroundDrawer.h"
#include "Air.h"

class Ground {
private:
	
	float 			m_minerals; // 0 .. 1
	float 			m_humidity; // 0 .. 1
	GroundDrawer 	m_drawable;

public:

	Ground ();
	void setup (sf::RenderWindow &window, Air &air);

	inline float getMinerals () const { return m_minerals; }
	inline float getHumidity () const { return m_humidity; }

	void updateImGUI ();
	void update (Air &air);
	void draw (sf::RenderWindow &window);

private:

};