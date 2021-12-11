#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>

class CCONSTANT {
public:
	static const float UNIT;
	static const float VIEW_WIDTH;
	static const float VIEW_HEIGHT;
	static const int ANIMATION_TIMER_LIMIT;
	static const std::string LEFT;
	static const std::string RIGHT;
	

	/* For traffic light */
	static const float RED_LIGHT_TIME;
	static const float YELLOW_LIGHT_TIME;
	static const float GREEN_LIGHT_TIME;

	/* Speed */
	static const float NORMAL_SPEED;
	static const float SLOW_DOWN_SPEED;
};

#endif