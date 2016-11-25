#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"

class TheSnakesGame;

class Snake {
	enum {SIZE = 5};
	Point body[SIZE];
	int direction = 3; 
	char arrowKeys[4];
	Color color;
	TheSnakesGame* theGame;
public:
	void setGame(TheSnakesGame* _theGame) {
		theGame = _theGame;
	}
	void setPosition(int y, int x);
	void setArrowKeys(const char* keys) {
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
	}
	void setColor(Color c) {
		color = c;
	}
	void move();
	int getDirection(char key);
	void setDirection(int dir) {
		direction = dir;
	}

};

#endif