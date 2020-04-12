#include "Sun.h"
#include "Confines.h"

#include "imgui.h"
#include "imgui-SFML.h"

using namespace sf;

Sun::Sun () 
: 
	m_warm(DEFAULT_WARM), 
	m_brightness(DEFAULT_BRIGHTNESS) 
{ 
	m_drawable.update_warm(m_warm); 
	m_drawable.update_brightness(m_brightness); 
}

void Sun::update () {

}

void Sun::draw (RenderWindow &window) {
	m_drawable.draw(window);
}

void Sun::updateImGUI () {
	ImGui::Text("Sun");
	if (ImGui::SliderFloat("Warm##Sun", &m_warm, MIN_WARM, MAX_WARM))
		m_drawable.update_warm(m_warm);
	if (ImGui::SliderFloat("Brightness##Sun", &m_brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS))
		m_drawable.update_brightness(m_brightness);
}
