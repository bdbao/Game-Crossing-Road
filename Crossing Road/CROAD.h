#ifndef CROAD_H
#define CROAD_H

#include "CLANE.h"
#include "CENEMY.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class CROAD : public CLANE {
	std::string direction;
public:
	CROAD(sf::Vector2f pos, float speed, std::string direction);
	void update();
};

#endif
