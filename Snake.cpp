#include "Snake.h"
#include "BoardManager.h"
#include "Point.h"

Snake::Snake(Color color, char bodyChar, BoardManager* boardManager,
             const char* keys, Point startPoint, Direction dir = DIRECTION_UP)
{
	setBoardManager(boardManager);
	setArrowKeys(keys);
	gun.setBoard(boardManager);
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
	else if (key == getShottingKey())
	{
		shoot();
	}
}


void Snake::move()
{
	if (_isNextStepValid())
	{
		theBoard->removeCell(body->getBody()[body->getCurrentSize() - 1]);
		theBoard->printCell(body->getBody()[body->getCurrentSize() - 1]);

		body->move();
		printSnake();
	}
}

void Snake::shoot()
{
	gun.shoot(body->getBody()[0], body->getDirection());
}

void Snake::wonStage()
{
	theBoard->removeCell(body->getBody()[body->getCurrentSize() - 1]);
	theBoard->printCell(body->getBody()[body->getCurrentSize() - 1]);

	body->increaseSnakeBody();

	if (status == SnakeStatus::REGULAR)
	{
		printSnake();
	}
	points++;
}

void Snake::setArrowKeys(const char* keys)
{
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
}

void Snake::resetGun()
{
	gun.reset();
}

void Snake::doNext()
{
	if (status == SnakeStatus::HIT && steps == GameSettings::RELIVE_AFTER_STEPS)
	{
		status = SnakeStatus::REGULAR;
		steps = 0;
		Point pt = theBoard->getRandomPosition(body->getCurrentSize());
		goToPoint(pt);
	}

	gun.doNext();

	if (status == SnakeStatus::REGULAR)
		move();
	else
		steps++;

	theBoard->printAmmo();
}

int Snake::getKeyDirection(char key)
{
	for (int i = 0; i < KEYS_SIZE - 1; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}

void Snake::goToPoint(const Point& pt)
{
	body->clean();
	body->setPosition(pt);
}

void Snake::goToPoint(const Point& pt, int direction)
{
	goToPoint(pt);
	setSnakeDirection(direction);
}

void Snake::resetSnake(const Point& pt, int direction, int size)
{
	status = SnakeStatus::REGULAR;
	steps = 0;
	goToPoint(pt, direction);
	setPoints(0);
	setSnakeSize(size);
}

void Snake::gotHit()
{
	Point* snakeBody = body->getBody();
	int snakeSize = body->getCurrentSize();
	for (int i = 0; i < snakeSize; i++)
	{
		theBoard->removeCell(snakeBody[i]);
		theBoard->printCell(snakeBody[i]);
	}
	status = SnakeStatus::HIT;
	steps = 0;
}

bool Snake::_isNextStepValid()
{
	Point nextPoint = body->getNextPoint();

	if (theBoard->isOccupatiedBySanke(nextPoint))
		return false;

	return true;
}
