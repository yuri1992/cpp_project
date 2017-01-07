#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Point.h"
#include "GameSettings.h"
#include "SnakeBody.h"
#include "Gun.h"

class BoardManager;

enum SnakeStatus
{
	REGULAR = 0,
	HIT = 1,
};

class Snake
{
	enum
	{
		KEYS_SIZE = 5,
	};


	Gun gun;
	BoardManager* theBoard = nullptr;
	SnakeBody* body;
	SnakeStatus status = SnakeStatus::REGULAR;
	char arrowKeys[KEYS_SIZE];
	int steps = 0;
	int points = 0;
public:
	Snake(Color color, char bodyChar, BoardManager* boardManager,
	      const char* keys, Point startPoint, Direction dir);
	void printSnake();
	void handleKey(int dir);
	void goToPoint(const Point& pt);
	void goToPoint(const Point& pt, int direction);
	void resetSnake(const Point& pt, int direction, int size);
	void gotHit();
	void move();
	void shoot();
	void wonStage();
	bool isWinGame() const { return points == GameSettings::POINT_TO_WIN_THE_GAME; }
	void resetGun();
	void doNext();

	// getter and setters to SnakeBody (proxy)
	int getKeyDirection(char key);
	Point getNextStep() const { return body->getNextPoint(); }
	Color getColor() const { return body->getColor(); }
	void setSnakeDirection(int direction) { body->setDirection(direction); }
	int getAmmo() { return gun.getAmmo(); }
	Gun* getGun() { return &gun; };
	void setSnakeSize(int size) { body->setCurrentSize(size); }

	// getters and setters
	int getShottingKey() { return arrowKeys[4]; }
	void setStatus(SnakeStatus st) { status = st; }
	SnakeStatus getStatus() { return status; }
	void setSteps(int st) { steps = st; }
	int getSteps() { return steps; }
	int getPoints() const { return points; }
	void setPoints(int point) { points = point; }
	void setBoardManager(BoardManager* _theBoard) { theBoard = _theBoard; }
	void setArrowKeys(const char* keys);


private:
	bool _isNextStepValid();
};

#endif
