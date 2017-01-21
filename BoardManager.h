#ifndef _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

#include <unordered_map>
#include "Point.h"
#include "Snake.h"
#include "MissionBase.h"

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
			size_t h1 = std::hash<double>()(k.getX());
			size_t h2 = std::hash<double>()(k.getY());
			return (h1 ^ (h2 << 1));
		}
	};
};

enum
{
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
	void resetBoard();

	void printBoard();
	void cleanBoard();
	void printScore() const;
	void printAmmo() const;
	void printBoardWithoutSnakePath();
	void printCell(int row, int col, Color color = Color::LIGHTGREY);
	void printCell(const Point& pt, Color color = Color::LIGHTGREY);
	void printCellWithoutSnake(int row, int col, Color color = Color::LIGHTGREY);
	char getCell(const Point& pt) { return board[pt.getY()][pt.getX()]; };
	void setCell(int row, int col, char ch) { board[row][col] = ch; }
	void setCell(const Point& pt, char ch) { board[pt.getY()][pt.getX()] = ch; }
	void removeCell(int row, int col) { board[row][col] = ' '; }
	void removeCell(const Point& p) { removeCell(p.getY(), p.getX()); }

	Snake* getSnakeInCell(const Point& p);
	bool isOccupatiedBySanke(const Point& p);

	bool isValidNumberCell(int row, int col, int number);
	void printNumberByPoint(int rand_row, int rand_col, int number, Color color = Color::LIGHTGREY);
	void printNumberByPoint(const Point& pt, int number, Color color = Color::LIGHTGREY);
	Point getRandomPosition(int size);
	int getNumberInCell(const Point& pt);
	void setNextNumber();

	void next();

	void removeNumberfromBoard(int number);
	bool removeNumberByPoint(const Point& pt);
	void prepareNextStage();
	void blinkPoint(int number, const Point& pt);
	bool findSolveOnBoard();
	int getNumberOfNumbers();

	// getters setters
	Snake* getSnake(int index) { return snakes[index]; }
	std::unordered_map<Point, int> getPointToNumber() const { return pointToNumber; }
	void setPointToNumber(const std::unordered_map<Point, int>& point_to_number) { pointToNumber = point_to_number; }
	std::unordered_map<int, Point> getNumberToPoint() const { return numberToPoint; }
	void setNumberToPoint(const std::unordered_map<int, Point>& number_to_point) { numberToPoint = number_to_point; }
	void setMission(MissionBase* _mission) { mission = _mission; }
	MissionBase* getMission() { return mission; }
};

#endif
