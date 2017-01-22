#ifndef _FLYINGCOL_H_
#define _FLYINGCOL_H_
#include "BasePlayerBoard.h"
#include "GameSettings.h"

class FlyingCol : public BasePlayerBoard
{
public:

	FlyingCol(int direction, const Point& pt, BoardManager* theBoard)
		: BasePlayerBoard(direction, pt, theBoard, FLYING_COL, LIGHTGREEN)
	{
	}

	FlyingCol(int direction, const Point& pt, BoardManager* theBoard, bool _isWallWalker)
		: FlyingCol(direction, pt, theBoard)
	{
		setIsWallWalker(_isWallWalker);
	};
	~FlyingCol();
	void destroy() override;
	void doNext() override;
	string type() override { return "flyingcol"; };
};
#endif
