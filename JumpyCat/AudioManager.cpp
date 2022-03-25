#include "AudioManager.h"

int AudioManager::m_pendingMessageCount = 0;
PlayMessage AudioManager::m_pendingMessages[AudioManager::MAX_PENDING_MESSAGES];

AudioManager::AudioManager()
{
	AudioManager::m_pendingMessageCount = 0;
}

void AudioManager::initialize()
{
	AudioManager::m_pendingMessageCount = 0;
}

void AudioManager::update(float dt)
{
	for (int i = 0; i < AudioManager::m_pendingMessageCount; i++)
	{
		sf::Sound* resource = loadSound(AudioManager::m_pendingMessages[i].id);
		startSound(resource, AudioManager::m_pendingMessages[i].volume);
	}
	AudioManager::m_pendingMessageCount = 0;
}

void AudioManager::playSound(SoundId id, int volume)
{
	//assert(m_pendingMessageCount < MAX_PENDING_MESSAGES);
	if (AudioManager::m_pendingMessageCount >= MAX_PENDING_MESSAGES)
		exit(-1);

	for (int i = 0; i < AudioManager::m_pendingMessageCount; i++)
	{
		if (AudioManager::m_pendingMessages[i].id == id)
		{
			AudioManager::m_pendingMessages[i].volume = std::max(volume, AudioManager::m_pendingMessages[i].volume);
			// no need to enqueue existing sound
			return;
		}
	}

	AudioManager::m_pendingMessages[AudioManager::m_pendingMessageCount].id = id;
	AudioManager::m_pendingMessages[AudioManager::m_pendingMessageCount].volume = volume;
	AudioManager::m_pendingMessageCount++;
}

sf::Sound* AudioManager::loadSound(SoundId id)
{
	sf::Sound* sound = new sf::Sound();
	//sound.setBuffer(*m_soundManager.getInstance().getSound(id.getSoundName()));
	//sound.setBuffer(*SoundManager::getInstance().getSound(id.getSoundName()));
	sound->setBuffer(*SoundManager::getInstance().m_sounds[id.getSoundName()]);
	return sound;
}

void AudioManager::startSound(sf::Sound* sound, int volume)
{
	sound->setVolume(volume);
	sound->play();
}