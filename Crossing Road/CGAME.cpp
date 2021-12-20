#include "CGAME.h"
#include "CROAD.h"
#include "CGRASS.h"

using namespace sf;
using namespace std;


CGAME::CGAME() : window(VideoMode(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT), "Crossing Road", Style::Close), player() {
    window.setFramerateLimit(60);
    view.setSize(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT);

    this->background_texture.loadFromFile("./assets/graphics/background.jpg");
    this->background_texture.setRepeated(true);
    this->background_sprite = sf::Sprite(this->background_texture);

    /* Scale the background image */
    sf::Vector2u size = this->background_texture.getSize();
   // this->background_sprite.setScale(Vector2f((float)CCONSTANT::WINDOW_WIDTH / size.x, (float)CCONSTANT::WINDOW_HEIGHT / size.y));
    this->background_sprite.setTextureRect(sf::IntRect(0, 0, CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT*10));
    this->background_sprite.setPosition(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -(int)CCONSTANT::WINDOW_HEIGHT * 9));
    /* Sound manager */
    this->sound_manager = SoundManager::getInstance();

    // setting the game level -- might be moved to another function
    for (int i = 0; i < 6; i++) {
        int type = Rand(1, 100);
        if (type <= 25) {
            cout << "Animal";
            if (rand() % 2 == 0)
               lanes.push_back(new CGRASS(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)i * 230.f), 2, CCONSTANT::LEFT));
            else
               lanes.push_back(new CGRASS(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)i * 230.f), 2, CCONSTANT::RIGHT));
        }
        else {
            cout << "Car";
            float speed = rand() % 5 + 2;
            if (rand() % 2 == 0)
                lanes.push_back(new CROAD(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)i * 230.f), speed, CCONSTANT::LEFT));
            else
                lanes.push_back(new CROAD(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)i * 230.f), speed, CCONSTANT::RIGHT));
            
        }
    }

    /* Set game state when beginning is MENU */
    //this->game_state = CCONSTANT::STATE_MENU;
    //this->game_state = CCONSTANT::STATE_START;  //Temp state to test the core game
}

CGAME::~CGAME() {
    for (int i = 0; i < this->lanes.size(); i++)
        delete this->lanes[i];
    delete this->sound_manager;
}

bool CGAME::isRunning() {
	return window.isOpen();
}

int CGAME::state() {
    return this->game_state;
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
        //this->game_state = CCONSTANT::STATE_LOAD;
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S)) {
        /* Save the game to file */
        //this->game_state = CCONSTANT::STATE_SAVE;
        return;
    }

    else player.setIsAnimating(false);
}

void CGAME::render() {
    window.clear();
    view.setCenter(Vector2f(50, player.getShape().getPosition().y - CCONSTANT::UNIT));
    window.setView(view);
    window.draw(this->background_sprite);
    //this->background_sprite.setPosition(this->view.getCenter() - Vector2f(550, 350));

    for (auto t : lanes) {
        /* Update lane */
        t->update();

        /* Draw lane */
        window.draw(t->getSprite());

        /* xxx: t->getTypeEnemy() cu update lien tuc */
        //cout << t->getTypeEnemy() << '\n';
        this->sound_manager->play_Enemy(t->getTypeEnemy());
        

        /* Draw objects on each lane */
        for (auto e : t->getEnemies()) {
            if (player.isImpact(e)) {
                cout << "GAME OVER!\n";
                this->sound_manager->play_GameOver();

                //exit(0);
            }
            window.draw(e->getSprite());
        }        
        
        /* Draw traffic light */
        if (t->getTrafficLightShape())
            window.draw(*t->getTrafficLightShape());
    }

    window.draw(player.getShape());
    window.setView(window.getDefaultView());
    foreground.update();
    for (auto e : foreground.getSnowflakes()) {
        window.draw(e);
    }

    window.display();
}