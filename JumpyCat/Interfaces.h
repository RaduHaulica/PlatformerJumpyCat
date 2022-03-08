#pragma once

class Input;

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