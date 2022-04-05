#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "Input.h"
#include "GameActorBase.h"
#include "PlayerState.h"

class GameEngine;

class IPlayerState;

class Player : public GameActorBase
{
public:
    std::string m_currentStateName;
    IPlayerState* m_currentState;

    int m_currentHealth;
    int m_maximumHealth;
    int m_coinsCollected;

    bool m_doubleJumpEnabled;
    bool m_doubleJumped;

    // methods

    Player(std::string name, sf::Vector2f size);

    virtual void handleInput(Input input);

    virtual void update(float dt);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void collideWall(GameObjectBase* collidedObject);
    void collideEnemy(GameObjectBase* collidedObject);
    void collideCollectible(GameObjectBase* collidedObject);

    void initializeState();
    bool isGrounded();
    void setPosition(sf::Vector2f position);

    void onEntry(GameObjectBase* collidedObject);
};