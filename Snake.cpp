#include "Snake.h"
#include "BoardManager.h"
#include "Point.h"

Snake::Snake(Color color, char symbol, BoardManager* theBoard,
             const char* keys, Point startPoint, Direction direction = DIRECTION_UP)
	: BasePlayerBoard(direction, startPoint, theBoard, symbol, color)
{
	pos.resize(SNAKE_START_SIZE);
	Snake::setPosition(startPoint);
	setArrowKeys(keys);
	gun = new Gun(theBoard);
}

Snake::~Snake()
{
	delete gun;
}

void Snake::handleKey(int key)
{
	int keyDirection = this->getKeyDirection(key);

	if (keyDirection != -1)
	{
		setDirection(keyDirection);
	}
	else if (status == SnakeStatus::REGULAR && key == getShottingKey())
	{
		shoot();
	}
}


void Snake::shoot()
{
	gun->shoot(getPosition(), getDirection());
}

void Snake::wonStage()
{
	increaseSnakeBody();

	if (status == SnakeStatus::REGULAR)
	{
		print();
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
	gun->reset();
}

void Snake::doNext()
{
	BoardManager* _theBoard = getBoard();

	if (status == SnakeStatus::HIT &&
		steps == GameSettings::RELIVE_AFTER_STEPS)
	{
		Point pt = _theBoard->getRandomPosition(getSnakeSize());
		status = SnakeStatus::REGULAR;
		steps = 0;
		setSnakeSize(SNAKE_START_SIZE + points);
		goToPoint(pt);
	}

	//gun->doNext();

	if (status == SnakeStatus::REGULAR)
	{
		if (_isNextStepValid())
		{
			remove();
			move();
			print();
		}
	}
	else
	{
		steps++;
	}

	_theBoard->printAmmo();
}

void Snake::destroy()
{
	gotHit();
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
	remove();
	setPosition(pt);
	print();
}

void Snake::goToPoint(const Point& pt, int direction)
{
	setDirection(direction);
	goToPoint(pt);
}

void Snake::resetSnake(const Point& pt, int direction, int size)
{
	status = SnakeStatus::REGULAR;
	steps = 0;
	goToPoint(pt, direction);
	setPoints(0);
	setSnakeSize(size);
}

void Snake::setPosition(const Point& newPosition)
{
	pos[0] = newPosition;
	for (unsigned i = 0; ++i < pos.size();)
	{
		pos[i] = pos[i - 1];
		pos[i] = pos[i].next(getInvertDirection());
	}
}

void Snake::gotHit()
{
	remove();
	pos.clear();
	status = SnakeStatus::HIT;
	steps = 0;
}

void Snake::increaseSnakeBody()
{
	pos.push_back(pos.back());
	move();
}

bool Snake::_isNextStepValid()
{
	Point nextPoint = getNextPosition();

	BoardManager* _theBoard = getBoard();
	if (_theBoard->isOccupatiedBySanke(nextPoint))
		return false;

	return true;
}
