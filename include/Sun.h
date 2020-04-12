#pragma once

#include <SFML/Graphics.hpp>

#include "SunDrawer.h"

class Sun {
private:
	
	float 			m_warm; // 0 .. 1
	float 			m_brightness; // 0 .. 1
	SunDrawer 		m_drawable;

public:

	Sun ();

	float getWarm () const { return m_warm; }
	float getBrightness () const { return m_brightness; }

	void updateImGUI ();
	void update ();
	void draw (sf::RenderWindow &window);

};