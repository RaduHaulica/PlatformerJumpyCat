#include "ColliderComponent.h"

void ColliderComponent::setPosition(sf::Vector2f position)
{
	for (int i = 0; i < m_colliders.size(); i++)
	{
		m_colliders[i].setPosition(position);
	}
}

void ColliderComponent::onEntry(GameObjectBase* intruder)
{
	//std::cout << m_parent->m_id << ": CollisionComponent : with " << intruder->m_id << " : onEntry()\n";
}

void ColliderComponent::onHold(GameObjectBase* intruder)
{
	//std::cout << "Holding: " << m_parent->m_id << " over: " << intruder->m_id << "\n";
}

void ColliderComponent::onExit(GameObjectBase* intruder)
{
	//std::cout << m_parent->m_id << ": CollisionComponent : with " << intruder->m_id << " : onExit()\n";
}

void ColliderComponent::addColliders(std::vector<sf::RectangleShape> colliders, std::vector<sf::Vector2f> offsets)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		m_colliders.push_back(colliders[i]);
		if (offsets.size() > 0)
			m_offsets.push_back(offsets[i]);
	}
}

void ColliderComponent::update(float dt, sf::Vector2f position)
{
	for (int i = 0; i < m_colliders.size(); i++)
	{
		m_colliders[i].setPosition(position + m_offsets[i]);
	}
}

void ColliderComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//if (config.debug)
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			target.draw(m_colliders[i]);
		}
	}
}