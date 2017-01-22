#include "FlyingCol.h"
#include "Snake.h"
#include "BoardManager.h"


FlyingCol::~FlyingCol()
{
}

void FlyingCol::destroy()
{
	remove();
	pos.clear();
}

void FlyingCol::doNext()
{
	BoardManager* _theBoard = getBoard();
	Point pt = getNextPosition();
	BasePlayerBoard* playerInterceted = _theBoard->getPlayerAtPoint(pt);

	if (playerInterceted != nullptr)
	{
		string type = playerInterceted->type();
		if (type == "snake")
		{
			playerInterceted->destroy();
		}
		else
		{
			return;
		}
	}
	else
	{
		// Removing Number is the position
		_theBoard->removeNumberByPoint(pt);
	}

	remove();
	move();
	print();
}
