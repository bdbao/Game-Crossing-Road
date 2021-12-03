#ifndef _CGAME_H_
#define _CGAME_H_

#include "CPEOPLE.h"
#include "CLANE.h"
#include "CROAD.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class CGAME {
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;
	CPEOPLE player;
	std::vector<CLANE*> lanes;
	
	void pollEvents();
public:
	CGAME();
	bool isRunning();
	void update();
	void render();
};


#endif // !_CGAME_H_
