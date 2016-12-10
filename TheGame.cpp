#include "TheGame.h"
#include "BoardManager.h"
#include "Point.h"
#include "Snake.h"
#include "io_utils.h"

TheGame::TheGame(const char* board[ROWS]) {
	// initialize Board
	boardManager = new BoardManager(board);

	// initialize Two Snakes on screen
	Point ptStart1 = Point(10, 9);
	Point ptStart2 = Point(70, 9);
	snakes = new Snake*[2];
	snakes[0] = new Snake(YELLOW, '@', boardManager, "imjl", ptStart1, DIRECTION_RIGHT);
	snakes[1] = new Snake(LIGHTBLUE, '#', boardManager, "wxad", ptStart2, DIRECTION_LEFT);
}

void TheGame::init() {
	boardManager->printBoard();
	snakes[0]->printSnake();
	snakes[1]->printSnake();
}

void TheGame::printScreen() {
	if (status == Game::STARTED || status == Game::SHOW_MAIN_MENU)
		showMainMenu();
	else if (status == Game::PAUSE || status == Game::SHOW_PAUSE_MENU)
		showPauseMenu();
	else if (status == Game::SHOW_INFORMATION)
		showInformation();
}

void TheGame::run() {

	printScreen();

	do {
		if (status == Game::STARTED ||
			status == Game::SHOW_MAIN_MENU ||
			status == Game::PAUSE ||
			status == Game::SHOW_PAUSE_MENU ||
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

		if (!isStageSolved()) {
			snakes[0]->move();
			snakes[1]->move();
			if (step++ % 5 == 0) {
				boardManager->setNextNumber(mission.generateNextNumber());
			}
			Sleep(400);
		}


		boardManager->printScoreBoard(mission.getMissionText(), snakes[0]->getPoints(), snakes[1]->getPoints());
	}
}

bool TheGame::isStageSolved() {
	/*
	 * return True when stage is completed!! not solved currently
	 */
	Point pt;
	int n, i;

	for (i = 0; i < 2; i++) {
		pt = snakes[i]->getNextStep();
		n = boardManager->getCellNumber(pt);

		if (n >= 0) {
			if (mission.isSolved(n)) {
				snakes[i]->wonStage();
				if (snakes[i]->isWinGame()) {
					// TODO : promot a win game message
					//_newGame();
					//TODO GO TO MAIN MENU AFTER WIN
				}
				else {
					// TODO : promot a won stage message
					_nextMission();
				}
				return true;
			}
			else {
				// TODO : promot a lose game message
				_nextMission();
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
		if (status == Game::STARTED || status == Game::SHOW_MAIN_MENU) {
			// handling Main Menu keys press
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
		else if (status == Game::PAUSE || status == Game::SHOW_PAUSE_MENU) {
			// handling Full Menu keys press
			switch (key) {
			case NUM_1:
				_exit();
				break;
			case NUM_2:
				_showMainMenu();
				break;
			case NUM_3:
				_continue();
				break;
				// (4)Restart Mission: delete all numbers + put snakes on starting position 
				//+ reset clock (from forum)  + [[ same snake size(i think- waiting for answer in forum)]]
			case NUM_4:
				_restartMission();
				break;
			case NUM_5:
				_nextMission();
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
				_showMainMenu();
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

void TheGame::showMainMenu() {
	clearScreen();
	gotoxy(0, 4); cout << "--------------------------------------------------------------------------------";
	gotoxy(35, 11); cout << "Snake Game";
	gotoxy(32, 12); cout << "-----------------";
	gotoxy(32, 14); cout << "(1) Instructions.";
	gotoxy(32, 15); cout << "(2) Play game!";
	gotoxy(32, 16); cout << "(9) Exit.";
	//gotoxy()
}

void TheGame::showPauseMenu() {




	clearScreen();
	cout <<
		"                                                                                " << endl <<
		"                                  Game Paused                                   " << endl <<
		"                               ----------------                                 " << endl <<
		"                               (1) Exit game.                                   " << endl <<
		"                               (2) Main menu.                                   " << endl <<
		"                               (3) Resume game.                                 " << endl <<
		"                               (4) Restart mission                              " << endl <<
		"                               (5) Start new mission                            " << endl <<
		"                               (6) Restart game.                                " << endl <<
		"                                                                                " << endl <<
		"                                                                                " << endl <<
		"                                                                                " << endl <<
		"		                                                                         " << endl <<
		"                                                                                " << endl <<
		"                                                                                " << endl;
}




void TheGame::_start() {
	status = Game::RUNNING;
	init();
}

void TheGame::_continue() {
	status = Game::RUNNING;
	clearScreen();
	boardManager->printBoardWithoutSnakePath();
}

void TheGame::_restartMission() {
	clearScreen();
	// TODO ITAY : we should be able to restart the game to same position of the initial mission
	status = Game::RUNNING;
}

void TheGame::_nextMission() {
	//clearScreen();
	mission.nextMission();
	status = Game::RUNNING;
}




void TheGame::_newGame() {
	// TODO ITAY: we should be able restart all the game to initial point.
	status = Game::RUNNING;
}
