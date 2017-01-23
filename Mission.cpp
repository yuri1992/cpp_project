#include <cmath>
#include "Mission.h"


using namespace std;

string Mission::getText() const
{
	char output[70];
	const char *cstr = missionText.c_str();
	sprintf(output, cstr, variables[0],variables[1]);

	return output;
	return missionText;
}
