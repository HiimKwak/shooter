#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& position)
	: super("@", position, Color::Blue),
	yPosition(static_cast<float>(position.y))
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 총알 이동처리, 프레임(상대적) 아닌 초(고정) 단위로 이동
	yPosition -= moveSpeed * deltaTime; // moveSpeed * 1/frameRate를 yPosition int에서 빼줌.

	// 좌표 검사
	if (yPosition < 0.0f)
	{
		// 삭제처리
		Destroy();
		return;
	}

	// 액터 위치로 변환
	Vector2 newPosition = GetPosition();
	newPosition.y = static_cast<int>(yPosition);

	// 위치 갱신
	SetPosition(newPosition);
}
