#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#include "Screen.h"
#include "BoardManager.h"

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
	BoardManager* theBoard;
public:
	TheGame();
	~TheGame();
	void printScreen() const;
	void run();
	bool isStageSolved();
private:
	void _showPauseMenu()
	{
		status = Game::SHOW_PAUSE_MENU;
		printScreen();
	}

	void _showInformation()
	{
		status = Game::SHOW_INFORMATION;
		printScreen();
	}

	void _showMainMenu()
	{
		status = Game::SHOW_MAIN_MENU;
		printScreen();
	}

	void _start();

	void _pause()
	{
		status = Game::PAUSE;
		printScreen();
	}

	void _restartGame();
	void _resumeGame();
	void _nextStage();
	void _restartStage();
	void _playReplay();
	void _newGame();

	void _finishGame()
	{
		status = Game::SHOW_MAIN_MENU;
		printScreen();
	}

	void _exit() { exit(0); }

	void _handleMenuKeyPress();
	void _handleGameKeyPress();
};

#endif
