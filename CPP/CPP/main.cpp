#include "pch.h"
#include <iostream>

using namespace std;

int main3()
{
	//allocate memory from heap
	int* newIntPtr = new int;
	*newIntPtr = 8;
	cout << "Value of intptr is " << *newIntPtr << endl;
	//free up the memory, never "double" delete it, set it to nullptr
	delete newIntPtr;
	newIntPtr = nullptr;

	int length;
	cout << "Enter the length of the array: ";
	cin >> length;

	int* intPtrArray = new int[length];

	return 0;
}