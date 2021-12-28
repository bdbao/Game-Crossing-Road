#define SFML_NO_DEPRECATED_WARNINGS
#include "CSETTINGS.h"

using namespace std;
using namespace sf;

CSETTINGS::CSETTINGS() {
	/*Load the font*/
	if (!font.loadFromFile("./assets/fonts/ChargeVector.ttf")) {
		cout << "Failed to load font!" << endl;
		return;
	}

	for (int i = 0; i < CCONSTANT::NUMBER_OF_SETTING_OPTIONS; ++i) {
		settings[i].setFont(font);
		settings[i].setColor(Color::White);
		settings[i].setStyle(Text::Bold);
	}

	/* Create options */
	settings[0].setColor(CCONSTANT::CHOSEN_OPTION);
	settings[0].setCharacterSize(settings[0].getCharacterSize() + 10);

	/* Set name of these options */
	settings[0].setString("Sound: ON");
	settings[1].setString("Return to Main Menu");
}

CSETTINGS::~CSETTINGS() {
	delete[] settings;
}

void CSETTINGS::draw(RenderWindow& window) {
	/* Set background color */
	RectangleShape rectangle(Vector2f(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT));
	rectangle.setFillColor(CCONSTANT::BACKGROUND);
	window.draw(rectangle);

	/* Display options */
	for (int i = 0; i < CCONSTANT::NUMBER_OF_SETTING_OPTIONS; ++i) {
		FloatRect textRect = settings[i].getLocalBounds();
		settings[i].setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		settings[i].setPosition(Vector2f(window.getSize().x / 2.0f,
			(window.getSize().y) /
			(CCONSTANT::NUMBER_OF_SETTING_OPTIONS + 1) *
			(i + 1) + 5));
		window.draw(settings[i]);
	}

	window.display();
}

void CSETTINGS::moveUp() {
	settings[selectedOption].setColor(Color::White);
	settings[selectedOption].setCharacterSize(settings[selectedOption].getCharacterSize() - 10);

	if (!selectedOption)
		selectedOption = CCONSTANT::NUMBER_OF_SETTING_OPTIONS - 1;
	else
		--selectedOption;

	settings[selectedOption].setColor(CCONSTANT::CHOSEN_OPTION);
	settings[selectedOption].setCharacterSize(settings[selectedOption].getCharacterSize() + 10);
}

void CSETTINGS::moveDown() {
	settings[selectedOption].setColor(Color::White);
	settings[selectedOption].setCharacterSize(settings[selectedOption].getCharacterSize() - 10);

	if (selectedOption == CCONSTANT::NUMBER_OF_SETTING_OPTIONS - 1)
		selectedOption = 0;
	else
		++selectedOption;

	settings[selectedOption].setColor(CCONSTANT::CHOSEN_OPTION);
	settings[selectedOption].setCharacterSize(settings[selectedOption].getCharacterSize() + 10);
}

int CSETTINGS::getOption() {
	switch (selectedOption) {
	case 0:
		return CCONSTANT::STATE_MENU;
	case 1:
		return CCONSTANT::STATE_MENU;
	}
}