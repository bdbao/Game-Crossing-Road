#ifndef CANIMAL_H
#define CANIMAL_H

#include "CENEMY.h"

#include <string>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class CANIMAL : public CENEMY {
protected:
	int textureId;
	int prevTextureId;
	int animationTimer;
	sf::IntRect getTextureRect(int id);
	int nextTextureId(int id);
	void setTextureId(int id);
public:
	CANIMAL(std::string textureFile, std::string direction, sf::Vector2f pos);
	virtual ~CANIMAL() {}
	void update();
};

#endif