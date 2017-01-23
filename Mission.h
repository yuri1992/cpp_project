#include <string>
using namespace std;
class Mission
{

	string missionText;
	string missionCode;
	int variables[2];
public:
	Mission(string code, string text, int vars[2])
	{
		missionCode = code;
		missionText = text;
		variables[0] = vars[0];
		variables[1] = vars[1];
	}

	string getText() const;
	string getCode() const { return missionCode; }
	int* getVariables() { return variables; }

};
