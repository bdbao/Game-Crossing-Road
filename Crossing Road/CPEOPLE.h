#ifndef _CPEOPLE_H_
#define _CPEOPLE_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CPEOPLE {
public:
	//sf::Texture texture;
	sf::RectangleShape shape;
	bool isDead;
	CPEOPLE();
	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();
	/*
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);
	bool isFinish();
	bool isDead();
	*/
};

#endif // !_CPEOPLE_H_
