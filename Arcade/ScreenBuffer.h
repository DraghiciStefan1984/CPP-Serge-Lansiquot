#pragma once
#include "SDL.h"
#include "Color.h"
#include <stdint.h>

struct SDL_Surface;

class ScreenBuffer
{
private:
	SDL_Surface* mSurface;
	uint32_t GetIndex(int r, int c);

public:
	ScreenBuffer();
	ScreenBuffer(const ScreenBuffer& screenBuffer);
	~ScreenBuffer();

	ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);
	void Init(uint32_t format, uint32_t width, uint32_t height);
	inline SDL_Surface* GetSurface() { return mSurface; }
	void Clear(const Color& c = Color::Black());
	void SetPixel(const Color& color, int x, int y);
};