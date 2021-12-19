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
	if (!texture.loadFromFile("assets/graphics/grass.jpg")) {
		cout << "Cannot find grass texture." << endl;
		return;
	}
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	Vector2u size = texture.getSize();
	cout << size.x << " " << size.y << endl;
	sprite.setScale(Vector2f((float)CCONSTANT::LANE_WIDTH / size.x, (float)CCONSTANT::LANE_HEIGHT / size.y));
	cout << sprite.getScale().x << " " << sprite.getScale().y << endl;
}

void CGRASS::update() {
	if (enemies.empty()) {
		if (direction == CCONSTANT::LEFT)
			enemies.push_back(new CANIMAL("reindeer_v1", direction, Vector2f(Rand(-(int)CCONSTANT::WINDOW_WIDTH/2.f, CCONSTANT::WINDOW_WIDTH/2.f), sprite.getPosition().y + 50)));
		else 
			enemies.push_back(new CANIMAL("reindeer_v1", direction, Vector2f(Rand( - (int)CCONSTANT::WINDOW_WIDTH / 2.f, CCONSTANT::WINDOW_WIDTH/2.f), sprite.getPosition().y + 50)));
		return;
	}

	Sprite& lastEnemyShape = enemies.back()->getSprite();
	if (Rand(1, 100) <= 60) {
		string animal;
		//if (Rand(1, 100) % 2 == 0) animal = "penguin";
		//else animal = "reindeer";
		animal = "reindeer";
		if (direction == CCONSTANT::LEFT && lastEnemyShape.getPosition().x <= -200)
			enemies.push_back(new CANIMAL(animal + "_v1", direction, Vector2f(Rand(1000, 1400), sprite.getPosition().y + 50)));
		if (direction == CCONSTANT::RIGHT && lastEnemyShape.getPosition().x >= -200)
			enemies.push_back(new CANIMAL(animal + "_v1", direction, Vector2f(Rand(-1400, -1000), sprite.getPosition().y + 50)));
	}

	for (int i = 0; i < (int)enemies.size(); i++)
		if (enemies[i]->isOutOfView())
			enemies.erase(enemies.begin() + i);

	for (int i = 0; i < (int)enemies.size(); i++) {
		enemies[i]->update();
		enemies[i]->move(speed);
	}
}

int CGRASS::getTrafficLightState() {
	return 0;
}

Sprite* CGRASS::getTrafficLightShape() {
	return nullptr;
}