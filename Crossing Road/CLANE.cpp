#include "CLANE.h"

using namespace sf;

RectangleShape & CLANE::getShape() {
	return shape;
}

CLANE::CLANE(float speed): speed(speed), isStopped(false), isSlowly(false) {}

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