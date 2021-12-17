#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>

class CCONSTANT {
public:
	/* Window setting */
	static const unsigned int WINDOW_WIDTH;
	static const unsigned int WINDOW_HEIGHT;

	/* Some setting */
	static const float UNIT;
	static const float VIEW_WIDTH;
	static const float VIEW_HEIGHT;
	static const int ANIMATION_TIMER_LIMIT;
	static const std::string LEFT;
	static const std::string RIGHT;

	/* CLANE */
	static const unsigned int LANE_WIDTH;
	static const unsigned int LANE_HEIGHT;
	

	/* For traffic light */
	static const float RED_LIGHT_TIME;
	static const float YELLOW_LIGHT_TIME;
	static const float GREEN_LIGHT_TIME;

	/* Speed */
	static const float NORMAL_SPEED;
	static const float SLOW_DOWN_SPEED;

	/* Sound */
	static const float DELAY_WALKING_SOUND;
};

#endif