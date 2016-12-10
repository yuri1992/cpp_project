#include <windows.h>
#include <iostream>
using namespace std;
//#include <math.h>       /* sqrt */

#include "TheGame.h"
#include "_board.h"

int main() {
	TheGame game = TheGame(board_example);
	game.run();
}








//int number = 17;
//bool answer = false;

//double a = 10 % 7;
//double b = 13 % 7;
//double c = 24 % 7;
//cout << "b   " << b << endl << "a   " << a << endl << "c   " << c << endl;
//if (floor(a) == a)
//	cout << "a It's whole" <<endl;
//else
//	cout << "a Not whole" << endl;


//if (floor(b) == b)
//	cout << "b It's whole" << endl;
//else
//	cout << "b Not whole" << endl;



//cout << "num/4 " << number % 4 << endl;
//cout << "number is " << number << endl;
//cout << "answer:  " << answer << endl;

////return answer;
//getch();

