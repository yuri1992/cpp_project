#include "TheGame.h"
#include "BoardManager.h"
#include "Point.h"
#include "Snake.h"
#include "io_utils.h"
#include <string>
#include <iostream>

TheGame::TheGame(const char* board[ROWS])
{
	// initialize Board
	boardManager = new BoardManager(board, &mission);

	// initialize Two Snakes on screen
	snakes = new Snake*[2];
	snakes[0] = new Snake(YELLOW, '@', boardManager, "imjl", Point(10, 9), DIRECTION_RIGHT);
	snakes[1] = new Snake(LIGHTBLUE, '#', boardManager, "wxad", Point(70, 9), DIRECTION_LEFT);
}

//THIS FUNCTION IS NOT CALLED ANYMORE.
void TheGame::init()
{
	mission.nextMission();
	boardManager->printBoardWithoutSnakePath();
	snakes[0]->printSnake();
	snakes[1]->printSnake();

	printScoreBoard();
}

void TheGame::printScreen()
{
	if (status == Game::STARTED || status == Game::SHOW_MAIN_MENU)
		showMainMenu();
	else if (status == Game::PAUSE || status == Game::SHOW_PAUSE_MENU)
		showPauseMenu();
	else if (status == Game::SHOW_INFORMATION)
		showInformation();
}

void TheGame::run()
{
	printScreen();

	do
	{
		if (status == Game::STARTED ||
			status == Game::SHOW_MAIN_MENU ||
			status == Game::PAUSE ||
			status == Game::SHOW_PAUSE_MENU ||
			status == Game::SHOW_INFORMATION)
		{
			_handleMenuKeyPress();
		}
		else
		{
			_handleGameKeyPress();
		}
	}
	while (true);
}


void TheGame::_handleGameKeyPress()
{
	if (status == Game::RUNNING)
	{
		char key = 0;
		if (_kbhit())
		{
			key = _getch();

			if (key == ESC)
			{
				_pause();
				return;
			}
			snakes[0]->handleKey(key);
			snakes[1]->handleKey(key);
		}

		if (isStageSolved())
		{
			if (snakes[0]->isWinGame())
			{
				//checks if snake got 12
				printMessageOnBoard("Snake 1 Won The game!!");
				status = Game::SHOW_MAIN_MENU;
				//_newGame();
			}
			else if (snakes[1]->isWinGame())
			{
				printMessageOnBoard("Snake 2 Won The game!!");
				status = Game::SHOW_MAIN_MENU;
				//_newGame();
			}

			else
			{
				_nextStage(); // the won stage print is in isStageSolved
			}

		}


		if (boardManager->getNumberOfNumbers() == 10) //TODO change to 60 eventually
		{
			// Threr are 60 numbers of borad we should 
			if (!boardManager->findSolveOnBoard())
				printMessageOnBoard("Sorry, we do not have solution on the board");
			else
				printMessageOnBoard("Nice try, We are to continue to next Stage");
			_nextStage();
		}

		if (step++ % 5 == 0)
			boardManager->setNextNumber(mission.generateNextNumber());

		snakes[0]->move();
		snakes[1]->move();
		Sleep(100);
	}
}

bool TheGame::isStageSolved()
{
	/*
	 * return True when stage is completed!! not solved currently
	 */
	Point pt;
	int n, i;

	for (i = 0; i < 2; i++)
	{
		pt = snakes[i]->getNextStep();
		n = boardManager->getCellNumber(pt);

		if (n >= 0)
		{
			if (mission.isSolved(n))
			{
				boardManager->removeNumberfromBoard(n);
				snakes[i]->wonStage();
				if (i == 0)
				{
					setTextColor(YELLOW);
					printMessageOnBoard("Snake 1 (yellow) is RIGHT! +1 point");
				}
				else if (i == 1)
				{
					setTextColor(LIGHTBLUE);
					printMessageOnBoard("Snake 2 (blue) is RIGHT! +1 point");
				}
			}
			else
			{
				if (i == 1)
				{
					setTextColor(YELLOW);
					printMessageOnBoard("Snake 2 is WRONG: +1 point for snake 1");
					snakes[0]->wonStage();
				}
				else
				{
					setTextColor(LIGHTBLUE);
					printMessageOnBoard("Snake 1 is WRONG: +1 point for snake 2");
					snakes[1]->wonStage();
				}
			}
			return true;
		}
	}

	return false;
}

void TheGame::_handleMenuKeyPress()
{
	if (_kbhit())
	{
		char key = 0;
		key = _getch();
		if (status == Game::STARTED || status == Game::SHOW_MAIN_MENU)
		{
			// handling Main Menu keys press
			switch (key)
			{
			case NUM_1:
				_showInformation();
				break;
			case NUM_2:
				_start();
				break;
			case NUM_9:
				_exit();
				break;
			default: break;
			}
		}
		else if (status == Game::PAUSE || status == Game::SHOW_PAUSE_MENU)
		{
			// handling Full Menu keys press
			switch (key)
			{
			case NUM_1:
				_exit();
				break;
			case NUM_2:
				_showMainMenu();
				break;
			case NUM_3:
				_resumeGame();
				break;
				// (4)Restart Mission: delete all numbers + put snakes on starting position 
				//+ reset clock (from forum)  + [[ same snake size(i think- waiting for answer in forum)]]
			case NUM_4:
				_restartStage();
				break;
			case NUM_5:
				_nextStage();
				break;
			case NUM_6:
				_newGame();
				break;
			default: break;
			}
		}
		else if (status == Game::SHOW_INFORMATION)
		{
			switch (key)
			{
			case NUM_9:
				_showMainMenu();
			default: break;
			}
		}
	}
}

void TheGame::_start()
{
	status = Game::RUNNING;
	_newGame();
}

void TheGame::_resumeGame()
{
	status = Game::RUNNING;
	clearScreen();
	boardManager->printBoardWithoutSnakePath();

}

void TheGame::_restartStage()
{
	//TODO - get this original BOARD FROM... elsewhere :X
	const char* blabla[ROWS] = {
		//	         10        20        30        40        50        60        70       79
		//	 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                                ", // 0
		"                                                                                ", // 1
		"                                                                                ", // 2
		"------------------------------------------------------------------------------- ", // 3
		"                                                                                ", // 4
		"                                                                                ", // 5
		"                                                                                ", // 6
		"                                                                                ", // 7
		"                                                                                ", // 8
		"                                                                                ", // 9
		"                                                                                ", // 10
		"                                                                                ", // 11
		"                                                                                ", // 12
		"                                                                                ", // 13
		"                                                                                ", // 14
		"                                                                                ", // 15
		"                                                                                ", // 16
		"                                                                                ", // 17
		"                                                                                ", // 18
		"                                                                                ", // 19
		"                                                                                ", // 20
		"                                                                                ", // 21
		"                                                                                ", // 22
		"                                                                                " };  // 23
//   01234567890123456789012345678901234567890123456789012345678901234567890123456789

	clearScreen();
	printScoreBoard();
	delete boardManager;
	boardManager = new BoardManager(blabla, &mission);
	snakes[0]->goToStartPoint(Point(10, 9));
	snakes[1]->goToStartPoint(Point(70, 9));
	snakes[0]->setSnakeDirection(DIRECTION_RIGHT);
	snakes[1]->setSnakeDirection(DIRECTION_LEFT);
	status = Game::RUNNING;
}

void TheGame::_nextStage()
{
	if (status == Game::PAUSE)
	{
		clearScreen();
		snakes[0]->goToStartPoint(Point(10, 9));
		snakes[1]->goToStartPoint(Point(70, 9));
		snakes[0]->setSnakeDirection(DIRECTION_RIGHT);
		snakes[1]->setSnakeDirection(DIRECTION_LEFT);
	}
	status = Game::RUNNING;
	boardManager->prepareNextStage();
	mission.nextMission();
	printScoreBoard();
	Sleep(1000);
}


void TheGame::_newGame()
{
	clearScreen();
	snakes[0]->setPoints(0);
	snakes[1]->setPoints(0);
	snakes[0]->goToStartPoint(Point(10, 9));
	snakes[1]->goToStartPoint(Point(70, 9));
	snakes[0]->setSnakeSize(3);
	snakes[1]->setSnakeSize(3);
	snakes[0]->setSnakeDirection(DIRECTION_RIGHT);
	snakes[1]->setSnakeDirection(DIRECTION_LEFT);
	boardManager->printBoardWithoutSnakePath();
	printScoreBoard();
	status = Game::RUNNING;
}

void TheGame::printScoreBoard()
{
	setTextColor(LIGHTGREY);
	gotoxy(0, 0);
	cout <<
		"  Mission:                                                                      " << endl <<
		"                                                                                " << endl <<
		"  Snake 1 Score: 0                                            Snake 2 Score: 0  " << endl <<
		"--------------------------------------------------------------------------------";
	gotoxy(11, 0);
	cout << mission.getMissionText();
	gotoxy(17, 2);
	cout << snakes[0]->getPoints() << " ";
	gotoxy(77, 2);
	cout << snakes[1]->getPoints() << " ";
	cout << flush;
}

void TheGame::printMessageOnBoard(string message)
{
	gotoxy(21, 1);
	cout << message;
	Sleep(2000); // a short wait until the game continues
	gotoxy(21, 1);
	cout << "                                                        ";
}

void TheGame::showInformation()
{
	clearScreen();
	cout <<
		"                                                                                " << endl <<
		"  Each player gets a snake to control and earn points.                          " << endl <<
		"  Players need to pick up numbers based on the current task.                    " << endl <<
		"  the snakes start at length 3, winner is the one that reaches 12 first         " << endl <<
		"  if a player gets a correct answer he gets longer (+point)			         " << endl <<
		"  if a player gets a wrong answer, the other player gets longer (+point)        " << endl <<
		"                                                                                " << endl <<
		"        Player 1 Controls                     Player 2 Controls                 " << endl <<
		"                                                                                " << endl <<
		"              W                                      I                          " << endl <<
		"            A   D                                  J   L                        " << endl <<
		"              X                                      M                          " << endl <<
		"		                                                                         " << endl <<
		"                                                                                " << endl <<
		"      Press (9) to go back to menu.                                             " << endl;
}

void TheGame::showMainMenu()
{
	clearScreen();
	gotoxy(0, 3);
	cout << "--------------------------------------------------------------------------------";
	gotoxy(35, 11);
	cout << "Snake Game";
	gotoxy(32, 12);
	cout << "-----------------";
	gotoxy(32, 14);
	cout << "(1) Instructions.";
	gotoxy(32, 15);
	cout << "(2) Play game!";
	gotoxy(32, 16);
	cout << "(9) Exit.";
	//gotoxy()
}

void TheGame::showPauseMenu()
{
	clearScreen();
	cout <<
		"                                                                                " << endl <<
		"                                  Game Paused                                   " << endl <<
		"                               ----------------                                 " << endl <<
		"                               (1) Exit game.                                   " << endl <<
		"                               (2) Main menu.                                   " << endl <<
		"                               (3) Resume game.                                 " << endl <<
		"                               (4) Restart stage                                " << endl <<
		"                               (5) Start new stage                              " << endl <<
		"                               (6) Restart game.                                " << endl <<
		"                                                                                " << endl;
}
