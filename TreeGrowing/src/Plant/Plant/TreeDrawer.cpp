#include "TreeDrawer.h"
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

TreeDrawer::TreeDrawer (Vector2f position) 
: 
	m_shapes(0), 
	m_current(0), 
	m_path("assets/Models/Tree/shapes/")
{
	ifstream fin;
	while (true) {
		fin.open(m_path + to_string(m_shapes) + string(".txt"));
		if (!fin.good()) {
			fin.close();
			break;
		} 
		fin.close();
		m_shapes++;
	}
	m_step = 1.f / m_shapes;
	m_tree.loadFromFile(m_path + to_string(m_current) + string(".txt"));
	m_tree.setPosition(position);
	m_tree.setFillColor(Color(89, 73, 68));
}

bool TreeDrawer::update (float growth) {
	if (growth > m_step * (m_current + 1) && m_current + 1 < m_shapes) {
		m_current++;
		m_tree.loadFromFile(m_path + to_string(m_current) + string(".txt"));
		m_tree.setPosition(m_tree.getPosition());
		m_tree.setScale(growth);
		return true;
	}
	m_tree.setScale(growth);
	return false;
}

void TreeDrawer::draw (RenderWindow &window) {
	window.draw(m_tree);
}
