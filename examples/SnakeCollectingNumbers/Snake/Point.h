#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "Gotoxy.h"
#include "Direction.h"

using namespace std;

class Point
{
	int x;
	int y;
	int dir_x = 1;
	int dir_y = 0;
	void moveImpl() {
		// we tried some stuff, it didn't work - I leave it to you...
		// x = (-min_x + x + dir_x + (max_x - min_x + 1)) % (max_x - min_x + 1) + min_x;
		// y = (-min_y + y + dir_y + (max_y - min_y + 1)) % (max_y - min_y + 1) + min_y;
		x = (x + dir_x + max_x) % max_x;
		y = (y + dir_y + max_y) % max_y;
	}
public:
	// consider moving this enum to a more suitable place
	enum { min_x = 1, max_x = 79, min_y = 4, max_y = 24 };
	Point(int x1=1, int y1=1) {
		x = x1;
		y = y1;
	}
	int getX() const { return x; }
	int getY() const { return y; }
	void draw(char c = '*') {
		gotoxy(x, y);
		cout << c << endl;
	}
	void changeDir(Direction dir);
	void move() {
		int sameDir = rand() % 10;
		if (!sameDir) {
			int dir = rand() % 4;
			changeDir((Direction)dir);
		}
		moveImpl();
	}
	void move(Direction dir) {
		changeDir(dir);
		moveImpl();
	}
};


#endif
