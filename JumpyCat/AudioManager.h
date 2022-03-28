#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <assert.h>
#include <cassert>

#include "Utility.h"
#include "SoundManager.h"

#include <array>

class AudioManager
{
public:
	AudioManager();
	static void initialize();

	static void update(float dt);
	static void playSound(SoundId id, int volume = 100);
	static std::unique_ptr<sf::Sound> loadSound(SoundId);
	static void startSound(std::unique_ptr<sf::Sound> sound, int volume = 100);

	static const int MAX_PENDING_MESSAGES = 15;

	static std::vector<std::unique_ptr<sf::Sound>> m_currentlyPlayingSounds;
	static std::array<PlayMessage, MAX_PENDING_MESSAGES> m_pendingMessages;
	static int m_pendingMessageCount;
	static SoundManager& m_soundManager;
};