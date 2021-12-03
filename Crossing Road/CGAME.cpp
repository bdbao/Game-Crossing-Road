#include "CGAME.h"
#include "CCONSTANT.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

bool CGAME::isRunning() {
	return window.isOpen();
}

void CGAME::pollEvents() {
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Up)
            player.moveUp();

        if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Down)
            player.moveDown(); 

        if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Left)
            player.moveLeft();

        if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Right)
            player.moveRight();
    }
}

void CGAME::update() {
    pollEvents();
}

void CGAME::render() {
    window.clear();
    view.setCenter(Vector2f(50, player.shape.getPosition().y - CCONSTANT::UNIT));
    window.setView(view);
    window.draw(player.shape);
    window.display();
}

CGAME::CGAME() : window(VideoMode(1100, 700), "Crossing Road", Style::Close), player() {
    window.setFramerateLimit(60);
    view.setSize(1100, 700);
}