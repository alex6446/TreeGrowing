#pragma once

#include <SFML/Graphics.hpp>

#include "LeafDrawer.h"
#include "Air.h"
#include "Sun.h"
#include "PlantShape.h"

#include "Resources.h"

class Leaf {
private:

    Resources 	m_resources;
    Resources 	m_required;
    Resources 	m_ration;
    
    float       m_square;
    bool 		m_dead;

    LeafDrawer  m_drawable;

public:

    Leaf (Resources &required, Resources &resources, float scale, sf::Vector2f &origin);
    ~Leaf ();

    float getWater (Air &air, Sun &sun);
    float getEnergy (Air &air, Sun &sun);
    void feed (Resources &resources);

    void setSquare (float square);
    void generatePosition (PlantShape &shape);
    void scalePosition (float growth);

    bool isDead () { return m_dead; }
    bool isActive () { return m_drawable.isActive(); }

    void update (float growth);
    void draw (sf::RenderWindow &window);

private:

    void consume ();
    void check_life ();
};
