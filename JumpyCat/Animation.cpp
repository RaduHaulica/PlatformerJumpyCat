#include "Animation.h"

Animation::Animation() {};

Animation::Animation(sf::Texture* texture, int frames, sf::Vector2f frameSizeTexture, sf::Vector2f frameSizeSprite, float duration, bool looping) :
    m_looping{ looping },
    m_timeElapsed{ 0.0f },
    m_animationDuration{ duration },
    m_animationFrameCount{ frames },
    m_currentFrame{ 0 }
{
    m_frameDuration = m_animationDuration / m_animationFrameCount;
    for (int i = 0; i < frames; i++)
    {
        sf::Sprite newSprite;
        newSprite.setTexture(*texture);
        newSprite.setTextureRect({i* (int)frameSizeTexture.x, 0, (int)frameSizeTexture.x, (int)frameSizeTexture.y});
        newSprite.setScale(frameSizeSprite.x / frameSizeTexture.x, frameSizeSprite.y / frameSizeTexture.y);
        m_animationFrames.push_back(newSprite);
    }
}

void Animation::update(float dt, sf::Vector2f position)
{
    if (m_animationDuration > 0.0f)
    {
        m_timeElapsed += dt;
        if (m_timeElapsed > m_animationDuration)
            m_timeElapsed = m_looping ? 0.0f : m_animationDuration;
        m_currentFrame = m_timeElapsed / (m_animationDuration / m_animationFrameCount);
        if (m_currentFrame == m_animationFrames.size())
            m_currentFrame--;
    }

    m_animationFrames[m_currentFrame].setPosition(position);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_animationFrames[m_currentFrame]);
    if (Config::showSpriteBoundingBoxes)
    {
		sf::RectangleShape frame;
		frame.setFillColor(sf::Color::Transparent);
		frame.setOutlineColor(sf::Color::Blue);
		frame.setOutlineThickness(1);
		frame.setPosition(m_animationFrames[m_currentFrame].getPosition());
		frame.setSize({ m_animationFrames[m_currentFrame].getGlobalBounds().width, m_animationFrames[m_currentFrame].getGlobalBounds().height });
		target.draw(frame);
    }
}

void Animation::reset()
{
    m_timeElapsed = 0.0f;
    m_currentFrame = 0;
}

void Animation::setPosition(sf::Vector2f newPosition)
{
    if (m_animationFrames.size() < 1)
        return;
    m_animationFrames[m_currentFrame].setPosition(newPosition);
}