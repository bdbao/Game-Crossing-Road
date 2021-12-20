#ifndef CSNOW_H
#define CSNOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class CSNOW {
	unsigned int elapsed;		
	unsigned int numOfSnowflakes;
	unsigned int delay;
	std::vector<sf::CircleShape> snowflakes;

	void createFlake();
public:
	CSNOW(int numOfSnowflakes = 200, int delay = 10);
	void update();
	std::vector<sf::CircleShape>& getSnowflakes();
};

#endif