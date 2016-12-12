#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Point.h"
#include "SnakeBody.h"
#include "BoardManager.h"
#include "GameSettings.h"

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
	~Snake();

	void printSnake();
	void handleKey(int dir);
	void goToStartPoint(const Point& pt);
	void move();
	void wonStage();
	bool isWinGame() const { return points == GameSettings::POINT_TO_WIN_THE_GAME; };

	// getter and setters to SnakeBody (proxy)
	int getKeyDirection(char key);
	Point getNextStep() const { return body->getNextPoint(); }
	Color getColor() const { return body->getColor(); }
	void setSnakeDirection(int direction) { body->setDirection(direction); };
	void setSnakeSize(int size) { body->setCurrentSize(size); }

	// getters and setters
	int getPoints() const { return points; }
	void setBoardManager(BoardManager* _theBoard) { theBoard = _theBoard; }
	void setArrowKeys(const char* keys);
	void setPoints(int point) { points = point; }

private:
	bool _isNextStepValid();
};

#endif
