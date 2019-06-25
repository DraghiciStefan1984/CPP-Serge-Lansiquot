// Arcade.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "Color.h"
#include "Screen.h"
using namespace std;

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 2;

int main(int argc, char* argv[])
{
	Screen screen;
	screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
	screen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Green());
	screen.SwapScreens();

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

	return EXIT_SUCCESS;
}