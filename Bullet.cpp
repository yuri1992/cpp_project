#include "Bullet.h"
#include "BoardManager.h"


Bullet::~Bullet()
{

}
	

void Bullet::doNext()
{
	remove();
	move();
	print();
}

void Bullet::destroy()
{
	remove();
	pos.empty();
}
