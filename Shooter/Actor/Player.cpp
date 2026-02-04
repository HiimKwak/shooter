#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"

Player::Player()
	: super("<=A=>", Vector2::Zero, Color::Green)
{
	// 생성 위치 설정
	int xPosition = (Engine::Get().GetWidth() / 2) - (width / 2);
	int yPosition = (Engine::Get().GetHeight() - 2);
	SetPosition(Vector2(xPosition, yPosition));
}

Player::~Player()
{
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 좌우 방향키 입력처리
	if (Input::Get().GetKey(VK_LEFT))
		MoveLeft();
	if (Input::Get().GetKey(VK_RIGHT))
		MoveRight();

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
