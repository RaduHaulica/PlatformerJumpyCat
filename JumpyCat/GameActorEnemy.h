#pragma once

#include "GameActorBase.h"
#include "GameActorState.h"
#include "Utility.h"

class GameActorEnemy : public GameActorBase
{
public:
	GameActorEnemy(std::string name, sf::Vector2f size);

	void update(float dt);

	void move(CONTROLS direction);

	bool isFootSlipping();
	bool walkedIntoAWall();
};