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
		NUM_1 = 1,
		NUM_2 = 1,
		NUM_3 = 1,
		NUM_4 = 1,
		NUM_5 = 1,
		NUM_6 = 1,
		NUM_7 = 7,
	};

	enum Game
	{
		PAUSE = 0,
		RUNNING = 1,
	};

	Game status = PAUSE;
	Snake** snakes;
	BoardManager* boardManager;
	MissionBase mission;

public:
	TheGame(const char* board[ROWS]);
	void init();
	void run();
	void showQuickMenu();
	void showFullMenu();
	bool isSolveMission(const Point& p) { return mission.isSolved(); }
	void setBoardManager(const char* board[ROWS]) { boardManager->setBoard(board); };

private:
	void _pause();
	void _continue();
	void _restartGame();

};

#endif
