#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "CROAD.h"
#include "CLANE.h"
#include "CCONSTANT.h"
#include "CCAR.h"
#include "utils.h"

using namespace std;
using namespace sf;

CROAD::CROAD(Vector2f pos, float speed, string direction): CLANE(speed), direction(direction) {
	shape.setSize(Vector2f(CCONSTANT::VIEW_WIDTH, 200));
	shape.setFillColor(Color::Red);
	shape.setPosition(pos);
}

void CROAD::update() {
	if (enemies.empty()) {
		if (direction == CCAR::LEFT)
			enemies.push_back(new CCAR(direction, Vector2f(600, shape.getPosition().y + rand() % 50)));
		if (direction == CCAR::RIGHT)
			enemies.push_back(new CCAR(direction, Vector2f(-1000, shape.getPosition().y + rand() % 50)));
		return ;
	}
		
	RectangleShape& lastEnemyShape = enemies.back()->getShape();
	if (Rand(1, 100) <= 60) {
		if (direction == CCAR::LEFT && lastEnemyShape.getPosition().x <= -200)
			enemies.push_back(new CCAR(direction, Vector2f(1400, shape.getPosition().y + rand()%50)));
		if (direction == CCAR::RIGHT && lastEnemyShape.getPosition().x >= -200)
			enemies.push_back(new CCAR(direction, Vector2f(-1400, shape.getPosition().y + rand()%50)));
	}

	for (int i = 0; i < (int)enemies.size(); i++)
		if (enemies[i]->isOutOfView())
			enemies.erase(enemies.begin() + i);

	for (int i = 0; i < (int)enemies.size(); i++)
		enemies[i]->move(speed);
}