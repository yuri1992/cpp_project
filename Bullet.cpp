#include "Bullet.h"

Bullet::Bullet(const Point& pt, int direction)
{
	this->pos = pt;
	this->direction = direction;
}


Bullet::~Bullet()
{
}


void Bullet::next()
{
	// bullet is moving twice a speed
	for (int i = 0 ; i< 2 ;i ++ )
	{
		pos.draw(' ');
		pos.move(direction);
	}
}


void Bullet::remove()
{
	pos.draw(' ');
	// clean board;
}
