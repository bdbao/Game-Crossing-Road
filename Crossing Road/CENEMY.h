#ifndef _CENEMY_H_
#define _CENEMY_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

class CENEMY {
protected:
	std::string direction;
	sf::RectangleShape shape;
public:
	static const std::string LEFT;
	static const std::string RIGHT;
	CENEMY(std::string direction, sf::Vector2f pos);
	void move(float speed);
	bool isOutOfView();
	sf::RectangleShape& getShape();
};

#endif // !_CENEMY_H_
