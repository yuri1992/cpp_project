#ifndef _BASE_PLAYER_
#define _BASE_PLAYER_
#include "Point.h"
#include <vector>
class BoardManager;

class BasePlayerBoard
{
public:
	BasePlayerBoard(int direction, const Point& pt, BoardManager* theBoard);
	BasePlayerBoard(int direction, const Point& pt, BoardManager* theBoard, char symbol);
	BasePlayerBoard(int direction, const Point& pt, BoardManager* theBoard, char symbol, Color color);
	virtual ~BasePlayerBoard();
private:
	bool isWallWalker = true;
	int direction;
	int speed = 1;
	char symbol;
	Color color;
	BoardManager* theBoard;
protected:
	vector<Point> pos;
public:

	virtual void print();
	virtual void remove();
	virtual vector<Point> getPositionVector() const { return pos; }
	virtual Point getPosition() const;
	virtual void setPosition(const Point& pos);
	virtual Point getNextPosition() const;
	virtual void destroy() = 0;
	virtual void doNext() = 0;
	virtual void move();

	// getters and setters
	bool getIsWallWalker() const { return isWallWalker; }
	void setIsWallWalker(bool _isWallWalker) { isWallWalker = _isWallWalker; }
	int getSpeed() const { return speed; }
	void setSpeed(int speed) { this->speed = speed; }
	int getDirection() const { return direction; }
	int getInvertDirection() const;
	void setDirection(int _direction)
	{
		this->direction = _direction;
	}
	char getSymbol() const { return symbol; }
	void setSymbol(char _symbol) { this->symbol = _symbol; }
	Color getColor() const { return color; }
	void setColor(Color _color) { this->color = _color; }
	BoardManager* getBoard();
	void setBoard(BoardManager* _theBoard) { this->theBoard = _theBoard; }
};

#endif
