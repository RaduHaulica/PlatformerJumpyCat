#include "SoundManager.h"

SoundManager& SoundManager::getInstance()
{
	static SoundManager* instance = new SoundManager();
	instance->initialize();
	return *instance;
}

SoundManager::SoundManager()
{
	std::string basePath = "./assets/sounds/";

	sf::SoundBuffer* jumpingSound = new sf::SoundBuffer();
	jumpingSound->loadFromFile(basePath + "cat_jumping.ogg");
	m_sounds.insert_or_assign("cat_jumping", jumpingSound);

	sf::SoundBuffer* coinCollectSound = new sf::SoundBuffer();
	coinCollectSound->loadFromFile(basePath + "powerup_coin2.ogg");
	m_sounds.insert_or_assign("coin_collect", coinCollectSound);
}

void SoundManager::initialize()
{
	std::string basePath = "./assets/sounds/";

	sf::SoundBuffer* jumpingSound = new sf::SoundBuffer();
	jumpingSound->loadFromFile(basePath + "cat_jumping.ogg");
	m_sounds.insert_or_assign("cat_jumping", jumpingSound);

	sf::SoundBuffer* coinCollectSound = new sf::SoundBuffer();
	coinCollectSound->loadFromFile(basePath + "powerup_coin2.ogg");
	m_sounds.insert_or_assign("coin_collected", coinCollectSound);
}

sf::SoundBuffer* SoundManager::getSound(std::string soundName)
{
	return m_sounds[soundName];
}

SoundManager::~SoundManager()
{
	std::map<std::string, sf::SoundBuffer*>::iterator iter;
	for (iter = m_sounds.begin(); iter != m_sounds.end(); iter++)
		delete iter->second;
}