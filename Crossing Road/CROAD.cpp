#include "CROAD.h"

using namespace std;
using namespace sf;

CROAD::CROAD(Vector2f pos, float speed, string direction): CLANE(speed), direction(direction) {
	//shape.setSize(Vector2f(CCONSTANT::VIEW_WIDTH, 200));
	//shape.setFillColor(Color::Red);
	texture.loadFromFile("./assets/graphics/road.jpg");
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
			enemies.push_back(new CCAR(direction, Vector2f(600, sprite.getPosition().y + rand() % 50)));
		if (direction == CCONSTANT::RIGHT)
			enemies.push_back(new CCAR(direction, Vector2f(-1000, sprite.getPosition().y + rand() % 50)));
		return ;
	}
		
	RectangleShape& lastEnemyShape = enemies.back()->getShape();
	if (Rand(1, 100) <= 60) {
		if (direction == CCONSTANT::LEFT && lastEnemyShape.getPosition().x <= -200)
			enemies.push_back(new CCAR(direction, Vector2f(Rand(1000, 1400), sprite.getPosition().y + rand()%50)));
		if (direction == CCONSTANT::RIGHT && lastEnemyShape.getPosition().x >= -200)
			enemies.push_back(new CCAR(direction, Vector2f(Rand(-1400, -1000), sprite.getPosition().y + rand() % 50)));
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

sf::Sprite& CROAD::getTrafficLightShape() {
	sf::Vector2f pos = this->sprite.getPosition();
	return this->traffic_light->getShape(pos);
}