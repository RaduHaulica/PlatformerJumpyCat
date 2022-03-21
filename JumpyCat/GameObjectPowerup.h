#pragma once

#include "GameObjectBase.h"

class GameObjectPowerup : public GameObjectBase
{
public:
	sf::Vector2f m_size;
	float m_accumulator;
	sf::Vector2f m_velocity;

	GameObjectPowerup():
		m_accumulator{ 0.0f }
	{
	}

	virtual void update(float dt) override
	{
		m_velocity = { 0.0f, m_size.y };
		m_size = { m_graphicsComponent.m_animations[m_graphicsComponent.m_currentAnimation].m_animationFrames[0].getGlobalBounds().width, m_graphicsComponent.m_animations[m_graphicsComponent.m_currentAnimation].m_animationFrames[0].getGlobalBounds().height };
		float pi = 3.14159f;
		m_accumulator += (2 * pi * dt);
		if (m_accumulator >= 2 * pi)
			m_accumulator -= (2 * pi);
		m_position += (m_velocity * std::sin(m_accumulator) * dt);

		setPosition(m_position);
		GameObjectBase::update(dt);
	}
};