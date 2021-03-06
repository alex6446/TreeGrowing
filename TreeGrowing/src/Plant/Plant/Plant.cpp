#include "Plant.h"
#include "Config.h"
#include "Plant/ConfigReader.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui-SFML.h"

#include <iostream>

using namespace sf;
using namespace std;

Plant::Plant (Vector2f position, int id, string type) 
: 
	m_type(type),
	m_id(id),
	m_growth(0.01f),
	m_dead(false),
	m_leaves(position, type),
	m_drawable(position, type)
{
	m_name.resize(255);
	m_title.resize(255);
	m_name = m_type + " " + to_string(m_id);
	m_title =  m_name + "###" + m_type + to_string(m_id);

	string file = MODELS_FOLDER;
	file += m_type;
	string config = file + CONFIG_FILE;

	m_required = getConfigResources(config, "PLANT_REQUIRED");
	m_eatrate = getConfigResources(config, "PLANT_EATRATE");
	m_max_collected = getConfigResources(config, "PLANT_MAX_COLLECTED");
	m_max_resources = getConfigResources(config, "PLANT_MAX_RESOURCES");
	m_growingRate = getConfigFloat(config, "PLANT_GROWING_RATE");
}

void Plant::update (Air &air, Ground &ground, Sun &sun) {
	updateImGUI ();
	if (!m_dead) {
		if (m_growth < 0.15f) m_collected = m_required.multiply(m_growth * 1000.f);
		collect_resources(air, ground, sun);

		distribute_resources();

		consume();
		check_life();
		if (m_drawable.update(m_growth))
			m_leaves.generatePosition(m_drawable.getShape());
	}
	m_leaves.update(m_growth);
}

void Plant::draw (RenderWindow &window) {
	m_drawable.draw(window);
	m_leaves.draw(window);
}

void Plant::collect_resources (Air &air, Ground &ground, Sun &sun) {
	m_collected.add(m_leaves.collect(air, sun));
	//m_collected = m_leaves.collect(air, sun);
	m_collected.water += ground.getHumidity() * (m_growth + 1.f) - (air.getTemperature() - DEFAULT_TEMPERATURE) / 10.f * m_growth ;
	m_collected.materials += ground.getMinerals() * (m_growth + 1.f);
	m_collected.cutoff(m_max_collected);
}

void Plant::distribute_resources () {
	m_resources.add(m_collected.subtract(m_required.multiply(m_growth + 1.f)));
	m_resources.cutoff(m_max_resources);
	m_leaves.feed(m_collected);
	m_leaves.grow(m_collected, m_growth, m_drawable.getShape());

	// Infinitive looop here if required is close to 0 --fixed
	for (int i = 0; i < 500; i++) {
		if (!m_collected.check_capacity((m_required.multiply(m_growth + 1.f)).multiply(m_growth)))
			break;
		m_collected.subtract((m_required.multiply(m_growth + 1.f)).multiply(m_growth));
		if (m_growth < 1.f)
			m_growth += m_growingRate;
	}
	//m_resources.add(m_collected);
	//m_collected = Resources(0.f, 0.f, 0.f);
}

void Plant::consume () {
	m_resources.subtract((m_required.multiply(m_eatrate)).multiply(m_growth + 1.f));
}

void Plant::check_life () {
	if (!m_resources.water || !m_resources.energy || !m_resources.materials || !m_leaves.getLeavesCount())
		m_dead = true;
}

void Plant::updateImGUI () {
	ImGui::Begin(m_title.c_str());
    if (ImGui::CollapsingHeader("Info")) {
        ImGui::Text("Growth:");
        ImGui::SameLine();
        ImGui::Text("%.6f", m_growth);
        ImGui::Text("Leaves:");
        ImGui::SameLine();
        ImGui::Text("%i", m_leaves.getLeavesCount());
        if (ImGui::BeginTabBar("InfoBar")) {
            if (ImGui::BeginTabItem("   Plant    ")) {
                updateImGuiInfo();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("   Leaves   ")) {
                m_leaves.updateImGuiInfo();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    }
    if (ImGui::CollapsingHeader("Settings")) {
        ImGui::Text("Name");
        char input[255];
        strcpy(input, m_name.c_str());
        if( ImGui::InputText("##Change name", input, 255)) {
            m_name = input;
            m_title = input;
            m_title += "###" + m_type + to_string(m_id);
        }
        if (ImGui::BeginTabBar("SettingsBar")) {
            if (ImGui::BeginTabItem("   Plant    ")) {
                updateImGuiSettings();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("   Leaves   ")) {
                m_leaves.updateImGuiSettings();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    }
	ImGui::End();

}

void Plant::updateImGuiInfo () {
    ImGui::Text("Resources");
    ImGui::Text("Water:");
    ImGui::SameLine();
    ImGui::Text("%.6f", m_resources.water);
    ImGui::Text("Energy:");
    ImGui::SameLine();
    ImGui::Text("%.6f", m_resources.energy);
    ImGui::Text("Materials:");
    ImGui::SameLine();
    ImGui::Text("%.6f", m_resources.materials);
    ImGui::Text("Collected");
    ImGui::Text("Water:");
    ImGui::SameLine();
    ImGui::Text("%.6f", m_collected.water);
    ImGui::Text("Energy:");
    ImGui::SameLine();
    ImGui::Text("%.6f", m_collected.energy);
    ImGui::Text("Materials:");
    ImGui::SameLine();
    ImGui::Text("%.6f", m_collected.materials);
}

void Plant::updateImGuiSettings () {
    ImGui::Text("Required");
    ImGui::SliderFloat("water##Required", &m_required.water, RESOURCES_MIN_RANGE, 1.f, "%.6f");
    ImGui::SliderFloat("energy##Required", &m_required.energy, RESOURCES_MIN_RANGE, 1.f, "%.6f");
    ImGui::SliderFloat("materials##Required", &m_required.materials, RESOURCES_MIN_RANGE, 1.f, "%.6f");
    ImGui::Text("EatRate");
    ImGui::SliderFloat("water##EatRate", &m_eatrate.water, RESOURCES_MIN_RANGE, 1.f, "%.6f");
    ImGui::SliderFloat("energy##EatRate", &m_eatrate.energy, RESOURCES_MIN_RANGE, 1.f, "%.6f");
    ImGui::SliderFloat("materials##EatRate", &m_eatrate.materials, RESOURCES_MIN_RANGE, 1.f, "%.6f");	
}
