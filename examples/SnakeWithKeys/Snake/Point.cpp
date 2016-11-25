#include "Point.h"

void Point::changeDir(Direction dir) {
	switch (dir) {
	case Direction::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case Direction::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case Direction::UP:
		dir_x = 0;
		dir_y = -1;
		break;
	case Direction::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	}
}