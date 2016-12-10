#pragma once
#include "io_utils.h"

using namespace std;
class MissionBase
{

	enum
	{
		SIZE = 60,
	};

	enum MissionStatus {
		PRIME_NUM = 0,   //2,3,5,7,11,13,17...
		DIVIDED_BY_4 = 1,   //0,4,8,12..
		MULTI_OF_7 = 2, //7,14,21..
		NATURAL_SQRT = 3,   //has a natural sqrt:  4,9,16,25,36....
		DIV_BY_7_REMAIN_3 = 4,  //divided by 7 leaves remainder of 3: 3,10,17,....
		POW_2_OF_13=5   //1 number: collect 13^2 = 169 (last num)..
	};

	int Numbers[SIZE];
	bool isPrime(int number);
	int currentMission;
	string currentMissionText;

public:
	MissionBase();
	~MissionBase();

	bool isSolved(int number);
	int generateNextNumber();
	int NextMission();
};
