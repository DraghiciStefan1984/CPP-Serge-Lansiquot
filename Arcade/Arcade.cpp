// Arcade.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "Color.h"
#include "ScreenBuffer.h"
using namespace std;

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO)) cout << "SDL init failed!!!" << endl;
 	SDL_Window* optrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	
	if (optrWindow == nullptr)
	{
		cout << "Cannot create window: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	SDL_Surface* noPtrWindowSurface = SDL_GetWindowSurface(optrWindow);
	SDL_PixelFormat* pixelFormat = noPtrWindowSurface->format;
	cout << "Window pixel format is: " << SDL_GetPixelFormatName(pixelFormat->format) << endl;
	Color::InitColorFormat(pixelFormat);
	ScreenBuffer screenBuffer;
	screenBuffer.Init(pixelFormat->format, noPtrWindowSurface->w, noPtrWindowSurface->h);
	screenBuffer.SetPixel(Color::Red(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SDL_BlitSurface(screenBuffer.GetSurface(), nullptr, noPtrWindowSurface, nullptr);
	SDL_UpdateWindowSurface(optrWindow);

	SDL_Event sdlEvent;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}

	SDL_DestroyWindow(optrWindow);
	SDL_Quit();

	return EXIT_SUCCESS;
}

