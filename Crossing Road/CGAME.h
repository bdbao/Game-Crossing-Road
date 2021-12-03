#ifndef _CGAME_H_
#define _CGAME_H_

#include "CPEOPLE.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CGAME {
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;
	CPEOPLE player;
	
	void pollEvents();
public:
	CGAME();
	bool isRunning();
	void update();
	void render();
};


#endif // !_CGAME_H_
