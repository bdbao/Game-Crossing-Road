#ifndef CCAR_H
#define CCAR_H

#include "CENEMY.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

class CCAR : public CENEMY {
public:
	CCAR(std::string direction, sf::Vector2f pos);
};

#endif