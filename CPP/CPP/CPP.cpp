// CPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	int x = 8;
	int* intPointer = &x;
	cout << "Address of x is: " << &x << endl;
	cout << "Value of x is: " << x << endl;

	*intPointer = 10;
	cout << "Address of x is: " << &x << endl;
	cout << "Value of x is: " << x << endl;

	return 0;
}