#ifndef _CROAD_H_
#define _CROAD_H_
#include "CLANE.h"
#include "CPlayer.h"
#include "CENEMY.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace sf;

class CFinishLine {
private:
	
public:
	bool checkCollision(Player player);
	void playSound();
};

