#include "FlyingCol.h"
#include "Snake.h"
#include "BoardManager.h"


FlyingCol::~FlyingCol()
{
}

void FlyingCol::destroy()
{
}

void FlyingCol::doNext()
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
