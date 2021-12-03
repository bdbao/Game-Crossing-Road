﻿#ifndef _CPEOPLE_H_
#define _CPEOPLE_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CPEOPLE {
	sf::Texture texture;
	sf::Sprite shape;
	int textureId;
	int prevTextureId;
	int animationTimer;
	bool isAnimating;
	bool isDead;
	int nextTextureId(int id);
	void setTextureId(int id);
	void processAnimation(int centerId);
	sf::IntRect getTextureRect(int id);
public:
	CPEOPLE();
	sf::Sprite& getShape();
	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();
	void setIsAnimating(bool state);
	/*
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);
	bool isFinish();
	bool isDead();
	*/
};

#endif // !_CPEOPLE_H_
