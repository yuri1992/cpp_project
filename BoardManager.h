#ifndef _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

#include "Point.h"
#include <map>
#include "MissionBase.h"
using namespace std;
//typedef char(&array_type)[ROWS][COLS + 1];
enum
{
	ROWS = 24,
	COLS = 80
};

class BoardManager
{
	MissionBase* mission;
	std::map<Point, int> pointToNumber;
	std::map<int, Point> numberToPoint;
	char originalBoard[ROWS][COLS + 1]; // this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1]; // this is the actual board we play on, i.e. changes on board are done here
public:
	void setMission(MissionBase* _mission) { mission = _mission; }
	BoardManager(const char* boardToCopy[ROWS], MissionBase *mission);
	~BoardManager();


	void printBoard();
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

	void setCell(int row, int col, char ch) { board[row][col] = ch; }
	void setCell(const Point& pt, char ch) { board[pt.getY()][pt.getX()] = ch; }
	void removeCell(int row, int col) { board[row][col] = ' '; }
	void removeCell(const Point& p) { removeCell(p.getY(), p.getX()); }

	void setBoard(const char* boardToCopy[ROWS]);
	void removeNumberfromBoard(int number);
	void prepareNextStage();
	void blinkPoint(int number, const Point& pt);
	bool findSolveOnBoard();

	int getNumberOfNumbers();
	//void setNumberOfNumbersToZero(); //no need



	
	//typedef char(&array_type)[ROWS][COLS + 1];
	//array_type getOriginalBoard(void);
};

#endif
