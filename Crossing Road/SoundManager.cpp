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
		sound_index["walking"] = 0;

		// 1: game_completed
		this->sound_buffer.push_back(temp);
		this->sound_buffer[1].loadFromFile("./assets/sounds/game-completed.wav");
		sound_index["game_completed"] = 1;

		// 2: game_over
		this->sound_buffer.push_back(temp);
		this->sound_buffer[2].loadFromFile("./assets/sounds/game-over.wav");
		sound_index["game_over"] = 2;

		// 3: reindeer.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[3].loadFromFile("./assets/sounds/reindeer.wav");
		sound_index["reindeer"] = 3;

		// 4: penguin.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[4].loadFromFile("./assets/sounds/penguin.wav");
		sound_index["penguin"] = 4;

		// 5: bulls.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[5].loadFromFile("./assets/sounds/bulls.wav");
		sound_index["bulls"] = 5;

		// 6: penguin.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[6].loadFromFile("./assets/sounds/car-horn.wav");
		sound_index["car"] = 6;

		// 7: double-horn.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[7].loadFromFile("./assets/sounds/double-horn.wav");
		sound_index["car_double"] = 7;
		
		//8 polarbear.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[8].loadFromFile("./assets/sounds/polarbear.wav");
		sound_index["polarbear"] = 8;

		//9 siberiandog.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[9].loadFromFile("./assets/sounds/siberiandog.wav");
		sound_index["siberiandog"] = 9;

		//10 snowman.wav
		this->sound_buffer.push_back(temp);
		this->sound_buffer[10].loadFromFile("./assets/sounds/snowman.wav");
		sound_index["snowman"] = 10;
		
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
	if (isMute) return;
	if (this->clock.getElapsedTime().asSeconds() - this->last_played[0].asSeconds() > CCONSTANT::DELAY_WALKING_SOUND) {
		this->last_played[0] = this->clock.getElapsedTime();
		this->sound[0].play();
	}
}

void SoundManager::play_GameCompleted() {
	if (isMute) return;
	// Play once only for each level
	// If you want to play again, use reset() method below
	if (this->last_played[1] == sf::Time()) {
		this->last_played[1] = this->clock.getElapsedTime();
		this->sound[1].play();
	}
}

void SoundManager::play_GameOver() {
	if (isMute) return;
	// Play once only for each level
	// If you want to play again, use reset() method below
	if (this->last_played[2] == sf::Time()) {
		this->last_played[2] = this->clock.getElapsedTime();
		this->sound[2].play();
	}
}

void SoundManager::play_Enemy(std::string typeEnemy) {
	if (isMute) return;
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
	if (isMute) return;
	this->clock.restart();
	for (int i = 0; i < (int)this->last_played.size(); i++) {
		last_played[i] = sf::Time();
	}
}

void SoundManager::play_Background() {
	if (isMute) {
		pause_Background();
		return;
	}
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


void SoundManager::play_EnemySound(const string& enemy) {
	if (isMute) return;
	int idx = sound_index[enemy];
	float delay_time = 2.f;
	if (enemy == "car") {
		delay_time = 2.25f;
	}
	else if (enemy == "bulls") {
		delay_time = CCONSTANT::DELAY_BULL_SOUND;
	}
	else if (enemy == "penguins") {
		delay_time = CCONSTANT::DELAY_PENGUIN_SOUND;
	}
	if (this->clock.getElapsedTime().asSeconds() - this->last_played[idx].asSeconds() - Rand(1000, 5000) / 1000.0 > delay_time) {
		// Update last played time
		this->last_played[idx] = this->clock.getElapsedTime();

		// Play sound
		this->sound[idx].play();
	}
}

/* For Mute State */
bool SoundManager::getIsMute() {
	return this->isMute;
}
void SoundManager::setIsMute(bool stateMute) {
	this->isMute = stateMute;
}