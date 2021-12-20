#include "CCONSTANT.h"
#include <SFML/Graphics.hpp>

using namespace sf;

const unsigned int CCONSTANT::WINDOW_WIDTH = 500;
const unsigned int CCONSTANT::WINDOW_HEIGHT = 700;

const int CCONSTANT::STATE_MENU = 0;
const int CCONSTANT::STATE_START = 1;
const int CCONSTANT::STATE_PAUSE = 2;
const int CCONSTANT::STATE_END = 3;
const int CCONSTANT::STATE_GAME_COMPLETED = 4;
const int CCONSTANT::STATE_GAME_OVER = 5;
const int CCONSTANT::STATE_SAVE = 6;
const int CCONSTANT::STATE_LOAD = 7;

const float CCONSTANT::UNIT = 5.f;
const float CCONSTANT::VIEW_HEIGHT = 5.f;
const float CCONSTANT::VIEW_WIDTH = 1100.f;
const int CCONSTANT::ANIMATION_TIMER_LIMIT = 5;
const std::string CCONSTANT::LEFT = "LEFT";
const std::string CCONSTANT::RIGHT = "RIGHT";

const unsigned int CCONSTANT::LANE_WIDTH = CCONSTANT::WINDOW_WIDTH;
const unsigned int CCONSTANT::LANE_HEIGHT = 200;

const float CCONSTANT::RED_LIGHT_TIME = 2.f;
const float CCONSTANT::YELLOW_LIGHT_TIME = 2.f;
const float CCONSTANT::GREEN_LIGHT_TIME = 5.f;

const float CCONSTANT::NORMAL_SPEED = 1.f;
const float CCONSTANT::SLOW_DOWN_SPEED = 1.5f;

const float CCONSTANT::DELAY_WALKING_SOUND = 0.375f;