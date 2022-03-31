#pragma once

#include "Input.h"

class GameActorBase;
class Input;
class GameEngine;

class IGameActorState
{
public:
    virtual IGameActorState* handleInput(GameActorBase& actor, Input input) { return nullptr; };
    virtual void update(GameActorBase& actor, float dt) {};
    virtual void onEntry(GameActorBase& actor) {};
    virtual void onExit(GameActorBase& actor) {};
};

class DuckingState : public IGameActorState
{
public:
    DuckingState();
    virtual IGameActorState* handleInput(GameActorBase& actor, Input input);
    virtual void update(GameActorBase& actor, float dt);
    virtual void onEntry(GameActorBase& actor);
    virtual void onExit(GameActorBase& actor);

private:
    float m_chargeTime;
};


class StandingState : public IGameActorState
{
public:
    StandingState() {};
    virtual IGameActorState* handleInput(GameActorBase& actor, Input input);
    virtual void update(GameActorBase& actor, float dt);
    virtual void onEntry(GameActorBase& actor);
    virtual void onExit(GameActorBase& actor);
};

class MovingState : public IGameActorState
{
public:
    float m_movementSpeed;

    MovingState();
    virtual IGameActorState* handleInput(GameActorBase& actor, Input input);
    virtual void update(GameActorBase& actor, float dt);
    virtual void onEntry(GameActorBase& actor);
    virtual void onExit(GameActorBase& actor);
};

class JumpingState : public IGameActorState
{
public:
    float m_movementSpeed;
    bool m_peaked;
    float m_hangTime;
    float m_maxHangTime;

    JumpingState();
    virtual IGameActorState* handleInput(GameActorBase& actor, Input input);
    virtual void update(GameActorBase& actor, float dt);
    virtual void onEntry(GameActorBase& actor);
    virtual void onExit(GameActorBase& actor);
};

class FallingState : public IGameActorState
{
public:
    float m_movementSpeed;
    float m_coyoteTime;
    bool m_coyoteEnabled;

    FallingState(bool coyoteEnabled = false);
    virtual IGameActorState* handleInput(GameActorBase& actor, Input input);
    virtual void update(GameActorBase& actor, float dt);
    virtual void onEntry(GameActorBase& actor);
    virtual void onExit(GameActorBase& actor);
};