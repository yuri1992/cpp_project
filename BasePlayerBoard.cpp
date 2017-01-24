#include "BasePlayerBoard.h"
#include "Point.h"
#include "BoardManager.h"


BasePlayerBoard::BasePlayerBoard(int dir, const Point& pt, BoardManager* _theBoard) : direction(dir), theBoard(_theBoard)
{
	BasePlayerBoard::setPosition(pt);
	startPt = new Point(pt);
}

BasePlayerBoard::BasePlayerBoard(int dir, const Point& pt, BoardManager* _theBoard, char _symbol)
	: direction(dir), symbol(_symbol), theBoard(_theBoard)
{
	BasePlayerBoard::setPosition(pt);
	startPt = new Point(pt);
}

BasePlayerBoard::BasePlayerBoard(int dir, const Point& pt, BoardManager* _theBoard, char _symbol, Color _color)
	: direction(dir), symbol(_symbol), color(_color), theBoard(_theBoard)
{
	BasePlayerBoard::setPosition(pt);
	startPt = new Point(pt);
}

BasePlayerBoard::~BasePlayerBoard()
{
	
}


void BasePlayerBoard::print()
{
	for (const Point& pt : pos)
	{
		theBoard->setCell(pt, getSymbol());
		theBoard->printCell(pt, getColor());
	}
}

void BasePlayerBoard::reset()
{
	if (pos.size() > 0)
	{
		pos[0] = Point(*startPt);
	}
	else
	{
		pos.push_back(Point(*startPt));
	}

}

void BasePlayerBoard::remove()
{
	for (const Point& pt : pos)
	{
		theBoard->removeCell(pt);
		theBoard->printCell(pt);
	};
}

Point BasePlayerBoard::getPosition() const
{
	// head of each played should be in the 0 place of pos vector

	if (pos.size() > 0)
	{
		return pos[0];
	}
	return Point(-1, -1);
}

Point BasePlayerBoard::getNextPosition() const
{
	// Return the next point of the head point at [0]
	if (pos.size() > 0)
	{
		Point pt = pos[0];
		return pt.next(direction);
	}
	return Point(-1, -1);
}

bool BasePlayerBoard::interceptPoint(const Point& interceptPt) const
{
	for (const Point& posPt : pos)
	{
		if (posPt == interceptPt)
			return true;
	};
	return false;
}

void BasePlayerBoard::move()
{
	int dir = getDirection();
	if (!getIsWallWalker())
	{
		Point pt = getPosition();
		if (pt.isBoundry(dir))
		{
			setDirection(getInvertDirection());
		}
	}

	if (pos.size() > 0)
	{
		for (unsigned i = pos.size(); --i > 0;)
		{
			pos[i] = pos[i - 1];
		}
		pos[0].move(dir);
	}
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
