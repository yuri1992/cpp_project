#ifndef CALCULATOR_QUESTION
#define CALCULATOR_QUESTION
#include <iostream>
#include <string>

using namespace std;


class CalculatorQuestion
{

	enum
	{
		PLUS = 0,
		MINUS = 1,
		MULTIPLY = 2,
		DIVIDE = 3
	};

	int op1, op2;
	int ansAfterOp2, ansAfterOp1;
	int nums[4];
	int hiddenAnswerIndex;
	int answer;
	static bool isPrime(int);
	void createNumsXY(int op, int& x, int& y);
	int workOperatorOn2Nums(int givenOperator, int firstNum, int secondNum);
	bool isSecondOperatorFirst();
	void generateNumbers(bool);
	string getOperatorChar(int givenOp);
	int pickHiddenIndex();
public:

	CalculatorQuestion();
	//void recreateQuestion();
	int getAnswer() { return answer; };
	string getFunctionString();
	// num1 [op1] num2 [op2] num3 = num4
};







#endif