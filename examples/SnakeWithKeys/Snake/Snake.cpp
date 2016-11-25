#include "Snake.h"

Snake::Snake(const Point& head, char c1, Direction dir) {
	c = c1;
	direction = dir;
	body[0] = head;
	body[0].draw(c);
	for (int i = 1; i < 7; ++i) {
		body[i] = body[i - 1];
		body[i].move();
		body[i].draw(c);
	}
}
void Snake::setKeys(char keyLeft, char keyRight, char keyUp, char keyDown) {
	dirKeys[Direction::LEFT] = keyLeft;
	dirKeys[Direction::RIGHT] = keyRight;
	dirKeys[Direction::UP] = keyUp;
	dirKeys[Direction::DOWN] = keyDown;
	isRandom = false;
}
void Snake::changeDir(char keyPressed) {
	for (const auto& key : dirKeys) {
		if (key == keyPressed) {
			// the smart and neat trick suggested by Yoav Lahav! 
			// if we use the refrerence of key, we can take its address and calc its place in the array
			// and the place in the array gives the value of the direction!
			// (yes, we could have use a regular loop with an index...)
			direction = (Direction)(&key - dirKeys);
			return;
		}
	}
}
void Snake::move(char keyPressed) {
	body[6].draw(' ');
	for (int i = 6; i > 0; --i) {
		body[i] = body[i - 1];
	}
	if (isRandom) {
		body[0].move();
	}
	else {
		changeDir(keyPressed);
		body[0].move(direction);
	}
	body[0].draw(c);
}

