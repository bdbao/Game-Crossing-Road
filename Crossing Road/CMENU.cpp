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
	
	/* Create options */
	menu[0].setFont(font);
	menu[0].setColor(Color::Yellow);
	menu[0].setString("Start Game");
	menu[0].setCharacterSize(menu[0].getCharacterSize() + 10);

	menu[1].setFont(font);
	menu[1].setColor(Color::White);
	menu[1].setString("Load Game");
	
	menu[2].setFont(font);
	menu[2].setColor(Color::White);
	menu[2].setString("Settings");
	
	menu[3].setFont(font);
	menu[3].setColor(Color::White);
	menu[3].setString("Quit");

	cout << "CMENU is loaded successfully!\n";
}

CMENU::~CMENU() {
	delete[] menu;
}

void CMENU::draw(RenderWindow& window) {
	/* Set background color */
	RectangleShape rectangle(Vector2f(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT));
	rectangle.setFillColor(Color(0, 0, 0, 200));
	window.draw(rectangle);

	/* Display options */
	for (int i = 0; i < CCONSTANT::NUMBER_OF_OPTIONS; ++i) {
		FloatRect textRect = menu[i].getLocalBounds();
		menu[i].setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		menu[i].setPosition(Vector2f(window.getSize().x / 2.0f,
			(window.getSize().y) /
			(CCONSTANT::NUMBER_OF_OPTIONS + 1) *
			(i + 1) + 20));
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

	menu[selectedOption].setColor(Color::Blue);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() + 10);
}

void CMENU::moveDown() {
	menu[selectedOption].setColor(Color::White);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() - 10);

	if (selectedOption == CCONSTANT::NUMBER_OF_OPTIONS - 1)
		selectedOption = 0;
	else
		++selectedOption;

	menu[selectedOption].setColor(Color::Blue);
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