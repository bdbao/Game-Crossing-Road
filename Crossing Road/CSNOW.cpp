#include "CSNOW.h"
#include "CCONSTANT.h"
#include <SFML/Graphics.hpp>


void CSNOW::createFlake()
{
	sf::CircleShape flake(float(rand()) / (float)(RAND_MAX / 3.0f) + 0.5f);
	flake.setPosition(float(rand() % CCONSTANT::WINDOW_WIDTH), 0.0f);
	flake.setFillColor(sf::Color::White);
	snowflakes.emplace_back(flake);
}

CSNOW::CSNOW(int numOfSnowflakes, int delay) : numOfSnowflakes(numOfSnowflakes), delay(delay), elapsed(0) {
	snowflakes.reserve(numOfSnowflakes);
}

void CSNOW::update()
{
	elapsed++;

	// If the delay has passed and the max num of snowflakes isn't reached, create another
	if (elapsed >= delay && snowflakes.size() < numOfSnowflakes)
	{
		createFlake();
		elapsed = 0;
	}

	for (unsigned int i = 0; i < snowflakes.size(); i++)
	{
		snowflakes[i].move(0.0f, snowflakes[i].getRadius() * 0.4f);
		if (snowflakes[i].getPosition().y >= CCONSTANT::WINDOW_HEIGHT)
		{
			snowflakes.erase(snowflakes.begin() + i);
		}
	}

}

std::vector<sf::CircleShape>& CSNOW::getSnowflakes() {
	return snowflakes;
}