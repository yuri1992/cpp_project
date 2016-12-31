#include "Screen.h"
#include "Color.h"
#include <string>

using namespace std;

#ifndef WINDOWS
// monkey patch the functions that not supported by linux 
	void Screen::gotoxy(int x, int y) {}
	int  Screen::_getch(void) { return 0; }
	int  Screen::_kbhit(void) { return 0; }
	void Screen::Sleep(unsigned long) {}
	void Screen::setTextColor(Color color) {}
	void Screen::hideCursor() {}
	void Screen::clearScreen() {}
	void Screen::clear_screen() {}
#else
void Screen::setCursor(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void Screen::setTextColor(Color colorToSet)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

void Screen::hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

void Screen::clearScreen()
{
	system("cls");
}
#endif


void Screen::showInformation()
{
	Screen::clearScreen();
	Screen::setTextColor(LIGHTGREY);
	cout <<
		"                                                                                " << endl <<
		"  Each player gets a snake to control and earn points.                          " << endl <<
		"  Players need to pick up numbers based on the current task.                    " << endl <<
		"  the snakes start at length 3, winner is the one that reaches 12 first         " << endl <<
		"  if a player gets a correct answer he gets longer (+point)			         " << endl <<
		"  if a player gets a wrong answer, the other player gets longer (+point)        " << endl <<
		"                                                                                " << endl <<
		"        Player 1 Controls                     Player 2 Controls                 " << endl <<
		"                                                                                " << endl <<
		"              W                                      I                          " << endl <<
		"            A   D                                  J   L                        " << endl <<
		"              X                                      M                          " << endl <<
		"		                                                                         " << endl <<
		"                                                                                " << endl <<
		"      Press (9) to go back to menu.                                             " << endl;
}

void Screen::showMainMenu()
{
	Screen::setTextColor(LIGHTGREY);
	Screen::clearScreen();
	Screen::setCursor(0, 3);
	cout << "--------------------------------------------------------------------------------";
	Screen::setCursor(35, 11);
	cout << "Snake Game";
	Screen::setCursor(32, 12);
	cout << "-----------------";
	Screen::setCursor(32, 14);
	cout << "(1) Instructions.";
	Screen::setCursor(32, 15);
	cout << "(2) Play game!";
	Screen::setCursor(32, 16);
	cout << "(9) Exit.";
	//Screen::setCursor()
}

void Screen::showPauseMenu()
{
	Screen::clearScreen();
	Screen::setTextColor(LIGHTGREY);
	cout <<
		"                                                                                " << endl <<
		"                                  Game Paused                                   " << endl <<
		"                               ----------------                                 " << endl <<
		"                               (1) Exit game.                                   " << endl <<
		"                               (2) Main menu.                                   " << endl <<
		"                               (3) Resume game.                                 " << endl <<
		"                               (4) Restart stage                                " << endl <<
		"                               (5) Start new stage                              " << endl <<
		"                               (6) Restart game.                                " << endl <<
		"                                                                                " << endl;
}

void Screen::printScoreBoard(string msg, int point1, int point2)
{
	Screen::setTextColor(LIGHTGREY);
	Screen::setCursor(0, 0);
	cout << "  Mission:                                                                      ";
	Screen::setCursor(0, 1);
	cout << "                                                                                ";
	Screen::setCursor(0, 2);
	cout << "  Snake 1 Score: 8                                            Snake 2 Score: 7  ";
	Screen::setCursor(0, 3);
	cout << "--------------------------------------------------------------------------------";
	Screen::setCursor(11, 0);
	cout << msg;
	Screen::setCursor(17, 2);
	cout << point1 << " ";
	Screen::setCursor(77, 2);
	cout << point2 << " ";
	cout << flush;
}

void Screen::printMessageOnBoard(string message, Color color)
{
	Screen::setTextColor(color);
	Screen::setCursor(21, 1);
	cout << message;
	Sleep(2000); // a short wait until the game continues
	Screen::setCursor(21, 1);
	cout << "                                                        ";
}