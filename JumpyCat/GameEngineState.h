#pragma once

#include "SFML/Graphics.hpp"
#include "Utility.h"

class Input;
class GameEngine;

class IGameEngineState
{
public:
    virtual IGameEngineState* handleInput(GameEngine& engine, std::vector<Input> input) = 0;
    virtual void update(GameEngine& engine, float dt) = 0;
    virtual void onEntry(GameEngine& engine) = 0;
    virtual void onExit(GameEngine& engine) = 0;
	virtual void draw(GameEngine& engine, sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual GameEngineStateName getCurrentState() = 0;
};

class GameEngineStateMenu : public IGameEngineState
{
public:
	virtual IGameEngineState* handleInput(GameEngine& engine, std::vector<Input> input) override;
	virtual void update(GameEngine& engine, float dt) override;
	virtual void onEntry(GameEngine& engine) override;
	virtual void onExit(GameEngine& engine) override;
	virtual void draw(GameEngine& engine, sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual GameEngineStateName getCurrentState() override;

	float m_buttonSwitchCooldownTimer;
	float m_buttonSwitchCooldown;
};

class GameEngineStatePlay : public IGameEngineState
{
public:
	virtual IGameEngineState* handleInput(GameEngine& engine, std::vector<Input> input) override;
	virtual void update(GameEngine& engine, float dt) override;
	virtual void onEntry(GameEngine& engine) override;
	virtual void onExit(GameEngine& engine) override;
	virtual void draw(GameEngine& engine, sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual GameEngineStateName getCurrentState() override;
};

class GameEngineStateGameOver: public IGameEngineState
{
public:
	virtual IGameEngineState* handleInput(GameEngine& engine, std::vector<Input> input) override;
	virtual void update(GameEngine& engine, float dt) override;
	virtual void onEntry(GameEngine& engine) override;
	virtual void onExit(GameEngine& engine) override;
	virtual void draw(GameEngine& engine, sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual GameEngineStateName getCurrentState() override;
};