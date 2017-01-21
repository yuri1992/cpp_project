#ifndef _BULLET_
#define _BULLET_

#include "Point.h"
#include "BasePlayerBoard.h"
#include "GameSettings.h"
class BoardManager;

class Bullet : public BasePlayerBoard
{
	Color color = RED;
public:
	Bullet(int direction, const Point& pt, BoardManager* theBoard)
		: BasePlayerBoard(direction, pt, theBoard, GUN_CHAR, RED) {};
	~Bullet();
	void doNext() override;
	void destroy() override;


	friend bool operator==(Bullet const& lhs, Bullet const& rhs)
	{
		return lhs.getDirection() == rhs.getDirection() && lhs.getPosition() == rhs.getPosition();
	}
};
#endif
