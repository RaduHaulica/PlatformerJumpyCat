#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Interfaces.h"
#include "GameObjectBase.h"
#include "Player.h"
#include "Input.h"
#include "Scenery.h"

class GameEngine : public IUpdatable, public sf::Drawable
{
public:
    GameEngine();

    ~GameEngine();

    virtual void update(float dt);

    virtual void handleInput(std::vector<Input> input);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<std::pair<GameObjectBase*, GameObjectBase*>> checkCollisions();

    std::vector<Input> collectInput();
    void addPlayer(Player* newPlayer)
    {
        m_playerEntities.push_back(newPlayer);
        newPlayer->m_parentGameEngine = this;
    }
    sf::Vector2f getPlayerPosition()
    {
        return m_playerEntities[0]->m_colliderComponent.m_colliders[0].getPosition();
    }
    void addEntity(GameObjectBase* newEntity)
    {
        m_gameEntities.push_back(newEntity);
        newEntity->m_parentGameEngine = this;
    }
    std::vector<GameObjectBase*> getWalls()
    {
        return m_gameEntities;
    }
    void addEnemy(Player* newEnemy)
    {
        m_enemyEntities.push_back(newEnemy);
        newEnemy->m_parentGameEngine = this;
    }
    void addScenery(Scenery* newScenery)
    {
        m_sceneryEntities.push_back(newScenery);
    }

private:
    float m_frameRate;
    float m_frameTime;
    float m_frameTimeAccumulator;

    bool m_keyPressedDown;
    bool m_keyPressedUp;
    bool m_keyPressedLeft;
    bool m_keyPressedRight;
    std::vector<GameObjectBase*> m_gameEntities;
    std::vector<GameObjectBase*> m_collectibleEntities;
    std::vector<GameObjectBase*> m_enemyEntities;
    std::vector<GameObjectBase*> m_playerEntities;
    std::vector<Scenery*> m_sceneryEntities;
};