#include "CPEOPLE.h"


using namespace std;
using namespace sf;

CPEOPLE::CPEOPLE() {
	texture.loadFromFile("./assets/texture/santa_claus.png");
	shape.setTexture(texture);
	textureId = 1;
	animationTimer = 0;
	shape.setTextureRect(getTextureRect(textureId));
	shape.setPosition(Vector2f(0.f, 0.f));
}

Sprite& CPEOPLE::getShape() {
	return shape;
}

void CPEOPLE::moveUp() {
	if (isAnimating) processAnimation(1);
	else setTextureId(1), animationTimer = 0;

	shape.setTextureRect(getTextureRect(textureId));
	shape.move(Vector2f(0.f, (-1) * CCONSTANT::UNIT));
}

void CPEOPLE::moveLeft() {
	if (isAnimating) processAnimation(10);
	else setTextureId(10), animationTimer = 0;

	shape.setTextureRect(getTextureRect(textureId));
	if (shape.getPosition().x > -(long long)(CCONSTANT::WINDOW_WIDTH - 20) / 2) // -525
		shape.move(Vector2f((-1) * CCONSTANT::UNIT, 0));
}

void CPEOPLE::moveRight() {
	if (isAnimating) processAnimation(4);
	else setTextureId(4), animationTimer = 0;

	shape.setTextureRect(getTextureRect(textureId));
	if (shape.getPosition().x < (CCONSTANT::WINDOW_WIDTH - 20) / 2) // 525
		shape.move(Vector2f(CCONSTANT::UNIT, 0));
}
void CPEOPLE::moveDown() {
	if (isAnimating) processAnimation(7);
	else setTextureId(7), animationTimer = 0;
	shape.setTextureRect(getTextureRect(textureId));
	shape.move(Vector2f(0, CCONSTANT::UNIT));
}

void CPEOPLE::setIsAnimating(bool state) {
	if (isAnimating && !state) {
		if (textureId % 3 == 0) textureId++;
		else if (textureId % 3 == 2) textureId--;
		animationTimer = 0;
	}
	shape.setTextureRect(getTextureRect(textureId));
	isAnimating = state;
}

IntRect CPEOPLE::getTextureRect(int id) {
	return IntRect((id%3)*100, (id/3)*100, 100, 100);
}

int CPEOPLE::nextTextureId(int id) {
	if (id % 3 == 2) return id - 1;
	else if (id % 3 == 0) return id + 1;
	else {
		if (prevTextureId == id - 1) return id + 1;
		else return id - 1;
	}
}

void CPEOPLE::setTextureId(int id) {
	prevTextureId = textureId;
	textureId = id;
}

void CPEOPLE::processAnimation(int centerId) {
	if (isAnimating) {
		if (abs(centerId - textureId) > 1) textureId = centerId;
		animationTimer++;
		if (animationTimer >= CCONSTANT::ANIMATION_TIMER_LIMIT)
			setTextureId(nextTextureId(textureId)), animationTimer = 0;
	}
}


bool CPEOPLE::isImpact(CENEMY* enemy) {
	FloatRect playerBound(shape.getGlobalBounds());
	playerBound.top += 70;
	playerBound.left += 30;
	playerBound.width = 30;
	playerBound.height = 30;
	return playerBound.intersects(enemy->getSprite().getGlobalBounds());
}


Vector2f CPEOPLE::getPlayerPosition() {
	Vector2f pos = this->shape.getPosition();
	return pos;
}


void CPEOPLE::setPlayerPosition(const Vector2f& pos) {
	this->shape.setPosition(pos);
}