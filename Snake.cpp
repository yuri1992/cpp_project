#include "Snake.h"
#include "TheSnakesGame.h"
void Snake::setPosition(int y, int x)
{
	for (int i = 0; i < SIZE; i++)
		body[i].set(x, y);
}
void Snake::move()
{
	body[SIZE - 1].draw(' ');
	for (int i = SIZE - 1; i > 0; --i)
		body[i] = body[i - 1];

	if (theGame->isWall(body[0].next(direction)))
		direction = 4;

	body[0].move(direction);
	setTextColor(color);
	body[0].draw('@');
}
int Snake::getDirection(char key)
{
	for (int i = 0; i < SIZE - 1; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}