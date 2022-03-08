#include "GameObject.h"

GameObject::GameObject() :
    m_terminated{ false },
	m_position{ sf::Vector2f(0, 0) }
{}

GameObject* GameObject::clone(sf::Vector2f position)
{
	GameObject* newObj = new GameObject();

	newObj->m_graphicsComponent = m_graphicsComponent;
	newObj->m_colliderComponent = m_colliderComponent;
	newObj->m_parentGameEngine = m_parentGameEngine;

	return newObj;
}

void GameObject::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_colliderComponent.setPosition(position);
	m_graphicsComponent.setPosition(position);
}

sf::Vector2f GameObject::getPosition()
{
	return m_position;
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_graphicsComponent);
	target.draw(m_colliderComponent);
}

void GameObject::update(float dt)
{
	m_graphicsComponent.update(dt, m_position);
	m_colliderComponent.update(dt, m_position);
}

void GameObject::handleInput(Input input)
{

}