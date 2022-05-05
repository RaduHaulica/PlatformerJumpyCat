#include "GameEngineState.h"

#include "Input.h"

// ===== =====
//	 MENU
// ===== =====

IGameEngineState* GameEngineStateMenu::handleInput(GameEngine& engine, Input input)
{
	return nullptr;
}

void GameEngineStateMenu::update(GameEngine& engine, float dt)
{

}

void GameEngineStateMenu::onEntry(GameEngine& engine)
{

}

void GameEngineStateMenu::onExit(GameEngine& engine)
{

}

// ===== =====
//	 PLAY
// ===== =====

IGameEngineState* GameEngineStatePlay::handleInput(GameEngine& engine, Input input)
{
	return nullptr;
}

void GameEngineStatePlay::update(GameEngine& engine, float dt)
{

}

void GameEngineStatePlay::onEntry(GameEngine& engine)
{

}

void GameEngineStatePlay::onExit(GameEngine& engine)
{

}

// ===== =====
//	 GAME OVER
// ===== =====

IGameEngineState* GameEngineStateGameOver::handleInput(GameEngine& engine, Input input)
{
	return nullptr;
}

void GameEngineStateGameOver::update(GameEngine& engine, float dt)
{

}

void GameEngineStateGameOver::onEntry(GameEngine& engine)
{

}

void GameEngineStateGameOver::onExit(GameEngine& engine)
{

}