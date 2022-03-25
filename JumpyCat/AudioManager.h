#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <assert.h>
#include <cassert>

#include "Utility.h"
#include "SoundManager.h"

class AudioManager
{
public:
	AudioManager();
	static void initialize();

	static void update(float dt);
	static void playSound(SoundId id, int volume = 100);
	static sf::Sound* loadSound(SoundId);
	static void startSound(sf::Sound*, int volume = 100);

	static const int MAX_PENDING_MESSAGES = 15;

	static PlayMessage m_pendingMessages[MAX_PENDING_MESSAGES];
	static int m_pendingMessageCount;
	static SoundManager& m_soundManager;
};