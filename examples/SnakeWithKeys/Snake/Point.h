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
		x = (x + dir_x + 80) % 80;
		y = (y + dir_y + 24) % 24;
	}
public:
	Point(int x1=1, int y1=1) {
		x = x1;
		y = y1;
	}
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
