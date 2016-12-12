#ifndef _BOARD_EXAMPLE_
#define _BOARD_EXAMPLE_
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// _board.h
// ---------
// A board example (this is NOT an interesting board, you should do better that that!)
// This file is a header file just for conveniency, but it CANNOT be included in multiple files.
// (The file creates the single board that we use as a global variable).
// You may for example include this file in main (ONLY) and use the board to init TheMathGame.
// TODO:[NOT NOW] in ex2 _boards.h will be replaced with a better way, reading boards from files.
//
// Author: Amir Kirsh
// First version: 2015-11-02
// 
// This code is part of a solution for "the math space ships game" excercise 1 in C++ course, Semester A 2016
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ROWS is an enum value in TheMathGame.h - make sure it's included above us

const char* board_example[ROWS] = {
	//	         10        20        30        40        50        60        70       79
	//	 01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"                                                                                ", // 0
	"                                                                                ", // 1
	"                                                                                ", // 2
	"------------------------------------------------------------------------------- ", // 3
	"                                                                                ", // 4
	"                                                                                ", // 5
	"                                                                                ", // 6
	"                                                                                ", // 7
	"                                                                                ", // 8
	"                                                                                ", // 9
	"                                                                                ", // 10
	"                                                                                ", // 11
	"                                                                                ", // 12
	"                                                                                ", // 13
	"                                                                                ", // 14
	"                                                                                ", // 15
	"                                                                                ", // 16
	"                                                                                ", // 17
	"                                                                                ", // 18
	"                                                                                ", // 19
	"                                                                                ", // 20
	"                                                                                ", // 21
	"                                                                                ", // 22
	"                                                                                "  // 23
//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
};

#endif