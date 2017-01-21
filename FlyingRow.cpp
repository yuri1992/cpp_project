#include "FlyingRow.h"
#include "BoardManager.h"


FlyingRow::~FlyingRow()
{
}

void FlyingRow::destroy()
{
}

void FlyingRow::doNext()
{
	for (int i = 0; i< getSpeed(); i++)
	{
		_doNext();
	}
}

void FlyingRow::_doNext()
{
	BoardManager* _theBoard = getBoard();
	Snake* snake = _theBoard->getSnakeInCell(getNextPosition());

	if (snake != nullptr)
	{
		snake->gotHit();
	}
	else
	{
		// Removing Number is the position
		_theBoard->removeNumberByPoint(getNextPosition());
	}

	remove();
	move();
	print();
}
