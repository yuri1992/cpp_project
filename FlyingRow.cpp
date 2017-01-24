#include "FlyingRow.h"
#include "BoardManager.h"


FlyingRow::~FlyingRow()
{
}

void FlyingRow::destroy()
{
	remove();
	pos.clear();
}

void FlyingRow::doNext()
{
	if (pos.size() == 0)
	{
		return;
	}
	for (int i = 0; i < getSpeed(); i++)
	{
		_doNext();
	}
}

void FlyingRow::_doNext()
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
		else if (playerInterceted->type() == "bullet")
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
