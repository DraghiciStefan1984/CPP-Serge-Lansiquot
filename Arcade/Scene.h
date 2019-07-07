#pragma once
#include <string>
#include <stdint.h>
#include <iostream>

using namespace std;

class Screen;

class Scene
{
public:
	virtual ~Scene() {}
	virtual void Init() = 0;
	virtual void Update(uint32_t dt) = 0;
	virtual void Draw(Screen& screen) = 0;
	virtual const string& GetSceneName() const = 0;
};