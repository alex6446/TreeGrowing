#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class SunDrawer {
private:

	std::vector<sf::CircleShape> m_circles;

public:

	SunDrawer ();

	void update_warm (float warm);
	void update_brightness (float brightness);
	void draw (sf::RenderWindow &window);

private:

	float compute_radius (unsigned index);

};

