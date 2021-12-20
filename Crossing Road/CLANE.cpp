#include "CLANE.h"

using namespace sf;

sf::Sprite & CLANE::getSprite() {
	return this->sprite;
}

CLANE::CLANE(float speed): speed(speed), isStopped(false), isSlowly(false) {
	this->time.restart();
	this->traffic_light = new CTRAFFICLIGHT;
}

CLANE:: ~CLANE() {
	for (int i = 0; i < this->enemies.size(); i++)
		delete this->enemies[i];
	delete this->traffic_light;
}

std::vector<CENEMY*>& CLANE::getEnemies() {
	return enemies;
}


void CLANE::setNormal() {
	this->isStopped = this->isSlowly = false;
}

void CLANE::setSlowly() {
	this->isStopped = false;
	this->isSlowly = true;
}

void CLANE::setStopped() {
	this->isStopped = true;
	this->isSlowly = false;
}

std::string CLANE::getTypeEnemy() {
	return this->typeEnemy;
}