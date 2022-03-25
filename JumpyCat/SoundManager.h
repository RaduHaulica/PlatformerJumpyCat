#pragma once

#include <SFML/Audio.hpp>

#include <string>
#include <map>

#include "Utility.h"

// ===== ===== ===== ===== =====
//		SOUND MANGER
// ===== ===== ===== ===== =====

class SoundManager
{
public:
	static SoundManager& getInstance();

	void initialize();

	~SoundManager();
	sf::SoundBuffer* getSound(std::string);

	std::map<std::string, sf::SoundBuffer*> m_sounds;
private:
	SoundManager();
};