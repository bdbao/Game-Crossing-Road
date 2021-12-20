#ifndef _CGAME_H_
#define _CGAME_H_

#include "CCAR.h"
#include "CLANE.h"
#include "CROAD.h"
#include "CSNOW.h"
#include "CGRASS.h"
#include "CPEOPLE.h"
#include "CCONSTANT.h"
#include "SoundManager.h"
#include "CTRAFFICLIGHT.h"
#include "CFinishLine.h"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class CGAME {
	/* Display */
	sf::RenderWindow window;
	sf::View view;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
	CSNOW foreground;

	/* Core game */
	sf::Event event;
	CPEOPLE player;
	std::vector<CLANE*> lanes;
	int game_level;
	CFinishLine* finish_line;

	/* Music */
	SoundManager* sound_manager;

	/* Event manager */
	int game_state;
	void pollEvents();
public:
	CGAME();
	~CGAME();
	
	bool isRunning();
	int state();

	void initLevel(int level);
	
	void update();
	void render();

	void play_Background_music();
	
	//Load and Save Game
	void loadGame();
	bool saveGame();
	void clearSavedGame();
};


#endif // !_CGAME_H_
