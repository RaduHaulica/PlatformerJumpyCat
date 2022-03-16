#pragma once

#include <SFML/Graphics.hpp>

#include "Interfaces.h"
#include "GraphicsComponent.h"
#include "ColliderComponent.h"
#include "Input.h"

class GameEngine;

class GameObjectBase: public ICollidable, public IUpdatable, public IControllable, public sf::Drawable
{
public:
    static int IDBase;
    int m_id;

    GameEngine* m_parentGameEngine;
    GraphicsComponent m_graphicsComponent;
    ColliderComponent m_colliderComponent;
    bool m_terminated;
    sf::Vector2f m_position;

    std::vector<GameObjectBase*> m_collidedWith;

    GameObjectBase();
    GameObjectBase* clone(sf::Vector2f position);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

    virtual void collide(GameObjectBase* collidee);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void update(float dt);
    virtual void handleInput(Input input);

};