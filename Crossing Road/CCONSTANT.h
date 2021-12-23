#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>
#include <SFML/Graphics.hpp>


class CCONSTANT {
public:

	/* Window setting */
	static const unsigned int WINDOW_WIDTH;
	static const unsigned int WINDOW_HEIGHT;

	/* CGAME status */
	static const int STATE_MENU;
	static const int STATE_START;
	static const int STATE_PAUSE;
	static const int STATE_END;
	static const int STATE_GAME_COMPLETED;
	static const int STATE_GAME_OVER;
	static const int STATE_SAVE;
	static const int STATE_LOAD;
	static const int STATE_SETTINGS;

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
	static const float DELAY_CAR_SOUND;
	static const float DELAY_REINDEER_SOUND;
	static const float DELAY_BULL_SOUND;
	static const float DELAY_PENGUIN_SOUND;

	/* Menu */
	static const int NUMBER_OF_OPTIONS;
	static const sf::Color CHOSEN_OPTION;
	static const sf::Color BACKGROUND;
};

#endif