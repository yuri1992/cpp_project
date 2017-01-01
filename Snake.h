#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Point.h"
#include "SnakeBody.h"
#include "BoardManager.h"
#include "GameSettings.h"
#include "Gun.h"

class Snake
{
	enum
	{
		KEYS_SIZE = 5
	};
	Gun gun;
	BoardManager* theBoard;
	SnakeBody* body;
	char arrowKeys[KEYS_SIZE];
	int points = 0;
public:
	Snake(Color color, char bodyChar, BoardManager* theBoard, const char* keys, Point startPoint, Direction dir);

	void printSnake();
	void handleKey(int dir);
	void goToPoint(const Point& pt);
	void goToPoint(const Point& pt, int direction);
	void resetSnake(const Point& pt, int direction, int size);
	void move();
	void shoot();
	void wonStage();
	bool isWinGame() const { return points == GameSettings::POINT_TO_WIN_THE_GAME; };
	void doNext();

	// getter and setters to SnakeBody (proxy)
	int getKeyDirection(char key);
	Point getNextStep() const { return body->getNextPoint(); }
	Color getColor() const { return body->getColor(); }
	void setSnakeDirection(int direction) { body->setDirection(direction); };
	void setSnakeSize(int size) { body->setCurrentSize(size); }

	// getters and setters
	int getShottingKey() { return arrowKeys[4]; }
	int getPoints() const { return points; }
	void setBoardManager(BoardManager* _theBoard) { theBoard = _theBoard; }
	void setArrowKeys(const char* keys);
	void setPoints(int point) { points = point; }

private:
	bool _isNextStepValid();
};

#endif
