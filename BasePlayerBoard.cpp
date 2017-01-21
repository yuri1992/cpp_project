#include "BasePlayerBoard.h"
#include "Point.h"
#include "BoardManager.h"


BasePlayerBoard::BasePlayerBoard(int direction, const Point& pt, BoardManager* theBoard) : direction(direction), theBoard(theBoard)
{
	BasePlayerBoard::setPosition(pt);
}

BasePlayerBoard::BasePlayerBoard(int direction, const Point& pt, BoardManager* theBoard, char symbol)
	: direction(direction), symbol(symbol), theBoard(theBoard)
{
	BasePlayerBoard::setPosition(pt);
}

BasePlayerBoard::BasePlayerBoard(int direction, const Point& pt, BoardManager* theBoard, char symbol, Color color)
	: direction(direction), symbol(symbol), color(color), theBoard(theBoard)
{
	BasePlayerBoard::setPosition(pt);
}

BasePlayerBoard::~BasePlayerBoard()
{
	// Todo : create decent cotr
}


void BasePlayerBoard::print()
{
	for (Point pt : pos)
	{
		theBoard->setCell(pt, getSymbol());
		theBoard->printCell(pt, getColor());
	}
}

void BasePlayerBoard::remove()
{
	for (Point pt : pos)
	{
		theBoard->removeCell(pt);
		theBoard->printCell(pt);
	};
}

Point BasePlayerBoard::getPosition() const
{
	// head of each played should be in the 0 place of pos vector
	return pos[0];
}

Point BasePlayerBoard::getNextPosition() const
{
	// Return the next point of the head point at [0]
	Point pt = pos[0];
	return pt.next(direction);
}

void BasePlayerBoard::move()
{
//	if (!getIsWallWalker())
//	{
//		Point pt = getPosition();
//		if (pt.isBoundry(getDirection()))
//		{
//			setDirection(getInvertDirection());
//		}
//	}

	if (pos.size() > 0)
	{
		for (unsigned i = pos.size(); --i > 0;)
		{
			pos[i] = pos[i - 1];
		}
	}

	int direction = getDirection();
	pos[0] = pos[0].next(direction);
}

int BasePlayerBoard::getInvertDirection() const
{
	int dir = getDirection();

	if (dir == DIRECTION_UP)
		return DIRECTION_DOWN;
	else if (dir == DIRECTION_DOWN)
		return DIRECTION_UP;
	else if (dir == DIRECTION_LEFT)
		return DIRECTION_RIGHT;

	return DIRECTION_LEFT;
}

BoardManager* BasePlayerBoard::getBoard()
{
	return theBoard;
}

void BasePlayerBoard::setPosition(const Point& newPosition)
{
	if (pos.size() > 0)
	{
		pos[0] = newPosition;
	}
	else
	{
		pos.push_back(newPosition);
	}
}
