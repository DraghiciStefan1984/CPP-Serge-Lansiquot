#pragma once
#include "Color.h"
#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>

using namespace std;


class BMPImage
{
private:
	vector<Color> mPixels;
	uint32_t mWidth, mHeight;

public:
	BMPImage();
	bool Load(const string& path);
	inline const vector<Color>& GetPixels()const { return mPixels; }
	inline uint32_t GetWidth() const { return mWidth; }
	inline uint32_t GetHeight() const { return mHeight; }
};