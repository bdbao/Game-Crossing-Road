#include "CGAME.h"
#include "CCONSTANT.h"
#include "CCAR.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


CGAME::CGAME() : window(VideoMode(1100, 700), "Crossing Road", Style::Close), player() {
    window.setFramerateLimit(60);
    view.setSize(1100, 700);
    
    // setting the game level -- might be moved to another function
    for (int i = 0; i < 6; i++) {
        float speed = rand() % 5 + 2;
        if (rand() % 2 == 0)
            lanes.push_back(new CROAD(Vector2f(-500.f, -200.f - (float)i * 230.f), speed, CCONSTANT::LEFT));
        else
            lanes.push_back(new CROAD(Vector2f(-500.f, -200.f - (float)i * 230.f), speed, CCONSTANT::RIGHT));
    }
}

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
    
    for (auto t : lanes) {
        t->update();
        window.draw(t->getShape());
        for (auto e : t->getEnemies()) {
            if (player.isImpact(e)) cout << "GAME OVER!\n";
            window.draw(e->getShape());
        }
    }

    window.draw(player.getShape());
    window.display();
}