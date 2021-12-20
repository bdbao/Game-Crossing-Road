#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

#include "utils.h"
#include "CCONSTANT.h"
#include "SFML/Audio.hpp"

#include <mutex>
#include <vector>
#include <string>

using std::mutex;
using std::vector;

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
	vector< sf::SoundBuffer> sound_buffer;

	sf::Clock clock;
	vector<sf::Time> last_played;


	/* Public methods*/
public:
	void play_Walking();

	void play_GameCompleted();

	void play_GameOver();

	void play_Enemy(std::string typeEnemy);

	void reset();

};

#endif // !_SOUNDMANAGER_H_
