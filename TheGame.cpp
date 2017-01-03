#include "TheGame.h"
#include <string>

TheGame::TheGame()
{
	// initialize Board
	boardManager = new BoardManager();
}

TheGame::~TheGame()
{
	delete boardManager;
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
		Snake* playerOne = boardManager->getSnake(0);
		Snake* playerTwo = boardManager->getSnake(1);
		if (_kbhit())
		{
			key = _getch();

			if (key == ESC)
			{
				_pause();
				return;
			}
			playerOne->handleKey(key);
			playerTwo->handleKey(key);
		}

		if (isStageSolved())
		{
			if (playerOne->isWinGame())
			{
				Screen::printMessageOnBoard("Snake 1 Won The game!!", playerOne->getColor());
				_finishGame();
				return;
			}
			else if (playerTwo->isWinGame())
			{
				Screen::printMessageOnBoard("Snake 2 Won The game!!", playerTwo->getColor());
				_finishGame();
				return;
			}
			else
			{
				_nextStage(); // the won stage print is in isStageSolved
				return;
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
		{
			boardManager->setNextNumber();
		}
			

		playerOne->doNext();
		playerTwo->doNext();

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
		Snake* snake = boardManager->getSnake(i);
		pt = snake->getNextStep();
		n = boardManager->getNumberInCell(pt);

		if (n >= 0)
		{
			boardManager->removeNumberfromBoard(n);
			if (boardManager->getMission()->isSolved(n))
			{
				//boardManager->removeNumberfromBoard(n);
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
					Snake* otherPlayer = boardManager->getSnake(0);
					boardManager->removeNumberByPoint(otherPlayer->getNextStep());
					otherPlayer->wonStage();
					Screen::printMessageOnBoard("Snake 2 is WRONG: +1 point for snake 1", Color::YELLOW);
				}
				else
				{
					Snake* otherPlayer = boardManager->getSnake(1);
					boardManager->removeNumberByPoint(otherPlayer->getNextStep());
					otherPlayer->wonStage();
					Screen::printMessageOnBoard("Snake 1 is WRONG: +1 point for snake 2", Color::LIGHTBLUE);
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
	boardManager->printScore();
}

void TheGame::_restartStage()
{
	boardManager->resetBoard();
	boardManager->printScore();
	status = Game::RUNNING;
}

void TheGame::_nextStage()
{
	if (status == Game::PAUSE)
	{
		Screen::clearScreen();
		boardManager->resetBoard();
	}

	boardManager->prepareNextStage();
	boardManager->printScore();

	status = Game::RUNNING;
}


void TheGame::_newGame()
{
	Screen::clearScreen();
	boardManager->resetBoard();
	boardManager->getSnake(0)->setSnakeSize(3);
	boardManager->getSnake(1)->setSnakeSize(3);
	boardManager->printScore();
	status = Game::RUNNING;
}
