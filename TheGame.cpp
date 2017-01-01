#include "TheGame.h"
#include "GameSettings.h"
#include "BoardManager.h"
#include "Point.h"
#include "Snake.h"
#include <string>

TheGame::TheGame()
{
	// initialize Board
	boardManager = new BoardManager(&mission);

	// initialize Two Snakes on screen
	snakes = new Snake*[2];
	snakes[0] = new Snake(YELLOW,
	                      GameSettings::SANKE_ONE_BODY_FILL,
	                      boardManager,
	                      "imjln",
	                      Point(10, 9), DIRECTION_RIGHT);

	snakes[1] = new Snake(LIGHTBLUE,
	                      GameSettings::SANKE_TWO_BODY_FILL,
	                      boardManager,
	                      "wxadz",
	                      Point(70, 9), DIRECTION_LEFT);
}

TheGame::~TheGame()
{
	delete boardManager;
	delete snakes;
}

void TheGame::printScreen() const
{
	if (status == Game::STARTED || status == Game::SHOW_MAIN_MENU)
		Screen::showMainMenu();
	else if (status == Game::PAUSE || status == Game::SHOW_PAUSE_MENU)
		Screen::showPauseMenu();
	else if (status == Game::SHOW_INFORMATION)
		Screen::showInformation();
}

void TheGame::printScore() const
{
	Screen::printScoreBoard(mission.getMissionText(),
	                        snakes[0]->getPoints(),
	                        snakes[1]->getPoints());
}

void TheGame::run()
{
	printScreen();
	do
	{
		if (status == Game::RUNNING)
		{
			_handleGameKeyPress();
		}
		else
		{
			_handleMenuKeyPress();
		}
	}
	while (true);
}


void TheGame::_handleGameKeyPress()
{
	if (status == Game::RUNNING)
	{
		char key;
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
				Screen::printMessageOnBoard("Snake 1 Won The game!!", snakes[0]->getColor());
				_finishGame();
				return;
			}
			else if (snakes[1]->isWinGame())
			{
				Screen::printMessageOnBoard("Snake 2 Won The game!!", snakes[1]->getColor());
				_finishGame();
				return;
			}
			else
			{
				_nextStage(); // the won stage print is in isStageSolved
			}
		}

		if (boardManager->getNumberOfNumbers() == GameSettings::MAX_NUMBER_ON_BOARD)
		{
			if (!boardManager->findSolveOnBoard())
				Screen::printMessageOnBoard("Sorry, we do not have solution on the board");
			else
				Screen::printMessageOnBoard("Nice try, We are to continue to next Stage");
			_nextStage();
		}

		if (step++ % GameSettings::STEPS_FOR_NEW_NUMBER == 0)
			boardManager->setNextNumber();

		snakes[0]->doNext();
		snakes[1]->doNext();

		Sleep(200);
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
		n = boardManager->getNumberInCell(pt);

		if (n >= 0)
		{
			boardManager->removeNumberfromBoard(n);
			if (mission.isSolved(n))
			{
				//boardManager->removeNumberfromBoard(n);
				snakes[i]->wonStage();
				if (i == 0)
				{
					Screen::printMessageOnBoard("Snake 1 (yellow) is RIGHT! +1 point", Color::YELLOW);
				}
				else if (i == 1)
				{
					Screen::printMessageOnBoard("Snake 2 (blue) is RIGHT! +1 point", Color::LIGHTBLUE);
				}
			}
			else
			{
				if (i == 1)
				{
					Screen::printMessageOnBoard("Snake 2 is WRONG: +1 point for snake 1", Color::YELLOW);
					boardManager->removeNumberByPoint(snakes[0]->getNextStep());
					snakes[0]->wonStage();
				}
				else
				{
					Screen::printMessageOnBoard("Snake 1 is WRONG: +1 point for snake 2", Color::LIGHTBLUE);
					boardManager->removeNumberByPoint(snakes[1]->getNextStep());
					snakes[1]->wonStage();
				}
			}
			return true;
		}
	}
	return false;
}

void TheGame::_restartGame()
{
	_newGame();
	status = Game::RUNNING;
}

void TheGame::_handleMenuKeyPress()
{
	if (_kbhit())
	{
		char key;
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
			case NUM_4:
				_restartStage();
				break;
			case NUM_5:
				_nextStage();
				break;
			case NUM_6:
				_restartGame();
				break;
			default: break;
			}
		}
		else if (status == Game::SHOW_INFORMATION)
		{
			if (key == NUM_9)
				_showMainMenu();
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
	Screen::clearScreen();

	boardManager->printBoardWithoutSnakePath();
	printScore();
}

void TheGame::_restartStage()
{
	boardManager->resetBoard();
	snakes[0]->goToPoint(Point(10, 9), DIRECTION_RIGHT);
	snakes[1]->goToPoint(Point(70, 9), DIRECTION_LEFT);

	printScore();
	status = Game::RUNNING;
}

void TheGame::_nextStage()
{
	if (status == Game::PAUSE)
	{
		Screen::clearScreen();
		boardManager->resetBoard();

		snakes[0]->goToPoint(Point(10, 9), DIRECTION_RIGHT);
		snakes[1]->goToPoint(Point(70, 9), DIRECTION_LEFT);
	}

	boardManager->prepareNextStage();
	mission.nextMission();

	printScore();
	status = Game::RUNNING;

	Sleep(1000);
}


void TheGame::_newGame()
{
	Screen::clearScreen();
	boardManager->resetBoard();

	snakes[0]->resetSnake(Point(10, 9), DIRECTION_RIGHT, 3);
	snakes[1]->resetSnake(Point(70, 9), DIRECTION_LEFT, 3);

	printScore();
	status = Game::RUNNING;
}
