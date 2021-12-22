#include "CROAD.h"

using namespace std;
using namespace sf;

CROAD::CROAD(Vector2f pos, float speed, string direction): CLANE(speed) {
	texture.loadFromFile("./assets/graphics/road.jpg");
	this->direction = direction;
	sprite = sf::Sprite(texture);
	sprite.setPosition(pos);
	Vector2u size = texture.getSize();
	cout << size.x << " " << size.y << endl;
	sprite.setScale(Vector2f((float)CCONSTANT::LANE_WIDTH / size.x, (float) CCONSTANT::LANE_HEIGHT / size.y));
	cout << sprite.getScale().x << " " << sprite.getScale().y << endl;
}

CROAD::~CROAD() {
}

void CROAD::update() {
	if (enemies.empty()) {
		if (direction == CCONSTANT::LEFT)
			enemies.push_back(new CCAR(direction, Vector2f(Rand(-(int)CCONSTANT::WINDOW_WIDTH / 2.f, CCONSTANT::WINDOW_WIDTH / 2.f), sprite.getPosition().y + 20)));
		if (direction == CCONSTANT::RIGHT)
			enemies.push_back(new CCAR(direction, Vector2f(Rand(-(int)CCONSTANT::WINDOW_WIDTH / 2.f, CCONSTANT::WINDOW_WIDTH / 2.f), sprite.getPosition().y + 20)));
		return ;
	}
		
	Sprite& lastEnemyShape = enemies.back()->getSprite();
	if (Rand(1, 100) <= 60) {
		typeEnemy = "car";
		
		if (direction == CCONSTANT::LEFT && lastEnemyShape.getPosition().x <= -200)
			enemies.push_back(new CCAR(direction, Vector2f(CCONSTANT::WINDOW_WIDTH + Rand(100, 400), sprite.getPosition().y + 20)));
		if (direction == CCONSTANT::RIGHT && lastEnemyShape.getPosition().x >= -200)
			enemies.push_back(new CCAR(direction, Vector2f(-(int)CCONSTANT::WINDOW_WIDTH - Rand(100, 400), sprite.getPosition().y + 20)));
	}

	for (int i = 0; i < (int)enemies.size(); i++)
		if (enemies[i]->isOutOfView())
			enemies.erase(enemies.begin() + i);


	/* Adjust traffic light here */
	int traffic_state = this->getTrafficLightState();
	/* Set traffic light */
	if (traffic_state == 0)
		this->setNormal();
	else if (traffic_state == 1)
		this->setSlowly();
	else
		this->setStopped();


	/* Adjust moving speed by traffic light */
	float moving_speed = this->speed;
	if (this->isStopped) {
		moving_speed = 0.0;
	}
	else if (this->isSlowly) {
		moving_speed = CCONSTANT::SLOW_DOWN_SPEED;
	}

	/* Moving with moving speed */
	for (int i = 0; i < (int)enemies.size(); i++)
		enemies[i]->move(moving_speed);
}

int CROAD::getTrafficLightState() {
	return this->traffic_light->getTrafficLight(this->time);
}

sf::Sprite* CROAD::getTrafficLightShape() {
	sf::Vector2f pos = this->sprite.getPosition();
	return &this->traffic_light->getShape(pos);
}