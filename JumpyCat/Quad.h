#pragma once

#include <SFML/Graphics.hpp>

/*
* a--b  texture polygon utility for animations and textured particles
* |  |
* d--c
*/
class Quad
{
public:
	sf::Vector2f a, b, c, d;

	Quad();
	Quad(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);

	Quad operator=(Quad other);
	void setCoords(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);
};