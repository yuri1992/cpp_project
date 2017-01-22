#ifndef _NUMBEREATER_H_
#define _NUMBEREATER_H_
#include "BasePlayerBoard.h"
#include "GameSettings.h"

class NumberEater : public BasePlayerBoard
{
public:
	NumberEater(int direction, const Point& pt, BoardManager* theBoard)
		: BasePlayerBoard(direction, pt, theBoard, NUMBER_EATER, MAGENTA)
	{
		setSpeed(2);
	}
	~NumberEater();
	void destroy() override;
	bool seekSulotion();
	void _doNext();
	void doNext() override;
	string type() override { return "numbereater"; };
};
#endif
