#include "BoardManager.h"
#include "io_utils.h"
#include <iostream>
#include <string>
#include <map>


BoardManager::BoardManager(const char* boardToCopy[ROWS]) {
	setBoard(boardToCopy);
}

void BoardManager::printBoard() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printCell(i, j);
		}
	}
}


//the function printBoard - printed the history of the snakes (full path they walked)
//so when continuing i run this function. (TEMP SOLUTION)
void BoardManager::printBoardWithoutSnakePath() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			//that runs this fun that just prints empty whenever it sees a snake
			printCellWithoutSnake(i, j);
		}
	}
}




void BoardManager::printCell(int row, int col, Color color) {
	setTextColor(color);
	gotoxy(col, row);
	std::cout << board[row][col];
	std::cout.flush();
}

void BoardManager::printCell(const Point& pt, Color color) {
	printCell(pt.getY(), pt.getX(), color);
}



void BoardManager::printCellWithoutSnake(int row, int col, Color color) {
	if (board[row][col] == '@' || board[row][col] == '#') return;
	setTextColor(color);
	gotoxy(col, row);
	std::cout << board[row][col];
	std::cout.flush();
}


int getDigitsNumber(int number) {
	int res = 0;
	while (number > 0) {
		res++;
		number /= 10;
	}
	return res;
}

bool BoardManager::isValidNumberCell(int row, int col, int number) {
	if (board[row][col] != ' ')
		return false;

	int digitsNumber = getDigitsNumber(number);

	if (col + digitsNumber > COLS)
		return false;

	for (int i = 0; i < digitsNumber; i++) {
		if ((board[row][col + i] != ' ' || // cell itself is empty
			board[row + 1][col + i] != ' ' || // the upper cell is empty
			board[row - 1][col + i] != ' ')) {
			return false;
		}
	}

	// checking the most left cell if empty or end or board
	if (col - 1 > 0)
		if (board[row][col - 1] != ' ')
			return false;

	// checking the most right cell if empty or end or board
	if (col + digitsNumber < COLS)
		if (board[row][col + digitsNumber] != ' ')
			return false;

	return true;
}

void BoardManager::printNumberFromPoint(int randRow, int randCol, int number) {
	int digitsNumber = getDigitsNumber(number);
	int tempNum = number;
	for (int i = digitsNumber; i > 0; i--) {
		board[randRow][randCol + i] = '0' + tempNum % 10;
		pointToNumber[Point(randCol + i, randRow)] = number;
		printCell(randRow, randCol + i);
		tempNum /= 10;
	}
}

void BoardManager::setNextNumber(int number) {
	bool isNumberSet = false;
	int randRow, randCol;
	while (!isNumberSet) {
		randRow = (rand() % (ROWS - 4)) + 4;
		randCol = rand() % COLS;
		if (isValidNumberCell(randRow, randCol, number)) {
			printNumberFromPoint(randRow, randCol, number);
			break;
		}
	}
}

int BoardManager::getCellNumber(const Point& pt) {
	if (pointToNumber.find(pt) != pointToNumber.end()) {
		return pointToNumber.at(pt);
	}
	return -1;

}

void BoardManager::setBoard(const char* boardToCopy[ROWS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			originalBoard[i][j] = boardToCopy[i][j];
			board[i][j] = originalBoard[i][j];
		}
		originalBoard[i][COLS] = '\0';
		board[i][COLS] = '\0';
	}
}

void BoardManager::printScoreBoard(string currentQuestion, int snake1Score, int snake2Score) {
	setTextColor(LIGHTGREY);
	gotoxy(0, 0);
	cout <<
		//	      10        20        30        40        50        60        70       79
		//1234567890123456789012345678901234567890123456789012345678901234567890123456789
		"Mission:                                                                        " << endl <<
		"                                                                                " << endl <<
		"  Snake 1 Score: 8                                            Snake 2 Score: 7  " << endl <<
		"--------------------------------------------------------------------------------" << endl;
	gotoxy(9, 0);
	cout << currentQuestion;
	gotoxy(17, 2);
	cout << snake1Score << " ";
	gotoxy(77, 2);
	cout << snake2Score << " ";
	cout << flush;
}

void BoardManager::printMessageOnBoard(string message) {
	gotoxy(21, 1);
	cout << message;
	Sleep(2000);  // a short wait until the game continues
	gotoxy(21, 1);
	cout << "                                                        ";

}

BoardManager::~BoardManager() {
	// Todo we should implement desctrouctor logic
}
