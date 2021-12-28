#include "CENEMY.h"


CENEMY::CENEMY(string direction, Vector2f pos): direction(direction) {
	sprite.setPosition(pos);
}


CENEMY::~CENEMY() {}


void CENEMY::move(float speed) {
	if (direction == CCONSTANT::LEFT) sprite.move(Vector2f(-speed, 0.));
	else sprite.move(Vector2f(speed, 0.));
}


bool CENEMY::isOutOfView() {
	return (sprite.getPosition().x < -2000 || sprite.getPosition().y > 2000);
}


sf::Sprite& CENEMY::getSprite() {
	return sprite;
}