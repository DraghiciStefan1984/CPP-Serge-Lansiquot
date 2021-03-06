// Battleships.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

const char * INPUT_ERROR_STRING = "Input error, please try again!";

enum { Aicraft_Carrier_Size = 5, Battleship_Size = 4, Cruiser_Size = 3, Destroyer_Size = 3, Submarine_Size = 2, 
	Board_Size = 10, Num_Ships = 5, Player_Name_Size = 8, Max_Ship_Size = Aicraft_Carrier_Size };
enum ShipType { ST_None = 0, ST_Aicraft_Carrier, ST_Battleship, ST_Cruiser, ST_Destroyer, ST_Submarine };
enum ShipOrientationType { SOT_Horizontal = 0, SOT_Vertical = 1 };
enum GuessType { GT_None = 0, GT_Missed, GT_Hit };
enum PlayerType { PT_Human = 0, PT_AI };

struct ShipPositionType
{
	int row;
	int column;
};

struct Ship
{
	ShipType shipType;
	int shipSize;
	ShipOrientationType orientation;
	ShipPositionType position;
};

struct ShipPartType
{
	ShipType shipType;
	bool isHit;
};

struct Player
{
	char playerName[Player_Name_Size];
	Ship ships[Num_Ships];
	GuessType guessBoard[Board_Size][Board_Size];
	ShipPartType shipBoard[Board_Size][Board_Size];
	PlayerType playerType;
};

void InitializePlayer(Player& player, const char * playerName);
void InitializeShip(Ship& ship, int shipSize, ShipType shipType);
void PlayGame(Player& player1, Player& player2);
bool WantToPlayAgain();
void SetupBoards(Player& player);
void ClearBoards(Player& player);
void DrawBoards(Player& player);
void DrawSeparatorLine();
void DrawShipBoardRow(const Player& player, int row);
void DrawGuessBoardRow(const Player& player, int row);
char GetShipRepresentation(const Player& player, int row, int column);
char GetGuessRepresentation(const Player& player, int row, int column);
const char * GetShipNameForShipType(ShipType shipType);
ShipPositionType GetBoardPoistion();
ShipPositionType MapBoardPosition(char rowInput, int columnInput);
ShipOrientationType GetShipOrientation();
bool IsValidPlacement(const Player& player, const Ship& currentShip, const ShipPositionType& shipPosition, const ShipOrientationType& shipOrientation);
void PlaceShipOnBoard(Player& player, Ship& currentShip, const ShipPositionType& shipPosition, const ShipOrientationType& shipOrientation);
ShipType UpdateBoards(ShipPositionType guess, Player& currentPlayer, Player& otherPlayer);
bool IsGameOver(const Player& player1, const Player& player2);
bool AreAllShipsSunk(const Player& player);
bool IsSunk(const Player& player, const Ship& ship);
void SwitchPlayers(Player ** currentPlayer, Player ** otherPlayer);
void DisplayWinner(const Player& player1, const Player& player2);
PlayerType GetPlayer2Type();
ShipPositionType GetAIGuess(const Player& aiPlayer);
ShipPositionType GetRandomPosition();
void SetupAIBoards(Player& player);

int main()
{
	srand(time(NULL));

	Player player1;
	Player player2;

	InitializePlayer(player1, "Player1");
	InitializePlayer(player2, "Player2");

	do
	{
		PlayGame(player1, player2);
	} while (WantToPlayAgain());

	return 0;
}

void InitializePlayer(Player& player, const char * playerName)
{
	if (playerName != nullptr && strlen(playerName) > 0)
	{
		strcpy_s(player.playerName, playerName);
	}

	InitializeShip(player.ships[0], Aicraft_Carrier_Size, ST_Aicraft_Carrier);
	InitializeShip(player.ships[1], Battleship_Size, ST_Battleship);
	InitializeShip(player.ships[2], Cruiser_Size, ST_Cruiser);
	InitializeShip(player.ships[3], Destroyer_Size, ST_Destroyer);
	InitializeShip(player.ships[4], Submarine_Size, ST_Submarine);
}

void InitializeShip(Ship& ship, int shipSize, ShipType shipType)
{
	ship.shipType = shipType;
	ship.shipSize = shipSize;
	ship.position.row = 0;
	ship.position.column = 0;
	ship.orientation = SOT_Horizontal;
}

void PlayGame(Player& player1, Player& player2)
{
	player1.playerType = PT_Human;
	player2.playerType = GetPlayer2Type();

	SetupBoards(player1);
	SetupBoards(player2);

	Player* currentPlayer = &player1;
	Player* otherPlayer = &player2;

	ShipPositionType guess;

	do
	{
		if (currentPlayer->playerType == PT_Human)
		{
			DrawBoards(*currentPlayer);
		}

		bool isValidGuess;

		do
		{
			if (currentPlayer->playerType == PT_Human)
			{
				cout << currentPlayer->playerName << " what is your guess? " << endl;
				guess = GetBoardPoistion();
			}
			else
			{
				guess = GetAIGuess(*currentPlayer);
			}

			isValidGuess = currentPlayer->guessBoard[guess.row][guess.column] == GT_None;

			if (!isValidGuess)
			{
				cout << "That was not a valid guess, try again!" << endl;
			}
		} while (!isValidGuess);

		ShipType shipType = UpdateBoards(guess, *currentPlayer, *otherPlayer);

		if (currentPlayer->playerType == PT_AI)
		{
			DrawBoards(*otherPlayer);
			cout << currentPlayer->playerName << " chose row" << char(guess.row + 'A') << " and column " << guess.column + 1 << endl;
		}
		else
		{
			DrawBoards(*currentPlayer);
		}

		if (shipType != ST_None && IsSunk(*otherPlayer, otherPlayer->ships[shipType - 1]))
		{
			if (currentPlayer->playerType == PT_AI)
			{
				cout << currentPlayer->playerName << " sunt your " << GetShipNameForShipType(shipType) << "!" << endl;
			}
			else
			{
				cout << "You sunk " << otherPlayer->playerName << "'s " << GetShipNameForShipType(shipType) << "!" << endl;
			}
		}
		WaitForKeyPress();
		SwitchPlayers(&currentPlayer, &otherPlayer);
	} while (!IsGameOver(player1, player2));
	DisplayWinner(player1, player2);
}

bool WantToPlayAgain()
{
	char input;
	const char validInput[2] = { 'y', 'n' };
	input = GetCharacter("Would you like to play again? (y/n)", INPUT_ERROR_STRING, validInput, 2, CC_LOWER_CASE);
	return input == 'y';
}

void SetupBoards(Player& player)
{
	ClearBoards(player);

	if (player.playerType == PT_AI)
	{
		SetupAIBoards(player);
		return;
	}

	for (int i = 0; i < Num_Ships; i++)
	{
		DrawBoards(player);
		Ship& currentShip = player.ships[i];
		ShipPositionType shipPosition;
		ShipOrientationType shipOrientation;
		bool isValidPlacement = false;

		do
		{
			cout << player.playerName << " please set the position and orientation for your " << GetShipNameForShipType(currentShip.shipType) << endl;
			shipPosition = GetBoardPoistion();
			shipOrientation = GetShipOrientation();
			isValidPlacement = IsValidPlacement(player, currentShip, shipPosition, shipOrientation);

			if (!isValidPlacement)
			{
				cout << "That was not a valid placement, please try again!" << endl;
			}
		} while (!isValidPlacement);

		PlaceShipOnBoard(player, currentShip, shipPosition, shipOrientation);
	}
	DrawBoards(player);
	WaitForKeyPress();
}

void ClearBoards(Player& player)
{
	for (int row = 0; row < Board_Size; row++)
	{
		for (int column = 0; column < Board_Size; column++)
		{
			player.guessBoard[row][column] = GT_None;
			player.shipBoard[row][column].shipType = ST_None;
			player.shipBoard[row][column].isHit = false;
		}
	}
}

void DrawSeparatorLine()
{
	cout << " ";
	for (int column = 0; column < Board_Size; column++)
	{
		cout << "+---";
	}
	cout << "+";
}

void DrawColumnsRow()
{
	cout << "  ";
	for (int column = 0; column < Board_Size; column++)
	{
		int columnName = column + 1;
		cout << " " << columnName << "  ";
	}
}

void DrawShipBoardRow(const Player& player, int row)
{
	char rowName = row + 'A';
	cout << rowName << "|";
	for (int column = 0; column < Board_Size; column++)
	{
		cout << " " << GetShipRepresentation(player, row, column) << " |";
	}
}

void DrawGuessBoardRow(const Player& player, int row)
{
	char rowName = row + 'A';
	cout << rowName << "|";
	for (int column = 0; column < Board_Size; column++)
	{
		cout << " " << GetGuessRepresentation(player, row, column) << " |";
	}
}

void DrawBoards(Player& player)
{
	ClearScreen();
	DrawColumnsRow();
	DrawColumnsRow();
	cout << endl;

	for (int row = 0; row < Board_Size; row++)
	{
		DrawSeparatorLine();
		cout << " ";
		DrawSeparatorLine();
		cout << endl;
		DrawShipBoardRow(player, row);
		cout << " ";
		DrawGuessBoardRow(player, row) ;
		cout << endl;
	}
	DrawSeparatorLine();
	cout << " ";
	DrawSeparatorLine();
	cout << endl;
}

char GetShipRepresentation(const Player& player, int row, int column)
{
	if (player.shipBoard[row][column].isHit)
	{
		return '*';
	}

	if (player.shipBoard[row][column].shipType==ST_Aicraft_Carrier)
	{
		return 'A';
	}
	else if (player.shipBoard[row][column].shipType == ST_Battleship)
	{
		return 'B';
	}
	else if (player.shipBoard[row][column].shipType == ST_Cruiser)
	{
		return 'C';
	}
	else if (player.shipBoard[row][column].shipType == ST_Destroyer)
	{
		return 'D';
	}
	else if (player.shipBoard[row][column].shipType == ST_Submarine)
	{
		return 'S';
	}
	else
	{
		return ' ';
	}
}

char GetGuessRepresentation(const Player& player, int row, int column)
{
	if (player.guessBoard[row][column] == GT_Hit)
	{
		return '*';
	}
	else if (player.guessBoard[row][column] == GT_Missed)
	{
		return 'o';
	}
	else
	{
		return ' ';
	}
}

const char * GetShipNameForShipType(ShipType shipType)
{
	if (shipType == ST_Aicraft_Carrier)
	{
		return "Aicraft carrier";
	}
	else if (shipType == ST_Battleship)
	{
		return "Battleship";
	}
	else if (shipType == ST_Destroyer)
	{
		return "Destroyer";
	}
	else if (shipType == ST_Cruiser)
	{
		return "Cruiser";
	}
	else if (shipType == ST_Submarine)
	{
		return "Submarine";
	}
	return "None";
}

ShipPositionType GetBoardPoistion()
{
	char rowInput;
	int columnInput;
	const char validRowsInputs[] = { 'A','B','C','D','E','F','G','H','I','J' };
	const int validColumnInputs[] = { 1,2,3,4,5,6,7,8,9,10 };
	rowInput = GetCharacter("Please enter a row (A-J): ", INPUT_ERROR_STRING, validRowsInputs, Board_Size, CC_UPPER_CASE);
	columnInput = GetInteger("Please enter a column (1-10): ", INPUT_ERROR_STRING, validColumnInputs, Board_Size);
	return MapBoardPosition(rowInput, columnInput);
}

ShipPositionType MapBoardPosition(char rowInput, int columnInput)
{
	int realRow = rowInput - 'A';
	int realColumn = columnInput - 1;
	ShipPositionType boardPosition;
	boardPosition.row = realRow;
	boardPosition.column = realColumn;
	return boardPosition;
}

ShipOrientationType GetShipOrientation()
{
	ShipOrientationType orientation;
	const char validInput[2] = { 'H', 'V' };
	char input = GetCharacter("Please choose an orientation (H) for horizontal, (V) for verical: ", INPUT_ERROR_STRING, validInput, 2, CC_UPPER_CASE);

	if (input == validInput[0])
	{
		return SOT_Horizontal;
	}
	else
	{
		return SOT_Vertical;
	}
}

bool IsValidPlacement(const Player& player, const Ship& currentShip, const ShipPositionType& shipPosition, const ShipOrientationType& shipOrientation)
{
	if (shipOrientation == SOT_Horizontal)
	{
		for (int column = shipPosition.column; column < (shipPosition.column + currentShip.shipSize); column++)
		{
			if (player.shipBoard[shipPosition.row][column].shipType != ST_None || column >= Board_Size)
			{
				return false;
			}
		}
	}
	else
	{
		for (int row = shipPosition.row; row < (shipPosition.row + currentShip.shipSize); row++)
		{
			if (player.shipBoard[row][shipPosition.column].shipType != ST_None || row >= Board_Size)
			{
				return false;
			}
		}
	}
	return true;
}

void PlaceShipOnBoard(Player& player, Ship& currentShip, const ShipPositionType& shipPosition, const ShipOrientationType& shipOrientation)
{
	currentShip.position = shipPosition;
	currentShip.orientation = shipOrientation;

	if (shipOrientation == SOT_Horizontal)
	{
		for (int column = shipPosition.column; column < (shipPosition.column + currentShip.shipSize); column++)
		{
			player.shipBoard[shipPosition.row][column].shipType = currentShip.shipType;
			player.shipBoard[shipPosition.row][column].isHit = false;
		}
	}
	else
	{
		for (int row = shipPosition.row; row < (shipPosition.row + currentShip.shipSize); row++)
		{
			player.shipBoard[row][shipPosition.column].shipType = currentShip.shipType;
			player.shipBoard[row][shipPosition.column].isHit = false;
		}
	}
}

ShipType UpdateBoards(ShipPositionType guess, Player& currentPlayer, Player& otherPlayer)
{
	if (otherPlayer.shipBoard[guess.row][guess.column].shipType != ST_None)
	{
		currentPlayer.guessBoard[guess.row][guess.column] = GT_Hit;
		otherPlayer.shipBoard[guess.row][guess.column].isHit = true;
	}
	else
	{
		currentPlayer.guessBoard[guess.row][guess.column] = GT_Missed;
	}
	return otherPlayer.shipBoard[guess.row][guess.column].shipType;
}

bool IsGameOver(const Player& player1, const Player& player2)
{
	return AreAllShipsSunk(player1) || AreAllShipsSunk(player2);
}

bool AreAllShipsSunk(const Player& player)
{
	for (int i = 0; i < Num_Ships; i++)
	{
		if (!IsSunk(player, player.ships[i]))
		{
			return false;
		}
	}
	return true;
}

bool IsSunk(const Player& player, const Ship& ship)
{
	if (ship.orientation == SOT_Horizontal)
	{
		for (int column = ship.position.column; column < (ship.position.column + ship.shipSize); column++)
		{
			if (!player.shipBoard[ship.position.row][column].isHit)
			{
				return false;
			}
		}
	}
	else
	{
		for (int row = ship.position.row; row < (ship.position.row + ship.shipSize); row++)
		{
			if (!player.shipBoard[row][ship.position.column].isHit)
			{
				return false;
			}
		}
	}
	return true;
}

void SwitchPlayers(Player ** currentPlayer, Player ** otherPlayer)
{
	Player* tempPlayer = *currentPlayer;
	*currentPlayer = *otherPlayer;
	*otherPlayer = tempPlayer;
}

void DisplayWinner(const Player& player1, const Player& player2)
{
	if (AreAllShipsSunk(player1))
	{
		cout << "Congratulations " << player2.playerName << ", you won!" << endl;
	}
	else
	{
		cout << "Congratulations " << player1.playerName << ", you won!" << endl;
	}
}

PlayerType GetPlayer2Type()
{
	const int validInputs[2] = { 1, 2 };
	int input = GetInteger("Who would you like to play against?\n1.Human\n2.AI\n\nWhat is your choice?", INPUT_ERROR_STRING, validInputs, 2);

	if (input == 1)
	{
		return PT_Human;
	}
	else
	{
		return PT_AI;
	}
}

ShipPositionType GetAIGuess(const Player& aiPlayer)
{
	return GetRandomPosition();
}

ShipPositionType GetRandomPosition()
{
	ShipPositionType guess;
	guess.row = rand() % Board_Size;
	guess.column = rand() % Board_Size;
	return guess;
}

void SetupAIBoards(Player& player)
{
	ShipPositionType position;
	ShipOrientationType orientation;

	for (int i = 0; i < Num_Ships; i++)
	{
		Ship& currentShip = player.ships[i];

		do
		{
			position = GetRandomPosition();
			orientation = ShipOrientationType(rand() % 2);
		} while (!IsValidPlacement(player, currentShip, position, orientation));
		PlaceShipOnBoard(player, currentShip, position, orientation);
	}
}