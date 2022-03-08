#pragma once

#include <SFML/Graphics.hpp>

const float pi = 3.141592f;

float degToRad(float degrees);
float radToDeg(float radians);
float norm(sf::Vector2f v);
sf::Vector2f normalize(sf::Vector2f v);
float distanceBetweenPoints(sf::Vector2f v1, sf::Vector2f v2);
float dot(sf::Vector2f v1, sf::Vector2f v2);
// angle in radians
sf::Vector2f rotateVector(sf::Vector2f v, float angle);
bool checkCollision(sf::RectangleShape r1, sf::RectangleShape r2);