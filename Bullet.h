#ifndef _BULLET_
#define _BULLET_

#include "Point.h"
class BoardManager;

class Bullet
{
	int direction;
	BoardManager* boardManager;
	Point pos;
public:
	Bullet(const Point& pt, int direction, BoardManager* boardManager);
	~Bullet();
	Point getNextPoint();
	Point& doNext();
	void remove();
	friend bool operator==(Bullet const& lhs, Bullet const& rhs)
	{
		return lhs.direction == rhs.direction && lhs.pos == rhs.pos;
	}
};
#endif
