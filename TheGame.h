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
		SHOW_MAIN_MENU = 3,
		SHOW_PAUSE_MENU = 4,
		SHOW_INFORMATION = 5,
	};

	int step = 0;
	Game status = STARTED;
	Snake** snakes;
	BoardManager* boardManager;
	MissionBase mission;

public:
	TheGame(const char* board[ROWS]);
	void init();

	void printScreen();
	void run();
	static void showInformation();
	static void showMainMenu();
	static void showPauseMenu();
	bool isStageSolved();

	void setBoardManager(const char* board[ROWS]) { boardManager->setBoard(board); };
	

private:
	void _exit() { exit(0); }

	void _pause() { status = Game::PAUSE; printScreen(); }
	void _showPauseMenu() { status = Game::SHOW_PAUSE_MENU; printScreen(); }
	void _showInformation() { status = Game::SHOW_INFORMATION; printScreen(); }
	void _showMainMenu() { status = Game::SHOW_MAIN_MENU; printScreen(); }

	void _start();
	void _resumeGame();
	//void _restartGame();
	void _nextStage();
	void _restartStage();
	void _newGame();
	void printScoreBoard();
	void printMessageOnBoard(string message);
	void _handleMenuKeyPress();
	void _handleGameKeyPress();
};

#endif
