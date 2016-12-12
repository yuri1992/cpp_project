#include "BoardManager.h"
#include "io_utils.h"
#include <iostream>
#include <string>
#include <map>
#include "_board.h"


BoardManager::BoardManager( MissionBase* mission)
{
	setBoard();
	setMission(mission);
	saver = getNumberToPoint();
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

void BoardManager::cleanBoard()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			removeCell(i, j);
			printCell(i, j);
		}
	}
}


//the function printBoard - printed the history of the snakes (full path they walked)
//so when continuing i run this function. (TEMP SOLUTION)
void BoardManager::printBoardWithoutSnakePath()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			//that runs this fun that just prints empty whenever it sees a snake
			printCellWithoutSnake(i, j);
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


void BoardManager::printCellWithoutSnake(int row, int col, Color color)
{
	if (board[row][col] == '@' || board[row][col] == '#') return;
	setTextColor(color);
	gotoxy(col, row);
	std::cout << board[row][col];
	std::cout.flush();
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

void BoardManager::printNumberFromPoint(int randRow, int randCol, int number, Color color)
{
	int digitsNumber = getDigitsNumber(number);
	int tempNum = number;
	numberToPoint[number] = Point(randCol, randRow);

	for (int i = digitsNumber - 1; i >= 0; i--)
	{
		board[randRow][randCol + i] = '0' + tempNum % 10;
		pointToNumber[Point(randCol + i, randRow)] = number;
		printCell(randRow, randCol + i, color);
		tempNum /= 10;
	}
}

void BoardManager::printNumberFromPoint(const Point& pt, int number, Color color)
{
	printNumberFromPoint(pt.getY(), pt.getX(), number, color);
}

void BoardManager::setNextNumber(int number)
{
	bool isNumberSet = false;
	int randRow, randCol;
	while (!isNumberSet)
	{
		randRow = (rand() % (ROWS - 4)) + 4;
		randCol = rand() % COLS;
		if (isValidNumberCell(randRow, randCol, number))
		{
			printNumberFromPoint(randRow, randCol, number);
			break;
		}
	}
}

int BoardManager::getCellNumber(const Point& pt)
{
	if (pointToNumber.find(pt) != pointToNumber.end())
	{
		return pointToNumber.at(pt);
	}
	return -1;
}

void BoardManager::setBoard()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[i][j] = board_example[i][j];
		}
		board[i][COLS] = '\0';
	}
}

void BoardManager::removeNumberfromBoard(int number)
{
	if (numberToPoint.find(number) != numberToPoint.end())
	{
		Point pt = numberToPoint.at(number);
		int digits = getDigitsNumber(number);
		for (int i = 0; i < digits; i++)
		{
			Point tmpPt = Point(pt.getX() + i, pt.getY());
			pointToNumber.erase(tmpPt);
			removeCell(tmpPt);
			printCell(tmpPt);
		}

		// lets delete the number
		numberToPoint.erase(number);
	}
}

void BoardManager::prepareNextStage()
{
	int numbersOnBoard = numberToPoint.size();
	while (numberToPoint.size() > 0 && numbersOnBoard / 2 <= numberToPoint.size())
	{
		for (auto const& x : numberToPoint)
		{
			if (rand() % 2 == 0)
			{
				removeNumberfromBoard(x.first);
				break;
			}
		}
	}
}

void BoardManager::blinkPoint(int number, const Point& pt)
{
	printNumberFromPoint(pt, number, Color::LIGHTRED);
	Sleep(200);			 
	printNumberFromPoint(pt, number, Color::LIGHTCYAN);
	Sleep(200);			 
	printNumberFromPoint(pt, number, Color::LIGHTGREEN);
	Sleep(200);			 
	printNumberFromPoint(pt, number);
	Sleep(200);
}

bool BoardManager::findSolveOnBoard()
{
	bool hasSolotion = false;
	for (auto const& x : numberToPoint)
	{
		if (mission->isSolved(x.first))
		{
			blinkPoint(x.first, x.second);
			hasSolotion = true;
		}
	}
	return hasSolotion;
}

int BoardManager::getNumberOfNumbers()
{
	return numberToPoint.size();
}

//void BoardManager::setNumberOfNumbersToZero()
//{
//deprecated for now
	//(need to tell it that there is zero numbers on the board, so countdown will begin fresh from 0 //for restartStage and NextStage from menu
//}


//array_type BoardManager::getOriginalBoard()
//{
//	return originalBoard;
//}

BoardManager::~BoardManager()
{

	// Todo we should implement desctrouctor logic
}

void BoardManager::saveStage()
{
	saver = getNumberToPoint();
}

void BoardManager::restoreStage()
{
	cleanBoard();
	numberToPoint.clear();
	pointToNumber.clear();
	for (auto const& x : saver)
	{
		printNumberFromPoint(x.second, x.first);
	}
}