#include "GameEngine.h"

#include "Utility.h"

GameEngine::GameEngine() :
    m_keyPressedDown{ false },
    m_keyPressedLeft{ false },
    m_keyPressedRight{ false },
    m_keyPressedUp{ false }
{}

GameEngine::~GameEngine()
{
    for (int i = 0; i < m_sceneryEntities.size(); i++)
        delete m_sceneryEntities[i];
    for (int i = 0; i < m_gameEntities.size(); i++)
        delete m_gameEntities[i];
    for (int i = 0; i < m_playerEntities.size(); i++)
        delete m_playerEntities[i];
}

void GameEngine::update(float dt)
{
    for (auto& player : m_playerEntities)
        player->update(dt);
    for (auto& entity : m_gameEntities)
        entity->update(dt);

    std::vector<std::pair<GameObject*, GameObject*>> collisionResults = checkCollisions();
	for (auto& [playerEntity, gameEntity] : collisionResults)
	{
		dynamic_cast<Player*>(playerEntity)->collide(gameEntity);
	}

    // ===== CLEANUP =====
    for (int i = 0; i < m_gameEntities.size(); i++)
    {
        if (m_gameEntities[i]->m_terminated)
        {
            m_gameEntities.erase(m_gameEntities.begin() + i);
            i--;
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
    for (auto& entity : m_gameEntities)
        entity->draw(target, states);
    for (auto& player : m_playerEntities)
        player->draw(target, states);
}

std::vector<std::pair<GameObject*, GameObject*>> GameEngine::checkCollisions()
{
    std::vector<std::pair<GameObject*, GameObject*>> results;

    for (int i = 0; i < m_playerEntities.size(); i++)
    {
        for (int j = 0; j < m_gameEntities.size(); j++)
        {
            for (int k = 0; k < m_playerEntities[i]->m_colliderComponent.m_colliders.size(); k++)
            {
                for (int l = 0; l < m_gameEntities[j]->m_colliderComponent.m_colliders.size(); l++)
                {
                    if (checkCollision(m_playerEntities[i]->m_colliderComponent.m_colliders[k], m_gameEntities[j]->m_colliderComponent.m_colliders[l]))
                    {
                        results.push_back({ m_playerEntities[i], m_gameEntities[j] });
                    }
                }
            }
        }
    }

    return results;
}