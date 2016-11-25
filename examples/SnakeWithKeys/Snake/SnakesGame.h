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
	Snake p[size] = {
		{ { 10, 10 }, '#' }, // snake 1
		{ { 20, 20 }, '$' }, // snake 2
		{ { 15, 70 }, '@' }  // snake 3
	};
public:
	SnakesGame() {
		p[0].setKeys('a', 'd', 'w', 'x');
		p[1].setKeys('j', 'l', 'i', ',');
	}
	void run();
};

#endif


