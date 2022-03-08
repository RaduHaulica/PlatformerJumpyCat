#pragma once

#include "Input.h"

class Player;
class Input;
class GameEngine;

class IPlayerState
{
public:
    virtual IPlayerState* handleInput(Player& player, Input input) { return nullptr; };
    virtual void update(Player& player, float dt) {};
    virtual void onEntry(Player& player) {};
    virtual void onExit(Player& player) {};
};

class DuckingState : public IPlayerState
{
public:
    DuckingState();
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);

private:
    float m_chargeTime;
};


class StandingState : public IPlayerState
{
public:
    StandingState() {};
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);
};

class MovingState : public IPlayerState
{
public:
    float m_movementSpeed;

    MovingState();
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);
};

class JumpingState : public IPlayerState
{
public:
    float m_movementSpeed;
    bool m_peaked;
    float m_hangTime;
    float m_maxHangTime;

    JumpingState();
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);
};

class FallingState : public IPlayerState
{
public:
    float m_movementSpeed;
    float m_coyoteTime;
    bool m_coyoteEnabled;

    FallingState(bool coyoteEnabled = false);
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);
};