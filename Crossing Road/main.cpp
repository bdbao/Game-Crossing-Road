#include "CGAME.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h> 

int main() {
	srand(time(NULL));
	CGAME * game = new CGAME();
	int state = -1;
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