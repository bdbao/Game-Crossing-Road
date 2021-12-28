#include "CANIMAL.h"


CANIMAL::CANIMAL(string textureFile, string direction, Vector2f pos) : CENEMY(direction, pos) {
	if (!texture.loadFromFile("assets/enemies/" + textureFile + ".png")) {
		cout << "Cannot find animal texture." << endl;
		return;
	}
	sprite.setTexture(texture);
	textureId = (direction == CCONSTANT::LEFT) ? 3 : 6;
	prevTextureId = textureId + 1;
	sprite.setTextureRect(getTextureRect(textureId));
	animationTimer = 0;
}


IntRect CANIMAL::getTextureRect(int id) {
	return IntRect((id % 3) * 100, (id / 3) * 100, 100, 100);
}


int CANIMAL::nextTextureId(int id) {
	if (id % 3 == 2) return id - 1;
	else if (id % 3 == 0) return id + 1;
	else {
		if (prevTextureId == id - 1) return id + 1;
		else return id - 1;
	}
}


void CANIMAL::setTextureId(int id) {
	prevTextureId = textureId;
	textureId = id;
}


void CANIMAL::update() {
	animationTimer += 1;
	if (animationTimer >= CCONSTANT::ANIMATION_TIMER_LIMIT + 10) {
		animationTimer = 0;
		setTextureId(nextTextureId(textureId));
		sprite.setTextureRect(getTextureRect(textureId));
	}
}