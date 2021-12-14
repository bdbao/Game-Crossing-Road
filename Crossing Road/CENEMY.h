#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CCONSTANT.h"


#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class CENEMY {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	std::string direction;
	sf::RectangleShape shape;
public:
	CENEMY(std::string direction, sf::Vector2f pos);
	virtual ~CENEMY();
	void move(float speed);
	bool isOutOfView();
	sf::RectangleShape& getShape();

	sf::Sprite& getSprite();
};

#endif // !_CENEMY_H_
