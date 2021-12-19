#include "CANIMAL.h"

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


CANIMAL::CANIMAL(string textureFile, string direction, Vector2f pos) : CENEMY(direction, pos) {
	if (!texture.loadFromFile("assets/enemies/" + textureFile + ".png")) {
		cout << "Cannot find animal texture." << endl;
		return;
	}
	sprite.setTexture(texture);

	//shape.setSize(Vector2f(500, 150));
	//shape.setFillColor(Color::Blue);
}