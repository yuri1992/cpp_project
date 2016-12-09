#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#include "io_utils.h"
#include "Snake.h"
#include "BoardManager.h"
#include "MissionBase.h"
#include "Point.h"


class TheGame
{
	enum
	{
		ESC = 27,
		NUM_1 = '1',
		NUM_2 = '2',
		NUM_3 = '3',
		NUM_4 = '4',
		NUM_5 = '5',
		NUM_6 = '6',
		NUM_7 = '7',
		NUM_8 = '8',
		NUM_9 = '9'
	};

	enum Game
	{
		PAUSE = 0,
		RUNNING = 1,
		STARTED = 2,
		SHOW_QUICK_MENU = 3,
		SHOW_FULL_MENU = 4,
		SHOW_INFORMATION = 5,
	};

	Game status = STARTED;
	Snake** snakes;
	BoardManager* boardManager;
	MissionBase mission;

public:
	TheGame(const char* board[ROWS]);
	void init();

	void printScreen();
	void run();
	void showQuickMenu();
	void showFullMenu();
	bool isSolveMission(const Point& p) { return mission.isSolved(); }

	void setBoardManager(const char* board[ROWS]) { boardManager->setBoard(board); };

private:
	void _exit() { exit(0); }

	void _pause() { status = Game::PAUSE; printScreen(); }
	void _showInformation() { status = Game::SHOW_INFORMATION;  printScreen(); }
	void _showFullMenu() { status = Game::SHOW_FULL_MENU; printScreen(); }

	void _start();
	void _continue();
	void _restartGame();
	void _nextGame();
	void _newGame();
	void _handleMenuKeyPress();
	void _handleGameKeyPress();
	void showInformation();
};

#endif
