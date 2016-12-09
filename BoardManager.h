#ifndef _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

#include "Point.h"

enum
{
	ROWS = 24,
	COLS = 80
};

class BoardManager
{
	char originalBoard[ROWS][COLS + 1]; // this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1]; // this is the actual board we play on, i.e. changes on board are done here
public:
	BoardManager(const char* boardToCopy[ROWS]);
	~BoardManager();

	void printBoard();

	void printCell(int row, int col, Color color = Color::LIGHTGREY);
	void printCell(const Point& pt, Color color = Color::LIGHTGREY);

	bool isWall(const Point& p) { return board[p.getY()][p.getX()] == '+'; }
	bool isFreeCell(const Point& pt);
	bool isFreeCell(int row, int col);

	bool isValidNumberCell(int row, int col, int number);
	void setNextNumber(int number);
	int getCellNumber(const Point& pt);

	void setCell(int row, int col, char ch) { board[row][col] = ch; }
	void setCell(const Point& pt, char ch) { board[pt.getY()][pt.getX()] = ch; }
	void removeCell(int row, int col) { board[row][col] = ' '; }
	void removeCell(const Point& p) { removeCell(p.getY(), p.getX()); }

	void setBoard(const char* boardToCopy[ROWS]);
};

#endif
