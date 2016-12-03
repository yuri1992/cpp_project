#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#include "io_utils.h"
#include "Snake.h"
#include "BoardManager.h"
#include "MissionBase.h"


class TheSnakesGame
{
	enum
	{
		ESC = 27
	};

	Snake s[2];
	BoardManager boardManager;
	MissionBase mission;

	//  BoardMission mission;
	//	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	//	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here

public:
	TheSnakesGame(const char* board[ROWS]);

	bool isSolveMission(const Point& p)
	{
		return mission.isSolved();
	}

	void run();
	void setBoardManager(const char* board[ROWS]);
};

#endif
