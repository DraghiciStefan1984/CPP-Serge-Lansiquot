#pragma once
#include <stdint.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
#include "SDL.h"
#include "ScreenBuffer.h"
#include "Color.h"
#include "Vec2D.h"
#include "Line2D.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"
#include "Utils.h"

using namespace std;

struct SDL_Window;
struct SDL_Surface;
class Line2D;

class Screen
{
private:
	Screen(const Screen& screen);
	Screen& operator=(const Screen& screen);
	uint32_t mWidth, mHeight;
	ScreenBuffer mBackBuffer;
	Color mClearColor;
	SDL_Window* moptrWindow;
	SDL_Surface* mnoptrWindowSurface;

	void ClearScreen();
	void FillPoly(const vector<Vec2D>& points, const Color color);

public:
	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
	void SwapScreens();
	inline void SetClearColor(const Color& clearColor) { mClearColor = clearColor; }
	inline uint32_t Width() const { return mWidth; }
	inline uint32_t Height() const { return mHeight; }
	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& point, const Color& color);
	void Draw(const Line2D& line, const Color& color);
	void Draw(const Triangle& triangle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
	void Draw(const AARectangle& rectangle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
	void Draw(const Circle& circle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
};

