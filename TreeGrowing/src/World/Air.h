#pragma once

#include <SFML/Graphics.hpp>

class Air {
private:

	float m_humidity; 	// 0 .. 1
	float m_temperature; 	// -20 .. 60

	sf::Color 	m_color;
	bool 		m_updated;

public:

	Air ();

	inline float getHumidity () const { return m_humidity; }
	inline float getTemperature () const { return m_temperature; }
	float getTemperatureNormalized ();
	inline sf::Color getColor () const { return m_color; } 
	inline bool isUpdated () const { return m_updated; }

	void updateImGUI ();
	void update ();

private:

	void update_color ();

};