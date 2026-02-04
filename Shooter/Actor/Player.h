#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player();
	~Player();


private:
	virtual void Tick(float deltaTime) override;

	// 오른쪽 이동
	void MoveRight();
	// 왼쪽 이동
	void MoveLeft();
};

