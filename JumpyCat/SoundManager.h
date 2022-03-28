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

	static void initialize();

	~SoundManager();
	std::unique_ptr<sf::Sound> getSound(std::string);

	std::map<std::string, sf::SoundBuffer*> m_sounds;
private:
	SoundManager();
};