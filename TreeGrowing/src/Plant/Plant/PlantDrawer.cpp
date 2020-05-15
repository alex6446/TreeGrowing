#include "PlantDrawer.h"
#include "Plant/ConfigReader.h"
#include "Config.h"

#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

PlantDrawer::PlantDrawer (Vector2f position, string type) 
: 
	m_shapes(0), 
	m_current(0), 
	m_type(type)
{
	string file = MODELS_FOLDER;
	file += m_type;
	string shapes_folder = file + SHAPES_FOLDER;
	ifstream fin;
	while (true) {
		fin.open(shapes_folder + to_string(m_shapes) + string(".txt"));
		if (!fin.good()) {
			fin.close();
			break;
		} 
		fin.close();
		m_shapes++;
	}
	m_step = 1.f / m_shapes;
	m_plant.loadFromFile(shapes_folder + to_string(m_current) + string(".txt"));
	m_plant.setPosition(position);
	m_plant.setFillColor(getConfigColor(file + CONFIG_FILE, "PLANT_COLOR"));
	m_scale_factor = getConfigVector2f(file + CONFIG_FILE, "PLANT_SCALE_FACTOR");
}

bool PlantDrawer::update (float growth) {
	if (growth > m_step * (m_current + 1) && m_current + 1 < m_shapes) {
		m_current++;
		m_plant.loadFromFile(string(MODELS_FOLDER) + m_type + 
			string(SHAPES_FOLDER) + to_string(m_current) + string(".txt"));
		m_plant.setPosition(m_plant.getPosition());
		m_plant.setScale(growth * m_scale_factor);
		return true;
	}
	m_plant.setScale(growth * m_scale_factor);
	return false;
}

void PlantDrawer::draw (RenderWindow &window) {
	window.draw(m_plant);
}
