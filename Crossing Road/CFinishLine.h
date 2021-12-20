#ifndef _CROAD_H_
#define _CROAD_H_


#include "CLANE.h"
#include "CENEMY.h"
#include "CPEOPLE.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class CFinishLine {
private:	
	sf::Texture texture;
	sf::Sprite sprite;

public:
	CFinishLine(sf::Vector2f pos);
	
	sf::Sprite* getShape();
	bool checkCollision(CPEOPLE& player);

	/* Tmp function */
	void update();
	int getTrafficLightState();
	sf::Sprite* getTrafficLightShape();
};

#endif _CROAD_H_