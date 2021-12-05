#ifndef GRASS_H
#define GRASS_H

#include "CLANE.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CGRASS : public CLANE {
	sf::RectangleShape shape;
public:
	CGRASS(sf::Vector2f pos);
};

#endif
