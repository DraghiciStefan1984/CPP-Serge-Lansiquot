#pragma once
#include <iostream>

class Vector2D
{
public:
	static const Vector2D Zero;
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();
	void SetX(float x);
	void SetY(float y);
	float GetX() const;
	float GetY() const;
	void Display() const;

	friend void operator<<(std::ostream& consoleOut, const Vector2D& vector);

private:
	float x, y;
};

