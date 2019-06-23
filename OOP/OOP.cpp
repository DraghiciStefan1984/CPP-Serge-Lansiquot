// OOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Point2D
{
private:
	int x;
	int y;

public:
	Point2D();
	Point2D(int x, int y);
	~Point2D() { cout << "Calling Point2D destructor..." << endl; }
	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
	void Display();

	//copy constructor
	Point2D(const Point2D& other)
	{
		x = 10;//other.x
		y = 12;//other.y
	}

	Point2D& RefToOurselves();
	Point2D* PointerToOurselves();
};

//call the param constructor to init the default constructor values
Point2D::Point2D() : Point2D(0, 0) {}

//use init list to init the values
Point2D::Point2D(int x, int y) : x(x), y(y) {}

void Point2D::SetX(int x) { this->x = x; }

void Point2D::SetY(int y) { this->y = y; }

int Point2D::GetX() { return this->x; }

int Point2D::GetY() { return this->y; }

void Point2D::Display() { cout << "(" << GetX() << "," << GetY() << ")" << endl; }

//return the value at the memory address
Point2D& Point2D::RefToOurselves() { return *this; } 

//return the actual pointer
Point2D* Point2D::PointerToOurselves() { return this; }

int main()
{
	Point2D point;
	point.SetX(23);
	point.SetY(15);
	point.Display();

	Point2D point2(55, 80);
	point2.Display();

	Point2D& refPoint = point.RefToOurselves();
	Point2D* ptrPoint = point.PointerToOurselves();

	cout << "Refs and Pointers" << endl;
	refPoint.Display();
	cout << "Point's address: " << &point << ", refPoint is referencing: " << &refPoint << ", ptrPoint is pointing to: " << ptrPoint << endl;
	ptrPoint->Display();

	Point2D pointCopyConstr(point);
	pointCopyConstr.Display();
	return 0;
}
