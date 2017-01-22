#include <stdlib.h>
#include "Point.h"
#include "BoardManager.h"


void Point::move()
{
	int dir = rand() % 4;
	move(dir);
}

Point::Point()
{
	x = 1;
	y = 1;
}

Point::Point(const Point& pt)
{
	x = pt.getX();
	y = pt.getY();
}

bool Point::isBoundry(int dir) const
{
	switch (dir)
	{
	case 0: // UP
		
		if (y - 1 < 4)
		{
			return true;
		}
		break;
	case 1: // DOWN
		
		if (y + 1 > 24)
		{
			return true;
		}
		break;
	case 2: // LEFT
		
		if (x - 1 < 0)
		{
			return true;
		}
		break;
	case 3: // RIGHT
		
		if (x + 1 > 79)
		{
			return true;
		}
		break;
	}
	return false;
}

void Point::move(int dir)
{
	switch (dir)
	{
	case 0: // UP
		--y;
		if (y < 4)
		{
			y = ROWS - 1;
		}
		break;
	case 1: // DOWN
		++y;
		if (y > 24)
		{
			y = 4;
		}
		break;
	case 2: // LEFT
		--x;
		if (x < 0)
		{
			x = COLS - 1;
		}
		break;
	case 3: // RIGHT
		++x;
		if (x > 79)
		{
			x = 0;
		}
		break;
	}
}
