#include "CTRAFFICLIGHT.h"

CTRAFFICLIGHT::CTRAFFICLIGHT() {

	sf::Image img;

	/* Load green light */
	//img.loadFromFile("./assets/traffic_light/green.jpg");
	//texture.loadFromImage(img);
	green_texture.loadFromFile("./assets/traffic_light/green.jpg");
	green_light.setTexture(green_texture);
	green_light.setPosition(sf::Vector2f(0.f, -350.f));

	/* Load yellow light */
	//img.loadFromFile("./assets/traffic_light/yellow.jpg");
	//texture.loadFromImage(img);
	yellow_texture.loadFromFile("./assets/traffic_light/yellow.jpg");
	yellow_light.setTexture(yellow_texture);
	yellow_light.setPosition(sf::Vector2f(0.f, -350.f));

	/* Load red light */
	//img.loadFromFile("./assets/traffic_light/red.jpg");
	//texture.loadFromImage(img);
	red_texture.loadFromFile("./assets/traffic_light/red.jpg");
	red_light.setTexture(red_texture);
	red_light.setPosition(sf::Vector2f(0.f, -350.f));
}

CTRAFFICLIGHT::~CTRAFFICLIGHT() {}


sf::Sprite& CTRAFFICLIGHT::getShape() {
	if (this->state == 0)
		return green_light;
	else if (this->state == 1)
		return yellow_light;
	else
		return red_light;
}


int CTRAFFICLIGHT::getTrafficLight(sf::Clock& clock) {
	/*  |  GREEN  |  YELLOW  |  RED  |  */
	/*  {0: green, 1: yellow, 2: red}   */

	float time = clock.getElapsedTime().asSeconds();
	if (time <= CCONSTANT::GREEN_LIGHT_TIME){
		this->state = 0;
		return 0;
	}
	else if (time > CCONSTANT::GREEN_LIGHT_TIME &&
				time <= CCONSTANT::GREEN_LIGHT_TIME + CCONSTANT::YELLOW_LIGHT_TIME) {
		this->state = 1;
		return 1;
	}
	else if (time > CCONSTANT::GREEN_LIGHT_TIME + CCONSTANT::YELLOW_LIGHT_TIME &&
				time <= CCONSTANT::GREEN_LIGHT_TIME + CCONSTANT::YELLOW_LIGHT_TIME + CCONSTANT::RED_LIGHT_TIME) {
		this->state = 2;
		return 2;
	}
	else {
		clock.restart();
		this->state = 0;
		return 0;
	}
	return 0;
}