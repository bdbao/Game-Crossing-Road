#include "CENEMY.h"
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;

const string CENEMY::LEFT = "LEFT";
const string CENEMY::RIGHT = "RIGHT";

CENEMY::CENEMY(string direction, Vector2f pos): direction(direction) {
	shape.setPosition(pos);
	shape.setSize(Vector2f(500, 150));
	shape.setFillColor(Color::Blue);
}

void CENEMY::move(float speed) {
	if (direction == LEFT) shape.move(Vector2f(-speed, 0.));
	else shape.move(Vector2f(speed, 0.));
}

bool CENEMY::isOutOfView() {
	return (shape.getPosition().x < -2000 || shape.getPosition().y > 2000);
}

sf::RectangleShape& CENEMY::getShape() {
	return shape;
}