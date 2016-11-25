#include <windows.h>
#include <iostream>
using namespace std;

#include "TheSnakesGame.h"
#include "_board.h"

int main() {
	TheSnakesGame game;
	game.setBoard(board_example);
	game.init();
	game.run();
}