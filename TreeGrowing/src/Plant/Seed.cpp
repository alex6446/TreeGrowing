#include "Seed.h"
#include "Config.h"

#include <fstream>
#include <vector>
#include <string>

#include "ConfigReader.h"

using namespace std;
using namespace sf;

Seed::Seed ()
: 
	m_bottom(1080.f), // Will reset in setup anyway
	m_active(false), 
	m_falling(false), 
	m_step(SEED_SPEED)
{}

void Seed::setPlant (string name) {
	string file = "assets/Models/";
	file.append(name);
	string config = file + "/config.txt";
	ifstream fin(file + "/seed.txt");
	if (!fin.good()) return;

	vector<Vector2f> verticies;
	Vector2f point;
	float r, g, b;
	fin >> r >> g >> b;
	while (fin >> point.x >> point.y)
		verticies.push_back(point);
	m_seed.setPointCount(verticies.size());
	for (size_t i = 0; i < verticies.size(); i++)
		m_seed.setPoint(i, verticies[i]); 
	m_seed.setOrigin(Vector2f(m_seed.getPoint(m_seed.getPointCount()/2).x, 
							  m_seed.getPoint(m_seed.getPointCount()/2).y));
	float scale = getConfigFloat(config, "SEED_SCALE");
	m_seed.setScale(scale, scale);
	m_seed.setFillColor(getConfigColor(config, "SEED_COLOR"));

	m_plant = name;
	m_active = true;
}

bool Seed::update (Vector2f mousePosition) {
	if (!m_active) return false;
	if (!m_falling) {
		m_seed.setPosition(mousePosition + SEED_SHIFT);
	} else {
		m_seed.move(0.f, m_step);
		m_step += SEED_ACCELERATION;
		if (m_seed.getPosition().y >= m_bottom) {
			m_falling = false;
			m_active = false;
			m_step = SEED_SPEED;
			return true;
		}
	}
	return false;
}

void Seed::draw (RenderWindow &window) {
	if (!m_active) return;
	window.draw(m_seed);
}
















