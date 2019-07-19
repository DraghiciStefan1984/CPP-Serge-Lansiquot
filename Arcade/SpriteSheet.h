#pragma once
#include "BMPImage.h"
#include <string>
#include <vector>
#include <stdint.h>
using namespace std;


struct Sprite
{
	uint32_t xPos = 0;
	uint32_t yPos = 0;
	uint32_t width = 0;
	uint32_t height = 0;
};


class SpriteSheet
{
private:
	struct BMPImageSection
	{
		string key = "";
		Sprite sprite;
	};

	BMPImage mBMPImage;
	vector<BMPImageSection> mSections;
	bool LoadSpriteSections(const string& path);

public:
	SpriteSheet();
	bool Load(const string& name);
	Sprite GetSprite(const string& spriteName) const;
	vector<string> SpriteNames() const;
	inline const BMPImage& GetBMPImage() const { return mBMPImage; }
	inline uint32_t GetWidth() const { return mBMPImage.GetWidth(); }
	inline uint32_t GetHeight() const { return mBMPImage.GetHeight(); }
};

