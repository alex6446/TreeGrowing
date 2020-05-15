#pragma once

// AIR /////////////////////
// Colors
#define BG_COLOR 			 sf::Color(20.f, 150.f, 250.f)
#define BG_COLOR_CHANGE		 140.f
							
// Ranges
#define MIN_HUMIDITY 		 0.f
#define MAX_HUMIDITY 		 1.f
#define DEFAULT_HUMIDITY 	 0.6f

#define MIN_TEMPERATURE 	-20.f 
#define MAX_TEMPERATURE  	 60.f 
#define DEFAULT_TEMPERATURE  20.f 

// GROUND //////////////////
// Ranges
#define MIN_MINERALS 		 0.f
#define MAX_MINERALS 		 1.f
#define DEFAULT_MINERALS 	 0.6f

// Generation
#define GROUND_HEIGHT		 0.9
#define HILL_NUMBER 		 30
#define HILL_HEIGHT 		 0.03
#define HILL_X_RANGE		 0.7

// Colors
#define SURFACE_COLD_COLOR	sf::Vector3f(255.f, 250.f, 250.f)
#define SOIL_COLD_COLOR		sf::Vector3f(129.f, 108.f, 91.f)
#define SURFACE_WARM_COLOR	sf::Vector3f(86.f, 125.f, 70.f)
#define SOIL_WARM_COLOR		sf::Vector3f(54.f, 35.f, 18.f)
#define SURFACE_HOT_COLOR	sf::Vector3f(212.f, 182.f, 128.f)
#define SOIL_HOT_COLOR		sf::Vector3f(112.f, 70.f, 42.f)

#define MINERAL_COLOR_0 	sf::Color(158, 116, 68)
#define MINERAL_COLOR_1 	sf::Color(168, 85, 77)
#define MINERAL_COLOR_2 	sf::Color(149, 155, 171)

// SUN /////////////////////
// Ranges
#define MIN_WARM 			 0.f
#define MAX_WARM 			 1.f
#define DEFAULT_WARM 		 0.4f

#define MIN_BRIGHTNESS 		 0.f
#define MAX_BRIGHTNESS 		 1.f
#define DEFAULT_BRIGHTNESS 	 0.5f

// Colors
#define SUN_COLD_COLOR 		 sf::Vector3f(231.f, 163.f, 0.f)
#define SUN_HOT_COLOR 		 sf::Vector3f(231.f, 225.f, 210.f)

// Parameters
#define SUN_POSITION 		 sf::Vector2f(75.f, 75.f)
#define SUN_MAX_ALPHA 		 255.f
#define SUN_RADIUS 			 25.f
#define SUN_RAYS_NUMBER 	 4
#define SUN_Q_COEFFICIENT 	 2

// PATHS ///////////////////

#define MODELS_FOLDER 		"assets/Models/"
#define SHAPES_FOLDER 		"/shapes/"
#define LEAF_FILE 			"/leaf.txt"
#define SEED_FILE 			"/seed.txt"
#define CONFIG_FILE 		"/config.txt"
