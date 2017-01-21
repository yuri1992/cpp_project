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
	remove();
	move();

	BoardManager* theBoard = getBoard();
	Snake* snake = theBoard->getSnakeInCell(getPosition());

	if (snake != nullptr)
	{
		snake->gotHit();
	}
	else
	{
		// Removing Number is the position
		theBoard->removeNumberByPoint(getPosition());
	}

	print();
}
