#ifndef CSETTINGS_H
#define CSETTINGS_H

#include "CCONSTANT.h"
#include "SoundManager.h"
#include <iostream>

class  CSETTINGS {
public:
	CSETTINGS();
	~CSETTINGS();

	void draw(sf::RenderWindow& window);
	int getOption();

	void moveUp();
	void moveDown();
private:
	int selectedOption = 0;
	sf::Texture title;
	sf::Font font;
	sf::Text* settings = new sf::Text[CCONSTANT::NUMBER_OF_SETTING_OPTIONS];
};

#endif // !CSETTINGS_H
