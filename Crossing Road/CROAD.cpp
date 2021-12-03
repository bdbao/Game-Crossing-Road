#include "CROAD.h"
#include "CLANE.h"
#include "CCONSTANT.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

CROAD::CROAD(Vector2f pos) {
	shape.setSize(Vector2f(CCONSTANT::VIEW_WIDTH, 200));
	shape.setFillColor(Color::Red);
	shape.setPosition(pos);
}

void CROAD::update() {

}