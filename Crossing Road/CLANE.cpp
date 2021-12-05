#include "CLANE.h"
#include "CENEMY.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

using namespace sf;

RectangleShape & CLANE::getShape() {
	return shape;
}

CLANE::CLANE(float speed): speed(speed) {}

std::vector<CENEMY*>& CLANE::getEnemies() {
	return enemies;
}