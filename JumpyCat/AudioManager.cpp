#include "AudioManager.h"

int AudioManager::m_pendingMessageCount = 0;
std::array<PlayMessage, AudioManager::MAX_PENDING_MESSAGES> AudioManager::m_pendingMessages;
std::vector<std::unique_ptr<sf::Sound>> AudioManager::m_currentlyPlayingSounds;

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
		std::unique_ptr<sf::Sound> resource = loadSound(AudioManager::m_pendingMessages[i].id);
		//startSound(std::move(resource), AudioManager::m_pendingMessages[i].volume);
		resource->setVolume(AudioManager::m_pendingMessages[i].volume);
		resource->play();
		AudioManager::m_currentlyPlayingSounds.push_back(std::move(resource));
	}
	AudioManager::m_pendingMessageCount = 0;

	for (int i = 0; i < AudioManager::m_currentlyPlayingSounds.size(); i++)
	{
		if (m_currentlyPlayingSounds[i]->getStatus() == sf::SoundSource::Status::Stopped)
		{
			m_currentlyPlayingSounds.erase(m_currentlyPlayingSounds.begin() + i);
			i--;
		}
	}
}

void AudioManager::playSound(SoundId id, int volume)
{
	if (AudioManager::m_pendingMessageCount >= MAX_PENDING_MESSAGES)
		return;

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

std::unique_ptr<sf::Sound> AudioManager::loadSound(SoundId id)
{
	std::unique_ptr<sf::Sound> sound;
	//sound.setBuffer(*m_soundManager.getInstance().getSound(id.getSoundName()));
	//sound.setBuffer(*SoundManager::getInstance().getSound(id.getSoundName()));
	sound = SoundManager::getInstance().getSound(id.getSoundName());
	return std::move(sound);
}

void AudioManager::startSound(std::unique_ptr<sf::Sound> sound, int volume)
{
	sound->setVolume(volume);
	sound->play();
}