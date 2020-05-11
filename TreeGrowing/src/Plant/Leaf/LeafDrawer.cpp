#include "LeafDrawer.h"

#include <vector>
#include <fstream>
#include <random>

#include <iostream>

using namespace std;
using namespace sf;

LeafDrawer::LeafDrawer (
	float scale, 
	Vector2f origin
) : 
	m_scale(scale),
	m_active(true), 
	m_falling(false),
	m_growing(true),
	m_step(1.f),
	m_origin(origin)
{
	//m_leaf.setFillColor(Color(19, 117, 27));
	m_leaf.setFillColor(Color(26, 117, 65));
	loadFromFile("assets/Models/Tree/leaf.txt");
	m_leaf.setScale(0.01f, 0.01f);
}

void LeafDrawer::generatePosition (PlantShape &shape) {
	int ind = rand()%(shape.getPointCount()-5) + 2;
	Vector2f branch = shape.getPoint(ind+1) - shape.getPoint(ind);
	float t = (float)rand() / RAND_MAX;
	Vector2f pos = shape.getPoint(ind) + branch * t;
	m_leaf.setPosition(pos);
	if (branch.y < 0) branch *= -1.f;
	float alpha = atan2(branch.y, branch.x) * 180.f / M_PI * -1.f + 180.f;
	int range = 120;
	float angle = 90.f - (rand() % range - range / 2 + alpha);
	m_leaf.setRotation(angle);
}

void LeafDrawer::loadFromFile (string file) {
	ifstream fin(file);
	Vector2f point;
	vector<Vector2f> entity;
	while (fin >> point.x >> point.y)
		entity.push_back(point);
	m_leaf.setPointCount(entity.size());
	for (size_t i = 0; i < entity.size(); i++)
		m_leaf.setPoint(i, entity[i]);
	m_leaf.setOrigin(m_leaf.getPoint(0));
}

void LeafDrawer::setScale (float growth, float square) {
	float k = growth / 1.2f * square;
	if (m_growing || growth < 1.f * 0.3f) {
		if (m_leaf.getScale().x < k)
			m_leaf.scale(1.05f, 1.05f);
		else m_growing = false;
	} else {
		m_leaf.setScale(k, k);
	}
}

void LeafDrawer::scalePosition (float growth) {
	m_leaf.setPosition(m_origin + (m_leaf.getPosition() - m_origin) * growth / m_scale);
	m_scale = growth;
}

void LeafDrawer::update (bool dead, float growth, float square) {
	if (!dead) {
		setScale(growth, square);
	} else {
		m_leaf.move(0.f, m_step);
		m_step += 0.1f;
		Color color = m_leaf.getFillColor();
		if (color.a - m_step / 5.f >= 0.f) {
			color.a -= m_step / 5.f;
			m_leaf.setFillColor(color);
		}
		if (m_leaf.getPosition().y >= m_origin.y)
			m_active = false;
	}
}

void LeafDrawer::draw (RenderWindow &window) {
	window.draw(m_leaf);
}
