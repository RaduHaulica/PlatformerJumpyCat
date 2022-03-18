#pragma once

#include "GameObjectBase.h"
#include "Player.h"

class HealthBar: public GameObjectBase
{
public:
	int m_currentHealth;
	int m_maximumHealth;
	sf::Vector2f m_position;
	Player* m_parentPlayer;

	std::vector<GraphicsComponent> m_graphicsComponents;

	HealthBar(sf::Vector2f newPosition):
		m_position{newPosition}
	{}

	void update(float dt)
	{
		//synchronize(m_parentPlayer);
		m_currentHealth = m_parentPlayer->m_currentHealth;
		m_maximumHealth = m_parentPlayer->m_maximumHealth;

		for (int i = 0; i < m_graphicsComponents.size(); i++)
		{
			m_graphicsComponents[i].m_currentAnimation = "empty";
		}

		for (int i = 0; i < m_currentHealth; i++)
		{
			m_graphicsComponents[i].m_currentAnimation = "full";
		}
	}

	void synchronize(Player* player)
	{
		m_parentPlayer = player;
		m_currentHealth = player->m_currentHealth;
		m_maximumHealth = player->m_maximumHealth;

		m_graphicsComponents.clear();
		for (int i = 0; i < m_maximumHealth; i++)
			m_graphicsComponents.push_back(GraphicsComponent());
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < m_maximumHealth; i++)
			m_graphicsComponents[i].draw(target, states);
	}

	void setPosition(sf::Vector2f newPosition)
	{
		for (int i = 0; i < m_maximumHealth; i++)
		{
			sf::Vector2f position = newPosition;
			position.x += (i * 64);
			m_graphicsComponents[i].m_animations["full"].m_animationFrames[0].setPosition(position);
			m_graphicsComponents[i].m_animations["empty"].m_animationFrames[0].setPosition(position);
		}
	}

};