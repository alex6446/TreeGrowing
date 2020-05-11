#include "GroundDrawer.h"
#include "Config.h"
#include <iostream>
#include <random>

using namespace sf;
using namespace std;

//Constructor

GroundDrawer::GroundDrawer () 
: 
	m_surface(sf::TriangleStrip), 
  	m_soil(sf::TriangleStrip)
{ 
	srand(time(NULL)); 
}
	
//Public functions

void GroundDrawer::generate_mesh (RenderWindow &window) {
	float median = window.getSize().y * GROUND_HEIGHT;
	float x_step = window.getSize().x / HILL_NUMBER;
	float x_range = x_step * HILL_X_RANGE;
	float y_step = window.getSize().y * HILL_HEIGHT;
	float y_range = y_step;

	float X = window.getSize().x;
	float Y = window.getSize().y;
	Vector2f point;
	for (float x_start = 0; x_start < X; x_start += x_step) {
		point = generate_point(
			x_start, x_start + x_step, x_range,
			median - y_step, median, y_range
		);
		m_surface.append(Vertex(point));
		m_surface.append(Vertex(Vector2f(point.x, Y)));
		m_soil.append(Vertex(Vector2f(point.x, point.y + y_range)));
		m_soil.append(Vertex(Vector2f(point.x, Y)));
	}
	
	m_surface[0].position.x = 0;
	m_surface[1].position.x = 0;
	m_surface[m_surface.getVertexCount()-1].position.x = X;
	m_surface[m_surface.getVertexCount()-2].position.x = X;
	
	m_soil[0].position.x = 0;
	m_soil[1].position.x = 0;
	m_soil[m_soil.getVertexCount()-1].position.x = X;
	m_soil[m_soil.getVertexCount()-2].position.x = X;

}

void GroundDrawer::generate_minerals (RenderWindow &window) {
	CircleShape mineral;
	mineral.setRadius(5.f);
	mineral.setPointCount(4);
	mineral.setOrigin(mineral.getRadius(), mineral.getRadius());

	vector<Color> colors = {
		MINERAL_COLOR_0,
		MINERAL_COLOR_1,
		MINERAL_COLOR_2
	};

	float y_start = window.getSize().y * (GROUND_HEIGHT + HILL_HEIGHT) + mineral.getRadius();
	float y_end = window.getSize().y;
	float y_range = y_end - y_start;
	float x_end = window.getSize().x;

	for (size_t i = 0; i < 100; i++) {
		mineral.setRotation(rand()%360);
		mineral.setPosition(generate_point(
			0.f, x_end, x_end,
			y_start, y_end,	y_range
		));
		mineral.setFillColor(colors[rand()%colors.size()]);
		m_minerals.push_back(mineral);
	}
}

void GroundDrawer::update_color (Air &air) {
	float t = air.getTemperature();

	Vector3f surfaceColor;
	Vector3f soilColor;
	if (t <= (MAX_TEMPERATURE - MIN_TEMPERATURE)/2.f + MIN_TEMPERATURE) {
		float k = (-MIN_TEMPERATURE + t) / (MAX_TEMPERATURE - MIN_TEMPERATURE) * 2;
		surfaceColor = SURFACE_COLD_COLOR + (SURFACE_WARM_COLOR - SURFACE_COLD_COLOR) * k;
		soilColor = SOIL_COLD_COLOR + (SOIL_WARM_COLOR - SOIL_COLD_COLOR) * k;
	} else {
		float k = ((-MIN_TEMPERATURE + t) / (MAX_TEMPERATURE - MIN_TEMPERATURE) - 0.5f) * 2.f;
		surfaceColor = SURFACE_WARM_COLOR + (SURFACE_HOT_COLOR - SURFACE_WARM_COLOR) * k;
		soilColor = SOIL_WARM_COLOR + (SOIL_HOT_COLOR - SOIL_WARM_COLOR) * k;
	}

	for (size_t i = 0; i < m_surface.getVertexCount(); i++)
		m_surface[i].color = Color(surfaceColor.x, surfaceColor.y, surfaceColor.z);
	for (size_t i = 0; i < m_soil.getVertexCount(); i++)
		m_soil[i].color = Color(soilColor.x, soilColor.y, soilColor.z);
	
}

void GroundDrawer::update_minerals (float minerals) {
	m_mineralsNumber = 
		m_minerals.size() * 
		(-MIN_MINERALS + minerals) / 
		(MAX_MINERALS - MIN_MINERALS);
}

void GroundDrawer::draw (RenderWindow &window) {
	window.draw(m_surface);
	window.draw(m_soil);
	for (size_t i = 0; i < m_mineralsNumber; i++)
		window.draw(m_minerals[i]);
}

//Private functions

Vector2f GroundDrawer::generate_point (float x_start, float x_end, float x_range, 
									   float y_start, float y_end, float y_range) {
	Vector2f point = Vector2f(rand()%(int)x_range, rand()%(int)y_range);
	point.x += (abs(x_start - x_end) - x_range) / 2 + x_start; 
	point.y += (abs(y_start - y_end) - y_range) / 2 + y_start; 
	return point;
}










