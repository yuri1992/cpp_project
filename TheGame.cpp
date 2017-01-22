#include "TheGame.h"
#include <string>

TheGame::TheGame()
{
	// initialize Board
	theBoard = new BoardManager();
}

TheGame::~TheGame()
{
	delete theBoard;
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
			theBoard->handleKey(key);
		}

		if (isStageSolved())
		{
			if (theBoard->isGameWon())
			{
				_finishGame();
				return;
			}
			else
			{
				_nextStage(); // the won stage print is in isStageSolved
				return;
			}
		}

		if (theBoard->getNumberAmountOnBoard() == GameSettings::MAX_NUMBER_ON_BOARD)
		{
			if (!theBoard->findSolveOnBoard())
				Screen::printMessageOnBoard("Sorry, we do not have solution on the board");
			else
				Screen::printMessageOnBoard("Nice try, We are to continue to next Stage");
			_nextStage();
		}

		if (step++ % GameSettings::STEPS_FOR_NEW_NUMBER == 0)
		{
			theBoard->setNextNumber();
		}

		theBoard->next();

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
		Snake* snake = theBoard->getSnake(i);
		if (snake->getStatus() == SnakeStatus::REGULAR)
		{
			pt = snake->getNextPosition();
			n = theBoard->getNumberInCell(pt);
			if (n >= 0)
			{
				theBoard->removeNumberfromBoard(n);
				if (theBoard->getMission()->isSolved(n))
				{
					//theBoard->removeNumberfromBoard(n);
					snake->wonStage();
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
						Snake* otherPlayer = theBoard->getSnake(0);
						theBoard->removeNumberByPoint(otherPlayer->getNextPosition());
						otherPlayer->wonStage();
						Screen::printMessageOnBoard("Snake 2 is WRONG: +1 point for snake 1", Color::YELLOW);
					}
					else
					{
						Snake* otherPlayer = theBoard->getSnake(1);
						theBoard->removeNumberByPoint(otherPlayer->getNextPosition());
						otherPlayer->wonStage();
						Screen::printMessageOnBoard("Snake 1 is WRONG: +1 point for snake 2", Color::LIGHTBLUE);
					}
				}
				return true;
			}
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
	theBoard->printBoard();
	theBoard->printScore();
}

void TheGame::_restartStage()
{
	theBoard->resetBoard();
	theBoard->printScore();
	status = Game::RUNNING;
}

void TheGame::_nextStage()
{
	if (status == Game::PAUSE)
	{
		Screen::clearScreen();
		theBoard->resetBoard();
	}

	theBoard->prepareNextStage();
	theBoard->printScore();

	status = Game::RUNNING;
}


void TheGame::_newGame()
{
	Screen::clearScreen();
	theBoard->resetBoard();
	theBoard->getSnake(0)->setSnakeSize(3);
	theBoard->getSnake(1)->setSnakeSize(3);
	theBoard->printScore();
	status = Game::RUNNING;
}
