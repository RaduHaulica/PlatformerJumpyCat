#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "GameObject.h"

class IPlayerState;

class Player : public GameObject
{
public:
    static const enum class STATES
    {
        STANDING,
        DUCKING,
    };

    static const float MAX_CHARGE_TIME;
    std::string m_name;
    sf::Vector2f m_size;
    sf::Vector2f m_position;
    sf::Vector2f m_positionOffset;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    float m_jumpHeightFactor;

    bool m_facingRight;
    bool m_collided;
    bool m_grounded;
    bool m_touchingLeft;
    bool m_touchingRight;
    bool m_touchingTop;

    std::string m_currentStateName;
    IPlayerState* m_currentState;

    sf::VertexArray m_feelers;
    GameObject* m_platform;


    Player(std::string name, sf::Vector2f size);

    virtual void handleInput(Input input);

    virtual void update(float dt);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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

    void collide(GameObject* collidedObject);
    void initializeFeelers();
    bool isGrounded();
    void setPosition(sf::Vector2f position);
};