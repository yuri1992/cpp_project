#include "SnakesGame.h"

void SnakesGame::run() {
	displayScreen();
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
			// move and check if the snake ate a number
			Point pos = snakes[i].move(keyPressed);
			int num = getNumber(pos);
			gotoxy(60, 20+i);
			cout << snakes[i].getChar() << " x = " << pos.getX() << ", y = " << pos.getY() << "   ";
			if (num != -1) {
				gotoxy(10, 10);
				cout << "snake " << snakes[i].getChar() << " got number : " << num << "!";
				Sleep(350);
				gotoxy(10, 10);
				cout << "                                                                 ";
				displayScreen();
			}
		}
	}
}
