#include "PlantsManager.h"
#include "Config.h"

#include <iostream>
#include <filesystem>

#include "ImGUI/imgui.h"
#include "ImGUI/imgui-SFML.h"

using namespace std;
using namespace sf;

PlantsManager::PlantsManager () {
	std::string s = MODELS_FOLDER;
	std::vector<std::string> r;
    for(auto& p : filesystem::directory_iterator(s))
        m_types.push_back((p.path().string()).erase(0, s.size()));

    m_current_type = m_types[0];
}

void PlantsManager::setup (RenderWindow &window) {
	m_seed.setBottom(window.getSize().y * GROUND_HEIGHT);
}

void PlantsManager::update (Air &air, Ground &ground, Sun &sun, Vector2f mousePosition) {

    if (m_seed.update(mousePosition)) {
    	m_plants.emplace_back(m_seed.getPosition(), m_plants.size(), m_seed.getPlant());
    }

    for (auto &plant : m_plants)
    	plant.update(air, ground, sun);

}

void PlantsManager::draw (RenderWindow &window) {
	for (auto &plant : m_plants)
    	plant.draw(window);
    m_seed.draw(window);
}

void PlantsManager::updateImGUI () {
	ImGui::Text("Plants");

    if (ImGui::BeginCombo("##combo", m_current_type.c_str())) {
	    for (int n = 0; n < m_types.size(); n++) {
	        bool is_selected = (m_current_type == m_types[n]);
	        if (ImGui::Selectable(m_types[n].c_str(), is_selected))
	            m_current_type = m_types[n];
	        if (is_selected)
	            ImGui::SetItemDefaultFocus(); 
	    }
	    ImGui::EndCombo();
	}
	ImGui::SameLine();
	if (ImGui::Button("Get Seed")) {
		m_seed.setPlant(m_current_type);
	}

}
