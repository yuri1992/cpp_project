#include "Gun.h"
#include "GameSettings.h"
#include "Snake.h"
#include "BoardManager.h"

Gun::Gun()
{
	ammo = GUN_AMMO_INITIAL;
	this->boardManager = nullptr;
	bullets.clear();
}

Gun::~Gun()
{
}


void Gun::shoot(const Point& pt, int direction)
{
	/*
	 * Creating new bullet if there any ammo left.
	 */
	if (ammo > 0)
	{
		// Moving the @pt to next point
		Point ptNew = pt;
		ptNew.move(direction);

		// adding bullet the vector.
		Bullet bul = Bullet(ptNew, direction, boardManager);
		bullets.push_back(bul);

		// decreaing ammo size.
		ammo--;
	}
}


void Gun::cleanBullets()
{
	for (Bullet bt : bullets)
	{
		bt.remove();
	}
	bullets.clear();
}


void Gun::reset()
{
	cleanBullets();
	ammo = GUN_AMMO_INITIAL;
	bullets.clear();
}

bool Gun::moveBulletNextPosition(Bullet& bt)
{
	/*
	 * return True when bullet hitted something and need to be removed from game
	 */
	Point pos = bt.getNextPoint();
	Snake* snake = boardManager->getSnakeInCell(pos);
	if (snake != nullptr)
	{
		snake->gotHit();
		if (snake->getGun() != this)
		{
			ammo++;
		}
		return true;
	}
	else if (boardManager->removeNumberByPoint(pos))
	{
		return true;
	}
	else
	{
		bt.doNext();
	}
	return false;
}

void Gun::doNext()
{
	for (auto bt = bullets.begin(); bt != bullets.end();)
	{
		// moving the bullet twice
		if (moveBulletNextPosition(*bt) || moveBulletNextPosition(*bt))
		{
			bt->remove();
			bt = bullets.erase(bt);
		}
		else
		{
			++bt;
		}
	}
}
