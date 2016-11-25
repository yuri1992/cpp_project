#ifndef _SNAKES_GAME_H_
#define _SNAKES_GAME_H_

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Snake.h"

using namespace std;

enum KEYS { ESC = 27 };

class SnakesGame {
	enum { size = 3 }; // a constant
	// data member: array of snakes
	Snake snakes[size] = {
		{ { 10, 10 }, '#' }, // snake 1
		{ { 20, 20 }, '$' }, // snake 2
		{ { 15, 70 }, '@' }  // snake 3
	};
	char screen[25][81] = { 
	//   12345678901234567890123456789012345678901234567890123456789012345678901234567890
		" 7   6                   5           13                                         ", // 1
		" 17                34                                                        4  ", // 2
		" 7   6                   5           13                                         ", // 3
		" 7   6                   5           13                                         ", // 4
	};
	int getDigit(int x, int y) {
		char c = screen[y][x];
		if (c == ' ') {
			return -1;
		}
		return c - '0';
	}
	int getNumber(const Point& pos) {
		int x = pos.getX();
		int y = pos.getY();
		int num = 0;
		while (x >= Point::min_x - 1 && getDigit(x, y) != -1) {
			// go left
			--x;
		}
		++x;
		// now we are on the units digit
		int digit;
		while (x <= Point::max_x && (digit = getDigit(x, y)) != -1) {
			// go right
			++x;
			num = num * 10 + digit;
		}
		return num > 0 ? num : -1;
	}
	void displayScreen() {
		gotoxy(0, 0);
		for (int i = 0; i < 4; ++i) {
			cout << screen[i];
		}
	}

public:
	SnakesGame() {
		snakes[0].setKeys('a', 'd', 'w', 'x');
		snakes[1].setKeys('j', 'l', 'i', ',');
	}
	void run();
};

#endif


