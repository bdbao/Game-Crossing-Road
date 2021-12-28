#include "CCAR.h"


CCAR::CCAR(string direction, Vector2f pos) : CENEMY(direction, pos) {
	string ver = to_string(Rand(1, 5));
	if (direction == CCONSTANT::LEFT) {
		texture.loadFromFile("./assets/enemies/car_v" + ver + "_toLeft.png");
	}
	else {
		texture.loadFromFile("./assets/enemies/car_v" + ver + "_toRight.png");
	}
	sprite.setTexture(texture);
}


void CCAR::update() {}

