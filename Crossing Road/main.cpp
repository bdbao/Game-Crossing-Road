#include "CGAME.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h> 

int main() {
	srand(time(NULL));
	CGAME * game = new CGAME();
	int state = -1;

	/* Play background music */
	//game->play_Background_music();
	sf::Music music;
	if (!music.openFromFile("./assets/sounds/background-music.wav")) {
		std::cout << "Cant open background-music file!\n";
	}
	else {
		//music.setVolume(50.2);
		music.setLoop(true);
		music.play();
	}

	while (game->isRunning()) {

		game->update();
		state = game->state();

		if (game->state() == CCONSTANT::STATE_START) {
			game->render();
		}
		else if (state == CCONSTANT::STATE_PAUSE) {
			continue;
		}
		else if (state == CCONSTANT::STATE_GAME_COMPLETED) {
			continue;
		}
		else if (state == CCONSTANT::STATE_GAME_OVER) {
			continue;
		}

		// 
	}
	delete game;
	return 0;
}