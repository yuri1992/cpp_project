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

void SnakeBody::move()
{
	this->body[currentSize - 1].draw(' ');
	for (int i = currentSize - 1; i > 0; --i)
		this->body[i] = this->body[i - 1];

	this->body[0].move(direction);
}

void SnakeBody::increaseSnakeBody()
{
	// TODO : implement function that will increase the snake body size
	// body should have one more node at the tail of the sanke.
	// you should allocate new memory and relase the old snake memory.
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
