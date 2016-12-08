#include "TheGame.h"
#include "BoardManager.h"
#include "Point.h"
#include "Snake.h"

TheGame::TheGame(const char* board[ROWS])
{
	// initialize Board
	boardManager = new BoardManager(board);

	// initialize Two Snakes on screen
	Point ptStart1 = Point(10, 9);
	Point ptStart2 = Point(70, 9);
	snakes = new Snake*[2];
	snakes[0] = new Snake(YELLOW, '@', boardManager, "imjl", ptStart1, DIRECTION_RIGHT);
	snakes[1] = new Snake(LIGHTBLUE, '#', boardManager, "wxad", ptStart2, DIRECTION_LEFT);
}

void TheGame::init()
{
	boardManager->printBoard();
	snakes[0]->printSnake();
	snakes[1]->printSnake();
}

void TheGame::run()
{
	init();
	// Todo: Should be added handling of other keys press like (ESC, Menu buttons)
	char key = 0;
	do
	{
		if (_kbhit())
		{
			key = _getch();
			snakes[0]->handleKey(key);
			snakes[1]->handleKey(key);
		}

		snakes[0]->move();
		snakes[1]->move();
		Sleep(400);
	}
	while (key != ESC);
}

void TheGame::showQuickMenu()
{
	// Todo: implement quick menu print
	// 1. erase all screen or print in the top first line.

}

void TheGame::showFullMenu()
{
	// Todo: implement quick menu print
	// 1. erase all screen
	// 2. gotoxy middle screen
	// 3. print menu.
}
