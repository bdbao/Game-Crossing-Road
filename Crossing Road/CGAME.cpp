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
    }
}

void CGAME::update() {
    pollEvents();

 
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        player.moveUp();
        player.setIsAnimating(true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down)) {
        player.moveDown();
        player.setIsAnimating(true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        player.moveLeft();
        player.setIsAnimating(true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        player.moveRight();
        player.setIsAnimating(true);
    } else player.setIsAnimating(false);
}

void CGAME::render() {
    window.clear();
    view.setCenter(Vector2f(50, player.getShape().getPosition().y - CCONSTANT::UNIT));
    window.setView(view);
    window.draw(player.getShape());
    window.display();
}

CGAME::CGAME() : window(VideoMode(1100, 700), "Crossing Road", Style::Close), player() {
    window.setFramerateLimit(60);
    view.setSize(1100, 700);
}