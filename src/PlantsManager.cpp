#include "PlantsManager.h"
#include "Confines.h"

#include "imgui.h"
#include "imgui-SFML.h"

using namespace std;
using namespace sf;

PlantsManager::PlantsManager () {}

void PlantsManager::setup (RenderWindow &window) {
	m_seed.setBottom(window.getSize().y * GROUND_HEIGHT);
}

void PlantsManager::update (Air &air, Ground &ground, Sun &sun, Vector2f mousePosition) {

    if (m_seed.update(mousePosition)) {
    	string plant = m_seed.getPlant();
    	if (plant == "Tree")
    		m_trees.emplace_back(m_seed.getPosition(), m_trees.size());

    }

    for (auto &tree : m_trees)
    	tree.update(air, ground, sun);

}

void PlantsManager::draw (RenderWindow &window) {
	for (auto &tree : m_trees)
    	tree.draw(window);
    m_seed.draw(window);
}

void PlantsManager::updateImGUI () {
	ImGui::Text("Plants");

    const char* items[] = { "Tree", "Flower", "Grass" };
	static const char* current_item = "Tree";
    if (ImGui::BeginCombo("##combo", current_item)) {
	    for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
	        bool is_selected = (current_item == items[n]);
	        if (ImGui::Selectable(items[n], is_selected))
	            current_item = items[n];
	        if (is_selected)
	            ImGui::SetItemDefaultFocus(); 
	    }
	    ImGui::EndCombo();
	}
	ImGui::SameLine();
	if (ImGui::Button("Get Seed")) {
		m_seed.setPlant(current_item);
	}

}
