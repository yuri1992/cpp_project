#include "TheGame.h"
#include "BoardManager.h"
#include "Point.h"
#include "Snake.h"
#include "io_utils.h"

TheGame::TheGame(const char* board[ROWS]) {
	// initialize Board
	boardManager = new BoardManager(board);

	// initialize Two Snakes on screen
	snakes = new Snake*[2];
	snakes[0] = new Snake(YELLOW, '@', boardManager, "imjl", Point(10, 9), DIRECTION_RIGHT);
	snakes[1] = new Snake(LIGHTBLUE, '#', boardManager, "wxad", Point(70, 9), DIRECTION_LEFT);
}

void TheGame::init() {
	boardManager->printBoard();
	snakes[0]->printSnake();
	snakes[1]->printSnake();
}

void TheGame::printScreen() {
	if (status == Game::STARTED || status == Game::SHOW_QUICK_MENU)
		showQuickMenu();
	else if (status == Game::PAUSE || status == Game::SHOW_FULL_MENU)
		showFullMenu();
	else if (status == Game::SHOW_INFORMATION)
		showInformation();
}

void TheGame::run() {

	printScreen();

	do {
		if (status == Game::STARTED ||
			status == Game::SHOW_QUICK_MENU ||
			status == Game::PAUSE ||
			status == Game::SHOW_FULL_MENU ||
			status == Game::SHOW_INFORMATION) {
			_handleMenuKeyPress();
		}
		else {
			_handleGameKeyPress();
		}
	} while (true);
}


void TheGame::_handleGameKeyPress() {
	if (status == Game::RUNNING) {
		char key = 0;
		if (_kbhit()) {
			key = _getch();

			if (key == ESC) {
				_pause();
				return;
			}

			snakes[0]->handleKey(key);
			snakes[1]->handleKey(key);
		}

		if (!isStageSolved())
		{
			snakes[0]->move();
			snakes[1]->move();
			if (step++ % 5 == 0)
			{
				boardManager->setNextNumber(mission.generateNextNumber());
			}
			Sleep(400);
		}
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
				snakes[i]->wonStage();

				if (snakes[i]->isWinGame())
					_newGame(); // TODO : promot a win game message					
				else
					_nextStage(); // TODO : promot a won stage message
				return true;
			}
			else
			{
				if (i == 1) {
					snakes[0]->wonStage();
					if (snakes[0]->isWinGame())
						_newGame(); // TODO : promot a win game message					
					else
						_nextStage(); // TODO : promot a won stage message
				}
				else
				{
					snakes[1]->wonStage();
					if (snakes[1]->isWinGame())
						_newGame(); // TODO : promot a win game message					
					else
						_nextStage(); // TODO : promot a won stage message
				}
				return true;
			}
		}
	}

	return false;
}

void TheGame::_handleMenuKeyPress() {
	if (_kbhit()) {
		char key = 0;
		key = _getch();
		if (status == Game::STARTED || status == Game::SHOW_QUICK_MENU) {
			// handling Quick Menu keys press
			switch (key) {
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
		else if (status == Game::PAUSE || status == Game::SHOW_FULL_MENU) {
			// handling Full Menu keys press
			switch (key) {
			case NUM_1:
				_exit();
				break;
			case NUM_2:
				_showFullMenu();
				break;
			case NUM_3:
				_continue();
				break;
			case NUM_4:
				_restartGame();
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
		else if (status == Game::SHOW_INFORMATION) {
			switch (key) {
			case NUM_9:
				_showQuickMenu();
			default:break;
			}
		}
	}
}

void TheGame::showInformation() {
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

void TheGame::showQuickMenu() {
	clearScreen();
	gotoxy(0, 4); cout << "--------------------------------------------------------------------------------";
	gotoxy(35, 11); cout << "Snake Game";
	gotoxy(32, 12); cout << "-----------------";
	gotoxy(32, 14); cout << "(1) Instructions.";
	gotoxy(32, 15); cout << "(2) Play game!";
	gotoxy(32, 16); cout << "(9) Exit.";
	//gotoxy()
}

void TheGame::showFullMenu() {

	// Todo ITAY: implement quick menu print
	// 1. erase all screen
	// 2. gotoxy middle screen
	// 3. print menu.
	cout << "Full " << endl;
}

void TheGame::_start() {
	status = Game::RUNNING;
	init();
}

void TheGame::_continue() {
	// TODO ITAY : we should print once again the board
	status = Game::RUNNING;
}

void TheGame::_restartGame() {
	// TODO ITAY : we should be able to restart the game to same position of the initial mission
	status = Game::RUNNING;
}

void TheGame::_nextStage() {
	status = Game::RUNNING;
	boardManager->prepareNextStage();
	mission.NextMission();
	snakes[0]->goToStartPoint(Point(10, 9));
	snakes[1]->goToStartPoint(Point(70, 9));
	Sleep(1000);
}

void TheGame::_newGame() {
	// TODO ITAY: we should be able restart all the game to initial point.
	status = Game::RUNNING;
}
