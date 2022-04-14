#include "GameMessageSystem.h"

#include "Player.h"
#include "GameEngine.h"

MessageSystemAssetManager::MessageSystemAssetManager()
{
	initialize();
}

MessageSystemAssetManager::~MessageSystemAssetManager()
{
	delete m_font;
	for (auto& item : m_textures)
	{
		delete item.second;
	}
}

void MessageSystemAssetManager::initialize()
{
	std::string basePath = "./assets/graphics/";
	
	sf::Texture* messageTex = new sf::Texture();
	messageTex->loadFromFile(basePath + "ribbon_message.png");
	m_textures.insert_or_assign(MessageType::MESSAGE, messageTex);

	sf::Texture* achievementTex = new sf::Texture();
	achievementTex->loadFromFile(basePath + "ribbon_star.png");
	m_textures.insert_or_assign(MessageType::ACHIEVEMENT, achievementTex);

	m_font = new sf::Font();
	if (!m_font->loadFromFile("./assets/Roboto-Bold.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}
}

sf::Texture* MessageSystemAssetManager::getTexture(MessageType type)
{
	return m_textures.at(type);
}

sf::Font* MessageSystemAssetManager::getFont()
{
	return m_font;
}

MessageSystemAssetManager& MessageSystemAssetManager::getInstance()
{
	static MessageSystemAssetManager* instance = new MessageSystemAssetManager();
	return *instance;
}

Message::Message(std::string message, MessageType type):
	m_totalDuration{ 3.0f },
	m_timeElapsed{ 0.0f },
	m_messageText{ message },
	m_isDead{false},
	m_messageType{ type }
{
	m_text.setFont(*MessageSystemAssetManager::getInstance().getFont());
	m_text.setString(m_messageText);
	m_messageSprite.setTexture(*MessageSystemAssetManager::getInstance().getTexture(type));
	m_messageSprite.setScale(1.5f, 1.5f);
}

void Message::update(float dt)
{
	m_timeElapsed += dt;
	if (m_timeElapsed >= m_totalDuration)
	{
		m_isDead = true;
	}
}

void Message::setPosition(sf::Vector2f newPosition)
{
	sf::Vector2f offset;
	if (m_messageType == MessageType::MESSAGE)
	{
		offset = sf::Vector2f(20.0f, 10.0f);
	}
	else
	{
		offset = sf::Vector2f(80.0f, 20.0f);
	}
	m_messageSprite.setPosition(newPosition);
	m_text.setPosition(newPosition + offset);
}

void Message::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_messageSprite);
	target.draw(m_text);
}

AchievementObserver::AchievementObserver():
	m_coinsAchievementUnlocked{false},
	m_fallAchievementUnlocked{false}
{}

void AchievementObserver::onNotify(const Player& entity, Event event)
{
	switch (event)
	{
	case Event::COINS_COLLECTED:
		if (!m_coinsAchievementUnlocked && entity.m_coinsCollected > 3)
		{
			GameMessageSystem::getInstance().addMessage("Mad stacks!", MessageType::ACHIEVEMENT);
			std::cout << "Stacks overflowing!" << std::endl;
			m_coinsAchievementUnlocked = true;
		}
		break;
	case Event::FELL_FROM_HEIGHT:
		if (!m_fallAchievementUnlocked)
		{
			GameMessageSystem::getInstance().addMessage("Leap of faith!", MessageType::ACHIEVEMENT);
			std::cout << "Leap of faith!" << std::endl;
			m_fallAchievementUnlocked = true;
		}
		break;
	}
}

void GameStateObserver::onNotify(const Player& entity, Event event)
{
	switch (event)
	{
		case Event::COINS_COLLECTED:
			if (entity.m_coinsCollected == 3)
			{
				GameMessageSystem::getInstance().addMessage("A door opens...", MessageType::MESSAGE);
				entity.m_parentGameEngine->openDoor();
				std::cout<<"A door opens..."<<std::endl;
			}
			break;
		case Event::RUNE_COLLECTED:
			GameMessageSystem::getInstance().addMessage("Double jump!", MessageType::MESSAGE);
			std::cout << "Double jump activated!" << std::endl;
			break;
	}
}

void Subject::registerObserver(Observer* observer)
{
	m_observers.push_back(observer);
}

void Subject::unregisterObserver(Observer* observer)
{
	std::remove(m_observers.begin(), m_observers.end(), observer);
}

void Subject::notify(const Player& entity, Event event)
{
	for (auto& observer : m_observers)
	{
		observer->onNotify(entity, event);
	}
}

void GameMessageSystem::update(float dt)
{
	float offsetX{ 910.0f };
	float offsetY{ 800.0f };

	for (int i = 0; i < m_messages.size(); i++)
	{
		m_messages[i].update(dt);
		if (m_messages[i].m_isDead)
		{
			m_messages.erase(m_messages.begin() + i);
			i--;
		}
		else
		{
			float size = m_messages[i].m_messageSprite.getGlobalBounds().height * 1.2f;
			m_messages[i].setPosition(sf::Vector2f(offsetX, offsetY - (i * size)));
		}
	}
}

void GameMessageSystem::addMessage(const std::string message, MessageType type)
{
	Message newMessage(message, type);
	m_messages.push_back(newMessage);
}

void GameMessageSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	for (auto& message:m_messages)
	{
		target.draw(message);
	}
}