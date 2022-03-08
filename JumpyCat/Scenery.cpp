#include "Scenery.h"

void Scenery::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_graphicsComponent);
}