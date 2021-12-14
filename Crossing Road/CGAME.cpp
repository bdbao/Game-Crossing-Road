#include "CGAME.h"

using namespace sf;
using namespace std;


CGAME::CGAME() : window(VideoMode(1100, 700), "Crossing Road", Style::Close), player(), traffic_light() {
    window.setFramerateLimit(60);
    view.setSize(1100, 700);
    clock.restart();
    
    // setting the game level -- might be moved to another function
    for (int i = 0; i < 6; i++) {
        float speed = rand() % 5 + 2;
        if (rand() % 2 == 0)
            lanes.push_back(new CROAD(Vector2f(-500.f, -200.f - (float)i * 230.f), speed, CCONSTANT::LEFT));
        else
            lanes.push_back(new CROAD(Vector2f(-500.f, -200.f - (float)i * 230.f), speed, CCONSTANT::RIGHT));
    }
}

CGAME::~CGAME() {
    for (int i = 0; i < this->lanes.size(); i++)
        delete this->lanes[i];
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

    /* Moving Keys */
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        cout << "Moving UP by pressing Up or W" << endl;
        player.moveUp();
        player.setIsAnimating(true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down)) {
        cout << "Moving DOWN by pressing Down or S" << endl;
        player.moveDown();
        player.setIsAnimating(true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        cout << "Moving LEFT by pressing Left or A" << endl;
        player.moveLeft();
        player.setIsAnimating(true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        cout << "Moving RIGHT by pressing Right or D" << endl;
        player.moveRight();
        player.setIsAnimating(true);
    }

    /* Interact keys */
    else if (Keyboard::isKeyPressed(Keyboard::Q) || Keyboard::isKeyPressed(Keyboard::Escape)) {
        /* Quit the game */
        this->window.close();
        cout << "QUIT by pressing Q" << endl;
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        /* Quit the game */
        this->window.close();
        cout << "QUIT by pressing ESC" << endl;
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::L)) {
        /* Load the game from file */
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S)) {
        /* Save the game to file */
        return;
    }

    else player.setIsAnimating(false);
}

void CGAME::render() {
    window.clear();
    view.setCenter(Vector2f(50, player.getShape().getPosition().y - CCONSTANT::UNIT));
    window.setView(view);
    
    int traffic_state = traffic_light.getTrafficLight(this->clock);

    for (auto t : lanes) {
        
        /* Set traffic light */
        if (traffic_state == 0)
            t->setNormal();
        else if (traffic_state == 1)
            t->setSlowly();
        else
            t->setStopped();
        Sprite obj = traffic_light.getShape();
        obj.setPosition(sf::Vector2f(-60, -355) + window.getView().getCenter());
        window.draw(obj);

        /* Update CROAD */
        t->update();

        /* Draw lane */
        window.draw(t->getShape());

        /* Draw objects on each lane */
        for (auto e : t->getEnemies()) {
            if (player.isImpact(e)) cout << "GAME OVER!\n";
            window.draw(e->getShape());
        }
    }

    window.draw(player.getShape());
    window.display();
}