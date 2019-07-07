#include "App.h"

App& App::Singleton()
{
	static App appInstance;
	return appInstance;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
	mnoptrWindow = mScreen.Init(width, height, mag);
	unique_ptr<ArcadeScene> arcadeScene = make_unique<ArcadeScene>();
	PushScene(move(arcadeScene));
	return mnoptrWindow != nullptr;
}

void App::Run()
{
	if (mnoptrWindow)
	{
		SDL_Event sdlEvent;
		bool running = true;
		uint32_t lastTick = SDL_GetTicks();
		uint32_t currentTick = lastTick;
		uint32_t dt = 10;
		uint32_t accumulator = 0;

		while (running)
		{
			currentTick = SDL_GetTicks();
			uint32_t frameTime = currentTick - lastTick;
			if (frameTime > 300) frameTime = 300;
			lastTick = currentTick;
			accumulator += frameTime;

			while (SDL_PollEvent(&sdlEvent))
			{
				switch (sdlEvent.type)
				{
				case SDL_QUIT:
					running = false;
					break;
				}
			}

			Scene* topScene = TopScene();
			if (topScene)
			{
				while (accumulator >= dt)
				{
					topScene->Update(dt);
					accumulator -= dt;
				}
				topScene->Draw(mScreen);
			}
			mScreen.SwapScreens();
		}
	}
}

void App::PushScene(unique_ptr<Scene> scene)
{ 
	if (scene)
	{
		scene->Init();
		mSceneStack.emplace_back(move(scene));
		if (TopScene()) SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
	}
}

void App::PopScene()
{
	if (mSceneStack.size > 1) mSceneStack.pop_back();
	if (TopScene()) SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
}

Scene* App::TopScene()
{
	if (mSceneStack.empty()) return nullptr;
	return mSceneStack.back().get();
}