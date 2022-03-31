#include "GameActorState.h"

#include "Input.h"
#include "GameActorBase.h"

// ===== ===== ===== ===== DUCKING STATE ===== ===== ===== =====

DuckingState::DuckingState()
{}

void DuckingState::update(GameActorBase& actor, float dt)
{}

IGameActorState* DuckingState::handleInput(GameActorBase& actor, Input input)
{
    if (!actor.isGrounded())
    {
        return new FallingState();
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        actor.faceLeft();
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        actor.faceRight();
    }
    if (input.control == CONTROLS::RELEASED_DOWN)
    {
        return new StandingState();
    }
    return nullptr; // stay in current state
}
void DuckingState::onEntry(GameActorBase& actor)
{
    sf::Vector2f colliderSize = actor.m_colliderComponent.m_colliders[0].getSize();
    colliderSize.y = colliderSize.y / 2;
    actor.m_colliderComponent.m_colliders[0].setSize(colliderSize);
    actor.m_colliderComponent.m_offsets[0] += sf::Vector2f({ 0, colliderSize.y });

    actor.m_acceleration = sf::Vector2f({ 0.0f, 0.0f });
    actor.m_velocity = sf::Vector2f({ 0.0f, 0.0f });
    actor.setMessage("Entered DuckingState");
    actor.m_graphicsComponent.m_currentAnimation = "ducking";
    actor.m_graphicsComponent.reset();
    actor.setPosition(actor.m_position);
    actor.m_currentStateName = "ducking";
}
void DuckingState::onExit(GameActorBase& actor)
{
    sf::Vector2f colliderSize = actor.m_colliderComponent.m_colliders[0].getSize();
    actor.m_colliderComponent.m_offsets[0] -= sf::Vector2f({ 0, colliderSize.y });
    colliderSize.y = colliderSize.y * 2;
    actor.m_colliderComponent.m_colliders[0].setSize(colliderSize);
    actor.setMessage("Exited DuckingState\n");
    actor.m_graphicsComponent.reset();
}

// ===== ===== ===== ===== STANDING STATE ===== ===== ===== =====

void StandingState::update(GameActorBase& actor, float dt)
{

}

IGameActorState* StandingState::handleInput(GameActorBase& actor, Input input)
{
    if (!actor.isGrounded())
    {
        return new FallingState();
    }
    if (input.control == CONTROLS::PRESSED_UP)
    {
        return new JumpingState();
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        actor.faceLeft();
        return new MovingState();
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        actor.faceRight();
        return new MovingState();
    }
    if (input.control == CONTROLS::PRESSED_DOWN)
    {
        return new DuckingState();
    }

    return nullptr; // stay in current state
}
void StandingState::onEntry(GameActorBase& actor)
{
    actor.setMessage("Entered StandingState");
    actor.m_acceleration = { 0.0f, 0.0f };
    actor.m_velocity = { 0.0f, 0.0f };
    actor.m_graphicsComponent.m_currentAnimation = "standing";
    actor.m_graphicsComponent.reset();
    actor.setPosition(actor.m_position);
    actor.m_currentStateName = "standing";
}
void StandingState::onExit(GameActorBase& actor)
{
    actor.setMessage("Exited StandingState\n");
    actor.m_graphicsComponent.reset();
}

// ===== ===== ===== ===== MOVING STATE ===== ===== ===== =====

MovingState::MovingState() :
    m_movementSpeed{ 400.0f }
{}

void MovingState::update(GameActorBase& actor, float dt)
{
}

IGameActorState* MovingState::handleInput(GameActorBase& actor, Input input)
{
    if (!actor.isGrounded())
    {
        return new FallingState(true);
    }
    if (input.control == CONTROLS::PRESSED_UP)
    {
        return new JumpingState();
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        actor.faceLeft();
        if (!actor.m_touchingLeft)
            actor.m_velocity.x = -m_movementSpeed;
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        actor.faceRight();
        if (!actor.m_touchingRight)
            actor.m_velocity.x = m_movementSpeed;
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

void MovingState::onEntry(GameActorBase& actor)
{
    actor.m_graphicsComponent.m_currentAnimation = "moving";
    actor.m_graphicsComponent.reset();
    actor.setPosition(actor.m_position);
    actor.m_currentStateName = "moving";
    actor.setMessage("Entered MovingState");
}
void MovingState::onExit(GameActorBase& actor)
{
    actor.setMessage("Exited MovingState\n");
    actor.m_graphicsComponent.reset();
}

// ===== ===== ===== ===== JUMPING STATE ===== ===== ===== =====

JumpingState::JumpingState() :
    m_movementSpeed{ 200.0f },
    m_hangTime{ 0.0f },
    m_maxHangTime{ 0.1f },
    m_peaked{ false }
{}

void JumpingState::update(GameActorBase& actor, float dt)
{
    if (m_peaked)
    {
        m_hangTime += dt;
        actor.m_velocity.y = 0.0f;
    }
}

IGameActorState* JumpingState::handleInput(GameActorBase& actor, Input input)
{
    if (actor.isGrounded())
    {
        return new StandingState();
    }
    if (actor.m_touchingTop)
    {
        m_peaked = true;
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        actor.faceLeft();
        actor.m_velocity.x = -m_movementSpeed;
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        actor.faceRight();
        actor.m_velocity.x = m_movementSpeed;
    }
    if (actor.m_velocity.y >= 0.0f)
    {
        m_peaked = true;
    }
    if (m_hangTime > m_maxHangTime)
    {
        return new FallingState();
    }

    return nullptr; // stay in current state
}

void JumpingState::onEntry(GameActorBase& actor)
{
    actor.setMessage("Entered JumpingState");
    actor.m_grounded = false;
    actor.m_jumping = true;
    actor.m_platform = nullptr;
    actor.m_velocity.y = actor.m_jumpHeightFactor * -200.0f;
    actor.m_acceleration.y = 800.0f;
    actor.m_graphicsComponent.m_currentAnimation = "jumping";
    actor.m_graphicsComponent.reset();
    actor.setPosition(actor.m_position);
    actor.m_currentStateName = "jumping";
}
void JumpingState::onExit(GameActorBase& actor)
{
    actor.setMessage("Exited JumpingState\n");
    actor.m_jumping = false;
    actor.m_graphicsComponent.reset();
}

// ===== ===== ===== ===== FALLING STATE ===== ===== ===== =====

FallingState::FallingState(bool coyoteEnabled) :
    m_movementSpeed{ 200.0f },
    m_coyoteTime{ 0.0f },
    m_coyoteEnabled{ coyoteEnabled }
{}

void FallingState::update(GameActorBase& actor, float dt)
{
    m_coyoteTime += dt;
}

IGameActorState* FallingState::handleInput(GameActorBase& actor, Input input)
{
    if (m_coyoteEnabled && input.control == CONTROLS::PRESSED_UP && m_coyoteTime < 0.1f)
    {
        return new JumpingState();
    }
    if (input.control == CONTROLS::PRESSED_LEFT)
    {
        actor.faceLeft();
        if (!actor.m_touchingLeft)
            actor.m_velocity.x = -m_movementSpeed;
    }
    if (input.control == CONTROLS::RELEASED_LEFT)
    {
        actor.m_velocity.x = 0.0f;
    }
    if (input.control == CONTROLS::PRESSED_RIGHT)
    {
        actor.faceRight();
        if (!actor.m_touchingRight)
            actor.m_velocity.x = m_movementSpeed;
    }
    if (input.control == CONTROLS::RELEASED_RIGHT)
    {
        actor.m_velocity.x = 0.0f;
    }
    if (actor.isGrounded())
    {
        return new StandingState();
    }

    return nullptr; // stay in current state
}

void FallingState::onEntry(GameActorBase& actor)
{
    actor.setMessage("Entered FallingState");
    actor.m_velocity.x = 0.0f;
    actor.m_velocity.y = 2 * m_movementSpeed;
    actor.m_acceleration.y = 400.0f;
    actor.m_graphicsComponent.m_currentAnimation = "falling";
    actor.m_graphicsComponent.reset();
    actor.setPosition(actor.m_position);
    actor.m_currentStateName = "falling";
    actor.m_grounded = false;
    actor.m_platform = nullptr;
}
void FallingState::onExit(GameActorBase& actor)
{
    actor.setMessage("Exited FallingState\n");
    actor.m_graphicsComponent.reset();
}