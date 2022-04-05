#include "GameActorEnemy.h"

#include "GameEngine.h"

GameActorEnemy::GameActorEnemy(std::string name, sf::Vector2f size) :
	GameActorBase(name, size)
{
	m_objectType = GameObjectType::ENEMY;
	m_facingRight = true;
}

void GameActorEnemy::update(float dt)
{
	// keeping this here for now
	Input mockInput;
	mockInput.control = CONTROLS::NOTHING;
	handleInput(mockInput);

	if (m_facingRight)
		move(CONTROLS::PRESSED_RIGHT);
	else
		move(CONTROLS::PRESSED_LEFT);

	int directionMultiplier = 1 + !m_facingRight * (-2);
	//m_velocity.x = 200 * directionMultiplier;

	GameActorBase::update(dt);


	if (isGrounded() && (isFootSlipping() || walkedIntoAWall()))
	{
		sf::Vector2f newPosition = m_position;
		newPosition.x += (directionMultiplier * (-1) * m_velocity.x * dt);
		setPosition(m_position);
		m_facingRight = !m_facingRight;
	}

	auto [x, y] = m_graphicsComponent.getScale();
	if ((m_facingRight && x < 0) || (!m_facingRight && x > 0))
	{
		m_graphicsComponent.setScale({ -x, y });
	}
	if (!m_facingRight)
	{
		m_graphicsComponent.setPosition({ m_position.x + m_size.x + 10, m_position.y });
	}
	else
	{
		m_graphicsComponent.setPosition({ m_position.x + m_size.x -100, m_position.y });
	}
}

void GameActorEnemy::move(CONTROLS direction)
{
	Input input;
	input.control = direction;
	handleInput(input);
}

bool GameActorEnemy::isFootSlipping()
{
	if (m_platform == nullptr)
		return false;

	bool leftFootOnGround{ false };
	bool rightFootOnGround{ false };
	for (auto& wall : m_parentGameEngine->getWalls())
	{
		if (wall->m_colliderComponent.m_colliders[0].getGlobalBounds().contains(bottomLeftFeeler))
		{
			leftFootOnGround = true;
		}
		if (wall->m_colliderComponent.m_colliders[0].getGlobalBounds().contains(bottomRightFeeler))
		{
			rightFootOnGround = true;
		}
	}

	return (leftFootOnGround + rightFootOnGround == 1);
}

bool GameActorEnemy::walkedIntoAWall()
{
	for (auto& wall : m_parentGameEngine->getWalls())
	{
		if (wall->m_colliderComponent.m_colliders[0].getGlobalBounds().contains(leftBottomFeeler)
			|| wall->m_colliderComponent.m_colliders[0].getGlobalBounds().contains(rightBottomFeeler))
		{
			return true;
		}
	}
	return false;
}