#ifndef CANIMAL_H
#define CANIMAL_H

#include "CENEMY.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

class CANIMAL : public CENEMY {
public:
	CANIMAL(std::string textureFile, std::string direction, sf::Vector2f pos);
};

#endif