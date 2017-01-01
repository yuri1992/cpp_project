#ifndef _BULLET_
#define _BULLET_

#include "Point.h"

class Bullet
{
	int direction;
	Point pos;
public:
	Bullet(const Point& pt, int direction);
	~Bullet();
	void doNext();
	void remove();
};
#endif
