// Arcade.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "Color.h"
#include "Screen.h"
#include "Line2D.h"
using namespace std;

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 2;

int main(int argc, char* argv[])
{
	Screen screen;
	screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
	Line2D line = { Vec2D(0,0), Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT) };
	Triangle triangle = { Vec2D(60, 10), Vec2D(10, 110) , Vec2D(110, 110) };
	AARectangle rectangle = { Vec2D(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25), 50, 50 };
	Circle circle = { Vec2D(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25), 50 };

	//screen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Green());
	//screen.Draw(line, Color::White());
	//screen.Draw(triangle, Color::Red());
	//screen.Draw(rectangle, Color::Red());
	screen.Draw(circle, Color::Red(), true, Color::Green());
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