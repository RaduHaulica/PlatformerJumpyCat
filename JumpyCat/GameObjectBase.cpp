#include "GameObjectBase.h"

#include "Utility.h"

int GameObjectBase::IDBase{ 0 };

GameObjectBase::GameObjectBase() :
    m_dead{ false },
    m_position{ sf::Vector2f(0, 0) }
{
    m_id = GameObjectBase::IDBase++;
}

GameObjectBase* GameObjectBase::clone(sf::Vector2f position)
{
    GameObjectBase* newObj = new GameObjectBase();

    newObj->m_graphicsComponent = m_graphicsComponent;
    newObj->m_colliderComponent = m_colliderComponent;
    newObj->m_parentGameEngine = m_parentGameEngine;

    return newObj;
}

void GameObjectBase::setPosition(sf::Vector2f position)
{
    m_position = position;
    m_colliderComponent.setPosition(position);
    m_graphicsComponent.setPosition(position);
}

sf::Vector2f GameObjectBase::getPosition()
{
    return m_position;
}

void GameObjectBase::collide(GameObjectBase* collidee)
{
	bool found = false;
	for (int i = 0; i < m_collidedWith.size(); i++)
		if (m_collidedWith[i] == collidee)
			found = true;
	if (!found)
	{
		m_collidedWith.push_back(collidee);
		m_colliderComponent.onEntry(collidee);
	}
}

void GameObjectBase::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_graphicsComponent);
	target.draw(m_colliderComponent);
}

void GameObjectBase::update(float dt)
{
	m_graphicsComponent.update(dt, m_position);
	m_colliderComponent.update(dt, m_position);

	for (int i = 0; i < m_collidedWith.size(); i++)
	{
		if (checkRectangleCollision(m_colliderComponent.m_colliders[0], m_collidedWith[i]->m_colliderComponent.m_colliders[0]))
			m_collidedWith[i]->m_colliderComponent.onHold(this);
		else
		{
			m_colliderComponent.onExit(m_collidedWith[i]);
			m_collidedWith.erase(m_collidedWith.begin() + i);
			i--;
		}
	}
}

void GameObjectBase::kill()
{
	m_dead = true;
}

void GameObjectBase::handleInput(Input input)
{

}