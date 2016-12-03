
#pragma once
#include "Point.h"

enum { ROWS = 24, COLS = 80 };

class BoardManager
{
	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
	void handleObjectCreationFromBoard(int row, int col);
public:
	BoardManager(const char originalBoard[ROWS][COLS]);
	~BoardManager();
	void print();
	void setCell(int row, int col, char ch);
	void removeCell(int row, int col);
	bool isWall(const Point& p) {
		return board[p.getY()][p.getX()] == '+';
	}

	void setBoard(const char* boardToCopy[]);
	
};

