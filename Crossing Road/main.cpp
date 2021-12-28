#include "CGAME.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h> 

int main() {
	srand(time(NULL));
	CGAME * game = new CGAME();
	int state = -1;
	
	while (game->isRunning()) {
		game->pollEvents(); cout << SoundManager::getInstance()->getIsMute() << endl;
		game->update();
		if (game->state() == CCONSTANT::STATE_START) {
			game->render();
		}

		// 
	}
	delete game;
	return 0;
}