// CPP-Classes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
using namespace std;

class Point2D
{
public:
	Point2D();
	Point2D(int x = 0, int y = 0);
	void SetX(int dx);
	void SetY(int dy);
	int GetX();
	int GeyY();
	void Display();

	Point2D& RefOurselves();
	Point2D* PointerOurselves();

	static void PrintStaticMsg() { cout << "Static msg!!!" << endl; }
	inline void PrintInlineMsg() { cout << "Inline msg!" << endl; }

private:
	int mX, mY;
};

/*
Point2D::Point2D()
{
	mX = 0;
	mY = 0;
}

Point2D::Point2D(int x, int y)
{
	mX = x;
	mY = y;
}
*/

//declare constructor using an initializer list before the body
Point2D::Point2D() :mX(0), mY(0) { this->Display(); }

Point2D::Point2D(int x, int y) : mX(0), mY(0) {}

//use initializer list to call another contructor
Point2D::Point2D() : Point2D(8, 8) {}

void Point2D::SetX(int dx) { mX = dx; }

void Point2D::SetY(int dy) { mY = dy; }

int Point2D::GetX() { return mX; }

int Point2D::GeyY() { return mY; }

void Point2D::Display() { cout << "X: " << mX << ", Y:" << mY << endl; }

Point2D & Point2D::RefOurselves() { return *this; }

Point2D * Point2D::PointerOurselves() { return this; }



int main()
{
	Point2D point(5, 8);
	Point2D otherPoint = { 8, 18 };
	point.Display();
	Point2D& refPoint = point.RefOurselves();
	Point2D* ptrPoint = point.PointerOurselves();
	refPoint.Display();
	ptrPoint->Display();
	Point2D::PrintStaticMsg();
	return 0;
}