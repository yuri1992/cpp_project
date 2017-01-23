#ifndef _MISSION_BASE_H_
#define _MISSION_BASE_H_
#include <string>
#include <fstream>
//#include <list>
#include "CalculatorQuestion.h"
#include "Mission.h"
#include <vector>
const string DIV = "DIV"; //collect a number that divides by X
const string POW = "POW"; //find pow of x^2
const string PRM = "PRM"; //find a prime num
const string MUL = "MUL"; //collect a number that is a multiplication of X
const string SQR = "SQR"; //collect a number that has a natural square root
const string REM = "REM"; //collect a number that divided by X has a remiander of Y
const string CLC = "CLC"; //calculator question- generated randomally



class MissionBase
{

	CalculatorQuestion* calcQuestion = nullptr;

	vector<Mission> missionVector;
	static bool isPrime(int number);
	int currentMission;
	string currentMissionText;
	string currentMissionCode;

public:
	MissionBase();
	~MissionBase();

	string getMissionText() const;
	bool isSolved(int number);
	int generateNextNumber();
	int nextMission();
};
#endif