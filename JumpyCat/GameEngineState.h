#pragma once

class Input;
class GameEngine;

class IGameEngineState
{
public:
    virtual IGameEngineState* handleInput(GameEngine& engine, Input input) = 0;
    virtual void update(GameEngine& engine, float dt) = 0;
    virtual void onEntry(GameEngine& engine) = 0;
    virtual void onExit(GameEngine& engine) = 0;
};

class GameEngineStateMenu : public IGameEngineState
{
public:
	virtual IGameEngineState* handleInput(GameEngine& engine, Input input) override;
	virtual void update(GameEngine& engine, float dt) override;
	virtual void onEntry(GameEngine& engine) override;
	virtual void onExit(GameEngine& engine) override;
};

class GameEngineStatePlay : public IGameEngineState
{
public:
	virtual IGameEngineState* handleInput(GameEngine& engine, Input input) override;
	virtual void update(GameEngine& engine, float dt) override;
	virtual void onEntry(GameEngine& engine) override;
	virtual void onExit(GameEngine& engine) override;
};

class GameEngineStateGameOver: public IGameEngineState
{
public:
	virtual IGameEngineState* handleInput(GameEngine& engine, Input input) override;
	virtual void update(GameEngine& engine, float dt) override;
	virtual void onEntry(GameEngine& engine) override;
	virtual void onExit(GameEngine& engine) override;
};