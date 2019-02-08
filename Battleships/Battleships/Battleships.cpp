// Battleships.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Utils.h"
#include <iostream>
#include <cstring>

using namespace std;

const char * INPUT_ERROR_STRING = "Input error, please try again!";

enum { Aicraft_Carrier_Size = 5, Battleship_Size = 4, Cruiser_Size = 3, Destroyer_Size = 3, Submarine_Size = 2, 
	Board_Size = 10, Num_Ships = 5, Player_Name_Size = 8, Max_Ship_Size = Aicraft_Carrier_Size };
enum ShipType { ST_None = 0, ST_Aicraft_Carrier, ST_Battleship, ST_Cruiser, ST_Destroyer, ST_Submarine };
enum ShipOrientationType { SOT_Horizontal = 0, SOT_Vertical = 1 };
enum GuessType { GT_None = 0, GT_Missed, GT_Hit };

struct ShipPositionType
{
	int row;
	int column;
};

struct Ship
{
	ShipType shipType;
	int shipSize;
	ShipOrientationType shipOrientation;
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
};

void InitializePlayer(Player& player, const char * playerName);
void InitializeShip(Ship& ship, int shipSize, ShipType shipType);
void PlayGame(Player& player1, Player& player2);
bool WantToPlayAgain();

int main()
{
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
		strcpy(player.playerName, playerName);
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
	ship.shipOrientation = SOT_Horizontal;
}

void PlayGame(Player& player1, Player& player2)
{

}

bool WantToPlayAgain()
{
	char input;
	const char validInput[2] = { 'y', 'n' };
	input = GetCharacter("Would you like to play again? (y/n)", INPUT_ERROR_STRING, validInput, 2, CC_LOWER_CASE);
	return input == 'y';
}