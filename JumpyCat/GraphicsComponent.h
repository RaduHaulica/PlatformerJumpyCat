#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"

class GameObject;

class GraphicsComponent : public sf::Drawable
{
public:
    GameObject* m_parent;

    std::map<std::string, Animation> m_animations;
    std::map<std::string, sf::Vector2f> m_offsets;
    std::string m_currentAnimation;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_animations.at(m_currentAnimation));
    }

    void changeAnimation(std::string newAnimation)
    {
        m_currentAnimation = newAnimation;
    }

    sf::Vector2f getScale()
    {
        return m_animations[m_currentAnimation].m_animationFrames[m_animations[m_currentAnimation].m_currentFrame].getScale();
    }

    void setScale(sf::Vector2f newScale)
    {
        int currentFrame = m_animations[m_currentAnimation].m_currentFrame;
        m_animations[m_currentAnimation].m_animationFrames[currentFrame].setScale(newScale);
    }

    void addAnimation(std::string name, Animation animation, sf::Vector2f offset)
    {
        m_animations.insert_or_assign(name, animation);
        m_offsets.insert_or_assign(name, offset);
    }

    void update(float dt, sf::Vector2f position)
    {
        m_animations[m_currentAnimation].update(dt, position + m_offsets[m_currentAnimation]);
    }

    //void setPosition(sf::Vector2f newPosition)
    //{
    //    int currentFrame = m_animations[m_currentAnimation].m_currentFrame;
    //    m_animations[m_currentAnimation].m_animationFrames[currentFrame].setPosition(newPosition);
    //}

    void setPosition(sf::Vector2f newPosition)
    {
        m_animations[m_currentAnimation].setPosition(newPosition + m_offsets[m_currentAnimation]);
    }

    void reset()
    {
        m_animations[m_currentAnimation].reset();
    }
};