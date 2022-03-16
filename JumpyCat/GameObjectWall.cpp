#include "GameObjectWall.h"

#include "Utility.h"
#include "Player.h"

GameObjectWall::GameObjectWall() {}

void GameObjectWall::collide(GameObjectBase* collidee)
{
    //GameObjectBase::collide(collidee);

    //sf::RectangleShape r2 = collidee->m_colliderComponent.m_colliders[0];
    //sf::RectangleShape r1 = m_colliderComponent.m_colliders[0];
    //sf::Vector2f position = r2.getPosition();

    //float thresholdX = r1.getSize().x/10;
    //float thresholdY = r1.getSize().y/10;

    //if (std::fabs(r1.getPosition().x - r2.getPosition().x - r2.getSize().x) < thresholdX)
    //{
    //    std::cout << "LEFT -> RIGHT\n";
    //    position.x = r1.getPosition().x - r2.getSize().x - 1;
    //}
    //else if (std::fabs(r1.getPosition().x + r1.getSize().x - r2.getPosition().x) < thresholdX)
    //{
    //    std::cout << "RIGHT -> LEFT\n";
    //    position.x = r1.getPosition().x + r1.getSize().x + 1;
    //}
    //else if (std::fabs(r1.getPosition().y - r2.getPosition().y - r2.getSize().y) < thresholdY)
    //{
    //    std::cout << "TOP\n\\/\nBOTTOM\n";
    //    position.y = r1.getPosition().y - r2.getSize().y - 1;
    //    dynamic_cast<Player*>(collidee)->m_grounded = true;
    //}
    //else if (std::fabs(r1.getPosition().y + r1.getSize().y - r2.getPosition().y) < thresholdY)
    //{
    //    std::cout << "BOTTOM\n^\nTOP\n";
    //    position.y = r1.getPosition().y + r1.getSize().y + 1;
    //    dynamic_cast<Player*>(collidee)->m_touchingTop = true;
    //}

    //dynamic_cast<Player*>(collidee)->setPosition(position);
}