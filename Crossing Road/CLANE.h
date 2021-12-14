#ifndef LANE_H
#define LANE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CENEMY.h"

class CLANE {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::RectangleShape shape;
	float speed;
	std::vector<CENEMY*> enemies;
	
	bool isStopped;
	bool isSlowly;
public:
	CLANE(float speed);
	virtual ~CLANE();
	virtual void update() = 0;
	std::vector<CENEMY*>& getEnemies();
	sf::RectangleShape& getShape();

	/* Set state for Traffic light */
	void setNormal();
	void setSlowly();
	void setStopped();
};

#endif