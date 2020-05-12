#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include "Plant/Resources.h"

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

Resources getConfigResource (std::string file, std::string name) {
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