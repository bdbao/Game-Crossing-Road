#include "CPEOPLE.h"
#include "CCONSTANT.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

CPEOPLE::CPEOPLE() {
	//texture.create(CCONSTANT::UNIT, CCONSTANT::UNIT);
	//shape.setTexture(texture);
	shape.setSize(Vector2f(100, 100));
	shape.setFillColor(Color::White);
	shape.setPosition(Vector2f(0.f, 0.f));
}

void CPEOPLE::moveUp() {
	shape.move(Vector2f(0.f, (-1) * CCONSTANT::UNIT));
}

void CPEOPLE::moveLeft() {
	if (shape.getPosition().x > -500)
		shape.move(Vector2f((-1) * CCONSTANT::UNIT, 0));
}

void CPEOPLE::moveRight() {
	if (shape.getPosition().x < 500)
		shape.move(Vector2f(CCONSTANT::UNIT, 0));
}
void CPEOPLE::moveDown() {
	shape.move(Vector2f(0, CCONSTANT::UNIT));
}