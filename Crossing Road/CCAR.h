#ifndef CCAR_H
#define CCAR_H



#include "utils.h"
#include "CENEMY.h"

#include <string>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class CCAR : public CENEMY {
public:
	CCAR(std::string direction, sf::Vector2f pos);
	void update();

	string getEnemyName() {
		return "car";
	}
};

#endif