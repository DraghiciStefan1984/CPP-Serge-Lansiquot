#pragma once
#include "Vec2D.h"
#include <vector>
#include <iostream>

using namespace std;

class Shape
{
protected:
	vector<Vec2D> mPoints;

public:
	virtual ~Shape();
	virtual Vec2D GetCenterPoint() const = 0;
	inline virtual vector<Vec2D> GetPoints()const { return mPoints; }
	void MoveBy(const Vec2D& deltaOffset);
};