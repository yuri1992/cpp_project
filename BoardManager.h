#ifndef _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

#include <unordered_map>
#include "Point.h"
#include "Snake.h"
#include "MissionBase.h"
#include "FlyingRow.h"

using namespace std;

namespace std
{
	template <>
	struct hash<Point>
	{
		std::size_t operator()(const Point& k) const
		{
			using std::size_t;
			using std::hash;
			return (53 + std::hash<int>()(k.getX()) * 53 + std::hash<int>()(k.getY()));
		}
	};
};

enum
{
	BOTS_PLAYER = 5,
	ROWS = 24,
	COLS = 80
};

class BoardManager
{
	MissionBase* mission;
	Snake** snakes;
	BasePlayerBoard** bots;

	std::unordered_map<Point, int> pointToNumber;
	std::unordered_map<int, Point> numberToPoint;
	char board[ROWS][COLS + 1]; // this is the actual board we play on, i.e. changes on board are done here//
public:
	BoardManager();
	~BoardManager();
	void resetBoard();

	void printBoard();
	void cleanBoard();
	void printScore() const;
	void printAmmo() const;
	void printBoardWithoutSnakePath();
	void printCell(int row, int col, Color color = Color::LIGHTGREY);
	void printCell(const Point& pt, Color color = Color::LIGHTGREY);
	void printCellWithoutSnake(int row, int col, Color color = Color::LIGHTGREY);
	char getCell(const Point& pt) { 
		return board[pt.getY()][pt.getX()]; 
	};
	void setCell(int row, int col, char ch)
	{
		board[row][col] = ch;
	}
	void setCell(const Point& pt, char ch)
	{
		board[pt.getY()][pt.getX()] = ch;
	}
	void removeCell(int row, int col)
	{
		board[row][col] = ' ';
	}
	void removeCell(const Point& p) { removeCell(p.getY(), p.getX()); }

	BasePlayerBoard* getPlayerAtPoint(const Point& p) const;
	Snake* getSnakeInCell(const Point& p);
	bool isOccupatiedBySanke(const Point& p);

	bool isValidNumberCell(int row, int col, int number);
	void printNumberByPoint(int rand_row, int rand_col, int number, Color color = Color::LIGHTGREY);
	void printNumberByPoint(const Point& pt, int number, Color color = Color::LIGHTGREY);
	Point getRandomPosition(int size);
	int getNumberInCell(const Point& pt);
	void setNextNumber();
	void next();
	bool isGameWon();
	void handleKey(char key);

	void removeNumberfromBoard(int number);
	bool removeNumberByPoint(const Point& pt);
	void prepareNextStage();
	void blinkPoint(int number, const Point& pt);
	bool findSolveOnBoard();
	vector<Point> getAllSolution();
	int getNumberAmountOnBoard() const;

	// getters setters
	Snake* getSnake(int index) const { return snakes[index]; }
	void setMission(MissionBase* _mission) { mission = _mission; }
	MissionBase* getMission() const { return mission; }
};

#endif
