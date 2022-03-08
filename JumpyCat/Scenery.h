#pragma once

#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"

class Scenery: public sf::Drawable
{
public:
	GraphicsComponent m_graphicsComponent;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};