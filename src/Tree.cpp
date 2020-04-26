#include "Tree.h"
#include "Confines.h"

#include "imgui.h"
#include "imgui-SFML.h"

using namespace sf;
using namespace std;

Tree::Tree (Vector2f position, int id) 
: 
	m_id(id),
	m_mode(0),
	m_required(0.24f, 0.35f, 0.25f),
	m_ration(0.24f, 0.35f, 0.24f),
	m_growingRate(0.00001f),
	m_growth(0.01f),
	m_dead(false),
	m_leaves(position),
	m_drawable(position)
{
	m_name.resize(255);
	m_title.resize(255);
	m_name = "Tree " + to_string(m_id);
	m_title =  m_name + "###Tree" + to_string(m_id);
}

void Tree::update (Air &air, Ground &ground, Sun &sun) {
	updateImGUI ();
	if (m_growth < 0.15f) m_collected = m_required.multiply(m_growth * 1000.f);
	collect_resources(air, ground, sun);

	distribute_resources();

	consume();
	check_life();
	if (m_drawable.update(m_growth))
		m_leaves.generatePosition(m_drawable.getShape());
	m_leaves.update(m_growth);
}

void Tree::draw (RenderWindow &window) {
	m_drawable.draw(window);
	m_leaves.draw(window);
}

void Tree::collect_resources (Air &air, Ground &ground, Sun &sun) {
	m_collected.add(m_leaves.collect(air, sun));
	//m_collected = m_leaves.collect(air, sun);
	m_collected.water += ground.getHumidity() * (m_growth + 1.f) - (air.getTemperature() - DEFAULT_TEMPERATURE) / 10.f * m_growth ;
	m_collected.materials += ground.getMinerals() * (m_growth + 1.f);
}

void Tree::distribute_resources () {
	m_resources.add(m_collected.subtract(m_required.multiply(m_growth + 1.f)));
	m_leaves.feed(m_collected);
	m_leaves.grow(m_collected, m_growth, m_drawable.getShape());

	while (m_collected.check_capacity((m_required.multiply(m_growth + 1.f)).multiply(m_growth))) {
		m_collected.subtract((m_required.multiply(m_growth + 1.f)).multiply(m_growth));
		if (m_growth < 1.f)
			m_growth += m_growingRate;
	}
	//m_resources.add(m_collected);
	//m_collected = Resources(0.f, 0.f, 0.f);
}

void Tree::consume () {
	m_resources.subtract(m_ration.multiply(m_growth + 1.f));
}

void Tree::check_life () {
	if (!m_resources.water || !m_resources.energy || !m_resources.materials)
		m_dead = true;
}

void Tree::updateImGUI () {
	ImGui::Begin(m_title.c_str());
	if (ImGui::Button("   Settings   ")) m_mode = 0;
	ImGui::SameLine();
	if (ImGui::Button("   Info   ")) m_mode = 1;
	switch (m_mode) {
		case 0:
		char input[255];
		strcpy(input, m_name.c_str());
		ImGui::Text("Required");
		ImGui::SliderFloat("water##Required", &m_required.water, 0.f, 1.f);
		ImGui::SliderFloat("energy##Required", &m_required.energy, 0.f, 1.f);
		ImGui::SliderFloat("materials##Required", &m_required.materials, 0.f, 1.f);
		ImGui::Text("Ration");
		ImGui::SliderFloat("water##Ration", &m_ration.water, 0.f, 1.f);
		ImGui::SliderFloat("energy##Ration", &m_ration.energy, 0.f, 1.f);
		ImGui::SliderFloat("materials##Ration", &m_ration.materials, 0.f, 1.f);	
		ImGui::Text("Name");
		if( ImGui::InputText("##Change name", input, 255)) {
			m_name = input;
			m_title = input;
			m_title += "###Tree" + to_string(m_id);
		}
		break;
		case 1:
		ImGui::Text("Growth:");
		ImGui::SameLine();
		ImGui::Text(to_string(m_growth).c_str());
		ImGui::Text("Resources");
		ImGui::Text("Water:");
		ImGui::SameLine();
		ImGui::Text(to_string(m_resources.water).c_str());
		ImGui::Text("Energy:");
		ImGui::SameLine();
		ImGui::Text(to_string(m_resources.energy).c_str());
		ImGui::Text("Materials:");
		ImGui::SameLine();
		ImGui::Text(to_string(m_resources.materials).c_str());
		ImGui::Text("Collected");
		ImGui::Text("Water:");
		ImGui::SameLine();
		ImGui::Text(to_string(m_collected.water).c_str());
		ImGui::Text("Energy:");
		ImGui::SameLine();
		ImGui::Text(to_string(m_collected.energy).c_str());
		ImGui::Text("Materials:");
		ImGui::SameLine();
		ImGui::Text(to_string(m_collected.materials).c_str());
	}
	ImGui::End();

}
