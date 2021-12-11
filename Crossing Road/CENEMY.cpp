#include "CENEMY.h"
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CCONSTANT.h"

using namespace sf;
using namespace std;

CENEMY::CENEMY(string direction, Vector2f pos): direction(direction) {
	shape.setPosition(pos);
}

void CENEMY::move(float speed) {
	if (direction == CCONSTANT::LEFT) shape.move(Vector2f(-speed, 0.));
	else shape.move(Vector2f(speed, 0.));
}

bool CENEMY::isOutOfView() {
	return (shape.getPosition().x < -2000 || shape.getPosition().y > 2000);
}

sf::RectangleShape& CENEMY::getShape() {
	return shape;
}

sf::Sprite& CENEMY::getSprite() {
	return sprite;
}