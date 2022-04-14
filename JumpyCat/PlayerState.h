#pragma once

#include "Input.h"
#include "GameActorState.h"
#include "AudioManager.h"

class Player;
class Input;
class GameEngine;

class IPlayerState: public IGameActorState
{
public:
    virtual IPlayerState* handleInput(Player& player, Input input) { return nullptr; };
    virtual void update(Player& player, float dt) {};
    virtual void onEntry(Player& player) {};
    virtual void onExit(Player& player) {};
};

class PlayerDuckingState : public IPlayerState
{
public:
    PlayerDuckingState();
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);

private:
    float m_chargeTime;
};


class PlayerStandingState : public IPlayerState
{
public:
    PlayerStandingState() {};
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);
};

class PlayerMovingState : public IPlayerState
{
public:
    float m_movementSpeed;

    PlayerMovingState();
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);
};

class PlayerJumpingState : public IPlayerState
{
public:
    float m_movementSpeed;
    bool m_peaked;
    float m_hangTime;
    float m_maxHangTime;
    float m_timeFromStart;
    float m_minJumpDelay;

    PlayerJumpingState();
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);
};

class PlayerFallingState : public IPlayerState
{
public:
    float m_movementSpeed;
    float m_coyoteTime;
    bool m_coyoteEnabled;
    float m_fallDistance;

    PlayerFallingState(bool coyoteEnabled = false);
    virtual IPlayerState* handleInput(Player& player, Input input);
    virtual void update(Player& player, float dt);
    virtual void onEntry(Player& player);
    virtual void onExit(Player& player);
};