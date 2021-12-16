#ifndef CROAD_H
#define CROAD_H

#include "CCAR.h"
#include "utils.h"
#include "CLANE.h"
#include "CENEMY.h"
#include "CCONSTANT.h"

#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CROAD : public CLANE {
	std::string direction;

public:
	CROAD(sf::Vector2f pos, float speed, std::string direction);
	~CROAD();

	void update();

	/* Traffic light */
	int getTrafficLightState();
	sf::Sprite& getTrafficLightShape();
};

#endif
