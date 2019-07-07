#pragma once
#include <memory>
#include "Scene.h"

class Screen;

enum EGame { TETRIS = 0, BREAK_OUT, ASTEROIDS, PACMAN, NUM_GAME };

class ArcadeScene : public Scene
{
private:
	unique_ptr<Scene> GetScene(EGame game);

public:
	ArcadeScene();
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const string& GetSceneName() const override;
};