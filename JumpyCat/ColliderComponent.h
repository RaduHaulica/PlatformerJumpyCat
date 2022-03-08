#pragma once

#include <SFML/Graphics.hpp>

class GameObject;

class ColliderComponent: public sf::Drawable
{
public:
	GameObject* m_parent;

	std::vector<sf::RectangleShape> m_colliders;
	std::vector<sf::Vector2f> m_offsets;

	void setPosition(sf::Vector2f position)
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			m_colliders[i].setPosition(position);
		}
	}

	void addColliders(std::vector<sf::RectangleShape> colliders, std::vector<sf::Vector2f> offsets)
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			m_colliders.push_back(colliders[i]);
			if (offsets.size() > 0)
				m_offsets.push_back(offsets[i]);
		}
	}

	void update(float dt, sf::Vector2f position)
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			m_colliders[i].setPosition(position + m_offsets[i]);
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//if (config.debug)
		{
			for (int i = 0; i < m_colliders.size(); i++)
			{
				target.draw(m_colliders[i]);
			}
		}
	}
};