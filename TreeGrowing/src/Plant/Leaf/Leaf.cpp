#include "Leaf.h"
#include "Config.h"
#include "Plant/ConfigReader.h"

using namespace sf;
using namespace std;

Leaf::Leaf (
	std::shared_ptr<Resources> required, 
    std::shared_ptr<Resources> eatrate,
    std::shared_ptr<Resources> max_resources,
    Resources &resources, 
    float scale, 
    sf::Vector2f origin,
    std::string type,
    ConvexShape &mesh
) : 
	m_required(required), // TODO: make m_required a refference (pointer) -- done
	m_eatrate(eatrate),
	m_max_resources(max_resources),
	m_dead(false),
	m_type(type),
	m_drawable(scale, origin, type, mesh)
{
	m_square = getConfigFloat(string(MODELS_FOLDER) + m_type + CONFIG_FILE, "LEAVES_SQUARE");
	feed(resources);
}

Leaf::~Leaf () {}

float Leaf::getWater (Air &air, Sun &sun) {
	return 
		(air.getHumidity() - 
		(air.getTemperature() - DEFAULT_TEMPERATURE) / 10.f * 
		sun.getWarm() * sun.getBrightness()) * 
		m_square * 0.1f;
}

float Leaf::getEnergy (Air &air, Sun &sun) {
	return 
		(sun.getWarm() * sun.getBrightness() + 
		(air.getTemperature() - DEFAULT_TEMPERATURE) / 100.f) * 
		m_square * 0.5f;
}

void Leaf::feed (Resources &resources) {
	m_resources.add(resources.subtract(m_required->multiply(m_square + 1.f)));
	m_resources.cutoff(*m_max_resources);	
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
	m_resources.subtract((m_required->multiply(*m_eatrate)).multiply(m_square));
}

void Leaf::check_life () {
	if (!m_resources.water || !m_resources.energy || !m_resources.materials) {
		m_dead = true;
	}
}
