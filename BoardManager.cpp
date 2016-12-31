#include "BoardManager.h"
#include <iostream>
#include <string>
#include <map>
#include "_board.h"



BoardManager::BoardManager(MissionBase* mission)
{
	setBoard();
	setMission(mission);
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
	
	Screen::setTextColor(color);
	Screen::setCursor(col, row);
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
	printCell(row, col, color);
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

bool BoardManager::isOccupatiedBySanke(const Point& p)
{
	return board[p.getY()][p.getX()] == GameSettings::SANKE_ONE_BODY_FILL || board[p.getY()][p.getX()] == GameSettings::SANKE_TWO_BODY_FILL;
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

void BoardManager::printNumberByPoint(int randRow, int randCol, int number, Color color)
{
	int digitsNumber = getDigitsNumber(number);
	int tempNum = number;
	numberToPoint[number] = Point(randCol, randRow);

	for (int i = digitsNumber - 1; i >= 0; i--)
	{
		board[randRow][randCol + i] = '0' + tempNum % 10;
		Point pt = Point(randCol + i, randRow);
		pointToNumber[pt] = number;
		printCell(randRow, randCol + i, color);
		tempNum /= 10;
	}
}

void BoardManager::printNumberByPoint(const Point& pt, int number, Color color)
{
	printNumberByPoint(pt.getY(), pt.getX(), number, color);
}

void BoardManager::setNextNumber()
{
	bool isNumberSet = false;
	int randRow, randCol;
	int number = mission->generateNextNumber();

	while (!isNumberSet)
	{
		if (numberToPoint.find(number) != numberToPoint.end())
		{
			number = mission->generateNextNumber();
		}
		else
		{
			randRow = (rand() % (ROWS - 5)) + 4;
			randCol = rand() % COLS;
			if (isValidNumberCell(randRow, randCol, number))
			{
				printNumberByPoint(randRow, randCol, number);
				break;
			}
		}
	}
}

int BoardManager::getNumberInCell(const Point& pt)
{

	if (pointToNumber.find(pt) != pointToNumber.end())
	{
		return pointToNumber.at(pt);
	}
	return -1;
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

void BoardManager::removeNumberByPoint(const Point& pt)
{
	int number = getNumberInCell(pt);
	if (number)
	{
		removeNumberfromBoard(number);
	}

}


void BoardManager::prepareNextStage()
{
	int numberToLeaveOnBoard = numberToPoint.size() / 2;
	while (numberToPoint.size() > 0 && numberToLeaveOnBoard < numberToPoint.size())
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


void BoardManager::resetBoard()
{
	cleanBoard();
	numberToPoint.clear();
	pointToNumber.clear();
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

void BoardManager::blinkPoint(int number, const Point& pt)
{
	printNumberByPoint(pt, number, Color::LIGHTRED);
	Sleep(200);
	printNumberByPoint(pt, number, Color::LIGHTCYAN);
	Sleep(200);
	printNumberByPoint(pt, number, Color::LIGHTGREEN);
	Sleep(200);
	printNumberByPoint(pt, number);
	Sleep(200);
}