#include "SnakesGame.h"

void SnakesGame::run() {
	while (true)
	{
		char keyPressed = 0;
		if (_kbhit()) {
			keyPressed = _getch();
			if (keyPressed == KEYS::ESC) {
				break;
			}
		}
		else {
			keyPressed = 0;
		}

		Sleep(50);
		for (size_t i = 0; i < size; ++i) {
			p[i].move(keyPressed);
		}
	}
}
