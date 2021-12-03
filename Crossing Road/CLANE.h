#ifndef LANE
#define LANE

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CLANE {
protected:
	sf::RectangleShape shape;
public:
	virtual void update() = 0;
	sf::RectangleShape & getShape();
};

#endif