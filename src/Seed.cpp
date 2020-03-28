#include "Seed.h"

#include <fstream>
#include <vector>

using namespace std;
using namespace sf;

Seed::Seed ()
: m_bottom(1080.f), 
  m_active(false), 
  m_falling(false), 
  m_step(5.f)
{}

void Seed::setPlant (string name) {
	string file = "Shapes/Seeds/";
	file.append(name);
	file.append(".txt");
	ifstream fin(file);
	if (!fin.good()) return;

	vector<Vector2f> verticies;
	Vector2f point;
	float r, g, b;
	fin >> r >> g >> b;
	while (fin >> point.x >> point.y)
		verticies.push_back(point);
	m_seed.setPointCount(verticies.size());
	for (int i = 0; i < verticies.size(); i++)
		m_seed.setPoint(i, verticies[i]); 
	m_seed.setOrigin(Vector2f(m_seed.getPoint(m_seed.getPointCount()/2).x, 
							  m_seed.getPoint(m_seed.getPointCount()/2).y));

	m_seed.setScale(0.4f, 0.4f);
	m_seed.setFillColor(Color(r, g, b));

	m_plant = name;
	m_active = true;
}

bool Seed::update (Vector2f mousePosition) {
	if (!m_active) return false;
	if (!m_falling) {
		m_seed.setPosition(mousePosition + Vector2f(-5.f, 5.f));
	} else {
		m_seed.move(0.f, m_step);
		m_step += 1.f;
		if (m_seed.getPosition().y >= m_bottom) {
			m_falling = false;
			m_active = false;
			m_step = 5.f;
			return true;
		}
	}
	return false;
}

void Seed::draw (RenderWindow &window) {
	if (!m_active) return;
	window.draw(m_seed);
}
















