#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class PlayerBullet : public Actor
{
	RTTI_DECLARATIONS(PlayerBullet, Actor)

public:
	PlayerBullet(const Vector2& position);
	~PlayerBullet();

	virtual void Tick(float deltaTime) override;

private:
	// 이동 속도(초당 이동 칸 수)
	float moveSpeed = 30.0f;

	// 위치 갱신할 때 소수점 처리 목적 변수
	float yPosition = 0.0f;
};

