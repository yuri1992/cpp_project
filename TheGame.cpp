#include "TheGame.h"


TheGame::TheGame(const char* board[ROWS])
{
	snakes = new Snake*[2];
	snakes[0] = new Snake(YELLOW, '@',  this, "wxad");
	snakes[1] = new Snake(LIGHTBLUE, '#', this, "wxad");

	setBoardManager(board);
}

void TheGame::init()
{
	snakes[0]->setGame(this);
	snakes[1]->setGame(this);
}

void TheGame::run()
{
	char key = 0;
	int dir;
	do
	{
		if (_kbhit())
		{
			key = _getch();
			if ((dir = snakes[0]->getDirection(key)) != -1)
				snakes[0]->setDirection(dir);
			else if ((dir = snakes[1]->getDirection(key)) != -1)
				snakes[1]->setDirection(dir);
		}
		snakes[0]->move();
		snakes[1]->move();
		Sleep(400);
	}
	while (key != ESC);
}
