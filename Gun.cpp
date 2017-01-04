#include "Gun.h"
#include "GameSettings.h"
#include "Snake.h"
#include "BoardManager.h"
#include <algorithm>

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
	if (ammo > 0)
	{
		Point ptNew = pt;
		ptNew.move(direction);

		Bullet bul = Bullet(ptNew, direction, boardManager);
		bullets.push_back(bul);
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

void Gun::destoryBullet(Bullet& bt)
{
	bt.remove();
}

bool Gun::moveBulletNextPosition(Bullet& bt)
{
	/*
	 * return False when bullet hitted something and need to be removed from game
	 */
	Point pos = bt.getNextPoint();
	char ch = boardManager->getCell(pos);
	if (ch != ' ')
	{
		Snake* snake = boardManager->getSnakeInCell(pos);
		if (snake != nullptr)
		{
			snake->gotHit();
			if (snake->getGun() == this)
			{
				Screen::printMessageOnBoard("You hitted Yourself :( 1", Color::GREEN);
				ammo++;
			}
			else
			{
				Screen::printMessageOnBoard("Nice Strike! ", Color::GREEN);
			}

			return false;
		}
		else if (boardManager->removeNumberByPoint(pos))
		{
			return false;
		}
	}
	else
	{
		bt.doNext();
	}
	return true;
}

void Gun::doNext()
{
	for (auto bt = bullets.begin(); bt != bullets.end();)
	{
		// moving the bullet twice
		bool erase = moveBulletNextPosition(*bt) && moveBulletNextPosition(*bt);
		if (!erase)
		{
			destoryBullet(*bt);
			bt = bullets.erase(bt);
		}
		else
		{
			++bt;
		}
	}
}
