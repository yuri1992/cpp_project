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
	void handleObjectCreationFromBoard(int row, int col);
public:
	BoardManager(const char* boardToCopy[ROWS]);
	~BoardManager();
	void printCell(int row, int col);
	void printCell(Point pt);
	void printBoard();
	void removeCell(int row, int col);
	bool isWall(const Point& p) { return board[p.getY()][p.getX()] == '+'; }
	void setCell(int row, int col, char ch);
	void setCell(Point pt, char ch);
	void setBoard(const char* boardToCopy[ROWS]);
};

#endif
