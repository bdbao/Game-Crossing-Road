#include "CGAME.h"

using namespace sf;
using namespace std;


CGAME::CGAME() : window(VideoMode(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT), "Crossing Road", Style::Close), player() {
    window.setFramerateLimit(60);
    view.setSize(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT);

    this->background_texture.loadFromFile("./assets/graphics/background.jpg");
    this->background_sprite = sf::Sprite(this->background_texture);

    /* Scale the background image */
    sf::Vector2u size = this->background_texture.getSize();
    this->background_sprite.setScale(Vector2f((float)CCONSTANT::WINDOW_WIDTH / size.x, (float)CCONSTANT::WINDOW_HEIGHT / size.y));
    
    /* Sound manager */
    this->sound_manager = new SoundManager;

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
    delete this->sound_manager;
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
        this->sound_manager->play_Walking();
        player.moveUp();
        player.setIsAnimating(true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down)) {
        cout << "Moving DOWN by pressing Down or S" << endl;
        this->sound_manager->play_Walking();
        player.moveDown();
        player.setIsAnimating(true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        cout << "Moving LEFT by pressing Left or A" << endl;
        this->sound_manager->play_Walking();
        player.moveLeft();
        player.setIsAnimating(true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        cout << "Moving RIGHT by pressing Right or D" << endl;
        this->sound_manager->play_Walking();
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
    this->background_sprite.setPosition(this->view.getCenter() - Vector2f(550, 350));
    window.draw(this->background_sprite);

    for (auto t : lanes) {
        /* Update lane */
        t->update();

        /* Draw lane */
        window.draw(t->getShape());

        /* Draw objects on each lane */
        for (auto e : t->getEnemies()) {
            if (player.isImpact(e)) cout << "GAME OVER!\n";
            window.draw(e->getShape());
        }        
        
        /* Draw traffic light */
        window.draw(t->getTrafficLightShape());
    }

    window.draw(player.getShape());
    window.display();
}