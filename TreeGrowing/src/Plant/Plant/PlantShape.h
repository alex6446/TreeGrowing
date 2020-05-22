#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Shapes/ConcaveShape.hpp>

class PlantShape : public thor::ConcaveShape {
private:

	sf::Vector2f 	mOrigin;
	sf::Vector2f 	mPosition;
	sf::Vector2f 	mScale;

public:

	PlantShape ();

	inline sf::Vector2f getOrigin () const { return mOrigin; } 
	inline void setOrigin (sf::Vector2f origin) { mOrigin = origin; }

	inline sf::Vector2f getScale () const { return mScale; }
	void setScale (sf::Vector2f k);
	void scale (sf::Vector2f k);

	void setPosition (sf::Vector2f position);
	inline sf::Vector2f getPosition () const { return mPosition; }

	void loadFromFile (std::string file);

};