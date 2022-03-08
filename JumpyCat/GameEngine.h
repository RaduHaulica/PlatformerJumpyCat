#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Interfaces.h"
#include "Player.h"
#include "Input.h"
#include "GameObject.h"
#include "Scenery.h"

class GameEngine : public IUpdatable, public sf::Drawable
{
public:
    GameEngine();

    ~GameEngine();

    virtual void update(float dt);

    virtual void handleInput(std::vector<Input> input);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<std::pair<GameObject*, GameObject*>> checkCollisions();

    std::vector<Input> collectInput();
    void addPlayer(Player* newPlayer)
    {
        m_playerEntities.push_back(newPlayer);
    }
    sf::Vector2f getPlayerPosition()
    {
        return m_playerEntities[0]->m_colliderComponent.m_colliders[0].getPosition();
    }
    void addEntity(GameObject* newEntity)
    {
        m_gameEntities.push_back(newEntity);
    }
    void addScenery(Scenery* newScenery)
    {
        m_sceneryEntities.push_back(newScenery);
    }

private:
    bool m_keyPressedDown;
    bool m_keyPressedUp;
    bool m_keyPressedLeft;
    bool m_keyPressedRight;
    std::vector<GameObject*> m_gameEntities;
    std::vector<Player*> m_playerEntities;
    std::vector<Scenery*> m_sceneryEntities;
};