#include "LeavesManager.h"

#include <iostream>

using namespace sf;
using namespace std;

LeavesManager::LeavesManager (Vector2f origin) 
: 
	m_origin(origin),
	m_required(new Resources(0.01f, 0.013f, 0.0006f)),
	m_growingRate(200.f)
{}

Resources LeavesManager::collect (Air &air, Sun &sun) {
	Resources collected;
	for (auto &leaf : m_leaves) {
		if (!leaf.isDead()) {
			collected.water += leaf.getWater(air, sun);
			collected.energy += leaf.getEnergy(air, sun);
		}
	}
	return collected;
}

void LeavesManager::feed (Resources &resources) {
	for (auto &leaf : m_leaves)
		if (!leaf.isDead())
			leaf.feed(resources);
}

// TODO: check if leaf will survive in next iteration -- done
void LeavesManager::grow (Resources &resources, float growth, PlantShape &shape) {
	size_t limit = growth * m_growingRate;
	//while (resources.check_capacity(m_required->multiply(1.f)) && m_leaves.size() <= limit) {
	while (resources.check_capacity(m_required->multiply(1.f)) && m_leaves.size() <= limit) {
		m_leaves.emplace_back(m_required, resources, growth, m_origin);
		m_leaves.back().generatePosition(shape);
	}
}

void LeavesManager::generatePosition (PlantShape &shape) {
	for (auto &leaf : m_leaves)
		if (!leaf.isDead())
			leaf.generatePosition(shape);
}

void LeavesManager::update (float growth) {
	for (size_t i = 0; i < m_leaves.size(); i++) {
		if (!m_leaves[i].isActive()) {
			m_leaves.erase(m_leaves.begin() + i);
		} else {
			m_leaves[i].scalePosition(growth);
			m_leaves[i].update(growth);
		}
	}
}

void LeavesManager::draw (RenderWindow &window) {
	for (auto &leaf : m_leaves)
		leaf.draw(window);
}
