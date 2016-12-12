#ifndef _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

#include "Point.h"
#include <map>
#include "MissionBase.h"
#include "Snake.h"
using namespace std;
//typedef char(&array_type)[ROWS][COLS + 1];
enum
{
	ROWS = 24,
	COLS = 80
};
class Snake;
class BoardManager
{
	
	MissionBase* mission;
	std::map<Point, int> pointToNumber;
	std::map<int, Point> numberToPoint;
	char board[ROWS][COLS + 1]; // this is the actual board we play on, i.e. changes on board are done here

	std::map<int, Point> saver; // will restore the stage from here
public:
	void setMission(MissionBase* _mission) { mission = _mission; }
	BoardManager(MissionBase *mission);
	~BoardManager();

	std::map<Point, int> getPointToNumber() const { return pointToNumber; }

	void setPointToNumber(const std::map<Point, int>& point_to_number) { pointToNumber = point_to_number;
	}

	std::map<int, Point> getNumberToPoint() const
	{
		return numberToPoint;
	}

	void setNumberToPoint(const std::map<int, Point>& number_to_point)
	{
		numberToPoint = number_to_point;
	}

	void saveStage();
	void restoreStage();
	void printBoard();
	void cleanBoard();
	void printBoardWithoutSnakePath();

	void printCell(int row, int col, Color color = Color::LIGHTGREY);
	void printCell(const Point& pt, Color color = Color::LIGHTGREY);
	void printCellWithoutSnake(int row, int col, Color color = Color::LIGHTGREY);

	bool isWall(const Point& p) { return board[p.getY()][p.getX()] == '+'; }

	bool isValidNumberCell(int row, int col, int number);
	void printNumberFromPoint(int rand_row, int rand_col, int number, Color color = Color::LIGHTGREY);
	void printNumberFromPoint(const Point& pt, int number, Color color = Color::LIGHTGREY);
	void setNextNumber(int number);
	int getCellNumber(const Point& pt);
	void setBoard();
	void setCell(int row, int col, char ch) { board[row][col] = ch; }
	void setCell(const Point& pt, char ch) { board[pt.getY()][pt.getX()] = ch; }
	void removeCell(int row, int col) { board[row][col] = ' '; }
	void removeCell(const Point& p) { removeCell(p.getY(), p.getX()); }

	void removeNumberfromBoard(int number);
	void prepareNextStage();
	void blinkPoint(int number, const Point& pt);
	bool findSolveOnBoard();	
	int getNumberOfNumbers();
};

#endif
