#include "CGAME.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h> 

int main() {
	srand(time(NULL));
	CGAME * game = new CGAME();
	while (game->isRunning()) {
		game->update();
		game->render();
	}
	delete game;
	return 0;
}