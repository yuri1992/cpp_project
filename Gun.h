#ifndef _GUN_H_
#define _GUN_H_

#include "Bullet.h"
#include <vector>

class BoardManager;

class Gun
{
	int ammo;
	vector<Bullet> bullets;
	BoardManager* boardManager;
public:
	Gun();
	~Gun();
	void shoot(const Point& pt, int direction);
	void cleanBullets();
	bool moveBulletNextPosition(Bullet& bt);
	void doNext();
	void reset();

	void setBoard(BoardManager* boardManager) { this->boardManager = boardManager; }
	int getAmmo() { return ammo; };
};

#endif;
