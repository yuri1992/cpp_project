#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"
#include "TheGame.h"

class Snake
{
	enum
	{
		SIZE = 5,
		DIRECTION_UP = 1,
		DIRECTION_RIGHT = 2,
		DIRECTION_DOWN = 3,
		DIRECTION_LEFT = 4
	};

	Point body[SIZE];
	int direction = DIRECTION_UP;
	char arrowKeys[4];
	Color color;
	char bodyFill;
	TheGame* theGame;
public:
	Snake(Color color, char bodyFill, TheGame* theGame, const char* keys,
	      int direction = DIRECTION_UP)
	{
		setDirection(direction);
		setColor(color);
		setBodyFill(bodyFill);
		setGame(theGame);
		setArrowKeys(keys);
	}

	void move();

	// getters and setters

	int getDirection(char key) const { return direction; }

	void setDirection(char direction) { this->direction = direction; }

	Color getColor() const { return color; }

	void setColor(Color color) { this->color = color; }

	char getBodyFill() const { return bodyFill; }

	void setBodyFill(char body_fill) { bodyFill = body_fill; }

	void setGame(TheGame* _theGame) { theGame = _theGame; }

	void setPosition(int y, int x);

	void setArrowKeys(const char* keys)
	{
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
	}

private:
	void _increseSize();
};

#endif