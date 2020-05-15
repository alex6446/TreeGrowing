#include "LeavesManager.h"
#include "Config.h"
#include "Plant/ConfigReader.h"

#include <iostream>

using namespace sf;
using namespace std;

LeavesManager::LeavesManager (Vector2f origin, string type) 
: 
	m_origin(origin),
	m_type(type)
{
	string file = MODELS_FOLDER;
	file += type;
	string config = file + CONFIG_FILE;

	m_required = shared_ptr<Resources>(new Resources(getConfigResources(config, "LEAVES_REQUIRED")));
	m_eatrate = shared_ptr<Resources>(new Resources(getConfigResources(config, "LEAVES_EATRATE")));
	m_max_resources = shared_ptr<Resources>(new Resources(getConfigResources(config, "LEAVES_MAX_RESOURCES")));
	m_growingRate = getConfigFloat(config, "LEAVES_GROWING_RATE");
	loadFromFile(file + LEAF_FILE);
}

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
		m_leaves.emplace_back(
			m_required, 
			m_eatrate, 
			m_max_resources, 
			resources, 
			growth, 
			m_origin,
			m_type,
			m_mesh
		);
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

void LeavesManager::loadFromFile (string file) {
	ifstream fin(file);
	Vector2f point;
	vector<Vector2f> entity;
	while (fin >> point.x >> point.y)
		entity.push_back(point);
	m_mesh.setPointCount(entity.size());
	for (size_t i = 0; i < entity.size(); i++)
		m_mesh.setPoint(i, entity[i]);
	m_mesh.setOrigin(m_mesh.getPoint(0));
}