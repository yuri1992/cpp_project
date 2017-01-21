#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Point.h"
#include "GameSettings.h"
#include "Gun.h"

class BoardManager;

enum SnakeStatus
{
	REGULAR = 0,
	HIT = 1,
};

class Snake : public BasePlayerBoard
{
	enum
	{
		KEYS_SIZE = 5,
	};

	Gun gun;
	SnakeStatus status = SnakeStatus::REGULAR;
	char arrowKeys[KEYS_SIZE];
	int steps = 0;
	int points = 0;
public:
	Snake(Color color, char bodyChar, BoardManager* boardManager,
	      const char* keys, Point startPoint, Direction dir);

	void doNext() override;
	void destroy() override {};
	void shoot();
	void resetGun();

	void handleKey(int dir);

	void goToPoint(const Point& pt);
	void goToPoint(const Point& pt, int direction);
	void resetSnake(const Point& pt, int direction, int size);
	void setPosition(const Point& newPosition) override;
	void gotHit();
	void increaseSnakeBody();
	void wonStage();
	bool isWinGame() const { return points == GameSettings::POINT_TO_WIN_THE_GAME; }

	int getKeyDirection(char key);

	// getters and setters
	int getAmmo() { return gun.getAmmo(); }
	Gun* getGun() { return &gun; };
	int getShottingKey() { return arrowKeys[4]; }

	int getSnakeSize() const { return int(pos.size()); }

	void setStatus(SnakeStatus st) { status = st; }
	SnakeStatus getStatus() const { return status; }

	void setSteps(int st) { steps = st; }
	int getSteps() const { return steps; }

	int getPoints() const { return points; }
	void setPoints(int point) { points = point; }

	void setArrowKeys(const char* keys);

	void setSnakeSize(int size) { pos.resize(size); }

private:
	bool _isNextStepValid() const;
};

#endif
