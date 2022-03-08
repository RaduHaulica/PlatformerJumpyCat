#include "Quad.h"

Quad::Quad() :
	a{ sf::Vector2f({0.0f,0.0f}) },
	b{ sf::Vector2f({0.0f,0.0f}) },
	c{ sf::Vector2f({0.0f, 0.0f}) },
	d{ sf::Vector2f({0.0f, 0.0f}) }
{
}

Quad::Quad(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d) :
	a{ a },
	b{ b },
	c{ c },
	d{ d }
{};

Quad Quad::operator=(Quad other)
{
	this->a = other.a;
	this->b = other.b;
	this->c = other.c;
	this->d = other.d;
	return *this;
}

void Quad::setCoords(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
};