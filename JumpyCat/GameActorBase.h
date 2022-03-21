#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "GameObjectBase.h"

class IGameActorState;

class GameActorBase : public GameObjectBase
{
public:
    std::string m_name;
    sf::Vector2f m_size;
    sf::Vector2f m_positionOffset;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    float m_jumpHeightFactor;

    bool m_facingRight;
    bool m_collided;
    bool m_grounded;
    bool m_jumping;
    bool m_touchingLeft;
    bool m_touchingRight;
    bool m_touchingTop;

    std::string m_currentStateName;
    IGameActorState* m_currentState;

    sf::CircleShape m_anchor;
    sf::VertexArray m_feelers;
    GameObjectBase* m_platform;

    // antennae
    sf::Vector2f bottomLeftFeeler;
    sf::Vector2f bottomRightFeeler;

    sf::Vector2f leftTopFeeler;
    sf::Vector2f leftBottomFeeler;

    sf::Vector2f rightTopFeeler;
    sf::Vector2f rightBottomFeeler;

    sf::Vector2f topLeftFeeler;
    sf::Vector2f topRightFeeler;

    // methods

    GameActorBase(std::string name, sf::Vector2f size);

    virtual void handleInput(Input input);

    virtual void update(float dt);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void collideWall(GameObjectBase* collidedObject);

    void explode()
    {
        // PEW PEW!
    }

    void setMessage(std::string newMessage)
    {
        std::cout << m_name << ": " << newMessage << "\n";
    }

    void faceRight()
    {
        m_facingRight = true;
    }
    void faceLeft()
    {
        m_facingRight = false;
    }

    void initializeFeelers();
    void initializeState();
    bool isGrounded();
    void setPosition(sf::Vector2f position);
};