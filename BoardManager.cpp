#include "BoardManager.h"
#include <iostream>
#include <string>
#include <map>
#include "Snake.h"
#include "MissionBase.h"
#include "FlyingRow.h"
#include "FlyingCol.h"
#include "NumberEater.h"


BoardManager::BoardManager()
{
	// initialize Two Snakes on screen
	snakes = new Snake*[2];
	snakes[0] = new Snake(YELLOW,
	                      GameSettings::SANKE_ONE_BODY_FILL,
	                      this,
	                      "imjln",
	                      Point(10, 9),
	                      DIRECTION_RIGHT);

	snakes[1] = new Snake(LIGHTBLUE,
	                      GameSettings::SANKE_TWO_BODY_FILL,
	                      this,
	                      "wxadz",
	                      Point(70, 9), DIRECTION_LEFT);

	bots = new BasePlayerBoard*[5];
	//bots[0] = new NumberEater(DIRECTION_DOWN, Point(55, 11), this);
	bots[0] = new FlyingCol(DIRECTION_UP, Point(45, 23), this, false);
	bots[1] = new FlyingCol(DIRECTION_DOWN, Point(55, 15), this);
	bots[2] = new FlyingRow(DIRECTION_LEFT, Point(50, 15), this, false);
	bots[3] = new FlyingRow(DIRECTION_RIGHT, Point(30, 23), this);
	bots[4] = new NumberEater(DIRECTION_DOWN, Point(10, 19), this);

	mission = new MissionBase();
}

BoardManager::~BoardManager()
{
	delete snakes[0];
	delete snakes[1];
	delete snakes;

	delete bots[0];
	delete bots[1];
	delete bots[2];
	delete bots[3];
	delete bots[4];
	delete bots;

	delete mission;
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

void BoardManager::printScore() const
{
	Screen::printScoreBoard(mission->getMissionText(),
	                        snakes[0]->getPoints(),
	                        snakes[1]->getPoints());
	printAmmo();
}

void BoardManager::printAmmo() const
{
	Screen::updateSnakesAmmo(snakes[0]->getAmmo(),
	                         snakes[1]->getAmmo());
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

BasePlayerBoard* BoardManager::getPlayerAtPoint(const Point& p) const
{
	for (int i = 0; i < BOTS_PLAYER; i++)
	{
		if (bots[i]->interceptPoint(p))
		{
			return bots[i];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (snakes[i]->interceptPoint(p))
		{
			return snakes[i];
		}
	}
	return nullptr;
}

Snake* BoardManager::getSnakeInCell(const Point& p)
{

	for (int i = 0; i < 2; i++)
	{
		if (snakes[i]->interceptPoint(p))
		{
			return snakes[i];
		}
	}
	return nullptr;
}

bool BoardManager::isOccupatiedBySanke(const Point& p)
{
	for (int i = 0; i < 2; i++)
	{
		if (snakes[i]->interceptPoint(p))
		{
			return true;
		}
	}
	return false;
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

Point BoardManager::getRandomPosition(int size)
{
	bool isNumberSet = false;
	int randRow = 0, randCol = 0;

	while (!isNumberSet)
	{
		randRow = (rand() % (ROWS - 5)) + 4;
		// Snake will be stright line	
		randCol = rand() % (COLS - size);


		// Validating the the cell are free from the other snake
		for (int i = 0; i < size; i ++)
		{
			if (isOccupatiedBySanke(Point(randRow, randCol + i)))
			{
				break;
			}
		}

		// removing all number in those cells (after validating)
		for (int i = 0; i < size; i++)
		{
			removeNumberByPoint(Point(randRow, randCol + i));
		}

		isNumberSet = true;
	}
	Point point = Point(randCol, randRow);
	return point;
}

void BoardManager::setNextNumber()
{
	bool isNumberSet = false;
	int randRow, randCol;
	int number = mission->generateNextNumber();

	while (!isNumberSet)
	{
		auto it = numberToPoint.find(number);
		if (it != numberToPoint.end())
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

void BoardManager::next()
{
	for (int i = 0; i < 2; i++)
	{
		snakes[i]->doNext();
	}
	for (int i = 0; i < BOTS_PLAYER; i ++)
	{
		bots[i]->doNext();
	}
}

bool BoardManager::isGameWon()
{
	for (int i = 0; i < 2; i++)
	{
		if (snakes[i]->isWinGame())
		{
			Screen::printMessageOnBoard("Won The game!!");
			return true;
		}
	}
	return false;
}
void BoardManager::handleKey(char key)
{
	for (int i = 0; i < 2; i++)
	{
		snakes[i]->handleKey(key);
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

bool BoardManager::removeNumberByPoint(const Point& pt)
{
	int number = getNumberInCell(pt);
	if (number > -1)
	{
		removeNumberfromBoard(number);
		return true;
	}
	return false;
}


void BoardManager::prepareNextStage()
{
	int numberToLeaveOnBoard = numberToPoint.size() / 2;
	while (numberToPoint.size() > 0 && numberToLeaveOnBoard < numberToPoint.size())
	{
		for (auto x : numberToPoint)
		{
			if (rand() % 2 == 0)
			{
				removeNumberfromBoard(x.first);
				break;
			}
		}
	}

	mission->nextMission();
	snakes[0]->resetGun();
	snakes[1]->resetGun();
}

bool BoardManager::findSolveOnBoard()
{
	bool hasSolotion = false;
	for (auto x : numberToPoint)
	{
		if (mission->isSolved(x.first))
		{
			blinkPoint(x.first, x.second);
			hasSolotion = true;
		}
	}
	return hasSolotion;
}

vector<Point> BoardManager::getAllSolution()
{
	vector<Point> sol;
	for (auto x : numberToPoint)
	{
		if (mission->isSolved(x.first))
		{
			sol.push_back(x.second);
		}
	}
	return sol;
}

int BoardManager::getNumberAmountOnBoard() const
{
	return numberToPoint.size();
}

void BoardManager::resetBoard()
{
	cleanBoard();
	numberToPoint.clear();
	pointToNumber.clear();

	snakes[0]->goToPoint(Point(10, 9), DIRECTION_RIGHT);
	snakes[0]->setStatus(SnakeStatus::REGULAR);
	snakes[0]->resetGun();


	snakes[1]->goToPoint(Point(70, 9), DIRECTION_LEFT);
	snakes[1]->setStatus(SnakeStatus::REGULAR);
	snakes[1]->resetGun();
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
