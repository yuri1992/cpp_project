#ifndef _GUN_H_
#define _GUN_H_
#include "Bullet.h"
#include <vector>

class Gun
{
	int ammo;
	vector<Bullet> bullets;
public:
	Gun();
	~Gun();
	void shoot(const Point& pt, int direction);
	void cleanBullets();
	void reset();
	void next();

	//

};

#endif;

