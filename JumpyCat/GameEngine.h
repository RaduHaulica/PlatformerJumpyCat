#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Input.h"
#include "Interfaces.h"
#include "GameObjectBase.h"
#include "GameObjectWall.h"
#include "GameObjectPowerup.h"
#include "Scenery.h"
#include "GameActorBase.h"
#include "GameActorEnemy.h"
#include "Player.h"
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
    void addPlayer(Player* newPlayer);
    sf::Vector2f getPlayerPosition();
    void addWallEntity(GameObjectWall* newEntity);
    std::vector<GameObjectWall*> getWalls();
    void addEnemy(GameActorEnemy* newEnemy);
    void addCollectible(GameObjectPowerup* newCollectible);
    void addScenery(Scenery* newScenery);
    void addPlayerHealthBar(HealthBar* hpBar);
    bool gameOver();

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
    std::vector<GameObjectPowerup*> m_collectibleEntities;
    std::vector<GameActorEnemy*> m_enemyEntities;
    std::vector<Player*> m_playerEntities;
    std::vector<Scenery*> m_sceneryEntities;
    HealthBar* m_playerHealthBar;
};