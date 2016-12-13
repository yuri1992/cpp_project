#ifndef _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

#include "Point.h"
#include <map>
#include "MissionBase.h"
#include "GameSettings.h"

using namespace std;

enum
{
	ROWS = 24,
	COLS = 80
};

class BoardManager
{
	///Snake** snakes;
	MissionBase* mission;
	std::map<Point, int> pointToNumber;
	std::map<int, Point> numberToPoint;
	char board[ROWS][COLS + 1]; // this is the actual board we play on, i.e. changes on board are done here
	std::map<int, Point> saver; // will restore the stage from here
public:
	BoardManager(MissionBase* mission);

	void saveStage();
	void resetBoard();
	void restoreStage();

	void printBoard();
	void cleanBoard();
	void printBoardWithoutSnakePath();
	void printCell(int row, int col, Color color = Color::LIGHTGREY);
	void printCell(const Point& pt, Color color = Color::LIGHTGREY);
	void printCellWithoutSnake(int row, int col, Color color = Color::LIGHTGREY);
	void setCell(int row, int col, char ch) { board[row][col] = ch; }
	void setCell(const Point& pt, char ch) { board[pt.getY()][pt.getX()] = ch; }
	void removeCell(int row, int col) { board[row][col] = ' '; }
	void removeCell(const Point& p) { removeCell(p.getY(), p.getX()); }

	bool isWall(const Point& p) { return board[p.getY()][p.getX()] == '+'; }
	bool isOccupatiedBySanke(const Point& p);

	bool isValidNumberCell(int row, int col, int number);
	void printNumberByPoint(int rand_row, int rand_col, int number, Color color = Color::LIGHTGREY);
	void printNumberByPoint(const Point& pt, int number, Color color = Color::LIGHTGREY);
	int getNumberInCell(const Point& pt);
	void setNextNumber();

	void removeNumberfromBoard(int number);
	void prepareNextStage();
	void blinkPoint(int number, const Point& pt);
	bool findSolveOnBoard();
	int getNumberOfNumbers();

	// getters setters
	void setBoard();
	std::map<Point, int> getPointToNumber() const { return pointToNumber; }
	void setPointToNumber(const std::map<Point, int>& point_to_number) { pointToNumber = point_to_number; }
	std::map<int, Point> getNumberToPoint() const { return numberToPoint; }
	void setNumberToPoint(const std::map<int, Point>& number_to_point) { numberToPoint = number_to_point; }
	void setMission(MissionBase* _mission) { mission = _mission; }
};

#endif
