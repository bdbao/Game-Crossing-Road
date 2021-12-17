#include "CGAME.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h> 

int main() {
	srand(time(NULL));
	CGAME * game = new CGAME();
	while (game->isRunning()) {

		game->update();

		// if game->state == start
		game->render();

		// 
	}
	delete game;
	return 0;
}