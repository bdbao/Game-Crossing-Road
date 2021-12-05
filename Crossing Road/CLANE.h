#ifndef LANE_H
#define LANE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CENEMY.h"

class CLANE {
protected:
	sf::RectangleShape shape;
	float speed;
	std::vector<CENEMY*> enemies;
public:
	CLANE(float speed);
	virtual void update() = 0;
	std::vector<CENEMY*>& getEnemies();
	sf::RectangleShape & getShape();
};

#endif