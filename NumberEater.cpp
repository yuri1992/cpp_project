#include "NumberEater.h"
#include "Snake.h"
#include "BoardManager.h"
#include <algorithm>

NumberEater::~NumberEater()
{
}

void NumberEater::destroy()
{
}

bool NumberEater::seekSulotion()
{
	BoardManager* _theBoard = getBoard();
	vector<Point> solutionsPts = _theBoard->getAllSolution();

	if (solutionsPts.empty())
		return false;

	Point pt = getPosition();

	// sorting all solutions points by the disctance from the current position
	std::sort(solutionsPts.begin(), solutionsPts.end(), [&pt]
	          (const Point& lhs, const Point& rhs)
	          {
		          return lhs.distance(pt) < rhs.distance(pt);
	          });

	// take the closet distance
	int distY = solutionsPts[0].getY() - pt.getY();

	if ((distY > 0 && distY <= 10) || distY < -10)
	{
		setDirection(DIRECTION_DOWN);
	}
	else if ((distY < 0 && distY >= -10) || distY > 10)
	{
		setDirection(DIRECTION_UP);
	}
	else if (pt.getY() == solutionsPts[0].getY())
	{
		int distX = solutionsPts[0].getX() - pt.getX();
		if ((distX > 0 && distX <= 40) || distX < -40)
		{
			setDirection(DIRECTION_RIGHT);
		}
		else if ((distX < 0 && distX >= -40) || distX > 40)
		{
			setDirection(DIRECTION_LEFT);
		}
	}
	return true;
}

void NumberEater::_doNext()
{
	if (seekSulotion())
	{
		remove();
		BoardManager* _theBoard = getBoard();
		Point pt = getNextPosition();
		BasePlayerBoard* playerInterceted = _theBoard->getPlayerAtPoint(pt);

		if (playerInterceted != nullptr)
		{
			if (playerInterceted->type() == "snake")
			{
				Snake* snake = static_cast<Snake*>(playerInterceted);
				snake->gotHit();
			}
			else
			{
				return;
			}
		}
		else
		{
			// Removing Number is the position
			_theBoard->removeNumberByPoint(getNextPosition());
		}

		move();
		print();
	}
}

void NumberEater::doNext()
{
	for (int i=0; i< getSpeed(); i++)
	{
		_doNext();
	}
}
