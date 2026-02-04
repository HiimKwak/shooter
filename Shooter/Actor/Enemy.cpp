#include "Enemy.h"
#include "Util/Util.h"
#include "Engine/Engine.h"
#include "Actor/EnemyBullet.h"
#include "Level/Level.h"

Enemy::Enemy(const char* image, int yPosition)
	:super(image)
{
	// 무작위 이동 방향
	int random = Util::Random(1, 10);

	if (random % 2 == 0)
	{
		// 짝수일 때 화면 우측에서 생성
		xPosition = static_cast<float>(Engine::Get().GetWidth() - width - 1);
		direction = MoveDirection::Left;
	}
	else
	{
		xPosition = 0.0f;
		direction = MoveDirection::Right;
	}

	// 이동 방향에 따른 적 스폰 위치 설정
	SetPosition(
		Vector2(static_cast<int>(xPosition), yPosition)
	);

	// 발사 타이머 목표 시간 설정
	timer.SetTargetTime(Util::RandomRange(1.0f, 3.0f));
}

Enemy::~Enemy()
{
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 이동 처리
	float dir = direction == MoveDirection::Left ? -1.0f : 1.0f;
	xPosition += moveSpeed * dir * deltaTime;

	// 화면 왼쪽을 완전히 벗어났으면
	if (xPosition + width < 0)
	{
		Destroy();
		return;
	}
	// 화면 오른쪽을 완전히 벗어났으면
	if (xPosition > Engine::Get().GetWidth() - 1)
	{
		Destroy();
		return;
	}

	// 위치 설정
	SetPosition(Vector2(
		static_cast<int>(xPosition),
		position.y
	));

	// 발사 타이머 업데이트
	timer.Tick(deltaTime);
	if (!timer.IsTimeout())
		return;

	// 타이머 리셋
	timer.Reset();

	// 총알 발사
	GetOwner()->AddNewActor(
		new EnemyBullet(
			Vector2(position.x + width / 2, position.y),
			Util::RandomRange(10.0f, 20.0f)
		));
}

void Enemy::OnDamaged()
{
	// 액터 제거
	Destroy();

	// todo: 이펙트 생성
}
