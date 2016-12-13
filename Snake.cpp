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
		theBoard->printCell(ptrSnakeBody[i], body->getColor());
	}
}

void Snake::handleKey(int key)
{
	int keyDirection = this->getKeyDirection(key);

	if (keyDirection != -1)
	{
		body->setDirection(keyDirection);
	}

	// TODO :[NOT NOW] handle others keys that can be pressed (fire) 
}


void Snake::move()
{
	if (_isNextStepValid())
	{
		theBoard->removeCell(body->getBody()[body->getCurrentSize() - 1 ]);
		theBoard->printCell(body->getBody()[body->getCurrentSize() - 1 ]);

		body->move();
		printSnake();
	}
}

void Snake::wonStage()
{
	theBoard->removeCell(body->getBody()[body->getCurrentSize() - 1]);
	theBoard->printCell(body->getBody()[body->getCurrentSize() - 1]);

	body->increaseSnakeBody();	
	printSnake();
	points++;
}

void Snake::setArrowKeys(const char* keys)
{
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
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

void Snake::goToStartPoint(const Point& pt)
{
	body->clean();
	body->setPosition(pt);
}

bool Snake::_isNextStepValid()
{
	Point nextPoint = body->getNextPoint();

	if (theBoard->isWall(nextPoint))
		return false;

	if (theBoard->isOccupatiedBySanke(nextPoint))
		return false;

	return true;
}
