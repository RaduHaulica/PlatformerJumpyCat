#pragma once

#include "GameActorBase.h"
#include "GameActorState.h"

class GameActorEnemy : public GameActorBase
{
public:
	GameActorEnemy(std::string name, sf::Vector2f size);

	void update(float dt);

	bool isFootSlipping();
	bool walkedIntoAWall();
};