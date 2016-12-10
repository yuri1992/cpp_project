#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"

using namespace std;

class Point
{
	int x = 1, y = 1;
public:
	Point();

	Point(int x, int y)
	{
		setX(x);
		setY(y);
	}

	int getX() const
	{
		return x;
	}

	int getY() const
	{
		return y;
	}

	void setX(int x)
	{
		this->x = x;
	}

	void setY(int y)
	{
		this->y = y;
	}

	void set(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	void draw(char ch)
	{
		gotoxy(x, y);
		cout << ch;
		cout.flush();
	}

	void move();

	void move(int direction);

	Point next(int direction)
	{
		Point next = *this;
		next.move(direction);
		return next;
	}

	bool isSame(const Point& p) const
	{
		return x == p.x && y == p.y;
	}


	friend bool operator==(const Point& lhs, const Point& rhs)
	{
		return lhs.x == rhs.x
			&& lhs.y == rhs.y;
	}

	friend bool operator!=(const Point& lhs, const Point& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const Point& lhs, const Point& rhs)
	{
		if (lhs.x < rhs.x)
			return true;
		if (rhs.x < lhs.x)
			return false;
		return lhs.y < rhs.y;
	}

	friend bool operator<=(const Point& lhs, const Point& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const Point& lhs, const Point& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const Point& lhs, const Point& rhs)
	{
		return !(lhs < rhs);
	}
};

#endif
