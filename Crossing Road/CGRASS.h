#ifndef GRASS
#define GRASS

#include "CLANE.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CGRASS : public CLANE {
	sf::RectangleShape shape;
public:
	CGRASS(sf::Vector2f pos);
};

#endif
