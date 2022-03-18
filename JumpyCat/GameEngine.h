#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Interfaces.h"
#include "GameObjectBase.h"
#include "GameObjectWall.h"
#include "GameActorBase.h"
#include "Player.h"
#include "Input.h"
#include "Scenery.h"
#include "HealthBar.h"

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
    void addWallEntity(GameObjectWall* newEntity)
    {
        m_gameWallEntities.push_back(newEntity);
        newEntity->m_parentGameEngine = this;
    }
    void addEnemyEntity(GameActorBase* newEnemy)
    {
        m_enemyEntities.push_back(newEnemy);
        newEnemy->m_parentGameEngine = this;
    }
    std::vector<GameObjectWall*> getWalls()
    {
        return m_gameWallEntities;
    }
    void addEnemy(GameActorBase* newEnemy)
    {
        m_enemyEntities.push_back(newEnemy);
        newEnemy->m_parentGameEngine = this;
    }
    void addScenery(Scenery* newScenery)
    {
        m_sceneryEntities.push_back(newScenery);
    }
    void addPlayerHealthBar(HealthBar* hpBar)
    {
        m_playerHealthBar = hpBar;
    }
    bool gameOver()
    {
        return m_gameEnded;
    }

private:
    float m_frameRate;
    float m_frameTime;
    float m_frameTimeAccumulator;

    bool m_gameEnded;

    bool m_keyPressedDown;
    bool m_keyPressedUp;
    bool m_keyPressedLeft;
    bool m_keyPressedRight;

    std::vector<GameObjectWall*> m_gameWallEntities;
    std::vector<GameObjectBase*> m_collectibleEntities;
    std::vector<GameActorBase*> m_enemyEntities;
    std::vector<Player*> m_playerEntities;
    std::vector<Scenery*> m_sceneryEntities;
    HealthBar* m_playerHealthBar;
};