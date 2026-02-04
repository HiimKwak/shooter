#include "GameLevel.h"
#include "Actor/Player.h"

GameLevel::GameLevel()
{
	// Player Ãß°¡
	AddNewActor(new Player());
}

GameLevel::~GameLevel()
{
}
