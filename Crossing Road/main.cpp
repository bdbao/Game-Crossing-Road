#include "CGAME.h"


int main() {
	CGAME * game = new CGAME();
	while (game->isRunning()) {
		game->update();
		game->render();
	}
	delete game;
	return 0;
}