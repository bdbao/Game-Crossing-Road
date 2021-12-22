#include "SoundManager.h"

/* Singleton design pattern */
SoundManager* SoundManager::pInstance = nullptr;
mutex SoundManager::mLocker;


SoundManager::SoundManager() {
	sf::SoundBuffer temp;
	
	/* Load all file to buffer here */
	{
		// 0: walking4.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[0].loadFromFile("./assets/sounds/walking4.wav");

		// 1: game_completed
		this->sound_buffer.push_back(temp);
		this->sound_buffer[1].loadFromFile("./assets/sounds/game-completed.wav");

		// 2: game_over
		this->sound_buffer.push_back(temp);
		this->sound_buffer[2].loadFromFile("./assets/sounds/game-over.wav");

		// 3: reindeer.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[3].loadFromFile("./assets/sounds/reindeer.wav");

		// 4: penguin.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[4].loadFromFile("./assets/sounds/penguin.wav");

		// 5: bulls.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[5].loadFromFile("./assets/sounds/bulls.wav");

		// 6: penguin.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[6].loadFromFile("./assets/sounds/car-horn.wav");

		// 7: double-horn.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[7].loadFromFile("./assets/sounds/double-horn.wav");
		
		//8 polar_bear.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[8].loadFromFile("./assets/sounds/polar_bear.wav");

		//9 siberian_dog.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[9].loadFromFile("./assets/sounds/siberia_dog.wav");

		//10 snowman.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[10].loadFromFile("./assets/sounds/snowman.wav");
		
	}
	
	/* Add buffer to sound */	
	this->sound.resize(this->sound_buffer.size());
	for (int i = 0; i < (int)this->sound_buffer.size(); i++)
		this->sound[i].setBuffer(this->sound_buffer[i]);
	
	/* Clock to manage multi thread and delay between sound */
	this->last_played.resize(this->sound_buffer.size(), sf::Time());	
	this->clock.restart();


	/* load background music */
	this->background_music = new sf::Music;
	if (!this->background_music->openFromFile("./assets/sounds/background-music.wav")) {
		std::cout << "Cannot open background music" << std::endl;
		return;
	}
	this->background_music->setLoop(true);
	this->isPlayingBackground = false;
}

void SoundManager::play_Walking() {
	if (this->clock.getElapsedTime().asSeconds() - this->last_played[0].asSeconds() > CCONSTANT::DELAY_WALKING_SOUND) {
		this->last_played[0] = this->clock.getElapsedTime();
		this->sound[0].play();
	}
}

void SoundManager::play_GameCompleted() {
	// Play once only for each level
	// If you want to play again, use reset() method below
	if (this->last_played[1] == sf::Time()) {
		this->last_played[1] = this->clock.getElapsedTime();
		this->sound[1].play();
	}
}

void SoundManager::play_GameOver() {
	// Play once only for each level
	// If you want to play again, use reset() method below
	if (this->last_played[2] == sf::Time()) {
		this->last_played[2] = this->clock.getElapsedTime();
		this->sound[2].play();
	}
}

void SoundManager::play_Enemy(std::string typeEnemy) {
	/* animal */
	if (typeEnemy == "reindeer") {
		// Check if the delta time between two playing is bigger than delay time
		// to avoid noisy when playing
		if (this->clock.getElapsedTime().asSeconds() - this->last_played[3].asSeconds() - Rand(1000, 3000) / 1000.0 > CCONSTANT::DELAY_REINDEER_SOUND) {
			// Update last played time
			this->last_played[3] = this->clock.getElapsedTime();

			// Play sound
			this->sound[3].play();
		}
	}
	if (typeEnemy == "penguin") {
		// Check if the delta time between two playing is bigger than delay time
		// to avoid noisy when playing
		if (this->clock.getElapsedTime().asSeconds() - this->last_played[4].asSeconds() - Rand(1000, 3000) / 1000.0 > CCONSTANT::DELAY_PENGUIN_SOUND) {
			// Update last played time
			this->last_played[4] = this->clock.getElapsedTime();

			// Play sound
			this->sound[4].play();
		}
	}
	if (typeEnemy == "bulls") {
		// Check if the delta time between two playing is bigger than delay time
		// to avoid noisy when playing
		if (this->clock.getElapsedTime().asSeconds() - this->last_played[5].asSeconds() - Rand(1000, 3000) / 1000.0 > CCONSTANT::DELAY_BULL_SOUND) {
			// Update last played time
			this->last_played[5] = this->clock.getElapsedTime();

			// Play sound
			this->sound[5].play();
		}
	}  

	/* car */
	if (typeEnemy == "car") {
		// Check if the delta time between two playing is bigger than delay time
		// to avoid noisy when playing
		long long pos = Rand(6, 7);
		if (this->clock.getElapsedTime().asSeconds() - this->last_played[pos].asSeconds() - Rand(1000, 3000) / 1000.0 > CCONSTANT::DELAY_CAR_SOUND) {
			// Update last played time
			this->last_played[pos] = this->clock.getElapsedTime();

			// Play sound
			this->sound[pos].play();
		}
	}
	
		if (typeEnemy == "polarBear") {
		// Check if the delta time between two playing is bigger than delay time
		// to avoid noisy when playing
		if (this->clock.getElapsedTime().asSeconds() - this->last_played[8].asSeconds() - Rand(1000, 3000) / 1000.0 > CCONSTANT::DELAY_BULL_SOUND) {
			// Update last played time
			this->last_played[8] = this->clock.getElapsedTime();

			// Play sound
			this->sound[8].play();
		}
	}

	if (typeEnemy == "siberianDog") {
		// Check if the delta time between two playing is bigger than delay time
		// to avoid noisy when playing
		if (this->clock.getElapsedTime().asSeconds() - this->last_played[9].asSeconds() - Rand(1000, 3000) / 1000.0 > CCONSTANT::DELAY_BULL_SOUND) {
			// Update last played time
			this->last_played[9] = this->clock.getElapsedTime();

			// Play sound
			this->sound[9].play();
		}
	}

	if (typeEnemy == "snowMan") {
		// Check if the delta time between two playing is bigger than delay time
		// to avoid noisy when playing
		if (this->clock.getElapsedTime().asSeconds() - this->last_played[10].asSeconds() - Rand(1000, 3000) / 1000.0 > CCONSTANT::DELAY_BULL_SOUND) {
			// Update last played time
			this->last_played[10] = this->clock.getElapsedTime();

			// Play sound
			this->sound[10].play();
		}
	}
}

void SoundManager::reset() {
	this->clock.restart();
	for (int i = 0; i < (int)this->last_played.size(); i++) {
		last_played[i] = sf::Time();
	}
}

void SoundManager::play_Background() {
	if (!this->isPlayingBackground) {
		this->isPlayingBackground = true;
		this->background_music->play();
	}
}

void SoundManager::pause_Background() {
	if (this->isPlayingBackground) {
		this->isPlayingBackground = false;
		this->background_music->pause();
	}
}

void SoundManager::stop_Background() {
	if (this->isPlayingBackground) {
		this->isPlayingBackground = false;
		this->background_music->stop();
	}
}
