#pragma once
#include "Screen.h"
#include "ArcadeScene.h"
#include "Scene.h"
#include <stdint.h>
#include <memory>
#include <cassert>

struct SDL_Window;

class App
{
private:
	Screen mScreen;
	SDL_Window* mnoptrWindow;
	vector<unique_ptr<Scene>> mSceneStack;

public:
	static App& Singleton();
	bool Init(uint32_t width, uint32_t height, uint32_t mag);
	void Run();
	void PushScene(unique_ptr<Scene> scene);
	void PopScene();
	Scene* TopScene();

	inline uint32_t Width() const { return mScreen.Width(); }
	inline uint32_t Height() const { return mScreen.Height(); }
};