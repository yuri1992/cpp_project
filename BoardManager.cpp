#include "BoardManager.h"
#include "io_utils.h"
#include <iostream>
#include <string>
#include <map>
#include "_board.h"


BoardManager::BoardManager(MissionBase* mission)
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

//	for (int i = 0; i < 2; i++)
//	{
//		Point snakeNestStep = snakes[i]->getNextStep();
//		int rowDiff = std::abs(row - snakeNestStep.getY());
//		int colDiff = std::abs(col - snakeNestStep.getX());
//
//		//i want it to be abit further than 1 step from the head, to still keep it more fair
//		if (rowDiff <= 2 && colDiff <= 2) return false;
//
//	}

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
		pointToNumber[Point(randCol + i, randRow)] = number;
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
			randRow = (rand() % (ROWS - 4)) + 4;
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


//TODO Solve bug, I THINK its going each number and 50% to remove it
//if so tell me ill solve:
//possible solution: get original map size -> iterate on half of the size -> rand()%originalSize -> add it to temp map -> 
// -> remove it from existing (old map) which will shrink by size -> ..
//if we had 60 orignal we will take 30 out randomally (I THINKKKK)
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
		printNumberByPoint(x.second, x.first);
	}
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