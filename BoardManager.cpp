#include "BoardManager.h"
#include "Gotoxy.h"
#include <iostream>

BoardManager::BoardManager(const char originalBoard[ROWS][COLS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			std::cout << originalBoard[i][j];
			std::cout.flush();
			board[i][j] = originalBoard[i][j];
			handleObjectCreationFromBoard(i, j);
		}
		board[i][COLS] = '\0';
	}
}


void BoardManager::setBoard(const char* boardToCopy[ROWS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			originalBoard[i][j] = boardToCopy[i][j];
		}
		originalBoard[i][COLS] = '\0';
	}
}

BoardManager::~BoardManager()
{
}
