#pragma once

#include <SFML/Graphics.hpp>

#include "TreeDrawer.h"
#include "Plant/LeavesManager.h"
#include "World/Air.h"
#include "World/Ground.h"
#include "World/Sun.h"

#include "Plant/Resources.h"

class Tree {
private:

	int 				m_id;
	std::string	 		m_name;
	std::string	 		m_title;
	int 				m_mode;

	Resources 			m_resources;
	Resources 			m_required;
	Resources 			m_ration;
	Resources 			m_collected;

	float 				m_growingRate;
	float 				m_growth; // 0..1
	bool 				m_dead;

	LeavesManager	 	m_leaves;
	TreeDrawer 			m_drawable;

public:

	Tree (sf::Vector2f position, int id);

	bool isDead () { return m_dead; }

	void update (Air &air, Ground &ground, Sun &sun);
	void draw (sf::RenderWindow &window);

private:

	void collect_resources (Air &air, Ground &ground, Sun &sun);
	void distribute_resources ();
	void check_life ();
	void consume ();

	void updateImGUI ();

};