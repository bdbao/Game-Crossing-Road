#define SFML_NO_DEPRECATED_WARNINGS
#include "CMENU.h"

using namespace std;
using namespace sf;

CMENU::CMENU() {
	/*Load the font*/
	if (!font.loadFromFile("./assets/fonts/ChargeVector.ttf")) {
		cout << "Failed to load font!" << endl;
		return;
	}
	
	for (int i = 0; i < CCONSTANT::NUMBER_OF_OPTIONS; ++i) {
		menu[i].setFont(font);
		menu[i].setColor(Color::White);
		menu[i].setStyle(Text::Bold);
	}

	/* Create options */
	menu[0].setColor(CCONSTANT::CHOSEN_OPTION);
	menu[0].setCharacterSize(menu[0].getCharacterSize() + 10);

	/* Set name of these options */
	menu[0].setString("New Game");
	menu[1].setString("Load Game");
	menu[2].setString("Settings");
	menu[3].setString("Quit");
}

CMENU::~CMENU() {
	delete[] menu;
}
void CMENU::draw(RenderWindow& window) {
	/* Set background color */
	RectangleShape rectangle(Vector2f(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT));
	rectangle.setFillColor(CCONSTANT::BACKGROUND);
	window.draw(rectangle);

	/* Display options */
	for (int i = 0; i < CCONSTANT::NUMBER_OF_OPTIONS; ++i) {
		FloatRect textRect = menu[i].getLocalBounds();
		menu[i].setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		menu[i].setPosition(Vector2f(window.getSize().x / 2.0f,
			(window.getSize().y) /
			(CCONSTANT::NUMBER_OF_OPTIONS + 1) *
			(i + 1)));
		window.draw(menu[i]);
	}

	window.display();
}

void CMENU::moveUp() {
	menu[selectedOption].setColor(Color::White);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() - 10);
	
	if (!selectedOption)
		selectedOption = CCONSTANT::NUMBER_OF_OPTIONS - 1;
	else
		--selectedOption;

	menu[selectedOption].setColor(CCONSTANT::CHOSEN_OPTION);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() + 10);
}

void CMENU::moveDown() {
	menu[selectedOption].setColor(Color::White);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() - 10);

	if (selectedOption == CCONSTANT::NUMBER_OF_OPTIONS - 1)
		selectedOption = 0;
	else
		++selectedOption;

	menu[selectedOption].setColor(CCONSTANT::CHOSEN_OPTION);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() + 10);
}

int CMENU::getOption() {
	switch (selectedOption) {
	case 0:
		return CCONSTANT::STATE_START;
	case 1:
		return CCONSTANT::STATE_LOAD;
	case 2:
		return CCONSTANT::STATE_SETTINGS;
	case 3:
		return CCONSTANT::STATE_END;
	}
}