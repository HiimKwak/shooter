#include <iostream>
#include <Windows.h> // 윈도우의 콘솔 API. 다른 운영체제 API는 헤더가 다르다

#include "Util/Util.h"
#include "Actor.h"
#include "Render/Renderer.h"
#include "Engine/Engine.h"

namespace Wanted
{
	Actor::Actor(const char* image, const Vector2& position, Color color)
		: position(position), color(color)
	{
		// q. RAII?
		width = static_cast<int>(strlen(image));
		this->image = new char[width + 1];
		strcpy_s(this->image, width + 1, image);
	}

	Actor::~Actor()
	{
		SafeDeleteArray(image);
	}

	void Actor::BeginPlay()
	{
		// toggle after receiving begin play call
		hasBegunPlay = true;
	}
	void Actor::Tick(float deltaTime)
	{
	}
	void Actor::Draw()
	{
		Renderer::Get().Submit(image, position, color, sortingOrder);
	}

	void Actor::Destroy()
	{
		// 삭제 플래그 설정
		destroyRequested = true; // 다음 프레임에 삭제 예정

		OnDestroy();
	}

	void Actor::OnDestroy()
	{
	}

	void Actor::QuitGame()
	{
		// 엔진 종료 요청
		Engine::Get().Quit();
	}

	bool Actor::TestIntersect(const Actor* const other)
	{
		// AABB(Axis Aligned Bounding Box)
		// 이 프로젝트의 경우는 y는 크기가 같으므로 x좌표만 고려
		int xMin = position.x;
		int xMax = position.x + width - 1;

		// 충돌을 비교할 다른 액터의 x좌표 정보
		int otherXMin = other->GetPosition().x;
		int otherXMax = other->position.x + other->width - 1; // 같은 클래스끼린 접근 허용

		// 안겹치는 조건 확인: 아예 떨어져있는 경우
		if (otherXMax < xMin || xMax < otherXMin || position.y == other->position.y) return false;

		return true;
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		// 변경하려는 위치가 현재 위치와 같으면 건너뜀
		if (position == newPosition)
			return;

		// 새로운 위치 설정
		position = newPosition;
	}

}