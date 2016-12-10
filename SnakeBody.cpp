#include "SnakeBody.h"

Point SnakeBody::getNextPoint()
{
	return this->body[0].next(direction);
}

Point SnakeBody::getNextPoint(int dir)
{
	return this->body[0].next(dir);
}

void SnakeBody::setPosition(int y, int x)
{
	for (int i = 0; i < currentSize; i++)
		this->body[i].set(x, y);
}

void SnakeBody::setPosition(const Point &pt)
{
	setPosition(pt.getY(), pt.getX());
}

void SnakeBody::move()
{
	this->body[currentSize - 1].draw(' ');
	for (int i = currentSize - 1; i > 0; --i)
		this->body[i] = this->body[i - 1];

	this->body[0].move(direction);
}

void SnakeBody::increaseSnakeBody()
{
	int currentSize = getCurrentSize();
	Point *nBody = new Point[currentSize + 1];

	for (int i = 0; i < currentSize; i++)
	{
		nBody[i] = body[i];
	}

	setCurrentSize(currentSize + 1);
}

void SnakeBody::setBody(Point start)
{
	this->body = new Point[currentSize];
	for (int i = 0; i < currentSize; i++)
	{
		this->body[i] = Point(start);
		start.setY(start.getY() + 1);
	}
}

void SnakeBody::clean()
{
	for (int i = 0; i < currentSize; i++)
		this->body[i].draw(' ');
}