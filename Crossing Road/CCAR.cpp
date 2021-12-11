#include "CCAR.h"

using namespace sf;
using namespace std;


CCAR::CCAR(string direction, Vector2f pos) : CENEMY(direction, pos) {
	shape.setSize(Vector2f(500, 150));
	shape.setFillColor(Color::Blue);
}