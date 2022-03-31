#include "Player.h"

#include "GameEngine.h"

Player::Player(std::string name, sf::Vector2f size) :
    GameActorBase(name, size),
    m_currentHealth{ 3 },
    m_maximumHealth{ 3 },
    m_coinsCollected{ 0 }
{}

void Player::update(float dt)
{
    m_currentState->update(*this, dt);

    m_velocity += (m_acceleration * dt);
    m_position += (m_velocity * dt);

    setPosition(m_position);
    GameObjectBase::update(dt);

    auto [x, y] = m_graphicsComponent.getScale();
    if ((m_facingRight && x < 0) || (!m_facingRight && x > 0))
    {
		m_graphicsComponent.setScale({ -x, y });
    }
    if (!m_facingRight)
    {
        m_graphicsComponent.setPosition({ m_position.x + m_size.x - 25, m_position.y });
    }

    m_grounded = false;
    m_touchingLeft = false;
    m_touchingRight = false;
    m_touchingTop = false;

    initializeFeelers();

    if (m_currentHealth <= 0)
        m_dead = true;
}

void Player::handleInput(Input input)
{
    IPlayerState* newState = m_currentState->handleInput(*this, input);
    if (newState != nullptr)
    {
        m_currentState->onExit(*this);

	    delete m_currentState;
		m_currentState = newState;

		m_currentState->onEntry(*this);
    }
     
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_graphicsComponent, states);
    target.draw(m_colliderComponent, states);

    target.draw(m_anchor);
    target.draw(m_feelers);
}

void Player::setPosition(sf::Vector2f position)
{
    m_anchor.setPosition(position);
    GameObjectBase::setPosition(position);

    auto [x, y] = m_graphicsComponent.getScale();
    if ((m_facingRight && x < 0) || (!m_facingRight && x > 0))
    {
        m_graphicsComponent.setScale({ -x, y });
    }
    if (!m_facingRight)
    {
        m_graphicsComponent.setPosition({ m_position.x + m_size.x - 25, m_position.y });
    }
}

bool Player::isGrounded()
{
    //return m_grounded;
    if (!m_platform)
        return false;

    initializeFeelers();

    sf::RectangleShape platformCollider = m_platform->m_colliderComponent.m_colliders[0];

    if (platformCollider.getGlobalBounds().contains(bottomLeftFeeler) || platformCollider.getGlobalBounds().contains(bottomRightFeeler))
    {
        m_grounded = true;
        return true;
    }
    else
    {
        m_grounded = false;
        m_platform = nullptr;

        // BUG FIX
		// changing platforms looks like a visual bug because it's a transition MOVING -> FALLING -> STANDING
        std::vector<GameObjectWall*> walls = m_parentGameEngine->getWalls();
		for (int i = 0; i < walls.size(); i++)
		{
			if (walls[i]->m_colliderComponent.m_colliders[0].getGlobalBounds().contains(bottomLeftFeeler) ||
				walls[i]->m_colliderComponent.m_colliders[0].getGlobalBounds().contains(bottomRightFeeler))
			{
				m_platform = walls[i];
				return true;
			}
		}
        // END BUG FIX

        return false;
    }

}

void Player::initializeState()
{
    m_currentState = new PlayerStandingState();
    m_currentState->onEntry(*this);
    m_graphicsComponent.m_currentAnimation = "standing";
}

void Player::collideWall(GameObjectBase* collidedObject)
{
    GameObjectBase::collide(collidedObject);
    m_collided = true;
    m_grounded = false;
    m_touchingLeft = false;
    m_touchingRight = false;
    m_touchingTop = false;

    initializeFeelers();

    // experimentally moved to GameObjectWall collide function
    // start
    sf::RectangleShape r1 = collidedObject->m_colliderComponent.m_colliders[0];
    sf::RectangleShape r2 = m_colliderComponent.m_colliders[0];
    sf::Vector2f position = r2.getPosition();

    float thresholdX = r1.getSize().x/10;
    float thresholdY = r1.getSize().y/10;

    if (std::fabs(r1.getPosition().x - r2.getPosition().x - r2.getSize().x) < thresholdX)
    {
        //std::cout << "LEFT -> RIGHT\n";
        position.x = r1.getPosition().x - r2.getSize().x - 1;
    }
    else if (std::fabs(r1.getPosition().x + r1.getSize().x - r2.getPosition().x) < thresholdX)
    {
        //std::cout << "RIGHT -> LEFT\n";
        position.x = r1.getPosition().x + r1.getSize().x + 1;
    }
    else if (std::fabs(r1.getPosition().y - r2.getPosition().y - r2.getSize().y) < thresholdY)
    {
        //std::cout << "TOP\n\\/\nBOTTOM\n";
        position.y = r1.getPosition().y - r2.getSize().y - 1;
        m_grounded = true;
        m_platform = collidedObject;
    }
    else if (std::fabs(r1.getPosition().y + r1.getSize().y - r2.getPosition().y) < thresholdY)
    {
        /*std::cout << "BOTTOM\n^\nTOP\n";*/
        position.y = r1.getPosition().y + r1.getSize().y + 1;
        m_touchingTop = true;
    }

    setPosition(position);
    // end
}

void Player::collideEnemy(GameObjectBase* collidedObject)
{
    //GameObjectBase::collide(collidedObject);
    bool found = false;
    for (int i = 0; i < m_collidedWith.size(); i++)
        if (m_collidedWith[i] == collidedObject)
            found = true;
    if (!found)
    {
        m_collidedWith.push_back(collidedObject);
        m_colliderComponent.onEntry(collidedObject);
        onEntry(collidedObject);
    }
}

void Player::collideCollectible(GameObjectBase* collidedObject)
{
    collidedObject->kill();
    m_coinsCollected++;

    SoundId coinSound;
    coinSound.m_name = "coin_collected";
    AudioManager::playSound(coinSound);
}

void Player::onEntry(GameObjectBase* collidedObject)
{
    m_currentHealth -= 1;
}