#include "CalculatorQuestion.h"
#include <cmath>



bool CalculatorQuestion::isSecondOperatorFirst()
{
	if ((op1 == PLUS || op1 == MINUS) && (op2 == DIVIDE || op2 == MULTIPLY)) return true;
	//if ((op1 == DIVIDE || op1 == MULTIPLY) && (op2 == PLUS || op2 == MINUS)) return false;
	//if ((op1 == DIVIDE || op1 == MULTIPLY) && (op2 == DIVIDE || op2 == MULTIPLY)) return false;
	//if ((op1 == PLUS || op1 == MINUS) && (op2 == PLUS || op2 == MINUS)) return false;
	return false;
}

CalculatorQuestion::CalculatorQuestion()
{
	op1 = rand() % 4; //0,1,2,3
	op2 = rand() % 4; //0,1,2,3
	bool op2First = isSecondOperatorFirst();
	generateNumbers(op2First);
	hiddenAnswerIndex = pickHiddenIndex();
	answer = nums[hiddenAnswerIndex];
};


int CalculatorQuestion::pickHiddenIndex()
{
	//could also pick the number in the answer spot.
	if (rand() % 2 == 0 && nums[4] <= 100 && nums[4] >= 0) return 3;
	return rand() % 3;
}

bool CalculatorQuestion::isPrime(int number)
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


void CalculatorQuestion::createNumsXY(int op, int& x, int& y)
{
	if (op == DIVIDE)
	{
		x = (rand() % 50) + 1;
		y = (rand() % 50) + 1;
		//if the first number is prime so for the divide ill get eighter 1 or the number itself... to keep it from doing unnecessary randoms
		if (isPrime(x))
			y = (rand() % 2 == 0) ? 1 : x;
		else
		{
			while (x % y != 0)
				y = rand() % 20 + 1;
		}
	}
	else
	{
		x = rand() % 60 + 1;
		y = rand() % 60 + 1;
	}
}



int CalculatorQuestion::workOperatorOn2Nums(int givenOperator, int firstNum, int secondNum)
{
	int ans;
	switch (givenOperator)
	{
	case PLUS:
		ans = firstNum + secondNum;
		break;
	case MINUS:
		ans = firstNum - secondNum;
		break;
	case MULTIPLY:
		ans = firstNum * secondNum;
		break;
	case DIVIDE:
		ans = firstNum / secondNum;
		break;
	default:
		ans = 999999; //shouldnt ever get here though..
	}

	return ans;
}

void CalculatorQuestion::generateNumbers(bool op2First)
{

	if (op2First)
	{
		createNumsXY(op2, nums[1], nums[2]);
		ansAfterOp2 = workOperatorOn2Nums(op2, nums[1], nums[2]);
		nums[0] = op1 == DIVIDE ? ansAfterOp2 * 3 : rand() % 60 + 1;
		nums[3] = ansAfterOp1 = workOperatorOn2Nums(op1, nums[0], ansAfterOp2);
	}

	else
	{
		createNumsXY(op1, nums[0], nums[1]);
		ansAfterOp1 = workOperatorOn2Nums(op1, nums[0], nums[1]);
		nums[2] = rand() % 30 + 1;
		if (op2 == DIVIDE)
		{
			//if the first number is prime so for the divide ill get eighter 1 or the number itself... to keep it from doing unnecessary randoms
			if (isPrime(ansAfterOp1))
				nums[2] = (rand() % 2 == 0) ? 1 : ansAfterOp1;
			else
			{
				while (ansAfterOp1 % nums[2] != 0)
					nums[2] = rand() % 20 + 1;
			}
		}
		nums[3] = ansAfterOp2 = workOperatorOn2Nums(op2, ansAfterOp1, nums[2]);
	}
}

char* CalculatorQuestion::getOperatorChar(int givenOp)
{
	char* ans;
	switch (givenOp)
	{
	case PLUS:
		ans = "+";
		break;
	case MINUS:
		ans = "-";
		break;
	case MULTIPLY:
		ans = "*";
		break;
	case DIVIDE:
		ans = "/";
		break;
	default:
		ans = "R"; //so ill know to see if error happens
	}
	return ans;
}



string CalculatorQuestion::getFunctionString()
{
	//test print commented
	//cout << nums[0] << " " << getOperatorChar(op1) << " " << nums[1] << " " << getOperatorChar(op2) << " " << nums[2] << " = " << nums[3] << endl;
	switch (hiddenAnswerIndex)
	{
	case 0:
		return  "__ " + string(getOperatorChar(op1)) + " " + to_string(nums[1]) + " " + string(getOperatorChar(op2)) + " " + to_string(nums[2]) + " = " + to_string(nums[3]);
	case 1:
		return  to_string(nums[0]) + " " + string(getOperatorChar(op1)) + " __ " + string(getOperatorChar(op2)) + " " + to_string(nums[2]) + " = " + to_string(nums[3]);
	case 2:
		return   to_string(nums[0]) + " " + string(getOperatorChar(op1)) + " " + to_string(nums[1]) + " " + string(getOperatorChar(op2)) + " __ = " + to_string(nums[3]);
	case 3:
		return   to_string(nums[0]) + " " + string(getOperatorChar(op1)) + " " + to_string(nums[1]) + " " + string(getOperatorChar(op2)) + " " + to_string(nums[2]) + " = __";
	default: return "bla"; // will never get here
	}

};



