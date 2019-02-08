#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	const int MAX = 10;
	int arr[MAX][MAX];
	int(*pointer)[MAX] = new int[MAX][MAX];

	for (int row = 0; row < MAX; row++)
	{
		for (int column = 0; column < MAX; column++)
		{
			pointer[row][column] = row * column;
			cout << "row=" << row << ", column=" << column << ", value=" << pointer[row][column] << endl;
		}
	}

	delete[] pointer;

	return 0;
}