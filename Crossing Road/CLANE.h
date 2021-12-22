#ifndef LANE_H
#define LANE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "CENEMY.h"
#include "CTRAFFICLIGHT.h"
#include "utils.h"

class CLANE {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	float speed;
	std::vector<CENEMY*> enemies;

	sf::Clock time;
	CTRAFFICLIGHT* traffic_light;
	bool isStopped;
	bool isSlowly;

	std::string typeEnemy;
public:
	CLANE(float speed);
	virtual ~CLANE();
	virtual void update() = 0;
	std::vector<CENEMY*>& getEnemies();
	sf::Sprite& getSprite();

	/* Set state for Traffic light */
	virtual int getTrafficLightState() = 0;
	virtual sf::Sprite* getTrafficLightShape() = 0;
	void setNormal();
	void setSlowly();
	void setStopped();

	std::string getTypeEnemy();
};

#endif