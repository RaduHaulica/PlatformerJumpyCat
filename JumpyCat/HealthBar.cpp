#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f newPosition) :
	m_position{ newPosition }
{
	m_font.loadFromFile("./assets/Roboto-Bold.ttf");
	m_coinText.setFont(m_font);
	m_coinText.setCharacterSize(36);
	m_coinText.setFillColor(sf::Color::Black);
}

void HealthBar::update(float dt)
{
	//synchronize(m_parentPlayer);
	m_currentHealth = m_parentPlayer->m_currentHealth;
	m_maximumHealth = m_parentPlayer->m_maximumHealth;
	m_currentCoins = m_parentPlayer->m_coinsCollected;
	m_coinText.setString(std::to_string(m_currentCoins) + "/3");

	for (int i = 0; i < m_graphicsComponents.size(); i++)
	{
		m_graphicsComponents[i].m_currentAnimation = "empty";
	}

	for (int i = 0; i < m_currentHealth; i++)
	{
		m_graphicsComponents[i].m_currentAnimation = "full";
	}
}

void HealthBar::synchronize(Player& player)
{
	m_parentPlayer = &player;
	m_currentHealth = player.m_currentHealth;
	m_maximumHealth = player.m_maximumHealth;

	m_graphicsComponents.clear();
	for (int i = 0; i < m_maximumHealth; i++)
		m_graphicsComponents.push_back(GraphicsComponent());
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	m_graphicsComponent.draw(target, states);
	target.draw(m_coinText, states);
	for (int i = 0; i < m_maximumHealth; i++)
		m_graphicsComponents[i].draw(target, states);
}

void HealthBar::setPosition(sf::Vector2f newPosition)
{
	m_graphicsComponent.m_animations["standing"].m_animationFrames[0].setPosition({ newPosition.x + 64 * m_maximumHealth, newPosition.y });
	m_coinText.setPosition({ newPosition.x + 64 * (m_maximumHealth + 1), newPosition.y });
	for (int i = 0; i < m_maximumHealth; i++)
	{
		sf::Vector2f position = newPosition;
		position.x += (i * 64);
		m_graphicsComponents[i].m_animations["full"].m_animationFrames[0].setPosition(position);
		m_graphicsComponents[i].m_animations["empty"].m_animationFrames[0].setPosition(position);
	}
}