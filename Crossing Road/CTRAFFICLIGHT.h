#ifndef _CTRAFFICLIGHT_H_
#define _CTRAFFICLIGHT_H_


#include "CCONSTANT.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



class CTRAFFICLIGHT {
private:
	sf::Texture green_texture;
	sf::Texture yellow_texture;
	sf::Texture red_texture;
	sf::Sprite green_light;
	sf::Sprite yellow_light;
	sf::Sprite red_light;

	int state;	// {0: green, 1: yellow, 2: red}
public:
	CTRAFFICLIGHT();
	~CTRAFFICLIGHT();

	sf::Sprite& getShape();
	int getTrafficLight(sf::Clock& clock);

};

#endif // !_CTRAFFICLIGHT_H_
