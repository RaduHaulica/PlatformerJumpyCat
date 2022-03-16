#pragma once

#include <SFML/Graphics.hpp>

#include "Interfaces.h"

class Animation : public sf::Drawable
{
public:
    std::vector<sf::Sprite> m_animationFrames;
    float m_timeElapsed;
    float m_animationDuration;
    float m_frameDuration;
    int m_animationFrameCount;
    int m_currentFrame;
    bool m_looping;

    Animation();

    Animation(sf::Texture* texture, int frames, sf::Vector2f frameSizeTexture, sf::Vector2f frameSizeSprite, float duration, bool looping = true);

    void update(float dt, sf::Vector2f position);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void reset();
    void setPosition(sf::Vector2f newPosition);
};