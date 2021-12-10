#ifndef CGRASS_H
#define CGRASS_H

#include "CLANE.h"
#include "CENEMY.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class CGRASS : public CLANE {
	std::string direction;
public:
	CGRASS(sf::Vector2f pos, float speed, std::string direction);
	void update();

	sf::Sprite& getSprite();
};

#endif