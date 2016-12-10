#include "MissionBase.h"
#include "io_utils.h"

MissionBase::MissionBase() {
}


MissionBase::~MissionBase() {
}

bool MissionBase::isSolved(int number) {
	return false;
}

int MissionBase::generateNextNumber() {
	//0 to 2 for range of numbers
	/*
	0: 0-25
	1: 26-81
	2: 82-169
	*/
	int ans;
	int numberRange = rand() % 3;


	//% for the number range and +x for the starting number X
	switch (numberRange) {
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

	// TODO Itay [DONE]; Please implemnt the required logic for generating next nubmer
	// it should only generate number by the required logic without any additional requirements
}
