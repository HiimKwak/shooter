#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/EnemySpawner.h"

GameLevel::GameLevel()
{
	// Player 추가
	AddNewActor(new Player());

	// 적 생성기 추가
	AddNewActor(new EnemySpawner());
}

GameLevel::~GameLevel()
{
}
