#pragma once

#include "GameObjectBase.h"
#include "Player.h"

class HealthBar: public GameObjectBase
{
public:
	int m_currentHealth;
	int m_maximumHealth;
	int m_currentCoins;
	sf::Text m_coinText;
	sf::Font m_font;
	sf::Vector2f m_position;
	Player* m_parentPlayer;

	std::vector<GraphicsComponent> m_graphicsComponents;

	HealthBar(sf::Vector2f newPosition);

	void update(float dt);
	void synchronize(Player* player);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f newPosition);
};