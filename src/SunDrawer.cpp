#include "SunDrawer.h"
#include "Confines.h"
#include <iostream>

using namespace sf;
using namespace std;

SunDrawer::SunDrawer () {
	CircleShape circle;
	circle.setRadius(SUN_RADIUS);
	circle.setOrigin(circle.getRadius(),circle.getRadius());
	circle.setPosition(SUN_POSITION);
	circle.setFillColor(Color(SUN_COLD_COLOR.x, SUN_COLD_COLOR.y, SUN_COLD_COLOR.z));
	for (size_t i = 0; i < SUN_RAYS_NUMBER; i++)
		m_circles.push_back(circle);
}

void SunDrawer::update_warm (float warm) {
	float k = (-MIN_WARM + warm) / (MAX_WARM - MIN_WARM);
	Vector3f color = SUN_COLD_COLOR + (SUN_HOT_COLOR - SUN_COLD_COLOR) * k;
	Color sun_color = Color(color.x, color.y, color.z);
	for (auto &circle : m_circles) {
		circle.setFillColor(sun_color);
		sun_color.a /= SUN_Q_COEFFICIENT;
	}
}

void SunDrawer::update_brightness (float brightness) {
	float k = (-MIN_BRIGHTNESS + brightness) / (MAX_BRIGHTNESS - MIN_BRIGHTNESS);
	float radius = k * (compute_radius(SUN_RAYS_NUMBER) - SUN_RADIUS) + SUN_RADIUS;
	for (size_t i = 0; i < m_circles.size(); i++) {
		m_circles[i].setRadius(compute_radius(i+1));
		if (radius < m_circles[i].getRadius())
			m_circles[i].setRadius(radius);
		m_circles[i].setOrigin(m_circles[i].getRadius(), m_circles[i].getRadius());
	}
}

void SunDrawer::draw (RenderWindow &window) {
	for (auto &circle : m_circles)
		window.draw(circle);
}

float SunDrawer::compute_radius (unsigned index) {
	float r = SUN_RADIUS;
	for (size_t i = 1; i < index; i++) {
		r *= SUN_Q_COEFFICIENT;
	}
	return r;
}
