#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

#include "utils.h"
#include "CCONSTANT.h"

#include <map>
#include <mutex>
#include <vector>
#include <string>
#include <iostream>

#include <SFML/Audio.hpp>

using std::mutex;
using std::vector;
using std::map;
using std::string;

class SoundManager {
	/* Singleton design pattern */
private:
	static SoundManager* pInstance;
	SoundManager();
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	static mutex mLocker;
public:
	static SoundManager* getInstance() {
		mLocker.lock();
		if (pInstance == nullptr) {
			pInstance = new SoundManager;
		}
		mLocker.unlock();
		return pInstance;
	}


	/* Attributes */
private:
	vector<sf::Sound> sound;
	vector<sf::SoundBuffer> sound_buffer;

	sf::Clock clock;
	vector<sf::Time> last_played;

	sf::Music* background_music;
	bool isPlayingBackground;

	map<string, int> sound_index;

	/* For Mute State */
	bool isMute = false;


	/* Public methods*/
public:
	void play_Walking();

	void play_GameCompleted();

	void play_GameOver();

	void play_Enemy(std::string typeEnemy);

	void play_Background();
	void pause_Background();
	void stop_Background();

	void play_EnemySound(const string& enemy);


	void reset();


	/* For Mute State */
	bool getIsMute() {
		return this->isMute;
	}
	void setIsMute(bool stateMute) {
		this->isMute = stateMute;
	}
};

#endif // !_SOUNDMANAGER_H_
