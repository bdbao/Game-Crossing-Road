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

    // setting the game level -- might be moved to void initLevel(level)
    this->game_level = 1;
    this->initLevel(this->game_level);

    /* Set game state when beginning is MENU */
    //this->game_state = CCONSTANT::STATE_MENU;
    this->game_state = CCONSTANT::STATE_START;  //Temp state to test the core game
}

CGAME::~CGAME() {
    cout << "~CGAME()" << endl;
    for (int i = 0; i < this->lanes.size(); i++)
        delete this->lanes[i];
    delete this->finish_line;
    delete this->sound_manager;
}

bool CGAME::isRunning() {
	return window.isOpen();
}

int CGAME::state() {
    return this->game_state;
}

void CGAME::initLevel(int level) {
    /* Delete old data */
    for (int i = 0; i < this->lanes.size();i++) {
        delete this->lanes[i];
    }
    delete this->finish_line;

    /* Init new lanes for level */
    int nLanes = 0;
    float speed;
    for (int i = 0; i < min(level, 5); i++)
    {
        /* CROAD */
        for (int i = 0; i < min(level, 2); i++) {
            cout << "CROAD";
            speed = min(10.0, nLanes * 0.5 + 2);
            if (rand() % 2 == 0)
                lanes.push_back(new CROAD(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)nLanes * 275.f), speed, CCONSTANT::LEFT));
            else
                lanes.push_back(new CROAD(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)nLanes * 275.f), speed, CCONSTANT::RIGHT));
            nLanes++;
        }

        /* CGRASS */
        for (int i = 0; i < min(level, 3); i++) {
            cout << "CGRASS";
            speed = min(10.0, nLanes * 0.5 + 2);
            if (rand() % 2 == 0)
                lanes.push_back(new CGRASS(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)nLanes * 275.f), speed, CCONSTANT::LEFT));
            else
                lanes.push_back(new CGRASS(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)nLanes * 275.f), speed, CCONSTANT::RIGHT));
            nLanes++;
        }
    }

    /* Add finish line */
   this->finish_line = new CFinishLine(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)nLanes++ * 275.f));
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

    /* Global Interact keys through all state of the game*/
    if (Keyboard::isKeyPressed(Keyboard::Q) || Keyboard::isKeyPressed(Keyboard::Escape)) {
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

    /* Local Moving Keys for playing game */
    if (this->game_state == CCONSTANT::STATE_START) {
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
        else if (Keyboard::isKeyPressed(Keyboard::P)) {
            /* Pause the game */
            if (this->game_state != CCONSTANT::STATE_PAUSE) {
                this->game_state = CCONSTANT::STATE_PAUSE;
                cout << "PAUSE by pressing P (RESUME by pressing any different keys)" << endl;
                system("pause");
            }
        }
    }
    else player.setIsAnimating(false);
    
    /* Paused */
    if (this->game_state == CCONSTANT::STATE_PAUSE) {
        // Set continuing state
        if (Keyboard::isKeyPressed(Keyboard::Space))
            this->game_state == CCONSTANT::STATE_START;
    }
    
    /* Game over */
    if (this->game_state == CCONSTANT::STATE_GAME_OVER) {
        // Need to draw image of game over here
        // ...

        //Check if pressing any key to do something:
        // such as press space to restart playing game at level 0
        // such as press esc to exit game

        return;
    }

    /* Completed each level */
    if (this->game_state == CCONSTANT::STATE_GAME_COMPLETED) {
        // Need to draw image of passing level here
        // ...
        
        //Check if pressing any key to do something:
        // such as press space to go to next level
        // such as press esc to exit game
        return;
    }


}

void CGAME::render() {
    window.clear();
    view.setCenter(Vector2f(50, player.getShape().getPosition().y - CCONSTANT::UNIT));
    window.setView(view);

    /* Draw background */
    //this->background_sprite.setPosition(this->view.getCenter() - Vector2f(550, 350));
    window.draw(this->background_sprite);

    /* Draw each lane and objects on it */
    for (auto t : lanes) {
        /* Update lane */
        t->update();

        /* Draw lane */
        window.draw(t->getSprite());


        /* Draw objects on each lane */
        for (auto e : t->getEnemies()) {
            if (player.isImpact(e)) {
                cout << "GAME OVER!\n";
                this->sound_manager->play_GameOver();
                this->game_state = CCONSTANT::STATE_GAME_OVER;

            }
            window.draw(e->getSprite());
        }

        /* Play object sound */
        this->sound_manager->play_Enemy(t->getTypeEnemy());

        /* Draw traffic light */
        if (t->getTrafficLightShape())
            window.draw(*t->getTrafficLightShape());
    }

    /* Draw finish line */
    window.draw(*this->finish_line->getShape());

    /* Draw player */
    window.draw(player.getShape());

    /* Draw snowflakes theme */
    window.setView(window.getDefaultView());
    foreground.update();
    for (auto e : foreground.getSnowflakes()) {
        window.draw(e);
    }

    /* Check finish level state */
    if (this->finish_line->checkCollision(this->player)) {
        this->sound_manager->play_GameCompleted();
        this->game_state = CCONSTANT::STATE_GAME_COMPLETED;
    }

    /* Display the draw */
    window.display();
}

void CGAME::play_Background_music() {
    sf::Music music;
    if (!music.openFromFile("./assets/sounds/background-music.wav")) {
        std::cout << "Cant open background-music file!\n";
    }
    else {
        //music.setVolume(50.2);
        music.setLoop(true);
        music.play();
    }
}

//Load, save game, clear saved game
bool CGAME::loadGame() {
    initLevel(game_level);
    Vector2f playerPosition = player.getPlayerPosition();
    player.setPlayerPosition(playerPosition);
}

bool CGAME::saveGame() {
    ofstream fout("game_log/game.txt");
    if (!fout) {
        cout << "Load file not found. Error." << endl;
        return false;
    }

    fout << "Coordinate of player: " << player.getPlayerPosition().x << " " 
        << player.getPlayerPosition().y << endl;

    fout << "Current Level: " << game_level << endl;
    fout << endl << endl;

    cout << "Save game successfully" << endl;
}

void CGAME::clearSavedGame() {
    ofstream clear("game_log/game.txt");
    clear.close();
}
