#include "Utility.h"

float degToRad(float degrees)
{
    return degrees * 180 / pi;
}

float radToDeg(float radians)
{
    return radians * pi / 180;
}

float norm(sf::Vector2f v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f normalize(sf::Vector2f v)
{
    return v / norm(v);
}

float distanceBetweenPoints(sf::Vector2f v1, sf::Vector2f v2)
{
    return std::sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
}

float dot(sf::Vector2f v1, sf::Vector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

// angle in radians
sf::Vector2f rotateVector(sf::Vector2f v, float angle)
{
    float oldAngle = atan2(v.y, v.x);
    return sf::Vector2f({ norm(v) * cos(oldAngle + angle), norm(v) * sin(oldAngle + angle) });
}

bool checkRectangleCollision(sf::RectangleShape r1, sf::RectangleShape r2)
{
    sf::RectangleShape newRS;
    newRS.setPosition(r1.getPosition() - r2.getSize());
    newRS.setSize(r1.getSize() + r2.getSize());
    return newRS.getGlobalBounds().contains(r2.getPosition());
}