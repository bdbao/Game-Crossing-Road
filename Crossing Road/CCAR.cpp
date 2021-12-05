#include "CCAR.h"

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


CCAR::CCAR(string direction, Vector2f pos) : CENEMY(direction, pos) {
}