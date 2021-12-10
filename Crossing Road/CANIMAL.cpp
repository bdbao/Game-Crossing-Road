#include "CANIMAL.h"

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


CANIMAL::CANIMAL(string direction, Vector2f pos) : CENEMY(direction, pos) {
	shape.setSize(Vector2f(500, 150));
	shape.setFillColor(Color::Blue);
}