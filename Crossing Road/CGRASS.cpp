#include "CGRASS.h"


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
			//enemies.push_back(new CANIMAL("reindeer_v1", direction, Vector2f(Rand(-(int)CCONSTANT::WINDOW_WIDTH / 2.f, CCONSTANT::WINDOW_WIDTH / 2.f), sprite.getPosition().y + 50)));
			enemies.push_back(new CREINDEER("_v1", direction, Vector2f(Rand(-(int)CCONSTANT::WINDOW_WIDTH / 2.f, CCONSTANT::WINDOW_WIDTH / 2.f), sprite.getPosition().y + 50)));
		else
			//enemies.push_back(new CANIMAL("reindeer_v1", direction, Vector2f(Rand(-(int)CCONSTANT::WINDOW_WIDTH / 2.f, CCONSTANT::WINDOW_WIDTH / 2.f), sprite.getPosition().y + 50)));
			enemies.push_back(new CREINDEER("_v1", direction, Vector2f(Rand(-(int)CCONSTANT::WINDOW_WIDTH / 2.f, CCONSTANT::WINDOW_WIDTH / 2.f), sprite.getPosition().y + 50)));
		return;
	}

	Sprite& lastEnemyShape = enemies.back()->getSprite();
	if (Rand(1, 100) <= 60) {
		/* random type of animal */
		long long randNumAnimal = Rand(1, 100);
		if (randNumAnimal % 6 == 0) typeEnemy = "reindeer";
		else if (randNumAnimal % 6 == 1) typeEnemy = "penguin";
		else if (randNumAnimal % 6 == 2) typeEnemy = "polarbear";
	    else if (randNumAnimal % 6 == 3) typeEnemy = "siberiandog";
		else if (randNumAnimal % 6 == 4) typeEnemy = "snowman";
		else typeEnemy = "bulls";
		
		/* random type of penguin */
		string typeAsset = "_v1";
		if (typeEnemy == "penguin") {
			typeAsset = "_v" + to_string(rand() % 3 + 1);
		}

		/*
		if (direction == CCONSTANT::LEFT && lastEnemyShape.getPosition().x <= -200)
			enemies.push_back(new CANIMAL(typeEnemy + typeAsset, direction, Vector2f(CCONSTANT::WINDOW_WIDTH + Rand(200, 400), sprite.getPosition().y + 50)));
		if (direction == CCONSTANT::RIGHT && lastEnemyShape.getPosition().x >= -200)
			enemies.push_back(new CANIMAL(typeEnemy + typeAsset, direction, Vector2f(-(int)CCONSTANT::WINDOW_WIDTH - Rand(200, 400), sprite.getPosition().y + 50)));
		*/

		if (direction == CCONSTANT::LEFT && lastEnemyShape.getPosition().x <= -200) {
			if (typeEnemy == "penguin")
				enemies.push_back(new CPENGUIN(typeAsset, direction, Vector2f(CCONSTANT::WINDOW_WIDTH + Rand(200, 400), sprite.getPosition().y + 50)));
			else if (typeEnemy == "reindeer")
				enemies.push_back(new CREINDEER(typeAsset, direction, Vector2f(CCONSTANT::WINDOW_WIDTH + Rand(200, 400), sprite.getPosition().y + 50)));
			else if (typeEnemy == "polarBear")
				enemies.push_back(new CPOLARBEAR(typeAsset, direction, Vector2f(CCONSTANT::WINDOW_WIDTH + Rand(200, 400), sprite.getPosition().y + 50)));
			else if (typeEnemy == "siberianDog")
				enemies.push_back(new CSIBERIANDOG(typeAsset, direction, Vector2f(CCONSTANT::WINDOW_WIDTH + Rand(200, 400), sprite.getPosition().y + 50)));
			else if (typeEnemy == "snowMan")
				enemies.push_back(new CSNOWMAN(typeAsset, direction, Vector2f(CCONSTANT::WINDOW_WIDTH + Rand(200, 400), sprite.getPosition().y + 50)));
			else 
				enemies.push_back(new CBULL(typeAsset, direction, Vector2f(CCONSTANT::WINDOW_WIDTH + Rand(200, 400), sprite.getPosition().y + 50)));
		}
		
		if (direction == CCONSTANT::RIGHT && lastEnemyShape.getPosition().x >= -200) {
			if (typeEnemy == "penguin")
				enemies.push_back(new CPENGUIN(typeAsset, direction, Vector2f(-(int)CCONSTANT::WINDOW_WIDTH - Rand(200, 400), sprite.getPosition().y + 50)));
			else if (typeEnemy == "reindeer")
				enemies.push_back(new CREINDEER(typeAsset, direction, Vector2f(-(int)CCONSTANT::WINDOW_WIDTH - Rand(200, 400), sprite.getPosition().y + 50)));
			else if (typeEnemy == "polarBear")
				enemies.push_back(new CPOLARBEAR(typeAsset, direction, Vector2f(-(int)CCONSTANT::WINDOW_WIDTH - Rand(200, 400), sprite.getPosition().y + 50)));
			else if (typeEnemy == "siberianDog")
				enemies.push_back(new CSIBERIANDOG(typeAsset, direction, Vector2f(-(int)CCONSTANT::WINDOW_WIDTH - Rand(200, 400), sprite.getPosition().y + 50)));
			else if (typeEnemy == "snowMan")
				enemies.push_back(new CSNOWMAN(typeAsset, direction, Vector2f(-(int)CCONSTANT::WINDOW_WIDTH - Rand(200, 400), sprite.getPosition().y + 50)));
			else
				enemies.push_back(new CBULL(typeAsset, direction, Vector2f(-(int)CCONSTANT::WINDOW_WIDTH - Rand(200, 400), sprite.getPosition().y + 50)));
		}

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
