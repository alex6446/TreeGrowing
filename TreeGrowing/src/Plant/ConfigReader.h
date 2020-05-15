#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include "Plant/Resources.h"

bool findConfigVar (std::string file, std::string name);
float getConfigFloat (std::string file, std::string name);
sf::Color getConfigColor (std::string file, std::string name);
Resources getConfigResources (std::string file, std::string name);
sf::Vector2f getConfigVector2f (std::string file, std::string name);