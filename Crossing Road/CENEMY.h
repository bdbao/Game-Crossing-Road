#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CCONSTANT.h"

#include <string>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class CENEMY {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	std::string direction;
public:
	CENEMY(std::string direction, sf::Vector2f pos);
	virtual ~CENEMY();
	virtual void update() = 0;
	void move(float speed);
	bool isOutOfView();
	sf::Sprite& getSprite();
};

#endif // !_CENEMY_H_
