// NumberGuesser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <ctime>

using namespace std;

bool WantToPlayAgain();
bool IsGameOver(int secretNumber, int numOfTries, int guess);
void PlayGame();
void DisplayResults(int secretNumber, int numOfTries);
int GetGuess(int numOfTries);

const int IGNORE_CHARS = 256;

int main()
{
	srand((unsigned int)time(NULL));

	do
	{
		PlayGame();
	} while (WantToPlayAgain());

	return 0;
}

void PlayGame()
{
	const int UPPER_BOUND = 100;
	int secretNumber = rand() % UPPER_BOUND;
	int numOfTries = ceil(log2(UPPER_BOUND));
	int guess = 0;

	cout << "The range of number is 0 -> 100" << endl;

	do
	{
		guess = GetGuess(numOfTries);

		if (guess != secretNumber)
		{
			numOfTries--;

			if (guess > secretNumber)
			{
				cout << "Too high!" << endl;
			}
			else
			{
				cout << "Too low!" << endl;
			}
		}
	} while (!IsGameOver(secretNumber, numOfTries, guess));

	DisplayResults(secretNumber, numOfTries);
}

void DisplayResults(int secretNumber, int numOfTries)
{
	if (numOfTries > 0) 
	{
		cout << "You got it! It was " << secretNumber << "!" << endl;
	}
	else
	{
		cout << "You didn't get it! It was " << secretNumber << "!" << endl;
	}
}

bool WantToPlayAgain()
{
	char input;
	bool failure;

	do
	{
		failure = false;
		cout << "Would you like to play again? (y/n) ";
		cin >> input;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << "Input error, please try again!" << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');
			input = tolower(input);
		}

	} while (failure);

	return input=='y';
}

bool IsGameOver(int secretNumber, int numOfTries, int guess)
{
	return secretNumber == guess || numOfTries == 0;
}

int GetGuess(int numOfTries)
{
	int guess;
	bool failure;

	do
	{
		failure = false;
		cout << "Please enter your guess (number of guesses left is " << numOfTries << "):";
		cin >> guess;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << "Input error: Please try again." << endl;
		}
	} while (failure);

	return guess;
}