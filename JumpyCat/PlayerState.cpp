#include "PlayerState.h"

#include "Config.h"
#include "Input.h"
#include "Player.h"
#include "Utility.h"

// ===== ===== ===== ===== DUCKING STATE ===== ===== ===== =====

PlayerDuckingState::PlayerDuckingState()
{}

void PlayerDuckingState::update(Player& player, float dt)
{}

IPlayerState* PlayerDuckingState::handleInput(Player& player, Input input)
{
    if (!player.isGrounded())
    {
        return new PlayerFallingState();
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
        return new PlayerStandingState();
    }
    return nullptr; // stay in current state
}
void PlayerDuckingState::onEntry(Player& player)
{
    sf::Vector2f colliderSize = player.m_colliderComponent.m_colliders[0].getSize();
    colliderSize.y = colliderSize.y / 2;
    player.m_colliderComponent.m_colliders[0].setSize(colliderSize);
    player.m_colliderComponent.m_offsets[0] += sf::Vector2f({ 0, colliderSize.y });

    player.m_acceleration = sf::Vector2f({ 0.0f, 0.0f });
    player.m_velocity = sf::Vector2f({ 0.0f, 0.0f });
    if (Config::showStateTransitions)
        player.setMessage("Entered DuckingState");
    player.m_graphicsComponent.m_currentAnimation = "ducking";
    player.m_graphicsComponent.reset();
    player.setPosition(player.m_position);
    player.m_currentStateName = "ducking";
}
void PlayerDuckingState::onExit(Player& player)
{
    sf::Vector2f colliderSize = player.m_colliderComponent.m_colliders[0].getSize();
    player.m_colliderComponent.m_offsets[0] -= sf::Vector2f({ 0, colliderSize.y });
    colliderSize.y = colliderSize.y * 2;
    player.m_colliderComponent.m_colliders[0].setSize(colliderSize);
    if (Config::showStateTransitions)
        player.setMessage("Exited DuckingState\n");
    player.m_graphicsComponent.reset();
}

// ===== ===== ===== ===== STANDING STATE ===== ===== ===== =====

void PlayerStandingState::update(Player& player, float dt)
{

}

IPlayerState* PlayerStandingState::handleInput(Player& player, Input input)
{
    if (!player.isGrounded())
    {
        return new PlayerFallingState();
    }
    if (input.control == CONTROLS::PRESSED_UP)
    {
        return new PlayerJumpingState();
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        player.faceLeft();
        return new PlayerMovingState();
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        player.faceRight();
        return new PlayerMovingState();
    }
    if (input.control == CONTROLS::PRESSED_DOWN)
    {
        return new PlayerDuckingState();
    }

    return nullptr; // stay in current state
}
void PlayerStandingState::onEntry(Player& player)
{
    if (Config::showStateTransitions)
        player.setMessage("Entered StandingState");
    player.m_acceleration = { 0.0f, 0.0f };
    player.m_velocity = { 0.0f, 0.0f };
    player.m_graphicsComponent.m_currentAnimation = "standing";
    player.m_graphicsComponent.reset();
    player.setPosition(player.m_position);
    player.m_currentStateName = "standing";
    player.m_doubleJumped = false;
}
void PlayerStandingState::onExit(Player& player)
{
    if (Config::showStateTransitions)
        player.setMessage("Exited StandingState\n");
    player.m_graphicsComponent.reset();
}

// ===== ===== ===== ===== MOVING STATE ===== ===== ===== =====

PlayerMovingState::PlayerMovingState():
    m_movementSpeed{ 400.0f }
{}

void PlayerMovingState::update(Player& player, float dt)
{
}

IPlayerState* PlayerMovingState::handleInput(Player& player, Input input)
{
    if (!player.isGrounded())
    {
        return new PlayerFallingState(true);
    }
    if (input.control == CONTROLS::PRESSED_UP)
    {
        return new PlayerJumpingState();
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
        return new PlayerStandingState();
    }
    if (input.control == CONTROLS::RELEASED_RIGHT)
    {
        return new PlayerStandingState();
    }
    if (input.control == CONTROLS::PRESSED_DOWN)
    {
        return new PlayerDuckingState();
    }

    return nullptr; // stay in current state
}

void PlayerMovingState::onEntry(Player& player)
{
    player.m_graphicsComponent.m_currentAnimation = "moving";
    player.m_graphicsComponent.reset();
    player.setPosition(player.m_position);
    player.m_currentStateName = "moving";
    if (Config::showStateTransitions)
        player.setMessage("Entered MovingState");
}
void PlayerMovingState::onExit(Player& player)
{
    if (Config::showStateTransitions)
        player.setMessage("Exited MovingState\n");
    player.m_graphicsComponent.reset();
}

// ===== ===== ===== ===== JUMPING STATE ===== ===== ===== =====

PlayerJumpingState::PlayerJumpingState():
    m_movementSpeed{ 200.0f },
    m_hangTime{ 0.0f },
    m_maxHangTime{ 0.1f },
    m_peaked{false},
	m_minJumpDelay{0.5f},
    m_timeFromStart{ 0.0f }
{}

void PlayerJumpingState::update(Player& player, float dt)
{
    if (m_peaked)
    {
        m_hangTime += dt;
        player.m_velocity.y = 0.0f;
    }
    if (m_timeFromStart <= m_minJumpDelay)
    {
        m_timeFromStart += dt;
    }
}

IPlayerState* PlayerJumpingState::handleInput(Player& player, Input input)
{
    if (player.m_doubleJumpEnabled && input.control == CONTROLS::PRESSED_UP && !player.m_doubleJumped && (m_timeFromStart>m_minJumpDelay))
    {
		player.m_doubleJumped = true;
        return new PlayerJumpingState();
    }
    if (player.isGrounded())
    {
        return new PlayerStandingState();
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
        return new PlayerFallingState();
    }

    return nullptr; // stay in current state
}

void PlayerJumpingState::onEntry(Player& player)
{
    if (Config::showStateTransitions)
        player.setMessage("Entered JumpingState");
    player.m_grounded = false;
    player.m_jumping = true;
    player.m_platform = nullptr;
    player.m_velocity.y = player.m_jumpHeightFactor * -200.0f;
    player.m_acceleration.y = 800.0f;
    player.m_graphicsComponent.m_currentAnimation = "jumping";
    player.m_graphicsComponent.reset();
    player.setPosition(player.m_position);
    player.m_currentStateName = "jumping";

    SoundId jumpSound;
    jumpSound.m_name = "cat_jumping";
    AudioManager::playSound(jumpSound);
}
void PlayerJumpingState::onExit(Player& player)
{
    if (Config::showStateTransitions)
        player.setMessage("Exited JumpingState\n");
    player.m_jumping = false;
    player.m_graphicsComponent.reset();
}

// ===== ===== ===== ===== FALLING STATE ===== ===== ===== =====

PlayerFallingState::PlayerFallingState(bool coyoteEnabled):
    m_movementSpeed{ 200.0f },
    m_coyoteTime{ 0.0f },
    m_coyoteEnabled{ coyoteEnabled }
{}

void PlayerFallingState::update(Player& player, float dt)
{
	if (m_coyoteTime < 0.1f)
        m_coyoteTime += dt;
}

IPlayerState* PlayerFallingState::handleInput(Player& player, Input input)
{
    if (m_coyoteEnabled && input.control == CONTROLS::PRESSED_UP && m_coyoteTime < 0.1f)
    {
        return new PlayerJumpingState();
    }
    if (player.m_doubleJumpEnabled && input.control == CONTROLS::PRESSED_UP && !player.m_doubleJumped)
    {
        player.m_doubleJumped = true;
        return new PlayerJumpingState();
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
        return new PlayerStandingState();
    }

    return nullptr; // stay in current state
}

void PlayerFallingState::onEntry(Player& player)
{
    if (Config::showStateTransitions)
        player.setMessage("Entered FallingState");
    player.m_velocity.x = 0.0f;
    player.m_velocity.y = 2 * m_movementSpeed;
    player.m_acceleration.y = 400.0f;
    player.m_graphicsComponent.m_currentAnimation = "falling";
    player.m_graphicsComponent.reset();
    player.setPosition(player.m_position);
    player.m_currentStateName = "falling";
    player.m_grounded = false;
    player.m_platform = nullptr;
}
void PlayerFallingState::onExit(Player& player)
{
    if (Config::showStateTransitions)
        player.setMessage("Exited FallingState\n");
    player.m_graphicsComponent.reset();
}