#include <cmath>
#include "MissionBase.h"

using namespace std;

MissionBase::MissionBase()
{
	nextMission();
}

MissionBase::~MissionBase()
{
}

bool MissionBase::isPrime(int number)
{
	if (number < 2) return false;
	if (number == 2) return true;
	if (number % 2 == 0) return false;
	for (int i = 3; (i * i) <= number; i += 2)
	{
		if (number % i == 0) return false;
	}
	return true;
}

string MissionBase::getMissionText() const
{
	return currentMissionText;
}

bool MissionBase::isSolved(int number)
{
	double sqrtOfNum;
	int tempCurrentMission = 0;
	bool answer = false;


	switch (currentMission)
	{
	case MissionStatus::PRIME_NUM:
		answer = isPrime(number);
		break;
	case MissionStatus::DIVIDED_BY_4:
		answer = (number % 4 == 0);
		break;
	case MissionStatus::MULTI_OF_7: //SAME AS DIVIDED BY
		answer = (number % 7 == 0);
		break;
	case MissionStatus::NATURAL_SQRT:
		sqrtOfNum = sqrt(number);
		answer = (floor(sqrtOfNum) == sqrtOfNum);
		break;
	case MissionStatus::DIV_BY_7_REMAIN_3:
		answer = (number % 7 == 3);
		break;
	case MissionStatus::POW_2_OF_13:
		answer = (number == 169);
		break;
	default:
		return false;
	}
	return answer;
}


int MissionBase::generateNextNumber()
{
	//0 to 2 for range of numbers
	/*
	0: 0-25
	1: 26-81
	2: 82-169
	*/
	int ans;
	int numberRange = rand() % 3;


	//% for the number range and +x for the starting number X
	switch (numberRange)
	{
	case 0:
		ans = rand() % 25;
		break;
	case 1:
		ans = rand() % 56 + 26;
		break;
	case 2:
		ans = rand() % 87 + 82;
		break;
	default: ans = 0;
	}

	return ans;
}

int MissionBase::nextMission()
{
	currentMission = rand() % 6;
	switch (currentMission)
	{
	case MissionStatus::PRIME_NUM:
		currentMissionText = "Collect a prime number";
		break;
	case MissionStatus::DIVIDED_BY_4:
		currentMissionText = "Collect a number that divides by 4";
		break;
	case MissionStatus::MULTI_OF_7: //SAME AS DIVIDED BY
		currentMissionText = "Collect a number that divides by 7";
		break;
	case MissionStatus::NATURAL_SQRT:
		currentMissionText = "Collect a number that has a natural square root";
		break;
	case MissionStatus::DIV_BY_7_REMAIN_3:
		currentMissionText = "Collect a number that divided by 7 has remainder of 3";
		break;
	case MissionStatus::POW_2_OF_13:
		currentMissionText = "collect the number 13^2";
		break;
	default:
		currentMissionText = "....";
	}

	return currentMission;
}
