#ifndef _GUN_H_
#define _GUN_H_

#include "Bullet.h"
#include <vector>

class BoardManager;

class Gun
{
	int ammo;
	vector<Bullet> bullets;
	BoardManager* theBoard;
public:
	Gun(BoardManager* the_board);

	~Gun();
	void shoot(const Point& pt, int direction);
	void cleanBullets();
	bool moveBulletNextPosition(Bullet& bt);
	BasePlayerBoard* getBulletAtPoint(const Point& pt);
	void doNext();
	void reset();

	void setBoard(BoardManager* _boardManager) { this->theBoard = _boardManager; }
	int getAmmo() { return ammo; };
};

#endif
