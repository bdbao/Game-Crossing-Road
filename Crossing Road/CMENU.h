#ifndef CMENU_H
#define CMENU_H

#include "CCONSTANT.h"
#include <iostream>

class  CMENU {
public:
	CMENU();
	~CMENU();

	void draw(sf::RenderWindow& window);
	int getOption();

	void moveUp();
	void moveDown();
private:
	int selectedOption = 0;
	sf::Texture title;
	sf::Font font;
	sf::Text* menu = nullptr;
};

#endif // !CMENU_H
