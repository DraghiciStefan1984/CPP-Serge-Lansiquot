#include "ArcadeScene.h"

ArcadeScene::ArcadeScene() {}

unique_ptr<Scene> ArcadeScene::GetScene(EGame game)
{
	switch (game)
	{
	case TETRIS:
		break;
	case BREAK_OUT:
		break;
	case ASTEROIDS:
		break;
	case PACMAN:
		break;
	case NUM_GAME:
		break;
	default:
		break;
	}

	return nullptr;
}

void ArcadeScene::Init()
{
}

void ArcadeScene::Update(uint32_t dt)
{
}

void ArcadeScene::Draw(Screen& screen)
{
}

const string& ArcadeScene::GetSceneName() const 
{
	string sceneName = "Arcade Scene";
	return sceneName; 
}