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
	menu = new Text[CCONSTANT::NUMBER_OF_OPTIONS];
	for (int i = 0; i < CCONSTANT::NUMBER_OF_OPTIONS; ++i) {
		menu[i].setFont(font);
		menu[i].setFillColor(Color::Black);
	}

	/* Set the default chosen option */
	menu[0].setFillColor(Color::Blue);
	menu[0].setCharacterSize(menu[0].getCharacterSize() + 10);

	/* Set name of these options */
	menu[0].setString("Start Game");
	menu[1].setString("Load Game");
	menu[2].setString("Settings");
	menu[3].setString("Quit");
}

CMENU::~CMENU() {
	if (menu) delete[] menu;
}

void CMENU::draw(sf::RenderWindow& window) {
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
			(i + 1) + 50));
		window.draw(menu[i]);
	}
}

void CMENU::moveUp() {
	menu[selectedOption].setFillColor(Color::White);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() - 10);
	
	if (!selectedOption)
		selectedOption = CCONSTANT::NUMBER_OF_OPTIONS - 1;
	else
		--selectedOption;

	menu[selectedOption].setFillColor(Color::Blue);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() + 10);
}

void CMENU::moveDown() {
	menu[selectedOption].setFillColor(Color::White);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() - 10);

	if (selectedOption == CCONSTANT::NUMBER_OF_OPTIONS - 1)
		selectedOption = 0;
	else
		++selectedOption;

	menu[selectedOption].setFillColor(Color::Blue);
	menu[selectedOption].setCharacterSize(menu[selectedOption].getCharacterSize() + 10);
}

int CMENU::getOption() {
	return selectedOption;
}