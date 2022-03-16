#pragma once

class Input;
class GameObjectBase;

class IUpdatable
{
public:
    virtual void update(float dt) = 0;
};

class IControllable
{
public:
    virtual void handleInput(Input input) = 0;
};

class ICollidable
{
public:
    virtual void collide(GameObjectBase* collidee) = 0;
};