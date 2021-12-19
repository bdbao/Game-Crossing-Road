#include "CCAR.h"
#include "utils.h"

using namespace sf;
using namespace std;

CCAR::CCAR(string direction, Vector2f pos) : CENEMY(direction, pos) {
	string ver = to_string(Rand(1, 3));
	if (direction == CCONSTANT::LEFT) {
		texture.loadFromFile("./assets/enemies/car_v" + ver + "_toLeft.png");
	}
	else {
		texture.loadFromFile("./assets/enemies/car_v" + ver + "_toRight.png");
	}
	sprite.setTexture(texture);
}