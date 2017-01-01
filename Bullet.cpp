#include "Bullet.h"

Bullet::Bullet(const Point& pt, int direction)
{
	this->pos = pt;
	this->direction = direction;
}


Bullet::~Bullet()
{
}


void Bullet::doNext()
{
	// bullet is moving twice a speed
	for (int i = 0 ; i< 2 ;i ++ )
	{
		this->pos.draw(' ');
		this->pos.move(direction);
		this->pos.draw('*');
	}
}


void Bullet::remove()
{
	pos.draw(' ');
	// clean board;
}
