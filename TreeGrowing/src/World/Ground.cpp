#include "Ground.h"
#include "Config.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui-SFML.h"

using namespace sf;

Ground::Ground () 
: 
	m_minerals(DEFAULT_MINERALS),
	m_humidity(DEFAULT_HUMIDITY) 
{}

void Ground::setup (RenderWindow &window, Air &air) {
	m_drawable.generate_mesh(window);
	m_drawable.generate_minerals(window);
	m_drawable.update_color(air);
	m_drawable.update_minerals(m_minerals);
}

void Ground::update (Air &air) {
	if (air.isUpdated())
		m_drawable.update_color(air);
}

void Ground::draw (RenderWindow &window) {
	m_drawable.draw(window);
}

void Ground::updateImGUI () {
	ImGui::Text("Ground");
	if (ImGui::SliderFloat("Minerals##Ground", &m_minerals, MIN_MINERALS, MAX_MINERALS))
		m_drawable.update_minerals(m_minerals);

	ImGui::SliderFloat("Humidity##Ground", &m_humidity, MIN_HUMIDITY, MAX_HUMIDITY);
}
