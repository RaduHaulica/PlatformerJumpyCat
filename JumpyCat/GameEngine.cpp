#include "GameEngine.h"

#include "Utility.h"

GameEngine::GameEngine() :
    m_keyPressedDown{ false },
    m_keyPressedLeft{ false },
    m_keyPressedRight{ false },
    m_keyPressedUp{ false },
    m_keyPressedEnter{ false },
    m_keyPressedEscape{ false },
    m_inputCooldownTime{ 0.0f },
    m_downCooldownAccumulator{ 0.0f },
    m_upCooldownAccumulator{ 0.0f },
    m_leftCooldownAccumulator{ 0.0f },
    m_rightCooldownAccumulator{ 0.0f },
    m_enterCooldownAccumulator{ 0.0f },
    m_escapeCooldownAccumulator{ 0.0f },
    m_frameRate{ 60.0f },
    m_frameTimeAccumulator{ 0.0f },
    m_gameEnded{ false },
    m_doorOpen{ false },
    m_buttonsCurrent{ 0 },
    m_buttonsMaxNumber{ 2 }
{ 
    m_frameTime = 1 / m_frameRate;
    m_currentState = new GameEngineStateMenu();
    m_currentState->onEntry(*this);
}

GameEngine::~GameEngine()
{}

void GameEngine::update(float dt)
{
    std::vector<Input> input = collectInput(dt);
    handleInput(input);
    m_currentState->update(*this, dt);
}

void GameEngine::handleInput(std::vector<Input> input)
{
	IGameEngineState* newState = m_currentState->handleInput(*this, input);
	if (newState != nullptr)
	{
        m_currentState->onExit(*this);
        delete m_currentState;
		
		m_currentState = newState;
        m_currentState->onEntry(*this);
	}
}

std::vector<Input> GameEngine::collectInput(float dt)
{
    std::vector<Input> resultsVector;
    std::string name{ "CONTROL" };
    Input result;
    result.control = CONTROLS::NOTHING;
	
	m_upCooldownAccumulator = std::fmaxf(0.0f, m_upCooldownAccumulator - dt);
	m_downCooldownAccumulator = std::fmaxf(0.0f, m_downCooldownAccumulator - dt);
	m_leftCooldownAccumulator = std::fmaxf(0.0f, m_leftCooldownAccumulator - dt);
	m_rightCooldownAccumulator = std::fmaxf(0.0f, m_rightCooldownAccumulator - dt);
	m_enterCooldownAccumulator = std::fmaxf(0.0f, m_enterCooldownAccumulator - dt);
	m_escapeCooldownAccumulator = std::fmaxf(0.0f, m_escapeCooldownAccumulator - dt);

    if (m_keyPressedLeft)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (Config::showControls)
                std::cout << name << ": " << "LEFT released\n";
            m_keyPressedLeft = false;
            result.control = CONTROLS::RELEASED_LEFT;
            resultsVector.push_back(result);
        }
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_leftCooldownAccumulator == 0.0f)
	{
        if (Config::showControls)
            if (!m_keyPressedLeft) std::cout << name << ": " << "LEFT pressed\n";
		m_keyPressedLeft = true;
		m_leftCooldownAccumulator = m_inputCooldownTime; 
		result.control = CONTROLS::PRESSED_LEFT;
        resultsVector.push_back(result);
	}

    if (m_keyPressedRight)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (Config::showControls)
                std::cout << name << ": " << "RIGHT released\n";
            m_keyPressedRight = false;
            result.control = CONTROLS::RELEASED_RIGHT;
            resultsVector.push_back(result);
        }
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_rightCooldownAccumulator == 0.0f)
	{
        if (Config::showControls)
            if (!m_keyPressedRight) std::cout << name << ": " << "RIGHT pressed\n";
		m_keyPressedRight = true;
		m_rightCooldownAccumulator = m_inputCooldownTime;
		result.control = CONTROLS::PRESSED_RIGHT;
        resultsVector.push_back(result);
	}

    if (m_keyPressedUp)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (Config::showControls)
                std::cout << name << ": " << "UP released\n";
            m_keyPressedUp = false;
            result.control = CONTROLS::RELEASED_UP;
            resultsVector.push_back(result);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_upCooldownAccumulator == 0.0f)
    {
        if (Config::showControls)
            if (!m_keyPressedUp) std::cout << name << ": " << "UP pressed\n";
        m_keyPressedUp = true;
		m_upCooldownAccumulator = m_inputCooldownTime;
        result.control = CONTROLS::PRESSED_UP;
        resultsVector.push_back(result);
    }

    if (m_keyPressedDown)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (Config::showControls)
                std::cout << name << ": " << "DOWN released\n";
            m_keyPressedDown = false;
            result.control = CONTROLS::RELEASED_DOWN;
            resultsVector.push_back(result);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_downCooldownAccumulator == 0.0f)
    {
        if (Config::showControls)
            if (!m_keyPressedDown) std::cout << name << ": " << "DOWN pressed\n";
        m_keyPressedDown = true;
		m_downCooldownAccumulator = m_inputCooldownTime;
        result.control = CONTROLS::PRESSED_DOWN;
        resultsVector.push_back(result);
    }

    if (m_keyPressedEnter)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            if (Config::showControls)
                std::cout << name << ": " << "ENTER released\n";
            m_keyPressedEnter = false;
			result.control = CONTROLS::RELEASED_ENTER;
            resultsVector.push_back(result);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && m_enterCooldownAccumulator == 0.0f)
    {
        if (Config::showControls)
            if (!m_keyPressedEnter) std::cout << name << ": " << "ENTER pressed\n";
        m_keyPressedEnter = true;
		m_enterCooldownAccumulator = m_inputCooldownTime;
        result.control = CONTROLS::PRESSED_ENTER;
        resultsVector.push_back(result);
    }
	
    if (m_keyPressedEscape)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            if (Config::showControls)
                std::cout << name << ": " << "ESCAPE released\n";
            m_keyPressedEscape = false;
            result.control = CONTROLS::RELEASED_ESCAPE;
            resultsVector.push_back(result);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_escapeCooldownAccumulator == 0.0f)
    {
        if (Config::showControls)
            if (!m_keyPressedEscape) std::cout << name << ": " << "ESCAPE pressed\n";
        m_keyPressedEscape = true;
		m_escapeCooldownAccumulator = m_inputCooldownTime;
        result.control = CONTROLS::PRESSED_ESCAPE;
        resultsVector.push_back(result);
    }		

    if (resultsVector.size() == 0)
        resultsVector.push_back(result);
    return resultsVector;
}

void GameEngine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    switch (m_currentState->getCurrentState())
    {
    case GameEngineStateName::PLAY:
		for (auto& scenery : m_sceneryEntities)
			scenery->draw(target, states);
		for (auto& wall : m_gameWallEntities)
			wall->draw(target, states);
		for (auto& collectible : m_collectibleEntities)
			collectible->draw(target, states);
		for (auto& enemy : m_enemyEntities)
			enemy->draw(target, states);
		for (auto& player : m_playerEntities)
			player->draw(target, states);
        for (auto& trigger : m_triggerEntities)
            trigger->draw(target, states);
		m_playerHealthBar->draw(target, states);
        break;
		
    case GameEngineStateName::MENU:
		target.draw(m_textOptionOne);
		target.draw(m_textOptionTwo);
        target.draw(m_textOptionSelector);

        target.draw(m_textControlHints);
        target.draw(m_textTitle);
        target.draw(*m_menuCat);
        target.draw(*m_menuPowerup);
        target.draw(*m_menuCoin);
        break;
		
    case GameEngineStateName::GAMEOVER:
        
        break;
    }
	
}

std::vector<std::pair<GameObjectBase*, GameObjectBase*>> GameEngine::checkCollisions()
{
    std::vector<std::pair<GameObjectBase*, GameObjectBase*>> results;

    // players hitting walls
    for (int i = 0; i < m_playerEntities.size(); i++)
    {
        for (int j = 0; j < m_gameWallEntities.size(); j++)
        {
            for (int k = 0; k < m_playerEntities[i]->m_colliderComponent.m_colliders.size(); k++)
            {
                for (int l = 0; l < m_gameWallEntities[j]->m_colliderComponent.m_colliders.size(); l++)
                {
                    if (checkRectangleCollision(m_playerEntities[i]->m_colliderComponent.m_colliders[k], m_gameWallEntities[j]->m_colliderComponent.m_colliders[l]))
                    {
                        //static_cast<Player*>(m_playerEntities[i])->collideWall(m_gameWallEntities[j]);
                        m_playerEntities[i]->collideWall(m_gameWallEntities[j].get());
                        m_gameWallEntities[j]->collide(m_playerEntities[i].get());
                    }
                }
            }
        }
    }

    // players getting collectibles
    for (int i = 0; i < m_playerEntities.size(); i++)
    {
        for (int j = 0; j < m_collectibleEntities.size(); j++)
        {
            if (checkRectangleCollision(m_playerEntities[i]->m_colliderComponent.m_colliders[0], m_collectibleEntities[j]->m_colliderComponent.m_colliders[0]))
            {
                //results.push_back({m_playerEntities[i].get(), m_collectibleEntities[j].get()});
                m_playerEntities[i]->collideCollectible(m_collectibleEntities[j].get());
                m_collectibleEntities[j]->collide(m_playerEntities[i].get());
            }
        }
    }

    // players pouncing on monsters
    for (int i = 0; i < m_playerEntities.size(); i++)
    {
        for (int j = 0; j < m_enemyEntities.size(); j++)
        {
            if (checkRectangleCollision(m_playerEntities[i]->m_colliderComponent.m_colliders[0], m_enemyEntities[j]->m_colliderComponent.m_colliders[0]))
            {
                //results.push_back({ m_playerEntities[i].get(), m_enemyEntities[j].get()});
                m_playerEntities[i]->collideEnemy(m_enemyEntities[j].get());
                m_enemyEntities[j]->collide(m_playerEntities[i].get());
            }
        }
    }

    // players hitting triggers
    for (int i = 0; i < m_playerEntities.size(); i++)
    {
        for (int j = 0; j < m_triggerEntities.size(); j++)
        {
            if (checkRectangleCollision(m_playerEntities[i]->m_colliderComponent.m_colliders[0], m_triggerEntities[j]->m_colliderComponent.m_colliders[0]))
            {
				//results.push_back({ m_playerEntities[i].get(), m_triggerEntities[j].get()});
				m_playerEntities[i]->collide(m_triggerEntities[j].get());
				m_triggerEntities[j]->collide(m_playerEntities[i].get());
            }
        }
    }

    // monsters running into walls
    for (int i = 0; i < m_enemyEntities.size(); i++)
    {
        for (int j = 0; j < m_gameWallEntities.size(); j++)
        {
            if (checkRectangleCollision(m_enemyEntities[i]->m_colliderComponent.m_colliders[0], m_gameWallEntities[j]->m_colliderComponent.m_colliders[0]))
            {
                //results.push_back({m_enemyEntities[i].get(), m_gameWallEntities[j].get()});
                m_enemyEntities[i]->collideWall(m_gameWallEntities[j].get());
                m_gameWallEntities[j]->collide(m_enemyEntities[i].get());
            }
        }
    }

    return results;
}

void GameEngine::addPlayer(std::unique_ptr<Player> newPlayer)
{
    newPlayer->m_parentGameEngine = this;
    m_playerEntities.push_back(std::move(newPlayer));
}

sf::Vector2f GameEngine::getPlayerPosition()
{
    return m_playerEntities[0]->m_colliderComponent.m_colliders[0].getPosition();
}

void GameEngine::addWallEntity(std::unique_ptr<GameObjectWall> newEntity)
{
    newEntity->m_parentGameEngine = this;
    m_gameWallEntities.push_back(std::move(newEntity));
}

std::vector<GameObjectWall*> GameEngine::getWalls()
{
    std::vector<GameObjectWall*> results;
	for (auto& wall : m_gameWallEntities)
		results.push_back(wall.get());
    return results;
}

void GameEngine::addEnemy(std::unique_ptr<GameActorEnemy> newEnemy)
{
    newEnemy->m_parentGameEngine = this;
    m_enemyEntities.push_back(std::move(newEnemy));
}

void GameEngine::addCollectible(std::unique_ptr<GameObjectPowerup> newCollectible)
{
    m_collectibleEntities.push_back(std::move(newCollectible));
}

void GameEngine::addScenery(std::unique_ptr<Scenery> newScenery)
{
    m_sceneryEntities.push_back(std::move(newScenery));
}

void GameEngine::addTrigger(std::unique_ptr<GameObjectBase> newTrigger)
{
    m_triggerEntities.push_back(std::move(newTrigger));
}

void GameEngine::addPlayerHealthBar(std::unique_ptr<HealthBar> hpBar)
{
    m_playerHealthBar = std::move(hpBar);
}

bool GameEngine::isGameOver()
{
    return m_gameEnded;
}

void GameEngine::openDoor()
{
	m_doorOpen = true;
    m_triggerEntities[0]->m_graphicsComponent.changeAnimation("open");
}

bool GameEngine::isDoorOpen()
{
    return m_doorOpen;
}

void GameEngine::triggerVictory()
{
	m_victory = true;
}