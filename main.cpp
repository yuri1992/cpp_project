#include <windows.h>
#include <iostream>
using namespace std;

#include "TheGame.h"
#include "_board.h"

int main() {
	TheGame game = TheGame(board_example);
	game.run();
}