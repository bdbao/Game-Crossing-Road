#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "CGRASS.h"
#include "CLANE.h"
#include "CCONSTANT.h"
#include "CANIMAL.h"
#include "utils.h"

using namespace std;
using namespace sf;

CGRASS::CGRASS(Vector2f pos, float speed, string direction) : CLANE(speed), direction(direction) {
	shape.setSize(Vector2f(CCONSTANT::VIEW_WIDTH, 200));
	shape.setFillColor(Color::Red);
	shape.setPosition(pos);
}

void CGRASS::update() {
	if (enemies.empty()) {
		if (direction == CCONSTANT::LEFT)
			enemies.push_back(new CANIMAL(direction, Vector2f(600, shape.getPosition().y + rand() % 50)));
		if (direction == CCONSTANT::RIGHT)
			enemies.push_back(new CANIMAL(direction, Vector2f(-1000, shape.getPosition().y + rand() % 50)));
		return;
	}

	RectangleShape& lastEnemyShape = enemies.back()->getShape();
	if (Rand(1, 100) <= 60) {
		if (direction == CCONSTANT::LEFT && lastEnemyShape.getPosition().x <= -200)
			enemies.push_back(new CANIMAL(direction, Vector2f(Rand(1000, 1400), shape.getPosition().y + rand() % 50)));
		if (direction == CCONSTANT::RIGHT && lastEnemyShape.getPosition().x >= -200)
			enemies.push_back(new CANIMAL(direction, Vector2f(Rand(-1400, -1000), shape.getPosition().y + rand() % 50)));
	}

	for (int i = 0; i < (int)enemies.size(); i++)
		if (enemies[i]->isOutOfView())
			enemies.erase(enemies.begin() + i);

	for (int i = 0; i < (int)enemies.size(); i++)
		enemies[i]->move(speed);
}