#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Point.h"

#include "Direction.h"

class Snake {
	Point body[7];
	Direction direction;
	char c;
	bool isRandom = true;
	char dirKeys[4]; // the keys for the four possible directions
public:
	Snake(const Point& head, char c1, Direction dir = Direction::DOWN);
	void setKeys(char keyLeft, char keyRight, char keyUp, char keyDown);
	void changeDir(char keyPressed);
	Point move(char keyPressed);
	char getChar() const { return c; }
};


#endif
