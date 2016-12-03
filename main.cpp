#include <windows.h>
#include <iostream>
using namespace std;

#include "TheSnakesGame.h"
#include "_board.h"

int main() {
	TheSnakesGame game = TheSnakesGame(board_example);
	game.run();
}