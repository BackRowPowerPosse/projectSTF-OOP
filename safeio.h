//----------------------------------------------------------------------------
// File:		safeio.h
//
// Function:	template<class T>
//		     void safeRead(istream& sin, T& input, const char* prompt) 
//----------------------------------------------------------------------------

#pragma once

#include "FleetLibrary.h"

using namespace std;

char safeChoice(string prompt, char choice1 = 'Y', char choice2 = 'N');
template<class T>
void safeRead(istream& sin, T& input, 
	const char* prompt = "invalid input--please input a NUMBER: ");
void safeRead(istream& sin, string& input,
	const char* prompt = "invalid input--please input a STRING: ");
void safeRead(istream& sin, short& input,
	const char* prompt = "invalid input--please input a NUMBER: ");