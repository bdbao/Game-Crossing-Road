#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_


#include "SFML/Audio.hpp"

#include <vector>

using std::vector;

class SoundManager {
	/* Singleton design pattern */
	static SoundManager* pInstance;

	vector<sf::Sound> sound;
	vector< sf::SoundBuffer> sound_buffer;

	sf::Clock clock;
	vector<sf::Time> last_played;
public:
	SoundManager();
	// SoundManager* getInstance();


	void play_Walking();

	void play_GameCompleted();

	void play_GameOver();

	void reset();

};

#endif // !_SOUNDMANAGER_H_
