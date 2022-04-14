#pragma once

#include "SFML/Graphics.hpp"

#include <algorithm>
#include <vector>
#include <string>

class Player;

enum class MessageType
{
	ACHIEVEMENT,
	MESSAGE
};

enum class Event
{
	COINS_COLLECTED,
	RUNE_COLLECTED,
	FELL_FROM_HEIGHT
};

class MessageSystemAssetManager
{
public:
	MessageSystemAssetManager();
	~MessageSystemAssetManager();
	static MessageSystemAssetManager& getInstance();
	void initialize();
	sf::Texture* getTexture(MessageType type);
	sf::Font* getFont();

	std::map<MessageType, sf::Texture*> m_textures;
	sf::Font* m_font;
};

class Message: public sf::Drawable
{
public:
	Message(std::string message, MessageType type);
	
	std::string m_messageText;
	MessageType m_messageType;
	sf::Sprite m_messageSprite;
	sf::Text m_text;
	sf::Font m_font;
	float m_timeElapsed;
	float m_totalDuration;
	bool m_isDead;

	void update(float dt);
	void setPosition(sf::Vector2f newPosition);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class GameMessageSystem: public sf::Drawable
{
public:
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addMessage(std::string message, MessageType type);

	static GameMessageSystem& getInstance()
	{
		static GameMessageSystem instance;
		return instance;
	}
	
	std::vector<Message> m_messages;
private:
	GameMessageSystem() {}
};

class Observer
{
public:
	virtual void onNotify(const Player& entity, Event event) = 0;
};

class AchievementObserver : public Observer
{
public:
	AchievementObserver();
	bool m_coinsAchievementUnlocked;
	bool m_fallAchievementUnlocked;

	void onNotify(const Player& entity, Event event) override;
};

class GameStateObserver : public Observer
{
public:
	void onNotify(const Player& entity, Event event) override;
};

class Subject
{
public:
	void registerObserver(Observer* observer);
	void unregisterObserver(Observer* observer);
	void notify(const Player& entity, Event event);

	std::vector<Observer*> m_observers;
};