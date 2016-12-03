#pragma once


class MissionBase
{
	enum
	{
		SIZE = 60
	};

	int Numbers[SIZE];
public:
	MissionBase();
	~MissionBase();
	bool isFinished();
	bool isSolved();
	void generateNextNumber();
};
