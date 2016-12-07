#include "BoardManager.h"
#include "io_utils.h"
#include <iostream>

void BoardManager::handleObjectCreationFromBoard(int row, int col)
{
}

BoardManager::BoardManager(const char* boardToCopy[ROWS])
{
	setBoard(boardToCopy);
}

void BoardManager::printBoard()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			printCell(i, j);
		}
	}
}

void BoardManager::printCell(int row, int col)
{
	gotoxy(col, row);
	std::cout << board[row][col];
	std::cout.flush();
}

void BoardManager::printCell(Point pt)
{
	int row = pt.getY();
	int col = pt.getX();

	gotoxy(col, row);
	std::cout << board[row][col];
	std::cout.flush();
}

void BoardManager::setCell(int row, int col, char ch)
{
	board[row][col] = ch;
}

void BoardManager::setCell(Point pt, char ch)
{
	board[pt.getY()][pt.getX()] = ch;
}

void BoardManager::removeCell(int row, int col)
{
	board[row][col] = ' ';
}

void BoardManager::setBoard(const char* boardToCopy[ROWS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			originalBoard[i][j] = boardToCopy[i][j];
			board[i][j] = originalBoard[i][j];
			handleObjectCreationFromBoard(i, j);
		}
		originalBoard[i][COLS] = '\0';
		board[i][COLS] = '\0';
	}
}

BoardManager::~BoardManager()
{
}


