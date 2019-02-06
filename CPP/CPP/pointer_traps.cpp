#include "pch.h"
#include <iostream>

using namespace std;

int main4()
{
	int* ptr = new int;
	delete ptr;
	//never delete a pointer twice, set it to nullptr
	//delete ptr;
	ptr = nullptr;

	int* ptrArray = new int[10];
	int x = 8;
	//never reassign a pointer from one type to another type => memory leak
	//ptr = &x;

	cout << "Address of ptrArray is: " << ptr << endl;

	//pointer no longer points to the head of the array. Don't do this. 
	//The "owning" pointer should remain on the first position.
	//use another variable to loop through the array elements.
	//ptr++;
	//cout << "Address of ptrArray is: " << ptr << endl;
	int* ptrArray2 = ptrArray;
	ptrArray2++;
	cout << "Address of ptrArray is: " << ptrArray2 << endl;

	return 0;
}