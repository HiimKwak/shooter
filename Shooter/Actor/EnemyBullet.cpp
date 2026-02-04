#include "EnemyBullet.h"
#include "Engine/Engine.h"

EnemyBullet::EnemyBullet(const Vector2& position, float moveSpeed)
	:super("#", position, Color::Red),
	moveSpeed(moveSpeed),
	yPosition(static_cast<float>(position.y))
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// y 위치 계산
	yPosition += moveSpeed * deltaTime;

	// 화면 하단을 벗어났는지
	if (yPosition >= Engine::Get().GetHeight())
	{
		Destroy();
		return;
	}

	// 위치 설정
	SetPosition(
		Vector2(position.x, static_cast<int>(yPosition))
	);
}
