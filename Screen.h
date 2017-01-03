#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "config.h"
#include "Color.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Screen
{
public:
	Screen() {};
	static void setCursor(int x, int y);
	static void setTextColor(Color);
	static void hideCursor();
	static void clearScreen();
	static void showInformation();
	static void showMainMenu();
	static void showPauseMenu();
	static void updateSnakesAmmo(int point1, int point2);
	static void printScoreBoard(std::string msg, int point1, int point2);
	static void printMessageOnBoard(std::string message, Color color = LIGHTGREY);
};

#endif