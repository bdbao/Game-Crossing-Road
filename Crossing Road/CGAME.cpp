#include "CGAME.h"

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
    this->game_state = CCONSTANT::STATE_MENU;
    //this->game_state = CCONSTANT::STATE_START;  //Temp state to test the core game

    /* Set showed game state in function initLevel(int) */
    this->showedGameOver = false;
    this->showedGameCompleted = false;
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
    this->lanes.clear();

    /* Set showed game state */
    this->showedGameOver = false;
    this->showedGameCompleted = false;

    this->game_level = level;
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
   this->finish_line = new CFinishLine(Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -50.f - (float)nLanes++ * 275.f));
}


void CGAME::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (game_state == CCONSTANT::STATE_MENU) {
            if (Keyboard::isKeyPressed(Keyboard::Up))
                menu.moveUp();
            if (Keyboard::isKeyPressed(Keyboard::Down))
                menu.moveDown();
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
                game_state = menu.getOption();
            }
                
        }
    }
}

void CGAME::update() {
    pollEvents();
    this->sound_manager->play_Background();

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

    /* Local Moving Keys while playing game */
    if (this->game_state == CCONSTANT::STATE_MENU) {
        menu.draw(window);
    }

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
                //this->game_state = CCONSTANT::STATE_PAUSE;
                /* khong can set thanh STATE_PAUSE nua */
                cout << "PAUSE by pressing P (RESUME by pressing any different keys)" << endl;
                this->sound_manager->pause_Background();
                system("pause");
            }
        }
    }
    else player.setIsAnimating(false);
    
    ///* Paused */
    //if (this->game_state == CCONSTANT::STATE_PAUSE) {
    //    // Set continuing state
    //    if (Keyboard::isKeyPressed(Keyboard::Space))
    //        this->game_state == CCONSTANT::STATE_START;
    //}
    
    /* Game over */
    if (this->game_state == CCONSTANT::STATE_GAME_OVER) {
        
        /* Print game over and hotkey instruction */
        if (!this->showedGameOver) {

            int notiSize = 72, instructionSize = 40;
            
            /* Print game over */
            Text text_gameover;
            Font font, font2;
            if (!font.loadFromFile("./assets/fonts/SuperGame.ttf"))  throw("Could not load the font");
            
            text_gameover.setFont(font);
            
            text_gameover.setCharacterSize(notiSize);
            text_gameover.setFillColor(Color::Black);
            text_gameover.setStyle(Text::Bold);
            text_gameover.setString("GAME OVER!!!");
            
            text_gameover.setOutlineColor(sf::Color::Magenta);
            text_gameover.setOutlineThickness(6.5);
            
            
            /* Set position of text: align center */
            sf::FloatRect textRect = text_gameover.getLocalBounds();
            text_gameover.setOrigin(textRect.width / 2, textRect.height / 2);
            text_gameover.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.2f));
            window.draw(text_gameover);


            /* Print extra information */
            if (!font2.loadFromFile("./assets/fonts/arial.ttf"))  throw("Could not load the font");

            Text text_replay;
            text_replay.setFont(font2);
            text_replay.setCharacterSize(instructionSize);
            text_replay.setFillColor(Color::Cyan);
            text_replay.setStyle(Text::Bold);
            text_replay.setString("Replay: SPACE");
            text_replay.setOutlineColor(sf::Color::Black);
            text_replay.setOutlineThickness(3);
            /* Set position of text: align center */
            sf::FloatRect textRect_replay = text_replay.getLocalBounds();
            text_replay.setOrigin(textRect_replay.width / 2, textRect_replay.height / 2);
            text_replay.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.5f));
            window.draw(text_replay);

            Text text_quit;
            text_quit.setFont(font2);
            text_quit.setCharacterSize(instructionSize);
            text_quit.setFillColor(Color::Cyan);
            text_quit.setStyle(Text::Bold);
            text_quit.setString("Quit game: Q");
            text_quit.setOutlineColor(sf::Color::Black);
            text_quit.setOutlineThickness(3);
            /* Set position of text: align center */
            sf::FloatRect  textRect_quit = text_quit.getLocalBounds();
            text_quit.setOrigin(textRect_quit.width / 2, textRect_quit.height / 2);
            text_quit.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.6f));
            window.draw(text_quit);

            
            window.display();
            this->showedGameOver = true;
        }
        	    
        //Check if pressing any key to do something:
        // such as press space to restart playing game at level 0
        // such as press esc to exit game
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            this->initLevel(1);
            this->game_state = CCONSTANT::STATE_START;
            this->showedGameOver = false;
            this->player.setPlayerPosition(Vector2f(0.f, 0.f));
            this->sound_manager->reset();
        }
        return;
    }

    /* Completed each level */
    if (this->game_state == CCONSTANT::STATE_GAME_COMPLETED) {
        // Need to draw image of passing level here
        // ...
        
        if (!this->showedGameCompleted) {

            int notiSize = 70, instructionSize = 40;

            Text level_completed;
            Font font;
            if (!font.loadFromFile("./assets/fonts/SuperGame.ttf"))  throw("Could not load the font");

            level_completed.setFont(font);

            level_completed.setCharacterSize(notiSize);
            level_completed.setFillColor(Color::Yellow);
            level_completed.setStyle(Text::Bold);
            level_completed.setString("Passed Level " + to_string(this->game_level));
            level_completed.setOutlineColor(sf::Color::Blue);
            level_completed.setOutlineThickness(6.5);

            /* Set position of text: align center */
            sf::FloatRect textRect = level_completed.getLocalBounds();
            level_completed.setOrigin(textRect.width / 2, textRect.height / 2);
            level_completed.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.2f));
            window.draw(level_completed);


            /* Print hotkey instruction */
            Font font2;
            if (!font2.loadFromFile("./assets/fonts/arial.ttf"))  throw("Could not load the font");

            Text next_level;
            next_level.setFont(font2);
            next_level.setCharacterSize(instructionSize);
            next_level.setFillColor(Color::Cyan);
            next_level.setStyle(Text::Bold);
            next_level.setString("Next level: SPACE");
            next_level.setOutlineColor(sf::Color::Black);
            next_level.setOutlineThickness(3);
            /* Set position of text: align center */
            sf::FloatRect textRect_next_level = next_level.getLocalBounds();
            next_level.setOrigin(textRect_next_level.width / 2, textRect_next_level.height / 2);
            next_level.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.5f));
            window.draw(next_level);

            
            Text text_quit;
            text_quit.setFont(font2);
            text_quit.setCharacterSize(instructionSize);
            text_quit.setFillColor(Color::Cyan);
            text_quit.setStyle(Text::Bold);
            text_quit.setString("Quit game: Q");
            text_quit.setOutlineColor(sf::Color::Black);
            text_quit.setOutlineThickness(3);
            /* Set position of text: align center */
            sf::FloatRect textRect_quit = text_quit.getLocalBounds();
            text_quit.setOrigin(textRect_quit.width / 2, textRect_quit.height / 2);
            text_quit.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.6f));
            window.draw(text_quit);


            this->showedGameCompleted = true;
            window.display();
        }
	    
        //Check if pressing any key to do something:
        // such as press space to go to next level
        // such as press esc to exit game
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            this->initLevel(++this->game_level);
            this->game_state = CCONSTANT::STATE_START;
            this->showedGameOver = false;
            this->player.setPlayerPosition(Vector2f(0.f, 0.f));
            this->sound_manager->reset();
        }

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

    /* Print current level */
    Text level_completed;
    Font font;
    if (!font.loadFromFile("./assets/fonts/arial.ttf"))  throw("Could not load the font");
    level_completed.setFont(font);
    level_completed.setCharacterSize(30);
    level_completed.setFillColor(Color::Black);
    level_completed.setStyle(Text::Bold);
    level_completed.setString("Level " + to_string(this->game_level));
    level_completed.setOutlineColor(sf::Color::Green);
    level_completed.setOutlineThickness(6.5);

    /* Set position of text: align center */
    sf::FloatRect textRect = level_completed.getLocalBounds();
    level_completed.setOrigin(textRect.width / 2, textRect.height / 2);
    level_completed.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, textRect.height / 2));
    window.draw(level_completed);

    /* Display the draw */
    window.display();
}


//Load, save game, clear saved game
void CGAME::loadGame() {
    initLevel(game_level);
    Vector2f playerPosition = player.getPlayerPosition();
    player.setPlayerPosition(playerPosition);
    return;
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
    return true;
}

void CGAME::clearSavedGame() {
    ofstream clear("game_log/game.txt");
    clear.close();
}
