#include "Air.h"
#include "Config.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui-SFML.h"

#include <iostream>

using namespace sf;
using namespace std;

Air::Air () 
: 
	m_humidity(DEFAULT_HUMIDITY), 
 	m_temperature(DEFAULT_TEMPERATURE) 
{ 
	update_color(); 
}

float Air::getTemperatureNormalized () {
	return (-MIN_TEMPERATURE + m_temperature) / (MAX_TEMPERATURE - MIN_TEMPERATURE);
}

void Air::update () {

}

void Air::update_color () {
	int k = BG_COLOR_CHANGE / (MAX_TEMPERATURE - MIN_TEMPERATURE) * (-MIN_TEMPERATURE + m_temperature);
	m_color =  sf::Color(BG_COLOR.r + k, BG_COLOR.g, BG_COLOR.b - k);	
}

void Air::updateImGUI () {
	m_updated = false;
	ImGui::Text("Air");
	ImGui::SliderFloat("Humidity##Air", &m_humidity, MIN_HUMIDITY, MAX_HUMIDITY);
	if (ImGui::SliderFloat("Temperature##Air", &m_temperature, MIN_TEMPERATURE, MAX_TEMPERATURE)) {
		update_color();
		m_updated = true;
	}
}