#pragma once

#include <SFML/Graphics.hpp>

#include "GameObjectBase.h"
#include "GraphicsComponent.h"
#include "ColliderComponent.h"
#include "Input.h"

class GameEngine;

class GameObjectWall : public GameObjectBase
{
public:
    GameObjectWall();
    virtual void collide(GameObjectBase* collidee);
};