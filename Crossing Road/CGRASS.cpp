#include "CGRASS.h"
#include "CCONSTANT.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

CGRASS::CGRASS(Vector2f pos): CLANE(1) {
	shape.setSize(Vector2f(CCONSTANT::VIEW_WIDTH, CCONSTANT::UNIT));
	shape.setPosition(pos);
}