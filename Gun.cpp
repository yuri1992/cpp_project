#include "Gun.h"
#include "GameSettings.h"


Gun::Gun()
{
	ammo = GUN_AMMO_INITIAL;
}

Gun::~Gun()
{
}


void Gun::shoot(const Point& pt, int direction)
{
	if (ammo > 0)
	{
		Bullet bul = Bullet(pt, direction);
		bullets.push_back(bul);
		ammo--;
	}
}


void Gun::cleanBullets()
{
	for (Bullet bt : bullets) {
		bt.remove();
	}
}


void Gun::reset()
{
	cleanBullets();
	ammo = GUN_AMMO_INITIAL;
	bullets.clear();
}


void Gun::doNext()
{
	for (auto& bt : bullets) {

			bt.doNext();
	}
}
