#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"
#include "SnakeBody.h"
#include "BoardManager.h"
class BoardManager;
class Snake
{
	enum
	{
		KEYS_SIZE = 4
	};

	BoardManager* theBoard;
	SnakeBody* body;
	char arrowKeys[KEYS_SIZE];
	int points = 0;
public:
	Snake(Color color, char bodyChar, BoardManager* theBoard, const char* keys, Point startPoint, Direction dir);
	void printSnake();
	void handleKey(int dir);
	Point getNextStep();
	void setSnakeSize(int size);
	int getKeyDirection(char key);
	void setSnakeDirection(int direction);
	void goToStartPoint(const Point& pt);
	void move();

	void wonStage();
	bool isWinGame();

	// getters and setters
	void setBoardManager(BoardManager* _theBoard) { theBoard = _theBoard; }

	void setArrowKeys(const char* keys)
	{
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
	}

	void setPoints(int point) { points = point; }
	int getPoints() { return points; }
private:
	bool _isNextStepValid();
};

#endif
