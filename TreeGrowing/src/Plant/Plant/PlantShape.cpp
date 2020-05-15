#include "PlantShape.h"

#include <fstream>

using namespace std;
using namespace sf;

PlantShape::PlantShape () 
: mOrigin(Vector2f(0.f, 0.f)), 
  mScale(1.f, 1.f)
{}

void PlantShape::setScale (Vector2f k) {
	Vector2f factor = Vector2f(k.x / mScale.x, k.y / mScale.y);
	Vector2f point;
	for (size_t i = 0; i < getPointCount(); i++) {
		point = getPoint(i) - mOrigin;
		point = Vector2f(point.x * factor.x, point.y * factor.y);
		point += mOrigin;
		setPoint(i, point);
	}
	mScale = k;
}

void PlantShape::scale (sf::Vector2f k) { 
	setScale(Vector2f(mScale.x * k.x, mScale.y * k.y)); 
}

void PlantShape::setPosition (Vector2f position) {
	Vector2f move = position - mOrigin;
	mOrigin += move;
	for (size_t i = 0; i < getPointCount(); i++)
		setPoint(i, getPoint(i) + move);
	mPosition = position;
}

void PlantShape::loadFromFile (std::string file) {
	ifstream fin(file);
	vector<Vector2f> verticies;
	Vector2f point;
	while (fin >> point.x >> point.y)
		verticies.push_back(point);
	setPointCount(verticies.size());
	for (size_t i = 0; i < verticies.size(); i++)
		setPoint(i, verticies[i]);
	mOrigin = Vector2f((getPoint(getPointCount()-1).x + getPoint(0).x)/2, getPoint(0).y);
	mScale = Vector2f(1.f, 1.f);
}

