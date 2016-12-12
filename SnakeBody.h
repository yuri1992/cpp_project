#ifndef _SNAKE_BODY_H_
#define _SNAKE_BODY_H_

#include "Point.h"

enum Direction
{
	DIRECTION_UP = 0,
	DIRECTION_DOWN = 1,
	DIRECTION_LEFT = 2,
	DIRECTION_RIGHT = 3
};

class SnakeBody
{
	enum
	{
		SNAKE_START_SIZE = 3
	};

	int direction = DIRECTION_UP;
	int currentSize = SNAKE_START_SIZE;
	char bodyChar;
	Color color;
	Point* body;
public:

	SnakeBody()
	{
		setColor(LIGHTGREY);
		setBodyChar('0');
	}

	SnakeBody(int direction, char body_char, Color color, Point startPoint)
	{
		setDirection(direction);
		setBodyChar(body_char);
		setColor(color);
		setBody(startPoint);
	}
	~SnakeBody();

	Point getNextPoint();
	Point getNextPoint(int dir);
	void setPosition(int y, int x);
	void setPosition(const Point& pt);
	void move();
	void clean();
	void increaseSnakeBody();

	// getters and setters
	int getDirection() { return direction; }
	void setDirection(int direction) { this->direction = direction; }
	char getBodyChar() const { return bodyChar; }
	void setBodyChar(char body_char) { bodyChar = body_char; }
	Color getColor() const { return color; }
	void setColor(Color color) { this->color = color; }
	Point* getBody() const { return body; }
	int getCurrentSize() const { return currentSize; }
	void setCurrentSize(int current_size) { currentSize = current_size;}
	void setBody(Point start);
	void setBody(Point* body) { this->body = body; }
};
#endif
