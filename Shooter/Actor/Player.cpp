#include "Player.h"
#include "Actor/PlayerBullet.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"

Player::Player()
	: super("<=A=>", Vector2::Zero, Color::Green),
	fireMode(FireMode::OneShot)
{
	// 생성 위치 설정
	int xPosition = (Engine::Get().GetWidth() / 2) - (width / 2);
	int yPosition = (Engine::Get().GetHeight() - 2);
	SetPosition(Vector2(xPosition, yPosition));

	// 타이머 목표 시간 설정
	timer.SetTargetTime(fireInterval);
}

Player::~Player()
{
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 종료 처리
	if (Input::Get().GetKeyDown(VK_ESCAPE))
		QuitGame();

	// 경과 시간 업데이트
	timer.Tick(deltaTime);

	// 좌우 방향키 입력처리
	if (Input::Get().GetKey(VK_LEFT))
		MoveLeft();
	if (Input::Get().GetKey(VK_RIGHT))
		MoveRight();

	// space로 총알 발사
	if (fireMode == FireMode::OneShot)
	{
		if (Input::Get().GetKeyDown(VK_SPACE))
			Fire();
	}
	else if (fireMode == FireMode::Repeat)
	{
		if (Input::Get().GetKey(VK_SPACE))
			FireInterval();
	}

	// 발사 모드 전환
	if (Input::Get().GetKeyDown('R')) // 소문자는 인식 안됨
	{
		int mode = static_cast<int>(fireMode);
		mode = 1 - mode;
		fireMode = static_cast<FireMode>(mode);
	}
}

void Player::MoveRight()
{
	// 1칸 이동
	position.x += 1;

	// "<-=A=->" : x + length - 1
	if (position.x + width > Engine::Get().GetWidth())
		position.x -= 1;
}

void Player::MoveLeft()
{
	// Vector2 position = GetPosition(); private에서 protected로 바꿨기 때문
	// 1칸 이동
	position.x -= 1;

	if (position.x < 0)
		position.x = 0;

}

void Player::Fire()
{
	// 발사 후 타이머 초기화
	timer.Reset();

	// 위치 설정
	Vector2 bulletPosition(
		position.x + (width / 2),
		position.y
	);

	// 액터 생성
	GetOwner()->AddNewActor(new PlayerBullet(bulletPosition));
}

void Player::FireInterval()
{
	// 발사 가능여부 확인
	if (!CanShoot())
		return;

	Fire();
}

bool Player::CanShoot() const
{
	// 경과 시간이 발사 간격보다 더 흘렀는지
	return timer.IsTimeout();
}
