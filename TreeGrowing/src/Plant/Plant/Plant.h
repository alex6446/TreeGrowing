#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "PlantDrawer.h"
#include "Plant/LeavesManager.h"
#include "World/Air.h"
#include "World/Ground.h"
#include "World/Sun.h"

#include "Plant/Resources.h"

class Plant {
private:

	std::string			m_type;

	int 				m_id;
	std::string	 		m_name;
	std::string	 		m_title;

	Resources 			m_resources;
	Resources 			m_required;
	Resources 			m_eatrate;
	Resources 			m_collected;

	Resources 			m_max_collected;
	Resources 			m_max_resources;

	float 				m_growingRate;
	float 				m_growth; // 0..1
	bool 				m_dead;

	LeavesManager	 	m_leaves;
	PlantDrawer 		m_drawable;

public:

	Plant (sf::Vector2f position, int id, std::string type);

	inline bool isDead () { return m_dead; }

	void update (Air &air, Ground &ground, Sun &sun);
	void draw (sf::RenderWindow &window);

private:

	void collect_resources (Air &air, Ground &ground, Sun &sun);
	void distribute_resources ();
	void check_life ();
	void consume ();

	void updateImGUI ();
    void updateImGuiInfo();
    void updateImGuiSettings();

};