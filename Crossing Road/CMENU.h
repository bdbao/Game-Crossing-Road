#ifndef CMENU_H
#define CMENU_H

#include "CCONSTANT.h"
#include "CSETTINGS.h"
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
	sf::Text* menu = new sf::Text[CCONSTANT::NUMBER_OF_OPTIONS];
};

#endif // !CMENU_H
