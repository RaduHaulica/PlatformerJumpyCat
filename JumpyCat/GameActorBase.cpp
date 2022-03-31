#include "GameActorBase.h"

#include "Input.h"
#include "GameActorState.h"
#include "GameEngine.h"

GameActorBase::GameActorBase(std::string name, sf::Vector2f size) :
    m_name{ name },
    m_size{ size },
    m_currentStateName{ "" },
    m_facingRight{ true },
    m_grounded{ false },
    m_touchingLeft{ false },
    m_touchingRight{ false },
    m_touchingTop{ false },
    m_acceleration{ sf::Vector2f({ 0.0f, 0.0f }) },
    m_velocity{ sf::Vector2f({ 0.0f, 0.0f }) },
    m_positionOffset{ sf::Vector2f({ 0.0f, 0.0f }) },
    m_jumpHeightFactor{ 3.0f },
    m_platform{ nullptr }
{
    m_feelers.setPrimitiveType(sf::PrimitiveType::Points);
    //m_graphicsComponent.m_currentAnimation = "standing";

    m_anchor.setFillColor(sf::Color::Green);
    m_anchor.setOrigin({ 5,5 });
    m_anchor.setRadius(5);
}

void GameActorBase::update(float dt)
{
    Input mockInput;
    mockInput.control = CONTROLS::NOTHING;
    handleInput(mockInput);
    m_currentState->update(*this, dt);

    m_velocity += (m_acceleration * dt);
    m_position += (m_velocity * dt);

    setPosition(m_position);
    GameObjectBase::update(dt);
    //std::cout << "actor collisions: " << m_collidedWith.size() << "\n";

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
}

void GameActorBase::handleInput(Input input)
{
    IGameActorState* newState = m_currentState->handleInput(*this, input);
    if (newState != nullptr)
    {
        m_currentState->onExit(*this);

        delete m_currentState;
        m_currentState = newState;

        m_currentState->onEntry(*this);
    }

}

void GameActorBase::initializeFeelers()
{
    sf::RectangleShape collider = m_colliderComponent.m_colliders[0];

    bottomLeftFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.05f, collider.getSize().y * 1.05f });
    bottomRightFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.95f, collider.getSize().y * 1.05f });

    leftTopFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * (-0.05f), collider.getSize().y * 0.05f });
    leftBottomFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * (-0.05f), collider.getSize().y * 0.95f });

    rightTopFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 1.05f, collider.getSize().y * 0.05f });
    rightBottomFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 1.05f, collider.getSize().y * 0.95f });

    topLeftFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.1f, collider.getSize().y * (-0.05f) });
    topRightFeeler = collider.getPosition() + sf::Vector2f({ collider.getSize().x * 0.9f, collider.getSize().y * (-0.05f) });

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

void GameActorBase::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_graphicsComponent, states);
    target.draw(m_colliderComponent, states);

    target.draw(m_anchor);
    target.draw(m_feelers);
}

void GameActorBase::setPosition(sf::Vector2f position)
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

bool GameActorBase::isGrounded()
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

void GameActorBase::initializeState()
{
    m_currentState = new StandingState();
    m_currentState->onEntry(*this);
    m_graphicsComponent.m_currentAnimation = "standing";
}

void GameActorBase::collideWall(GameObjectBase* collidedObject)
{
    GameObjectBase::collide(collidedObject);
    m_collided = true;
    m_grounded = false;
    m_touchingLeft = false;
    m_touchingRight = false;
    m_touchingTop = false;

    initializeFeelers();

    // start
    sf::RectangleShape r1 = collidedObject->m_colliderComponent.m_colliders[0];
    sf::RectangleShape r2 = m_colliderComponent.m_colliders[0];
    sf::Vector2f position = r2.getPosition();

    float thresholdX = r1.getSize().x / 10;
    float thresholdY = r1.getSize().y / 10;

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

    //for (int i = 0; i < collidedObject->m_colliderComponent.m_colliders.size(); i++)
    //{
    //    if (collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(bottomLeftFeeler)
    //        || collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(bottomRightFeeler))
    //    {
    //        m_grounded = true;
    //        //m_position.y = collidedObject->m_colliderComponent.m_colliders[0].getPosition().y - collider.getSize().y;
    //        m_platform = collidedObject;
    //        m_velocity.y = 0.0f;
    //    }

    //    if (collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(leftTopFeeler)
    //        || collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(leftBottomFeeler))
    //    {
    //        m_touchingLeft = true;
    //        //m_position.x = collidedObject->m_colliderComponent.m_colliders[0].getPosition().x + collidedObject->m_colliderComponent.m_colliders[0].getSize().x;
    //        m_velocity.x = 0.0f;
    //    }

    //    if (collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(rightTopFeeler)
    //        || collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(rightBottomFeeler))
    //    {
    //        m_touchingRight = true;
    //        //m_position.x = collidedObject->m_colliderComponent.m_colliders[0].getPosition().x - collider.getSize().x;
    //        m_velocity.x = 0.0f;
    //    }

    //    if (collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(topLeftFeeler)
    //        || collidedObject->m_colliderComponent.m_colliders[i].getGlobalBounds().contains(topRightFeeler))
    //    {
    //        m_touchingTop = true;
    //        //m_position.y = collidedObject->m_colliderComponent.m_colliders[i].getPosition().y + collidedObject->m_colliderComponent.m_colliders[i].getSize().y;
    //        m_velocity.y = 0.0f;
    //    }

    //}
}