#include "SoundManager.h"

SoundManager& SoundManager::getInstance()
{
	static SoundManager* instance = new SoundManager();
	return *instance;
}

SoundManager::SoundManager()
{
	//std::string basePath = "./assets/sounds/";

	//sf::SoundBuffer* jumpingSound = new sf::SoundBuffer();
	//jumpingSound->loadFromFile(basePath + "cat_jumping.ogg");
	//m_sounds.insert_or_assign("cat_jumping", jumpingSound);

	//sf::SoundBuffer* coinCollectSound = new sf::SoundBuffer();
	//coinCollectSound->loadFromFile(basePath + "powerup_coin2.ogg");
	//m_sounds.insert_or_assign("coin_collect", coinCollectSound);
}

void SoundManager::initialize()
{
	// makes sure there's an instance the first time the function is called
	SoundManager& self = getInstance();

	std::string basePath = "./assets/sounds/";

	sf::SoundBuffer* jumpingSound = new sf::SoundBuffer();
	jumpingSound->loadFromFile(basePath + "cat_jumping.ogg");
	self.m_sounds.insert_or_assign("cat_jumping", jumpingSound);

	sf::SoundBuffer* coinCollectSound = new sf::SoundBuffer();
	coinCollectSound->loadFromFile(basePath + "powerup_coin2.ogg");
	self.m_sounds.insert_or_assign("coin_collected", coinCollectSound);

	sf::SoundBuffer* runeColectSound = new sf::SoundBuffer();
	runeColectSound->loadFromFile(basePath + "powerup_rune.ogg");
	self.m_sounds.insert_or_assign("rune_collected", runeColectSound);

	sf::SoundBuffer* achievementSound = new sf::SoundBuffer();
	achievementSound->loadFromFile(basePath + "achievement.ogg");
	self.m_sounds.insert_or_assign("achievement", achievementSound);
}

std::unique_ptr<sf::Sound> SoundManager::getSound(std::string soundName)
{
	std::unique_ptr<sf::Sound> result = std::make_unique<sf::Sound>();
	result->setBuffer(*m_sounds[soundName]);
	return std::move(result);
}

SoundManager::~SoundManager()
{
	std::map<std::string, sf::SoundBuffer*>::iterator iter;
	for (iter = m_sounds.begin(); iter != m_sounds.end(); iter++)
		delete iter->second;
}