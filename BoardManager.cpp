#include "BoardManager.h"
#include "io_utils.h"
#include <iostream>
#include <string>

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

void BoardManager::printCell(int row, int col, Color color)
{
	setTextColor(color);
	gotoxy(col, row);
	std::cout << board[row][col];
	std::cout.flush();
}

void BoardManager::printCell(const Point& pt, Color color)
{
	printCell(pt.getY(), pt.getX(), color);
}

int getDigitsNumber(int number)
{
	int res = 0;
	while (number > 0)
	{
		res++;
		number /= 10;
	}
	return res;
}

bool BoardManager::isValidNumberCell(int row, int col, int number)
{
	if (board[row][col] != ' ')
		return false;

	int digitsNumber = getDigitsNumber(number);

	if (col + digitsNumber > COLS)
		return false;

	for (int i = 0; i < digitsNumber; i++)
	{
		if ((board[row][col + i] != ' ' || // cell itself is empty
			board[row + 1][col + i] != ' ' || // the upper cell is empty
			board[row - 1][col + i] != ' '))
		{
			return false;
		}
	}

	// checking the most left cell if empty or end or board
	if (col - 1 > 0)
		if (board[row][col - 1] != ' ') 
			return false;

	// checking the most right cell if empty or end or board
	if (col + digitsNumber < COLS)
		if (board[row][col + digitsNumber] != ' ') 
			return false;

	return true;
}

void BoardManager::setNextNumber(int number)
{
	bool isNumberSet = false;
	int randRow, randCol;
	while (!isNumberSet)
	{
		randRow = rand() % ROWS;
		randCol = rand() % COLS;
		if (isValidNumberCell(randRow, randCol, number))
		{
			setCell(randRow, randCol, '1');
			printCell(randRow, randCol);
			break;
		}
	}
}

int BoardManager::getCellNumber(const Point& pt)
{
	// TODO Itay; as we talked you should be able to return the number in @pt
	// Maybe you should use Dict(key value) storage for easier fetch.
	return -1;
}

void BoardManager::setBoard(const char* boardToCopy[ROWS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			originalBoard[i][j] = boardToCopy[i][j];
			board[i][j] = originalBoard[i][j];
		}
		originalBoard[i][COLS] = '\0';
		board[i][COLS] = '\0';
	}
}

BoardManager::~BoardManager()
{
	// Todo we should implement desctrouctor logic
}
