#include "LeafDrawer.h"
#include "Plant/ConfigReader.h"
#include "Config.h"

#include <vector>
#include <fstream>
#include <random>

#include <iostream>

using namespace std;
using namespace sf;

LeafDrawer::LeafDrawer (
	float scale, 
	Vector2f origin,
	string type,
	ConvexShape &leaf
) : 
	m_scale(scale),
	m_active(true), 
	m_falling(false),
	m_growing(true),
	m_step(1.f),
	m_origin(origin),
	m_type(type),
	m_leaf(leaf)
{
	//m_leaf.setFillColor(Color(19, 117, 27));
	string file = MODELS_FOLDER;
	file += type;
	string config = file + CONFIG_FILE;
	m_leaf.setFillColor(getConfigColor(config, "LEAVES_COLOR"));
	//loadFromFile(file + LEAF_FILE);
	m_scale_factor = getConfigVector2f(config, "LEAVES_SCALE_FACTOR");
	m_leaf.setScale(0.01f * m_scale_factor);
	m_mesh_start = getConfigFloat(config, "LEAVES_MESH_START_PADDING");
	m_mesh_end = getConfigFloat(config, "LEAVES_MESH_END_PADDING");
	m_angle_range = getConfigFloat(config, "LEAVES_ANGLE_RANGE");
	m_leaves_direction = getConfigFloat(config, "LEAVES_DIRECTION");
}

void LeafDrawer::generatePosition (PlantShape &shape) {
	int ind = rand()%(shape.getPointCount()-1-m_mesh_start-m_mesh_end) + m_mesh_start;
	Vector2f branch = shape.getPoint(ind+1) - shape.getPoint(ind);
	float t = (float)rand() / RAND_MAX;
	Vector2f pos = shape.getPoint(ind) + branch * t;
	m_leaf.setPosition(pos);
	int range = m_angle_range;
	float angle = 0.f;
	switch (m_leaves_direction) {
	case 0: { // following branch 
		if (branch.y < 0) branch *= -1.f;
		float alpha = atan2(branch.y, branch.x) * 180.f / M_PI * -1.f + 180.f;
		angle = 90.f - (rand() % range - range / 2 + alpha);
		break;
	}
	case 1: { // up
		angle = (rand() % range - range / 2);
		break;
	}
	case 2: { // down
		angle = (rand() % range - range / 2) + 180.f;
		break;
	}
	};
	m_leaf.setRotation(angle);
}

void LeafDrawer::setScale (float growth, float square) {
	float k = growth / 1.2f * square;
	if (m_growing || growth < 1.f * 0.3f) {
		if (m_leaf.getScale().x / m_scale_factor.x < k)
			m_leaf.scale(1.05f, 1.05f);
		else m_growing = false;
	} else {
		m_leaf.setScale(k * m_scale_factor);
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
