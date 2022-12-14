#include "GameEngineState.h"

#include "Input.h"
#include "GameEngine.h"
#include "Utility.h"

// ===== =====
//	 MENU
// ===== =====

IGameEngineState* GameEngineStateMenu::handleInput(GameEngine& engine, std::vector<Input> input)
{
	for (auto& command : input)
	{	
		if (command.control == CONTROLS::PRESSED_ENTER && engine.m_buttonsCurrent == 1)
		{
			engine.triggerVictory();
		}
		if (command.control == CONTROLS::PRESSED_ENTER && engine.m_buttonsCurrent == 0)
		{
			std::cout<<"GAME ENGINE >> MENU STATE >> ENTER PRESSED"<<std::endl;
			return new GameEngineStatePlay();
		}

		if ((command.control == CONTROLS::PRESSED_DOWN || command.control == CONTROLS::PRESSED_UP) && (m_buttonSwitchCooldown == 0.0f))
		{
			std::cout<<"GAME ENGINE >> MENU STATE >> UP/DOWN PRESSED"<<std::endl;
			engine.m_buttonsCurrent = (engine.m_buttonsCurrent + 1) % engine.m_buttonsMaxNumber;
			engine.m_textOptionSelector.setPosition(sf::Vector2f(480, 200 + engine.m_buttonsCurrent * 50));
			m_buttonSwitchCooldown = m_buttonSwitchCooldownTimer;
		}
	}
	return nullptr;
}

void GameEngineStateMenu::update(GameEngine& engine, float dt)
{
	m_buttonSwitchCooldown = std::fmaxf(0.0f, m_buttonSwitchCooldown - dt);

	engine.m_menuCat->update(dt);
	engine.m_menuCoin->update(dt);
	engine.m_menuPowerup->update(dt);
}

void GameEngineStateMenu::onEntry(GameEngine& engine)
{
	m_buttonSwitchCooldown = 0.0f;
	m_buttonSwitchCooldownTimer = 0.25f;
}

void GameEngineStateMenu::onExit(GameEngine& engine)
{
}

void GameEngineStateMenu::draw(GameEngine& engine, sf::RenderTarget& target, sf::RenderStates states) const
{
}

GameEngineStateName GameEngineStateMenu::getCurrentState()
{
	return GameEngineStateName::MENU;
}

// ===== =====
//	 PLAY
// ===== =====

IGameEngineState* GameEngineStatePlay::handleInput(GameEngine& engine, std::vector<Input> input)
{
	for (auto& player : engine.m_playerEntities)
		for (auto& command : input)
			player->handleInput(command);
	return nullptr;
}

void GameEngineStatePlay::update(GameEngine& engine, float dt)
{
	engine.m_frameTimeAccumulator += dt;
	while (engine.m_frameTimeAccumulator > engine.m_frameTime) // fixed step update
	{
		
		engine.m_frameTimeAccumulator -= engine.m_frameTime;

		for (auto& player : engine.m_playerEntities)
			player->update(engine.m_frameTime);
		for (auto& entity : engine.m_collectibleEntities)
			entity->update(engine.m_frameTime);
		for (auto& enemy : engine.m_enemyEntities)
			enemy->update(engine.m_frameTime);
		for (auto& wall : engine.m_gameWallEntities)
			wall->update(engine.m_frameTime);
		for (auto& trigger : engine.m_triggerEntities)
			trigger->update(engine.m_frameTime);

		// collisions
		engine.checkCollisions();

		// ===== CLEANUP =====
		for (int i = 0; i < engine.m_collectibleEntities.size(); i++)
		{
			if (engine.m_collectibleEntities[i]->m_dead)
			{
				engine.m_collectibleEntities.erase(engine.m_collectibleEntities.begin() + i);
				i--;
			}
		}

		engine.m_playerHealthBar->update(engine.m_frameTime);

		for (int i = 0; i < engine.m_playerEntities.size(); i++)
		{
			if (engine.m_playerEntities[i]->m_dead)
				engine.m_gameEnded = true;
		}
	}
}

void GameEngineStatePlay::onEntry(GameEngine& engine)
{

}

void GameEngineStatePlay::onExit(GameEngine& engine)
{

}

void GameEngineStatePlay::draw(GameEngine& engine, sf::RenderTarget& target, sf::RenderStates states) const
{
}

GameEngineStateName GameEngineStatePlay::getCurrentState()
{
	return GameEngineStateName::PLAY;
}

// ===== =====
//	 GAME OVER
// ===== =====

IGameEngineState* GameEngineStateGameOver::handleInput(GameEngine& engine, std::vector<Input> input)
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

GameEngineStateName GameEngineStateGameOver::getCurrentState()
{
	return GameEngineStateName::GAMEOVER;
}