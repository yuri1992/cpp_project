#include "TheSnakesGame.h"

void TheSnakesGame::handleObjectCreationFromBoard(int row, int col)
{
	char ch = board[row][col];
	if (ch == '@')
		s[0].setPosition(row, col);
	if (ch == '#')
		s[1].setPosition(row, col);
}
void TheSnakesGame::setBoard(const char* boardToCopy[ROWS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			originalBoard[i][j] = boardToCopy[i][j];
		}
		originalBoard[i][COLS] = '\0';
	}
}
void TheSnakesGame::init()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << originalBoard[i][j];
			cout.flush();
			board[i][j] = originalBoard[i][j];
			handleObjectCreationFromBoard(i, j);
		}
		board[i][COLS] = '\0';
	}

	s[0].setGame(this);
	s[1].setGame(this);
	s[0].setColor(YELLOW);
	s[1].setColor(LIGHTBLUE);
	s[0].setArrowKeys("wxad");
	s[1].setArrowKeys("8246");
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