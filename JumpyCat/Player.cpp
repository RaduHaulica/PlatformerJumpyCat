#include "Player.h"

#include "Input.h"
#include "PlayerState.h"

const float Player::MAX_CHARGE_TIME = 2.0f;

Player::Player(std::string name, sf::Vector2f size) :
    m_name{ name },
    m_size{ size },
    m_currentState{ new StandingState() },
    m_currentStateName { "standing" },
    m_facingRight{ true },
    m_grounded{false},
    m_touchingLeft{false},
    m_touchingRight{false},
    m_touchingTop{false},
    m_acceleration{ sf::Vector2f({ 0.0f, 0.0f }) },
    m_velocity{ sf::Vector2f({ 0.0f, 0.0f }) },
    m_position{ sf::Vector2f({ 400.0f, -300.0f }) },
    m_positionOffset{ sf::Vector2f({ 0.0f, 0.0f }) },
    m_jumpHeightFactor{ 3.0f },
    m_platform { nullptr }
{
    m_feelers.setPrimitiveType(sf::PrimitiveType::Points);
    m_graphicsComponent.m_currentAnimation = "standing";

    m_currentState->onEntry(*this);
}

void Player::update(float dt)
{
    m_currentState->update(*this, dt);

    m_velocity += (m_acceleration * dt);
    m_velocity.y += (400.0f * dt); // gravity
    if (isGrounded())
        m_velocity.y = 0.0f;
    m_position += (m_velocity * dt);

    m_colliderComponent.update(dt, m_position);
    m_graphicsComponent.update(dt, m_position);

    auto [x, y] = m_graphicsComponent.getScale();
    if ((m_facingRight && x < 0) || (!m_facingRight && x > 0))
    {
		m_graphicsComponent.setScale({ -x, y });
    }
    if (!m_facingRight)
    {
        m_graphicsComponent.setPosition({ m_position.x + m_size.x, m_position.y });
    }

    m_grounded = false;
    m_touchingLeft = false;
    m_touchingRight = false;
    m_touchingTop = false;

    sf::RectangleShape collider = m_colliderComponent.m_colliders[0];

    sf::Vector2f bottomLeftFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.1f, collider.getSize().y * 1.05f });
    sf::Vector2f bottomRightFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.9f, collider.getSize().y * 1.05f });

    sf::Vector2f leftTopFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * (-0.05f), collider.getSize().y * 0.1f });
    sf::Vector2f leftBottomFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * (-0.05f), collider.getSize().y * 0.9f });

    sf::Vector2f rightTopFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 1.05f, collider.getSize().y * 0.1f });
    sf::Vector2f rightBottomFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 1.05f, collider.getSize().y * 0.9f });

    sf::Vector2f topLeftFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.1f, collider.getSize().y * (-0.05f) });
    sf::Vector2f topRightFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.9f, collider.getSize().y * (-0.05f) });


    sf::Color color = sf::Color::Red;
    m_feelers.clear();
    m_feelers.append({ bottomLeftFeeler, color });
    m_feelers.append({ bottomRightFeeler, color });
    m_feelers.append({ leftTopFeeler, color });
    m_feelers.append({ leftBottomFeeler, color });
    m_feelers.append({ rightTopFeeler, color });
    m_feelers.append({ rightBottomFeeler, color });
    m_feelers.append({ topLeftFeeler, color });
    m_feelers.append({ topRightFeeler, color });
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

void Player::initializeFeelers()
{
    sf::RectangleShape collider = m_colliderComponent.m_colliders[0];

    sf::Vector2f bottomLeftFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.05f, collider.getSize().y * 1.05f });
    sf::Vector2f bottomRightFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.95f, collider.getSize().y * 1.05f });

    sf::Vector2f leftTopFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * (-0.05f), collider.getSize().y * 0.05f });
    sf::Vector2f leftBottomFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * (-0.05f), collider.getSize().y * 0.95f });

    sf::Vector2f rightTopFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 1.05f, collider.getSize().y * 0.05f });
    sf::Vector2f rightBottomFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 1.05f, collider.getSize().y * 0.95f });

    sf::Vector2f topLeftFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.1f, collider.getSize().y * (-0.05f) });
    sf::Vector2f topRightFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.9f, collider.getSize().y * (-0.05f) });

    sf::Color color = sf::Color::Red;
    m_feelers.clear();
    m_feelers.append({ bottomLeftFeeler, color });
    m_feelers.append({ bottomRightFeeler, color });
    m_feelers.append({ leftTopFeeler, color });
    m_feelers.append({ leftBottomFeeler, color });
    m_feelers.append({ rightTopFeeler, color });
    m_feelers.append({ rightBottomFeeler, color });
    m_feelers.append({ topLeftFeeler, color });
    m_feelers.append({ topRightFeeler, color });
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_graphicsComponent, states);
    target.draw(m_colliderComponent, states);

    target.draw(m_feelers);
}

void Player::setPosition(sf::Vector2f position)
{
    m_position = position;
    GameObject::setPosition(position);
}

bool Player::isGrounded()
{
    if (!m_platform)
        return false;

    sf::RectangleShape collider = m_colliderComponent.m_colliders[0];

    sf::Vector2f bottomLeftFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.05f, collider.getSize().y * 1.05f });
    sf::Vector2f bottomRightFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.95f, collider.getSize().y * 1.05f });

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
        return false;
    }
}

void Player::collide(GameObject* collidedObject)
{
    m_collided = true;
    m_grounded = false;
    m_touchingLeft = false;
    m_touchingRight = false;
    m_touchingTop = false;

    sf::RectangleShape collider = m_colliderComponent.m_colliders[0];

    sf::Vector2f bottomLeftFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.1f, collider.getSize().y * 1.05f });
    sf::Vector2f bottomRightFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.9f, collider.getSize().y * 1.05f });

    sf::Vector2f leftTopFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * (-0.05f), collider.getSize().y * 0.1f });
    sf::Vector2f leftBottomFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * (-0.05f), collider.getSize().y * 0.9f });

    sf::Vector2f rightTopFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 1.05f, collider.getSize().y * 0.1f });
    sf::Vector2f rightBottomFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 1.05f, collider.getSize().y * 0.9f });

    sf::Vector2f topLeftFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.1f, collider.getSize().y * (-0.05f) });
    sf::Vector2f topRightFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.9f, collider.getSize().y * (-0.05f) });


    for (int i = 0; i < collidedObject->m_colliderComponent.m_colliders.size(); i++)
    {
        if (collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(bottomLeftFeeler)
            || collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(bottomRightFeeler))
        {
            m_grounded = true;
            m_position.y = collidedObject->m_colliderComponent.m_colliders[0].getPosition().y - collider.getSize().y - m_colliderComponent.m_offsets[i].y;
            m_platform = collidedObject;
            m_velocity.y = 0.0f;
        }

        if (collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(leftTopFeeler)
            || collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(leftBottomFeeler))
        {
            m_touchingLeft = true;
            m_position.x = collidedObject->m_colliderComponent.m_colliders[0].getPosition().x + collidedObject->m_colliderComponent.m_colliders[0].getSize().x - m_colliderComponent.m_offsets[0].x;
            m_velocity.x = 0.0f;
        }

        if (collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(rightTopFeeler)
            || collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(rightBottomFeeler))
        {
            m_touchingRight = true;
            m_position.x = collidedObject->m_colliderComponent.m_colliders[0].getPosition().x - collider.getSize().x - m_colliderComponent.m_offsets[0].x;
            m_velocity.x = 0.0f;
        }

        if (collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(topLeftFeeler)
            || collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(topRightFeeler))
        {
            m_touchingTop = true;
            m_position.y = collidedObject->m_colliderComponent.m_colliders[i].getPosition().y + collidedObject->m_colliderComponent.m_colliders[i].getSize().y - m_colliderComponent.m_offsets[i].y;
            m_velocity.y = 0.0f;
        }


    }
}