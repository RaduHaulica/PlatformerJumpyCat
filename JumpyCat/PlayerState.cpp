#include "PlayerState.h"

#include "Input.h"
#include "Player.h"

// ===== ===== ===== ===== DUCKING STATE ===== ===== ===== =====

DuckingState::DuckingState() :
    m_chargeTime{ 0 }
{}

void DuckingState::update(Player& player, float dt)
{
    m_chargeTime += dt;
    if (m_chargeTime > Player::MAX_CHARGE_TIME)
    {
        player.explode();
    }
}

IPlayerState* DuckingState::handleInput(Player& player, Input input)
{
    if (!player.isGrounded())
    {
        return new FallingState();
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        player.faceLeft();
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        player.faceRight();
    }
    if (input.control == CONTROLS::RELEASED_DOWN)
    {
        return new StandingState();
    }
    return nullptr; // stay in current state
}
void DuckingState::onEntry(Player& player)
{
    sf::Vector2f colliderSize = player.m_colliderComponent.m_colliders[0].getSize();
    colliderSize.y = colliderSize.y / 2;
    player.m_colliderComponent.m_colliders[0].setSize(colliderSize);
    player.m_colliderComponent.m_offsets[0] += sf::Vector2f({ 0, colliderSize.y });

    player.m_acceleration = sf::Vector2f({ 0.0f, 0.0f });
    player.m_velocity = sf::Vector2f({ 0.0f, 0.0f });
    player.setMessage("Entered DuckingState");
    player.m_graphicsComponent.m_currentAnimation = "ducking";
    player.m_currentStateName = "ducking";
}
void DuckingState::onExit(Player& player)
{
    sf::Vector2f colliderSize = player.m_colliderComponent.m_colliders[0].getSize();
    player.m_colliderComponent.m_offsets[0] -= sf::Vector2f({ 0, colliderSize.y });
    colliderSize.y = colliderSize.y * 2;
    player.m_colliderComponent.m_colliders[0].setSize(colliderSize);
    player.setMessage("Exited DuckingState\n");
}

// ===== ===== ===== ===== STANDING STATE ===== ===== ===== =====

void StandingState::update(Player& player, float dt)
{

}

IPlayerState* StandingState::handleInput(Player& player, Input input)
{
    if (!player.isGrounded())
    {
        return new FallingState();
    }
    if (input.control == CONTROLS::PRESSED_UP)
    {
        return new JumpingState();
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        player.faceLeft();
        return new MovingState();
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        player.faceRight();
        return new MovingState();
    }
    if (input.control == CONTROLS::PRESSED_DOWN)
    {
        return new DuckingState();
    }

    return nullptr; // stay in current state
}
void StandingState::onEntry(Player& player)
{
    player.setMessage("Entered StandingState");
    player.m_acceleration = { 0.0f, 0.0f };
    player.m_velocity = { 0.0f, 0.0f };
    player.m_graphicsComponent.m_currentAnimation = "standing";
    player.m_currentStateName = "standing";
}
void StandingState::onExit(Player& player)
{
    player.setMessage("Exited StandingState\n");
}

// ===== ===== ===== ===== MOVING STATE ===== ===== ===== =====

MovingState::MovingState():
    m_movementSpeed{ 400.0f }
{}

void MovingState::update(Player& player, float dt)
{
}

IPlayerState* MovingState::handleInput(Player& player, Input input)
{
    if (!player.isGrounded())
    {
        return new FallingState(true);
    }
    if (input.control == CONTROLS::PRESSED_UP)
    {
        return new JumpingState();
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        player.faceLeft();
        if (!player.m_touchingLeft)
            player.m_velocity.x = -m_movementSpeed;
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        player.faceRight();
        if (!player.m_touchingRight)
            player.m_velocity.x = m_movementSpeed;
    }
    if (input.control == CONTROLS::RELEASED_LEFT)
    {
        return new StandingState();
    }
    if (input.control == CONTROLS::RELEASED_RIGHT)
    {
        return new StandingState();
    }
    if (input.control == CONTROLS::PRESSED_DOWN)
    {
        return new DuckingState();
    }

    return nullptr; // stay in current state
}

void MovingState::onEntry(Player& player)
{
    player.m_graphicsComponent.m_currentAnimation = "moving";
    player.m_currentStateName = "moving";
    player.setMessage("Entered MovingState");
}
void MovingState::onExit(Player& player)
{
    player.setMessage("Exited MovingState\n");
}

// ===== ===== ===== ===== JUMPING STATE ===== ===== ===== =====

JumpingState::JumpingState():
    m_movementSpeed{ 200.0f },
    m_hangTime{ 0.0f },
    m_maxHangTime{ 0.2f },
    m_peaked{false}
{}

void JumpingState::update(Player& player, float dt)
{
    if (m_peaked)
    {
        m_hangTime += dt;
        player.m_velocity.y = 0.0f;
    }
}

IPlayerState* JumpingState::handleInput(Player& player, Input input)
{
    if (player.isGrounded())
    {
        return new StandingState();
    }
    if (player.m_touchingTop)
    {
        m_peaked = true;
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        player.faceLeft();
        player.m_velocity.x = -m_movementSpeed;
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        player.faceRight();
        player.m_velocity.x = m_movementSpeed;
    }
    if (player.m_velocity.y >= 0.0f)
    {
        m_peaked = true;
    }
    if (m_hangTime > m_maxHangTime)
    {
        return new FallingState();
    }

    return nullptr; // stay in current state
}

void JumpingState::onEntry(Player& player)
{
    player.setMessage("Entered JumpingState");
    player.m_grounded = false;
    player.m_platform = nullptr;
    player.m_velocity.y = player.m_jumpHeightFactor * -250.0f;
    player.m_acceleration.y = 800.0f;
    player.m_graphicsComponent.m_currentAnimation = "jumping";
    player.m_currentStateName = "jumping";
}
void JumpingState::onExit(Player& player)
{
    player.setMessage("Exited JumpingState\n");
}

// ===== ===== ===== ===== FALLING STATE ===== ===== ===== =====

FallingState::FallingState(bool coyoteEnabled):
    m_movementSpeed{ 200.0f },
    m_coyoteTime{ 0.0f },
    m_coyoteEnabled{ coyoteEnabled }
{}

void FallingState::update(Player& player, float dt)
{
    m_coyoteTime += dt;
}

IPlayerState* FallingState::handleInput(Player& player, Input input)
{
    if (m_coyoteEnabled && input.control == CONTROLS::PRESSED_UP && m_coyoteTime < 0.1f)
    {
        return new JumpingState();
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        player.faceLeft();
        if (!player.m_touchingLeft)
            player.m_velocity.x = -m_movementSpeed;
    }
    if (input.control == CONTROLS::RELEASED_LEFT)
    {
        player.m_velocity.x = 0.0f;
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        player.faceRight();
        if (!player.m_touchingRight)
            player.m_velocity.x = m_movementSpeed;
    }
    if (input.control == CONTROLS::RELEASED_RIGHT)
    {
        player.m_velocity.x = 0.0f;
    }
    if (player.isGrounded())
    {
        return new StandingState();
    }

    return nullptr; // stay in current state
}

void FallingState::onEntry(Player& player)
{
    player.setMessage("Entered FallingState");
    player.m_velocity.x = 0.0f;
    player.m_velocity.y = 2 * m_movementSpeed;
    player.m_acceleration.y = 400.0f;
    player.m_graphicsComponent.m_currentAnimation = "falling";
    player.m_currentStateName = "falling";
    player.m_grounded = false;
    player.m_platform = nullptr;
}
void FallingState::onExit(Player& player)
{
    player.setMessage("Exited FallingState\n");
}