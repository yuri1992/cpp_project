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
	}

	FlyingRow(int direction, const Point& pt, BoardManager* theBoard, bool _isWallWalker)
		: BasePlayerBoard(direction, pt, theBoard, FLYING_ROW, LIGHTMAGENTA)
	{
		setIsWallWalker(_isWallWalker);
	};
	~FlyingRow();
	void destroy() override;
	void doNext() override;
};
#endif
