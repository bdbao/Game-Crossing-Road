#ifndef CGRASS_H
#define CGRASS_H

#include "utils.h"
#include "CLANE.h"
#include "CENEMY.h"
#include "CANIMAL.h"
#include "CCONSTANT.h"
#include "CPENGUIN.h"
#include "CSNOWMAN.h"
#include "CREINDEER.h"
#include "CSIBERIANDOG.h"

#include <vector>
#include <string>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class CGRASS : public CLANE {
	std::string direction;
public:
	CGRASS(sf::Vector2f pos, float speed, std::string direction);
	void update();
	int getTrafficLightState();
	sf::Sprite* getTrafficLightShape();
};

#endif