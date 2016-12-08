#include "Snake.h"
#include "TheGame.h"

Snake::Snake(Color color, char bodyChar, BoardManager* theBoard,
             const char* keys, Point startPoint, Direction dir = DIRECTION_UP)
{
	setBoardManager(theBoard);
	setArrowKeys(keys);
	body = new SnakeBody(dir, bodyChar, color, startPoint);
}

void Snake::printSnake()
{
	Point* ptrSnakeBody = body->getBody();
	char ch = body->getBodyChar();
	for (int i = 0; i < body->getCurrentSize(); i ++)
	{
		theBoard->setCell(ptrSnakeBody[i], ch);
		setTextColor(body->getColor());
		theBoard->printCell(ptrSnakeBody[i]);
	}
}

void Snake::handleKey(int key)
{
	int keyDirection = this->getKeyDirection(key);

	if (keyDirection != -1)
	{
		body->setDirection(keyDirection);
	}

	// Todo : handle others keys that can be pressed (fire)
}

void Snake::move()
{
	if (_isNextStepValid())
	{
		body->move();
		printSnake();
	}
}

int Snake::getKeyDirection(char key)
{
	for (int i = 0; i < KEYS_SIZE; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}

bool Snake::_isNextStepValid()
{
	Point nextPoint = body->getNextPoint();

	if (theBoard->isWall(nextPoint))
		return false;

	// Todo: should be handled cases when there already a snake in the @nextPoint
	// should check with @boardManager if the cell is free


	return true;
}
