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
