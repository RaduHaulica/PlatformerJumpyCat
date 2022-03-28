#include "GameEngine.h"

#include "Utility.h"

GameEngine::GameEngine() :
    m_keyPressedDown{ false },
    m_keyPressedLeft{ false },
    m_keyPressedRight{ false },
    m_keyPressedUp{ false },
    m_frameRate{ 60.0f },
    m_frameTimeAccumulator{ 0.0f },
    m_gameEnded{ false }
{
    m_frameTime = 1 / m_frameRate;
}

GameEngine::~GameEngine()
{
    for (int i = 0; i < m_sceneryEntities.size(); i++)
        delete m_sceneryEntities[i];
    for (int i = 0; i < m_gameWallEntities.size(); i++)
        delete m_gameWallEntities[i];
    for (int i = 0; i < m_playerEntities.size(); i++)
        delete m_playerEntities[i];
    for (int i = 0; i < m_enemyEntities.size(); i++)
        delete m_enemyEntities[i];
    for (int i = 0; i < m_collectibleEntities.size(); i++)
        delete m_collectibleEntities[i];

}

void GameEngine::update(float dt)
{
    m_frameTimeAccumulator += dt;
    while (m_frameTimeAccumulator > m_frameTime)
    {
        m_frameTimeAccumulator -= m_frameTime;

		for (auto& player : m_playerEntities)
			player->update(m_frameTime);
        for (auto& entity : m_collectibleEntities)
            entity->update(m_frameTime);
        for (auto& enemy : m_enemyEntities)
            enemy->update(m_frameTime);
		for (auto& wall : m_gameWallEntities)
            wall->update(m_frameTime);

		// collisions
		checkCollisions();

		// ===== CLEANUP =====
		for (int i = 0; i < m_collectibleEntities.size(); i++)
		{
			if (m_collectibleEntities[i]->m_dead)
			{
                m_collectibleEntities.erase(m_collectibleEntities.begin() + i);
				i--;
			}
		}

        m_playerHealthBar->update(m_frameTime);

        for (int i = 0; i < m_playerEntities.size(); i++)
        {
            if (m_playerEntities[i]->m_dead)
                m_gameEnded = true;
        }
    }

}

void GameEngine::handleInput(std::vector<Input> input)
{
    for (auto& player : m_playerEntities)
        for (auto& command:input)
            player->handleInput(command);
}

std::vector<Input> GameEngine::collectInput()
{
    std::vector<Input> resultsVector;
    std::string name{ "CONTROL" };
    Input result;
    result.control = CONTROLS::NOTHING;

    if (m_keyPressedLeft)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            std::cout << name << ": " << "LEFT released\n";
            m_keyPressedLeft = false;
            result.control = CONTROLS::RELEASED_LEFT;
            resultsVector.push_back(result);
        }
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
        if (!m_keyPressedLeft) std::cout << name << ": " << "LEFT pressed\n";
		m_keyPressedLeft = true;
		result.control = CONTROLS::PRESSED_LEFT;
        resultsVector.push_back(result);
	}


    if (m_keyPressedRight)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            std::cout << name << ": " << "RIGHT released\n";
            m_keyPressedRight = false;
            result.control = CONTROLS::RELEASED_RIGHT;
            resultsVector.push_back(result);
        }
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
        if (!m_keyPressedRight) std::cout << name << ": " << "RIGHT pressed\n";
		m_keyPressedRight = true;
		result.control = CONTROLS::PRESSED_RIGHT;
        resultsVector.push_back(result);
	}

    if (m_keyPressedUp)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            std::cout << name << ": " << "UP released\n";
            m_keyPressedUp = false;
            result.control = CONTROLS::RELEASED_UP;
            resultsVector.push_back(result);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (!m_keyPressedUp) std::cout << name << ": " << "UP pressed\n";
        m_keyPressedUp = true;
        result.control = CONTROLS::PRESSED_UP;
        resultsVector.push_back(result);
    }

    if (m_keyPressedDown)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            std::cout << name << ": " << "DOWN released\n";
            m_keyPressedDown = false;
            result.control = CONTROLS::RELEASED_DOWN;
            resultsVector.push_back(result);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (!m_keyPressedDown) std::cout << name << ": " << "DOWN pressed\n";
        m_keyPressedDown = true;
        result.control = CONTROLS::PRESSED_DOWN;
        resultsVector.push_back(result);
    }

    if (resultsVector.size() == 0)
        resultsVector.push_back(result);
    return resultsVector;
}

void GameEngine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
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
    m_playerHealthBar->draw(target, states);
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
                        static_cast<Player*>(m_playerEntities[i])->collideWall(m_gameWallEntities[j]);
                        m_gameWallEntities[j]->collide(m_playerEntities[i]);
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
                results.push_back({m_playerEntities[i], m_collectibleEntities[j]});
                m_playerEntities[i]->collideCollectible(m_collectibleEntities[j]);
                m_collectibleEntities[j]->collide(m_playerEntities[i]);
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
                results.push_back({ m_playerEntities[i], m_enemyEntities[j] });
                m_playerEntities[i]->collideEnemy(m_enemyEntities[j]);
                m_enemyEntities[j]->collide(m_playerEntities[i]);
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
                results.push_back({m_enemyEntities[i], m_gameWallEntities[j]});
                m_enemyEntities[i]->collideWall(m_gameWallEntities[j]);
                m_gameWallEntities[j]->collide(m_enemyEntities[i]);
            }
        }
    }

    return results;
}

void GameEngine::addPlayer(Player* newPlayer)
{
    m_playerEntities.push_back(newPlayer);
    newPlayer->m_parentGameEngine = this;
}

sf::Vector2f GameEngine::getPlayerPosition()
{
    return m_playerEntities[0]->m_colliderComponent.m_colliders[0].getPosition();
}

void GameEngine::addWallEntity(GameObjectWall* newEntity)
{
    m_gameWallEntities.push_back(newEntity);
    newEntity->m_parentGameEngine = this;
}

std::vector<GameObjectWall*> GameEngine::getWalls()
{
    return m_gameWallEntities;
}

void GameEngine::addEnemy(GameActorBase* newEnemy)
{
    m_enemyEntities.push_back(newEnemy);
    newEnemy->m_parentGameEngine = this;
}

void GameEngine::addCollectible(GameObjectPowerup* newCollectible)
{
    m_collectibleEntities.push_back(newCollectible);
}

void GameEngine::addScenery(Scenery* newScenery)
{
    m_sceneryEntities.push_back(newScenery);
}

void GameEngine::addPlayerHealthBar(HealthBar* hpBar)
{
    m_playerHealthBar = hpBar;
}

bool GameEngine::gameOver()
{
    return m_gameEnded;
}