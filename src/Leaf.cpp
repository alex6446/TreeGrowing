#include "Leaf.h"

using namespace sf;

Leaf::Leaf (
	std::shared_ptr<Resources> required, 
	Resources &resources, 
	float scale, 
	Vector2f origin
) : 
	m_required(required), // TODO: make m_required a refference (pointer) -- done
	m_ration(0.01f, 0.012f, 0.0005f),
	m_square(1.f),
	m_dead(false),
	m_drawable(scale, origin)
{
	feed(resources);
}

Leaf::~Leaf () {}

float Leaf::getWater (Air &air, Sun &sun) {
	return 
		air.getHumidity() * 
		(1.01f - air.getTemperatureNormalized()) * 
		(1.01f - sun.getWarm() * sun.getBrightness()) * 
		m_square;
}

float Leaf::getEnergy (Air &air, Sun &sun) {
	return 
		sun.getWarm() * 
		sun.getBrightness() * 
		//(air.getTemperatureNormalized() + 1.f) * 
		(air.getTemperatureNormalized() / 2.f + 1.f) * 
		m_square; // TODO: decrease water if its hot
}

void Leaf::feed (Resources &resources) {
	m_resources.add(resources.subtract(m_required->multiply(m_square + 1.f)));	
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
