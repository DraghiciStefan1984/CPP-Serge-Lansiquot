// CPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

void FuncByValue(int x);
void FuncByPtr(int * x);
void FuncByRef(int &x);
void FuncArray(int arr[], int length);

int main2()
{
	int x = 8;
	int* intPointer = &x;
	cout << "Address of x is: " << &x << endl;
	cout << "Value of x is: " << x << endl;

	*intPointer = 10;
	cout << "Address of x is: " << &x << endl;
	cout << "Value of x is: " << x << endl;

	int &intRef = x;
	intRef = 18;
	cout << "Value of intRef is: " << intRef << endl;
	cout << "Address of intRef is: " << &intRef << endl;

	//cannot change value of variable, but can change the reference
	const int* intConstPtr = &x;
	//intConstPtr = 20f;
	int y = 28;
	intConstPtr = &y;

	//cannot change reference, but can change the value of variable
	int* const constIntPtr = &y;
	//constIntPtr = &x;
	*constIntPtr = 38;
	cout << "Value of constIntPtr is: " << *constIntPtr << endl;

	//cannot change reference, nor the value of variable (ref)
	const int & constIntRef = x;
	//constIntRef = 20;
	//constIntRef = &y;

	//cannot change reference, nor the value of variable (pointer)
	const int * const constIntConstPtr = &x;

	FuncByValue(x);
	cout << "Value of x modif by FuncByValue is: " << x << endl;

	FuncByPtr(&x);
	cout << "Value of x modif by FuncByPtr is: " << x << endl;

	FuncByRef(x);
	cout << "Value of x modif by FuncByRef is: " << x << endl;

	int arr[5] = { 2,3,4,5,6 };
	int* ptr = nullptr;
	ptr = arr;
	cout << "The value pointed by ptr is: " << *ptr << endl;

	ptr = &arr[2];
	cout << "The value pointed by ptr is: " << *ptr << endl;
	cout << "The address of element 0 is: " << &arr[0] << endl;
	cout << "The address of element 1 is: " << &arr[1] << endl;
	cout << "The address of element 2 is: " << &arr[2] << endl;

	return 0;
}

void FuncByValue(int x)
{
	x = 88;
	cout << "Value of x is: " << x << endl;
}

void FuncByPtr(int * x)
{
	*x = 88;
	cout << "Value of x is: " << *x << endl;
}

void FuncByRef(int &x)
{
	x = 99;
	cout << "Value of x is: " << x << endl;
}

void FuncArray(int arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		arr[i]++;
	}
}