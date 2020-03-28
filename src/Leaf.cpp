#include "Leaf.h"

using namespace sf;

Leaf::Leaf (Resources &required, Resources &resources, float scale, Vector2f &origin) 
: m_required(required), // TODO: make m_required a refference
  m_ration(5.f, 6.f, 7.f),
  m_square(1.f),
  m_dead(false),
  m_drawable(scale, origin)
{
	feed(resources);
}

Leaf::~Leaf () {}

float Leaf::getWater (Air &air, Sun &sun) {
	return air.getHumidity() * (1.05f - air.getTemperaturePercentage()) * m_square;
}

float Leaf::getEnergy (Air &air, Sun &sun) {
	return sun.getWarm() * sun.getBrightness() * (air.getTemperaturePercentage() + 1.f) * m_square; // TODO: decrease water if its hot
}

void Leaf::feed (Resources &resources) {
	m_resources.add(resources.subtract(m_required.multiply(m_square)));	
}

void Leaf::setSquare (float square) {
	m_square = square;
}

void Leaf::generatePosition (PlantShape &shape) {
	m_drawable.generatePosition(shape);
}

void Leaf::scalePosition (float growth) {
	m_drawable.scalePosition(growth);
}

void Leaf::update (float growth) {
	if (!m_dead) {
		consume();
		check_life();
	}
	m_drawable.update(m_dead, growth, m_square);
}

void Leaf::draw (RenderWindow &window) {
	m_drawable.draw(window);
}

void Leaf::consume () {
	m_resources.subtract(m_ration.multiply(m_square));
}

void Leaf::check_life () {
	if (!m_resources.water || !m_resources.energy || !m_resources.materials) {
		m_dead = true;
	}
}
