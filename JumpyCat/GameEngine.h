#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Config.h"
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
    void addPlayer(std::unique_ptr<Player> newPlayer);
    sf::Vector2f getPlayerPosition();
    void addWallEntity(std::unique_ptr<GameObjectWall> newEntity);
    std::vector<GameObjectWall*> getWalls();
    void addEnemy(std::unique_ptr<GameActorEnemy> newEnemy);
    void addCollectible(std::unique_ptr<GameObjectPowerup> newCollectible);
    void addScenery(std::unique_ptr<Scenery> newScenery);
    void addTrigger(std::unique_ptr<GameObjectBase> newTrigger);
    void addPlayerHealthBar(std::unique_ptr<HealthBar> hpBar);
    bool gameOver();
    void openDoor();
    bool isDoorOpen();
    void victory();
	
    std::unique_ptr<HealthBar> m_playerHealthBar;

private:
    float m_frameRate;
    float m_frameTime;
    float m_frameTimeAccumulator;

    bool m_gameEnded;
    bool m_doorOpen;
    bool m_victory;

    bool m_keyPressedDown;
    bool m_keyPressedUp;
    bool m_keyPressedLeft;
    bool m_keyPressedRight;

    std::vector<std::unique_ptr<GameObjectWall>> m_gameWallEntities;
    std::vector< std::unique_ptr<GameObjectPowerup>> m_collectibleEntities;
    std::vector< std::unique_ptr<GameActorEnemy>> m_enemyEntities;
    std::vector< std::unique_ptr<Player>> m_playerEntities;
    std::vector< std::unique_ptr<Scenery>> m_sceneryEntities;
    std::vector< std::unique_ptr<GameObjectBase>> m_triggerEntities;
};