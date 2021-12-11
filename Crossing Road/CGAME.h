#ifndef _CGAME_H_
#define _CGAME_H_

#include "CCAR.h"
#include "CLANE.h"
#include "CROAD.h"
#include "CGRASS.h"
#include "CPEOPLE.h"
#include "CCONSTANT.h"
#include "CTRAFFICLIGHT.h"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class CGAME {
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;
	CPEOPLE player;
	std::vector<CLANE*> lanes;

	
	/* Traffic light */
	sf::Clock clock;
	CTRAFFICLIGHT traffic_light;
	
	void pollEvents();
public:
	CGAME();
	bool isRunning();
	void update();
	void render();
};


#endif // !_CGAME_H_
