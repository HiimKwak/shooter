#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace Wanted;

class Player : public Actor
{
	// 발사 모드
	enum class FireMode
	{
		None = -1,
		OneShot,
		Repeat
	};

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

	// 총알 발사 함수
	void Fire();
	// 연사 함수
	void FireInterval();
	// 발사 가능여부 확인
	bool CanShoot() const;

private:
	FireMode fireMode = FireMode::None;

	// 경과시간
	Timer timer;

	// 연사 간격
	float fireInterval = 0.2f;
};

