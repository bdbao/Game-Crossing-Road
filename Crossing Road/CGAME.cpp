#define SFML_NO_DEPRECATED_WARNINGS
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
    ofstream fout("game_log/temp_file.dat", ios::out | ios::binary);
    fout.clear();

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
    bool dir;
    for (int i = 0; i < min(level, 5) + 1; i++) {
        /* CROAD */
        for (int j = 0; j < min(level, 5); j++) {
            cout << "CROAD";
            speed = min(10.0, nLanes * 0.5 + 2);
            Vector2f tmp = Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -200.f - (float)nLanes * 275.f);
            fout.write((char*)&tmp, sizeof(Vector2f));
            fout.write((char*)&speed, sizeof(float));
            fout.write((char*)&dir, sizeof(bool));
            dir = rand() % 2;
            if (!dir) {
                bool t = rand() % 2;
                if (!t)
                    lanes.push_back(new CROAD(tmp, speed, CCONSTANT::LEFT));
                else
                    lanes.push_back(new CGRASS(tmp, speed, CCONSTANT::LEFT));
                fout.write((char*)&t, sizeof(bool));
            }
            else {
                bool t = rand() % 2;
                if (!t)
                    lanes.push_back(new CROAD(tmp, speed, CCONSTANT::RIGHT));
                else
                    lanes.push_back(new CGRASS(tmp, speed, CCONSTANT::RIGHT));
                fout.write((char*)&t, sizeof(bool));
            }
            nLanes++;
        }
    }

    /* Add finish line */
    Vector2f fl = Vector2f(-(int)CCONSTANT::WINDOW_WIDTH / 2.f + 50, -50.f - (float)nLanes++ * 275.f);
    finish_line = new CFinishLine(fl);
    fout.write((char*)&fl, sizeof(Vector2f));
}


void CGAME::pollEvents() {
    window.setKeyRepeatEnabled(false);
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (game_state == CCONSTANT::STATE_MENU) {
            menu.draw(window);
            if (Keyboard::isKeyPressed(Keyboard::Up))
                menu.moveUp();
            if (Keyboard::isKeyPressed(Keyboard::Down))
                menu.moveDown();
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
                game_state = menu.getOption();
            }
            return;
        }
        if (game_state == CCONSTANT::STATE_SETTINGS) {
            settings.draw(window);
            if (Keyboard::isKeyPressed(Keyboard::Up))
                settings.moveUp();
            if (Keyboard::isKeyPressed(Keyboard::Down))
                settings.moveDown();
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                game_state = settings.getOption();
            }
        }
        if (game_state == CCONSTANT::STATE_START && Keyboard::isKeyPressed(Keyboard::P)) {
            /* Pause the game */
            cout << "PAUSE by pressing P (RESUME by pressing any different keys)" << endl;
            game_state = CCONSTANT::STATE_PAUSE;
            this->sound_manager->pause_Background();
            this->sound_manager->pauseAllEnemySound();
        }
        if (game_state == CCONSTANT::STATE_PAUSE) {
            if (event.type == Event::KeyPressed && !Keyboard::isKeyPressed(Keyboard::P))
                game_state = CCONSTANT::STATE_START;
        }
        if (game_state == CCONSTANT::STATE_LOAD) {
            if (Keyboard::isKeyPressed(Keyboard::Space))
                game_state = CCONSTANT::STATE_MENU;
        }
        if (game_state == CCONSTANT::STATE_SAVE) {
            if (Keyboard::isKeyPressed(Keyboard::Space))
                game_state = CCONSTANT::STATE_START;
        }
    }
}


void CGAME::update() {
    //pollEvents();
    if (this->game_state != CCONSTANT::STATE_PAUSE)
        this->sound_manager->play_Background();
    
    /* Global Interact keys through all state of the game*/
    if (Keyboard::isKeyPressed(Keyboard::Q) || Keyboard::isKeyPressed(Keyboard::Escape)) {
        /* Quit the game */
        if (game_state == CCONSTANT::STATE_MENU) return;
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
    else if (Keyboard::isKeyPressed(Keyboard::M)) {
        isNewGame = true;
        game_state = CCONSTANT::STATE_MENU;
    }

    /* Local Moving Keys while playing game */

    if (this->game_state == CCONSTANT::STATE_START) {
        if (isNewGame) {
            initLevel(1);
            this->player.setPlayerPosition(Vector2f(0.f, 0.f));
            this->sound_manager->reset();
            isNewGame = false;
            return;
        }

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
        else if (Keyboard::isKeyPressed(Keyboard::S)) {
            if (!showedGameOver) {
                saveGame();
                game_state = CCONSTANT::STATE_SAVE;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::L)) {
            /* Load the game from file */
            initLevel(game_level);
            this->player.setPlayerPosition(Vector2f(0.f, 0.f));
            this->sound_manager->reset();
            isNewGame = false;
            return;
        } else player.setIsAnimating(false);
    }
   
    if (this->game_state == CCONSTANT::STATE_PAUSE) {
        int instructionSize = 30;

        Sprite backdrop;
        Texture backdropTexture;
        backdropTexture.loadFromFile("./assets/graphics/background3.jpg");
        backdrop.setTexture(backdropTexture);
        window.draw(backdrop);

        Font font;
        if (!font.loadFromFile("./assets/fonts/plaguard.otf"))  throw("Could not load the font");

        Font font2;
        if (!font2.loadFromFile("./assets/fonts/ChargeVector.ttf"))  throw("Could not load the font");

        Text noti;
        noti.setFont(font);
        noti.setCharacterSize(56);
        noti.setStyle(Text::Bold);
        noti.setFillColor(Color::White);
        noti.setString("GAME PAUSED!");
        /* Set position of text: align center */
        sf::FloatRect textRect_noti = noti.getLocalBounds();
        noti.setOrigin(textRect_noti.width / 2, textRect_noti.height / 2);
        noti.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.30f));
        window.draw(noti);

        Text backToGame;
        backToGame.setFont(font2);
        backToGame.setCharacterSize(instructionSize);
        backToGame.setFillColor(Color::White);
        backToGame.setString("Back to game: Arbitrary key");
        /* Set position of text: align center */
        sf::FloatRect textRect_backToGame = backToGame.getLocalBounds();
        backToGame.setOrigin(textRect_backToGame.width / 2, textRect_backToGame.height / 2);
        backToGame.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.55f));
        window.draw(backToGame);

        Text goToMenu;
        goToMenu.setFont(font2);
        goToMenu.setCharacterSize(instructionSize);
        goToMenu.setFillColor(Color::White);
        goToMenu.setString("Go to menu: M");
        /* Set position of text: align center */
        sf::FloatRect textRect_goToMenu = goToMenu.getLocalBounds();
        goToMenu.setOrigin(textRect_goToMenu.width / 2, textRect_goToMenu.height / 2);
        goToMenu.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.65f));
        window.draw(goToMenu);

        Text text_quit;
        text_quit.setFont(font2);
        text_quit.setCharacterSize(instructionSize);
        text_quit.setFillColor(Color::White);
        text_quit.setString("Quit game: Q");
        /* Set position of text: align center */
        sf::FloatRect textRect_quit = text_quit.getLocalBounds();
        text_quit.setOrigin(textRect_quit.width / 2, textRect_quit.height / 2);
        text_quit.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.75f));
        window.draw(text_quit);

        window.display();
    }

    /* Game over */
    if (this->game_state == CCONSTANT::STATE_GAME_OVER) {
        /* Print game over and hotkey instruction */

        if (!this->showedGameOver) {
            int notiSize = 72, instructionSize = 32;
            
            RectangleShape rectangle(Vector2f(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT));
            rectangle.setFillColor(Color(0, 0, 0, 200));
            window.draw(rectangle);

            /* Print game over */
            Text text_gameover;
            Font font, font2;
            if (!font.loadFromFile("./assets/fonts/plaguard.otf"))  throw("Could not load the font");
            
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
            if (!font2.loadFromFile("./assets/fonts/ChargeVector.ttf"))  throw("Could not load the font");

            Text text_replay;
            text_replay.setFont(font2);
            text_replay.setCharacterSize(instructionSize);
            text_replay.setFillColor(Color::White);
            text_replay.setString("Replay: SPACE");
            /* Set position of text: align center */
            sf::FloatRect textRect_replay = text_replay.getLocalBounds();
            text_replay.setOrigin(textRect_replay.width / 2, textRect_replay.height / 2);
            text_replay.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.5f));
            window.draw(text_replay);

            Text text_quit;
            text_quit.setFont(font2);
            text_quit.setCharacterSize(instructionSize);
            text_quit.setFillColor(Color::White);
            text_quit.setString("Quit game: Q");
            /* Set position of text: align center */
            sf::FloatRect  textRect_quit = text_quit.getLocalBounds();
            text_quit.setOrigin(textRect_quit.width / 2, textRect_quit.height / 2);
            text_quit.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.6f));
            window.draw(text_quit);

            
            window.display();
            clearSavedGame();
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
            int notiSize = 56, instructionSize = 32;

            RectangleShape rectangle(Vector2f(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT));
            rectangle.setFillColor(Color(0, 0, 0, 200));

            window.draw(rectangle);

            Text level_completed;
            Font font;
            if (!font.loadFromFile("./assets/fonts/plaguard.otf"))  throw("Could not load the font");

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
            if (!font2.loadFromFile("./assets/fonts/ChargeVector.ttf"))  throw("Could not load the font");

            Text next_level;
            next_level.setFont(font2);
            next_level.setCharacterSize(instructionSize);
            next_level.setFillColor(Color::White);
            next_level.setString("Next level: SPACE");
            /* Set position of text: align center */
            sf::FloatRect textRect_next_level = next_level.getLocalBounds();
            next_level.setOrigin(textRect_next_level.width / 2, textRect_next_level.height / 2);
            next_level.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.5f));
            window.draw(next_level);

            Text text_save;
            text_save.setFont(font2);
            text_save.setCharacterSize(instructionSize);
            text_save.setFillColor(Color::White);
            text_save.setString("Save game: S");
            /* Set position of text: align center */
            sf::FloatRect textRect_save = text_save.getLocalBounds();
            text_save.setOrigin(textRect_save.width / 2, textRect_save.height / 2);
            text_save.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.6f));
            window.draw(text_save);

            Text text_quit;
            text_quit.setFont(font2);
            text_quit.setCharacterSize(instructionSize);
            text_quit.setFillColor(Color::White);
            text_quit.setString("Quit game: Q");
            /* Set position of text: align center */
            sf::FloatRect textRect_quit = text_quit.getLocalBounds();
            text_quit.setOrigin(textRect_quit.width / 2, textRect_quit.height / 2);
            text_quit.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.7f));
            window.draw(text_quit);


            this->showedGameCompleted = true;
            window.display();
        }
	    
        //Check if pressing any key to do something:
        // such as press space to go to next level
        // such as press esc to exit game
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            this->initLevel(++game_level);
            this->game_state = CCONSTANT::STATE_START;
            this->showedGameOver = false;
            this->player.setPlayerPosition(Vector2f(0.f, 0.f));
            this->sound_manager->reset();
        }

        return;
    }

    if (this->game_state == CCONSTANT::STATE_LOAD) {
        if (loadGame()) {
            game_state = CCONSTANT::STATE_START;
        }
        else {
            int instructionSize = 30;

            RectangleShape rectangle(Vector2f(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT));
            rectangle.setFillColor(Color(174, 188, 253));
            window.draw(rectangle);
            
            Font font;
            if (!font.loadFromFile("./assets/fonts/plaguard.otf"))  throw("Could not load the font");
            Font font2;
            if (!font2.loadFromFile("./assets/fonts/ChargeVector.ttf"))  throw("Could not load the font");

            Text noti;
            noti.setFont(font);
            noti.setCharacterSize(56);
            noti.setStyle(Text::Bold);
            noti.setFillColor(Color::White);
            noti.setString("NOT FOUND!");
            /* Set position of text: align center */
            sf::FloatRect textRect_noti = noti.getLocalBounds();
            noti.setOrigin(textRect_noti.width / 2, textRect_noti.height / 2);
            noti.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.30f));
            window.draw(noti);

            Text backToMenu;
            backToMenu.setFont(font2);
            backToMenu.setCharacterSize(instructionSize);
            backToMenu.setFillColor(Color::White);
            backToMenu.setString("Back to menu: Space");
            /* Set position of text: align center */
            sf::FloatRect textRect_backToMenu = backToMenu.getLocalBounds();
            backToMenu.setOrigin(textRect_backToMenu.width / 2, textRect_backToMenu.height / 2);
            backToMenu.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.55f));
            window.draw(backToMenu);

            window.display();
        }
        return;
    }

    if (game_state == CCONSTANT::STATE_SAVE) {
        int instructionSize = 30;

        RectangleShape rectangle(Vector2f(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT));
        rectangle.setFillColor(Color(174, 188, 253));
        window.draw(rectangle);

        Font font;
        if (!font.loadFromFile("./assets/fonts/plaguard.otf"))  throw("Could not load the font");

        Font font2;
        if (!font2.loadFromFile("./assets/fonts/ChargeVector.ttf"))  throw("Could not load the font");

        Text noti;
        noti.setFont(font);
        noti.setCharacterSize(56);
        noti.setStyle(Text::Bold);
        noti.setFillColor(Color::White);
        noti.setString("GAME SAVED!");
        /* Set position of text: align center */
        sf::FloatRect textRect_noti = noti.getLocalBounds();
        noti.setOrigin(textRect_noti.width / 2, textRect_noti.height / 2);
        noti.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.30f));
        window.draw(noti);

        Text backToGame;
        backToGame.setFont(font2);
        backToGame.setCharacterSize(instructionSize);
        backToGame.setFillColor(Color::White);
        backToGame.setString("Back to game: Space");
        /* Set position of text: align center */
        sf::FloatRect textRect_backToGame = backToGame.getLocalBounds();
        backToGame.setOrigin(textRect_backToGame.width / 2, textRect_backToGame.height / 2);
        backToGame.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.55f));
        window.draw(backToGame);

        Text goToMenu;
        goToMenu.setFont(font2);
        goToMenu.setCharacterSize(instructionSize);
        goToMenu.setFillColor(Color::White);
        goToMenu.setString("Go to menu: M");
        /* Set position of text: align center */
        sf::FloatRect textRect_goToMenu = goToMenu.getLocalBounds();
        goToMenu.setOrigin(textRect_goToMenu.width / 2, textRect_goToMenu.height / 2);
        goToMenu.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.65f));
        window.draw(goToMenu);

        Text text_quit;
        text_quit.setFont(font2);
        text_quit.setCharacterSize(instructionSize);
        text_quit.setFillColor(Color::White);
        text_quit.setString("Quit game: Q");
        /* Set position of text: align center */
        sf::FloatRect textRect_quit = text_quit.getLocalBounds();
        text_quit.setOrigin(textRect_quit.width / 2, textRect_quit.height / 2);
        text_quit.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, CCONSTANT::WINDOW_HEIGHT * 0.75f));
        window.draw(text_quit);

        window.display();
        return;
    }

    if (this->game_state == CCONSTANT::STATE_END)
        window.close();
}


void CGAME::render() {
    window.clear();
    view.setCenter(Vector2f(50, player.getShape().getPosition().y - CCONSTANT::UNIT));
    window.setView(view);

    /* Draw background */
    //this->background_sprite.setPosition(this->view.getCenter() - Vector2f(550, 350));
    window.draw(this->background_sprite);

    int player_position_idx = round(((float) player.getPlayerPosition().y + 200) / -275.0);
    //cout << player_position_idx << endl;

    /* Draw each lane and objects on it */
    int lane_idx = 0;
    bool is_draw = false;
    for (auto t : lanes) {
        is_draw = (lane_idx >= player_position_idx - 1) && (lane_idx <= player_position_idx + 2);
        lane_idx++;

        /* Update lane */
        t->update();

        /* Draw lane */
        if(is_draw)
            window.draw(t->getSprite());


        /* Draw objects on each lane and check collision */
        if (is_draw) {
            for (auto e : t->getEnemies()) {
                if (player.isImpact(e)) {
                    cout << "GAME OVER!\n";
                    this->sound_manager->play_GameOver();
                    player.gameOver(t->getDirection());
                    this->game_state = CCONSTANT::STATE_GAME_OVER;
                    cout << "Collision with " << e->getEnemyName() << endl;
                }
                window.draw(e->getSprite());

                /* Play obstacle sound */
                this->sound_manager->play_EnemySound(e->getEnemyName());
            }
        }

        /* Play object sound *///window.draw(player.getShape());
        //this->sound_manager->play_Enemy(t->getTypeEnemy());

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

    if (game_level % 3 == 0) {
        RectangleShape rectangle(Vector2f(CCONSTANT::WINDOW_WIDTH, CCONSTANT::WINDOW_HEIGHT));
        rectangle.setFillColor(Color(0, 0, 133, 150));
        window.draw(rectangle);
    }

    /* Print current level */
    Text current_level;
    Font font;
    if (!font.loadFromFile("./assets/fonts/plaguard.otf"))  throw("Could not load the font");
    current_level.setFont(font);
    current_level.setCharacterSize(34);
    current_level.setFillColor(Color(174, 188, 253));
    current_level.setStyle(Text::Bold);
    current_level.setString("Level " + to_string(this->game_level));
    current_level.setOutlineColor(Color::Black);
    current_level.setOutlineThickness(3);

    /* Set position of text: align center */
    sf::FloatRect textRect = current_level.getLocalBounds();
    current_level.setOrigin(textRect.width / 2, textRect.height / 2);
    current_level.setPosition(sf::Vector2f(CCONSTANT::WINDOW_WIDTH / 2.0f, textRect.height / 2));
    window.draw(current_level);


    /* Display the draw */
    if (game_state != CCONSTANT::STATE_GAME_OVER)
        window.display();

    /* Debug part */
    //cout << this->player.getPlayerPosition().x << " " << this->player.getPlayerPosition().y << endl;
}


//Load, save game, clear saved game
bool CGAME::loadGame() {
    ifstream fin("game_log/game.dat", ios::in | ios::binary);
    if (!fin) {
        cout << "Load file not found. Error." << endl;
        return false;
    }

    isNewGame = false;
    int tmp_lvl;
    fin.read((char*)&tmp_lvl, 4);
    if (!tmp_lvl) return false;
    game_level = tmp_lvl;
    fin.read((char*)&showedGameCompleted, sizeof(bool));
    
    if (showedGameCompleted) {
        initLevel(++game_level);
        return true;
    }

    Vector2f pos;
    fin.read((char*)&pos, sizeof(Vector2f));
    cout << pos.x << " " << pos.y << endl;
    player.setPlayerPosition(pos);

    for (int i = 0; i < lanes.size(); i++)
        delete this->lanes[i];

    if (finish_line) delete finish_line;
    lanes.clear();

    Vector2f xy;
    float speed;
    bool dir;
    bool type;
    for (int i = 0; i < min(game_level, 5) + 1; i++) {
        for (int j = 0; j < min(game_level, 5); j++) {
            fin.read((char*)&xy, sizeof(Vector2f));
            fin.read((char*)&speed, sizeof(float));
            fin.read((char*)&dir, sizeof(bool));
            fin.read((char*)&type, sizeof(bool));

            if (!dir) {
                if (!type)
                    lanes.push_back(new CROAD(xy, speed, CCONSTANT::LEFT));
                else
                    lanes.push_back(new CGRASS(xy, speed, CCONSTANT::LEFT));
            }
            else {
                if (!type)
                    lanes.push_back(new CROAD(xy, speed, CCONSTANT::RIGHT));
                else
                    lanes.push_back(new CGRASS(xy, speed, CCONSTANT::RIGHT));
            }
        }
    }
    
    Vector2f fl;
    fin.read((char*)&fl, sizeof(Vector2f));
    finish_line = new CFinishLine(fl);
    
    return true;
}

bool CGAME::saveGame() {
    ofstream fout("game_log/game.dat", ios::out | ios::binary);
    ifstream fin("game_log/temp_file.dat", ios::in | ios::binary);
    if (!fout || !fin) {
        cout << "Load file not found. Error." << endl;
        return false;
    }
    fout.write((char*)&game_level, 4);
    fout.write((char*)&showedGameCompleted, sizeof(bool));
    Vector2f pos = player.getPlayerPosition();
    cout << pos.x << " " << pos.y << endl;
    fout.write((char*)&pos, sizeof(Vector2f));
    
    char c;
    while (!fin.eof()) {
        c = fin.get();
        fout.put(c);
    }

    cout << "Save game successfully" << endl;
    return true;
}

void CGAME::clearSavedGame() {
    ofstream fout("game_log/game.dat", ios::binary);
    fout.clear();
    int tmp = 0;
    fout.write((char*)&tmp, sizeof(int));
}
