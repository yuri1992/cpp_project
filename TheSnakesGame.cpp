#include "TheSnakesGame.h"



TheSnakesGame::TheSnakesGame(const char* board[ROWS])
{
	setBoardManager(board);
	s[0] = Snake(YELLOW, this, "wxad")
	s[1] = Snake(LIGHTBLUE, this, "wxad")
}

void TheSnakesGame::run()
{
	char key = 0;
	int dir;
	do
	{
		if (_kbhit())
		{
			key = _getch();
			if ((dir = s[0].getDirection(key)) != -1)
				s[0].setDirection(dir);
			else if ((dir = s[1].getDirection(key)) != -1)
				s[1].setDirection(dir);
		}
		s[0].move();
		s[1].move();
		Sleep(400);
	} while (key != ESC);
}
