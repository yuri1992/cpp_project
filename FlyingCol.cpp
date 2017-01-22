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
		_theBoard->removeNumberByPoint(pt);
	}

	remove();
	move();
	print();
}
