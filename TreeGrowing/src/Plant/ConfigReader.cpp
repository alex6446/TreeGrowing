#include "ConfigReader.h"

bool findConfigVar (std::string file, std::string name) {
	std::ifstream fin(file);
	std::string variable;
	while (fin >> variable)
		if (variable == name)
			return true;
	return false;
}

float getConfigFloat (std::string file, std::string name) {
	std::ifstream fin(file);
	std::string variable;
	float value;
	while (fin >> variable) {
		if (variable == name) {
			fin >> value;
			return value;
		}
	}
	return 0;
}

sf::Color getConfigColor (std::string file, std::string name) {
	std::ifstream fin(file);
	std::string variable;
	float r, g, b;
	while (fin >> variable) {
		if (variable == name) {
			fin >> r >> g >> b;
			return sf::Color(r, g, b);
		}
	}
	return sf::Color::Black;
}

Resources getConfigResources (std::string file, std::string name) {
	std::ifstream fin(file);
	std::string variable;
	float w, e, m;
	while (fin >> variable)
		if (variable == name) {
			fin >> w >> e >> m;
			return Resources(w, e, m);
		}
	return Resources(0, 0, 0);
}

sf::Vector2f getConfigVector2f (std::string file, std::string name) {
	std::ifstream fin(file);
	std::string variable;
	sf::Vector2f value(0.f, 0.f);
	while (fin >> variable)
		if (variable == name) {
			fin >> value.x >> value.y;
			return value;
		}
	return value;
}