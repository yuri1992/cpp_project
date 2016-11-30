#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#include "io_utils.h"
#include "Snake.h"
#include "BoardManager.h"


class TheSnakesGame {
	enum {ESC = 27};
	Snake s[2];
	BoardManager boardManager;
	MissionFactory missionFactory;

//  BoardMission mission;
//	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
//	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here

public:
	void setBoard(const char* boardToCopy[ROWS]);
	void initBoard();
	void init();
	bool isSolveMission(const Point& p) {
		//mission->isSolved();
	}
	void run();
};

#endif