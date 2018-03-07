//----------------------------------------------------------------------------
// File:		safeio.h
//
// Function:	template<class T>
//		     void safeRead(istream& sin, T& input, const char* prompt) 
//----------------------------------------------------------------------------

#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

char safeChoice(string prompt, char choice1 = 'Y', char choice2 = 'N');
template<class T>
void safeRead(istream& sin, T& input, 
	const char* prompt = "invalid input--please input a NUMBER: ");