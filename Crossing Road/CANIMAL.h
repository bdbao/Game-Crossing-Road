#ifndef CANIMAL_H
#define CANIMAL_H

#include "CENEMY.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

class CANIMAL : public CENEMY {
	int textureId;
	int prevTextureId;
	int animationTimer;
	sf::IntRect getTextureRect(int id);
	int nextTextureId(int id);
	void setTextureId(int id);
public:
	CANIMAL(std::string textureFile, std::string direction, sf::Vector2f pos);
	void update();
};

#endif