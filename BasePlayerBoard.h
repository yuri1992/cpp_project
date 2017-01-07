#pragma once
#include "Point.h"
#include "BoardManager.h"

class BasePlayerBoard
{
public:
	BasePlayerBoard(int direction, Point& pt);
	BasePlayerBoard(int direction, Point& pt, BoardManager* theBoard);
	BasePlayerBoard();
	virtual ~BasePlayerBoard();
private:
	int direction;
	char symbol;
	Point* pos;
	BoardManager* theBoard;
public:
	virtual void doNext();
	virtual Point& getPosition();
	virtual Point& getNextPosition();
	virtual void destory();
	virtual void remove();

	int getDirection() const { return direction; }
	void setDirection(int direction) { this->direction = direction; }
	char getSymbol() const { return direction; }
	void setSymbol(char symbol) { this->symbol = symbol; }
	void setBoard(BoardManager* theBoard) { this->theBoard = theBoard; }
	void setPosition(BoardManager* theBoard);

};

