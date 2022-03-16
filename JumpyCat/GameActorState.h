#pragma once

#include "Input.h"

class GameActorBase;
class Input;
class GameEngine;

class IGameActorState
{
public:
    virtual IGameActorState* handleInput(GameActorBase& player, Input input) { return nullptr; };
    virtual void update(GameActorBase& player, float dt) {};
    virtual void onEntry(GameActorBase& player) {};
    virtual void onExit(GameActorBase& player) {};
};

class DuckingState : public IGameActorState
{
public:
    DuckingState();
    virtual IGameActorState* handleInput(GameActorBase& player, Input input);
    virtual void update(GameActorBase& player, float dt);
    virtual void onEntry(GameActorBase& player);
    virtual void onExit(GameActorBase& player);

private:
    float m_chargeTime;
};


class StandingState : public IGameActorState
{
public:
    StandingState() {};
    virtual IGameActorState* handleInput(GameActorBase& player, Input input);
    virtual void update(GameActorBase& player, float dt);
    virtual void onEntry(GameActorBase& player);
    virtual void onExit(GameActorBase& player);
};

class MovingState : public IGameActorState
{
public:
    float m_movementSpeed;

    MovingState();
    virtual IGameActorState* handleInput(GameActorBase& player, Input input);
    virtual void update(GameActorBase& player, float dt);
    virtual void onEntry(GameActorBase& player);
    virtual void onExit(GameActorBase& player);
};

class JumpingState : public IGameActorState
{
public:
    float m_movementSpeed;
    bool m_peaked;
    float m_hangTime;
    float m_maxHangTime;

    JumpingState();
    virtual IGameActorState* handleInput(GameActorBase& player, Input input);
    virtual void update(GameActorBase& player, float dt);
    virtual void onEntry(GameActorBase& player);
    virtual void onExit(GameActorBase& player);
};

class FallingState : public IGameActorState
{
public:
    float m_movementSpeed;
    float m_coyoteTime;
    bool m_coyoteEnabled;

    FallingState(bool coyoteEnabled = false);
    virtual IGameActorState* handleInput(GameActorBase& player, Input input);
    virtual void update(GameActorBase& player, float dt);
    virtual void onEntry(GameActorBase& player);
    virtual void onExit(GameActorBase& player);
};