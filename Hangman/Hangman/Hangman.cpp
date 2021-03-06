// Hangman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include "Utils.h"

using namespace std;

const int IGNORE_CHARS = 256;
const char* INPUT_ERROR_STRING = "Input error: please try again!";

void PlayGame();
int GetSecretPhrase(char secretPhrase[], int maxLength);
bool WantToPlayAgain();
char* MakeHiddenPhrase(const char* secretPhrase, int secretPhraseLength);
void DrawBoard(int numGuessesLeft, const char* noPtrHiddenPhrase);
char GetGuess();
void UpdateBoard(char guess, char * noPtrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int & numGuessesLeft);
bool IsGameOver(int numGuessesLeft, const char * noPtrHiddenPhrase, int secretPhraseLength);
void DisplayResult(const char * secretPhrase, int numGuessesLeft);

int main()
{
	do
	{
		PlayGame();
	} while (WantToPlayAgain());

	return 0;
}

void PlayGame()
{
	const int SECRET_PHRASE_MAX_LENGTH = 256;
	const int MAX_NUM_OF_GUESSES = 6;
	char secretPhrase[SECRET_PHRASE_MAX_LENGTH];
	char* ownerPtrHiddenPhrase = nullptr;
	int numGuessesLeft = MAX_NUM_OF_GUESSES;
	char guess;
	int secretPhraseLength = GetSecretPhrase(secretPhrase, SECRET_PHRASE_MAX_LENGTH);
	ownerPtrHiddenPhrase = MakeHiddenPhrase(secretPhrase, secretPhraseLength);

	DrawBoard(numGuessesLeft, ownerPtrHiddenPhrase);

	do
	{
		guess = GetGuess();
		UpdateBoard(guess, ownerPtrHiddenPhrase, secretPhrase, secretPhraseLength, numGuessesLeft);
		DrawBoard(numGuessesLeft, ownerPtrHiddenPhrase);
	} while (!IsGameOver(numGuessesLeft, ownerPtrHiddenPhrase, secretPhraseLength));

	DisplayResult(secretPhrase, numGuessesLeft);

	delete[] ownerPtrHiddenPhrase;
	ownerPtrHiddenPhrase = nullptr;
}

int GetSecretPhrase(char secretPhrase[], int maxLength)
{
	bool failure;
	int length;

	do
	{
		failure = false;
		cout << "Please enter the secret phrase: ";
		cin.get(secretPhrase, maxLength);

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << INPUT_ERROR_STRING << endl;
			failure = true;
		}
		else
		{
			length = strlen(secretPhrase);

			if (length == 0)
			{
				cout << "You must enter a word longer than 0 chars." << endl;
				failure = true;
			}
		}
	} while (failure);

	return length;
}

bool WantToPlayAgain()
{
	const char validInputs[] = { 'y', 'n' };
	char response = GetCharacter("Would you like to play again?(y/n) ", INPUT_ERROR_STRING, validInputs, 2);
	return response == 'y';
}

char* MakeHiddenPhrase(const char* secretPhrase, int secretPhraseLength)
{
	char* hiddenPhrase = new char[secretPhraseLength + 1];

	for (int i = 0; i < secretPhraseLength; i++)
	{
		if (secretPhrase[i] != ' ')
		{
			hiddenPhrase[i] = '-';
		}
		else
		{
			hiddenPhrase[i] = ' ';
		}
	}
	hiddenPhrase[secretPhraseLength] = '\0';
	return hiddenPhrase;
}

void DrawBoard(int numGuessesLeft, const char* noPtrHiddenPhrase)
{
	ClearScreen();

	switch (numGuessesLeft)
	{
	case 0:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  / \\" << endl;
		cout << "-+-" << endl;
	}
	break;

	case 1:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  / " << endl;
		cout << "-+-" << endl;
	}
	break;

	case 2:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |    " << endl;
		cout << "-+-" << endl;
	}
	break;

	case 3:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|" << endl;
		cout << " |    " << endl;
		cout << "-+-" << endl;
	}
	break;

	case 4:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |   |" << endl;
		cout << " |    " << endl;
		cout << "-+-" << endl;
	}
	break;

	case 5:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |    " << endl;
		cout << " |    " << endl;
		cout << "-+-" << endl;
	}
	break;

	case 6:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |    " << endl;
		cout << " |    " << endl;
		cout << " |    " << endl;
		cout << "-+-" << endl;
	}
	break;

	default:
		break;
	}

	cout << "Secret phrase: " << noPtrHiddenPhrase << endl;
}

char GetGuess()
{
	return GetCharacter("Please input your guess: ", INPUT_ERROR_STRING);
}

void UpdateBoard(char guess, char * noPtrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int & numGuessesLeft)
{
	bool found = false;

	for (int i = 0; i < secretPhraseLength; i++)
	{
		if (tolower(secretPhrase[i] == guess))
		{
			noPtrHiddenPhrase[i] = secretPhrase[i];
			found = true;
		}
	}

	if (!found)
	{
		numGuessesLeft--;
	}
}

bool IsGameOver(int numGuessesLeft, const char * noPtrHiddenPhrase, int secretPhraseLength)
{
	bool hasDash = false;

	for (int i = 0; i < secretPhraseLength; i++)
	{
		if (noPtrHiddenPhrase[i] == '-')
		{
			hasDash = true;
			break;
		}
	}
	return numGuessesLeft == 0 || !hasDash;
}

void DisplayResult(const char * secretPhrase, int numGuessesLeft)
{
	if (numGuessesLeft > 0)
	{
		cout << "You got it! It was: " << secretPhrase << endl;
	}
	else
	{
		cout << "You didn't get it! It was: " << secretPhrase << endl;
	}
}