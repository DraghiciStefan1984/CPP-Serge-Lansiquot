#include "pch.h"
#include <iostream>
#include <cstring>

using namespace std;

char* ReverseCopy(char * phrase);

int main()
{
	const int MAX_BUFFER_LENGTH = 256;
	char buffer[MAX_BUFFER_LENGTH];

	cout << "Tnter a phrase: ";
	cin.get(buffer, MAX_BUFFER_LENGTH - 1);
	cout << "You entered: " << buffer << endl;

	char* owningPtrRevPhrase = ReverseCopy(buffer);
	cout << "The phrase was: " << owningPtrRevPhrase << endl;

	delete[] owningPtrRevPhrase;
	owningPtrRevPhrase = nullptr;

	return 0;
}

char* ReverseCopy(char * phrase)
{
	int length = strlen(phrase);
	char* reverseString = new char[length+1];//+1 for the null char
	int j = 0;

	for (int i = length - 1; i >= 0; i--)
	{
		reverseString[j] = phrase[i];
		j++;
	}
	reverseString[j] = '\0';
	return reverseString;
}