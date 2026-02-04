#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace Wanted;

class Enemy : public Actor
{
	// 이동 방향
	enum class MoveDirection
	{
		None = -1,
		Left,
		Right
	};

	RTTI_DECLARATIONS(Enemy, Actor)

public:
	Enemy(const char* image = "(oOo)", int yPosition = 5);
	~Enemy();

	virtual void Tick(float deltaTime) override;

	void OnDamaged();

private:
	MoveDirection direction = MoveDirection::None;
	// 좌우 이동 처리를 위한 변수
	float xPosition = 0.0f;
	float moveSpeed = 5.0f;

	// 발사 타이머
	Timer timer;
};

