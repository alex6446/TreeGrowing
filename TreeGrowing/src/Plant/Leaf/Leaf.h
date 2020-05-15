#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "LeafDrawer.h"

#include "World/Air.h"
#include "World/Sun.h"

#include "Plant/Plant/PlantShape.h"
#include "Plant/Resources.h"

class Leaf {
private:

    Resources 	m_resources;
    std::shared_ptr<Resources> 	m_required;
    std::shared_ptr<Resources> 	m_eatrate;
    std::shared_ptr<Resources>  m_max_resources;

    float           m_square;  
    bool 		    m_dead;
    std::string     m_type;

    LeafDrawer      m_drawable;

public:

    Leaf (
        std::shared_ptr<Resources> required, 
        std::shared_ptr<Resources> eatrate,
        std::shared_ptr<Resources> max_resources,
        Resources &resources, 
        float scale, 
        sf::Vector2f origin,
        std::string type,
        sf::ConvexShape &mesh
    );
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
