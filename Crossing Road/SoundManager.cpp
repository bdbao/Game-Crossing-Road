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
	}
	
	/* Add buffer to sound */	
	this->sound.resize(this->sound_buffer.size());
	for (int i = 0; i < (int)this->sound_buffer.size(); i++)
		this->sound[i].setBuffer(this->sound_buffer[i]);
	
	/* Clock to manage multi thread and delay between sound */
	this->last_played.resize(this->sound_buffer.size(), sf::Time());	
	this->clock.restart();
}

void SoundManager::play_Walking() {
	if (this->clock.getElapsedTime().asSeconds() - this->last_played[0].asSeconds() > 0.375) {
		this->last_played[0] = this->clock.getElapsedTime();
		this->sound[0].play();
	}
}

void SoundManager::play_GameCompleted() {
	// Play once only for each level
	// If you want to play again, use reset() method below
	if (this->last_played[0] == sf::Time()) {
		this->last_played[0] = this->clock.getElapsedTime();
		this->sound[1].play();
	}
}

void SoundManager::play_GameOver() {
	if (this->clock.getElapsedTime().asSeconds() - this->last_played[0].asSeconds() > 0.375) {
		this->last_played[0] = this->clock.getElapsedTime();
		this->sound[2].play();
	}
}


void SoundManager::reset() {
	for (int i = 0; i < (int)this->last_played.size(); i++) {
		last_played[i] = sf::Time();
	}
}