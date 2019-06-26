#pragma once
#include <iostream>
#include <cmath>
#include "SDL.h"
#include "Utils/Utils.h"
#include "Utils/Vec2D.h"

using namespace std;

class Line2D
{
private:
	Vec2D mP0, mP1;

public:
	Line2D();
	Line2D(float x0, float y0, float x1, float y1);
	Line2D(const Vec2D& p0, const Vec2D& p1);

	inline const Vec2D& GetP0() const { return mP0; }
	inline const Vec2D& GetP1() const { return mP1; }
	inline void SetP0(const Vec2D& p0) { this->mP0 = p0; }
	inline void SetP1(const Vec2D& p1) { this->mP1 = p1; }

	bool operator==(const Line2D& line) const;
	float MinDistanceFromPoint(const Vec2D& p, bool limitToSegment = false) const;
	Vec2D ClosestPoint(const Vec2D& p, bool limitToSegment = false) const;
	Vec2D MidPoint() const;
	float Slope() const;
	float Length() const;
};