#include "SpriteSheet.h"
#include "Utils.h"
#include "FileCommandLoader.h"
#include "App.h"


SpriteSheet::SpriteSheet() {}

bool SpriteSheet::LoadSpriteSections(const string& path)
{
	FileCommandLoader fileLoader;

	Command spriteCommand;
	spriteCommand.command = "sprite";
	spriteCommand.parseFunc = [&](ParseFuncParams params)
	{
		BMPImageSection section;
		mSections.push_back(section);
	};
	fileLoader.AddCommand(spriteCommand);

	Command keyCommand;
	keyCommand.command = "key";
	keyCommand.parseFunc = [&](ParseFuncParams params)
	{
		mSections.back().key = FileCommandLoader::ReadString(params);
	};
	fileLoader.AddCommand(keyCommand);

	Command xPosCommand;
	xPosCommand.command = "xPos";
	xPosCommand.parseFunc = [&](ParseFuncParams params)
	{
		mSections.back().sprite.xPos = FileCommandLoader::ReadInt(params);
	};
	fileLoader.AddCommand(xPosCommand);

	Command yPosCommand;
	yPosCommand.command = "yPos";
	yPosCommand.parseFunc = [&](ParseFuncParams params)
	{
		mSections.back().sprite.yPos = FileCommandLoader::ReadInt(params);
	};
	fileLoader.AddCommand(yPosCommand);

	Command widthCommand;
	widthCommand.command = "width";
	widthCommand.parseFunc = [&](ParseFuncParams params)
	{
		mSections.back().sprite.width = FileCommandLoader::ReadInt(params);
	};
	fileLoader.AddCommand(widthCommand);

	Command heightCommand;
	heightCommand.command = "height";
	heightCommand.parseFunc = [&](ParseFuncParams params)
	{
		mSections.back().sprite.height = FileCommandLoader::ReadInt(params);
	};
	fileLoader.AddCommand(heightCommand);


	return fileLoader.LoadFile(path);
}

bool SpriteSheet::Load(const string& name)
{
	bool loadedImage = mBMPImage.Load(string("Assets/") + name + ".bmp");
	bool loadedSpriteSections = LoadSpriteSections(string("Assets/") + name + ".txt");
	return loadedImage && loadedSpriteSections;
}

Sprite SpriteSheet::GetSprite(const string& spriteName) const
{
	size_t length = mSections.size();
	for (size_t i = 0; i < length; ++i)
	{
		if (StringCompare(mSections[i].key, spriteName)) return mSections[i].sprite;
	}
	return Sprite();
}

vector<string> SpriteSheet::SpriteNames() const
{
	vector<string> spriteNames;
	for (const auto& section : mSections) spriteNames.push_back(section.key);
	return spriteNames;
}
