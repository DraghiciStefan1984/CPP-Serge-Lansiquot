#include "pch.h"
#include "Vector2D.h"
#include <iostream>

Vector2D::Vector2D():Vector2D(0, 0)
{
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}


Vector2D::~Vector2D()
{
}

void Vector2D::SetX(float x)
{
	this->x = x;
}

void Vector2D::SetY(float y)
{
	this->y = y;
}

float Vector2D::GetX() const
{
	return this->x;
}

float Vector2D::GetY() const
{
	return this->y;
}

void Vector2D::Display() const
{
	std::cout << "X: " << this->x << ", Y: " << this->y << std::endl;
}

void operator<<(std::ostream & consoleOut, const Vector2D & vector)
{
	consoleOut << "X: " << this->x << ", Y: " << this->y << std::endl;
}
