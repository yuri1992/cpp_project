#ifndef _FLYINGROW_H_
#define _FLYINGROW_H_
#include "BasePlayerBoard.h"
#include "GameSettings.h"

class FlyingRow : public BasePlayerBoard
{
public:

	FlyingRow(int direction, const Point& pt, BoardManager* theBoard)
		: BasePlayerBoard(direction, pt, theBoard, FLYING_ROW, LIGHTMAGENTA)
	{
		setSpeed(2);
		setIsBulletproof(true);
	}

	FlyingRow(int direction, const Point& pt, BoardManager* theBoard, bool _isWallWalker)
		: FlyingRow(direction, pt, theBoard)
	{
		setIsWallWalker(_isWallWalker);
	};
	~FlyingRow();
	void destroy() override;
	void doNext() override;
	void _doNext();
	string type() override { return "flyingrow"; };
};
#endif
