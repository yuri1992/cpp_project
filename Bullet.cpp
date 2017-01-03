#include "Bullet.h"
#include "BoardManager.h"


Bullet::Bullet(const Point& pt, int direction, BoardManager* board)
{
	this->pos = pt;
	this->direction = direction;
	this->boardManager = board;
}


Bullet::~Bullet()
{

}

Point Bullet::getNextPoint()
{
	Point ptNext = pos;
	ptNext.move(direction);
	return ptNext;
}

Point& Bullet::doNext()
{
	boardManager->removeCell(pos);
	boardManager->printCell(pos);

	this->pos.move(direction);

	boardManager->setCell(pos, GUN_CHAR);
	boardManager->printCell(pos, RED);
	return pos;
}


void Bullet::remove()
{
	boardManager->removeCell(pos);
	boardManager->printCell(pos);
}
