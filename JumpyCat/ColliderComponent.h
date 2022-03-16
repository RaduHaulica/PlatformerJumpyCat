#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class GameObjectBase;

class ColliderComponent: public sf::Drawable
{
public:
	GameObjectBase* m_parent;

	std::vector<sf::RectangleShape> m_colliders;
	std::vector<sf::Vector2f> m_offsets;

	void setPosition(sf::Vector2f position);

	void onEntry(GameObjectBase* intruder);
	void onHold(GameObjectBase* intruder);
	void onExit(GameObjectBase* intruder);

	void addColliders(std::vector<sf::RectangleShape> colliders, std::vector<sf::Vector2f> offsets);

	void update(float dt, sf::Vector2f position);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};