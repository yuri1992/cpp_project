#include <cmath>
#include "MissionBase.h"


using namespace std;

MissionBase::MissionBase()
{
	ifstream file;
	//list<Mission> missionList;
	//Mission* temp = new Mission();
	file.open("normalMode.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			string missionCode, missionText;
			int numOfVariables;
			int variables[2] = { 0,0 };
			file >> missionCode;
			file.get();
			getline(file, missionText);
			file >> numOfVariables;
			for (int i = 0; i < numOfVariables; ++i)
			{
				string tempStringNum;
				file >> tempStringNum;
				variables[i] = stoi(tempStringNum);

			}
			Mission* temp = new Mission(missionCode, missionText, variables);
			missionVector.push_back(*temp);
			delete temp;
		}
		file.close();
	}
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
	int var1 = missionVector.at(currentMission).getVariables()[0];
	int var2 = missionVector.at(currentMission).getVariables()[1];

	if(currentMissionCode == DIV)
	{
		answer = (number % var1 == 0);
	}

	else if (currentMissionCode == PRM)
	{
		answer = isPrime(number);
	}

	else if(currentMissionCode == POW)
	{
		answer = (number == pow(var1,2));
	}
	else if (currentMissionCode == MUL)
	{
		answer = (number % var1 == 0);
	}
	else if (currentMissionCode == SQR)
	{
		sqrtOfNum = sqrt(number);
		answer = (floor(sqrtOfNum) == sqrtOfNum);
	}
	else if (currentMissionCode == REM)
	{
		answer = (number % var1 == var1);
	}

	else if (currentMissionCode == CLC)
	{
		answer = number == calcQuestion->getAnswer();
	}
	else
	{
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
	currentMission = rand() % missionVector.size();
	Mission tempMission = missionVector.at(currentMission);
	currentMissionText = tempMission.getText();
	currentMissionCode = tempMission.getCode();
	if ( currentMissionCode == "CLC")
	{
		int numberDifficulty = tempMission.getVariables()[0];
		if (calcQuestion != nullptr) delete calcQuestion;
			calcQuestion = new CalculatorQuestion(numberDifficulty);
			currentMissionText = calcQuestion->getFunctionString();
	}
	return currentMission;
}
