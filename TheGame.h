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
		ESC = 27
	};

	Snake **snakes;
	BoardManager *boardManager;
	MissionBase mission;

public:
	TheGame(const char* board[ROWS]);
	void init();
	void run();
	bool isSolveMission(const Point& p) { return mission.isSolved(); }
	void setBoardManager(const char* board[ROWS]){ boardManager->setBoard(board);};
};

#endif
