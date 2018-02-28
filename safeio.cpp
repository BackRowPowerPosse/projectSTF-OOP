//----------------------------------------------------------------------------
// File:	safeio.cpp
// 
// Function:
//      safeChoice
//----------------------------------------------------------------------------

#include "safeio.h"

//----------------------------------------------------------------------------
// Function: safeChoice(string prompt, char choice1, char choice2)
//
// Title:		safeChoice
//
// Description: 
//			Safely allows user to select one of two characters
//   
// Programmer:	Paul Bladek
// 
// Date:		5/1/2006
//
// Version: 1.0
// 
// Environment: Hardware: PC
//              Software: Windows 10 
//              Compiles under Microsoft Visual C++ 2017
//
// Input:		char input from console
//
// Output:		Screen display of prompt
//
// Calls: none
//
// Called By:	main()
//				setShips()
//
//
// Parameters:	prompt: string; prompt for input
//				choice1: char; the default choice
//				choice2: char; the other choice
// 
// Returns:		the character input and validated
//
// History Log:
//				5/1/06 PB completed version 1.0
// ---------------------------------------------------------------------------
char safeChoice(string prompt, char choice1, char choice2)
{
	char input = choice1;
	ostringstream outSStream;
	outSStream << " (" << choice1 << "/" << choice2 << "): "
		<< choice1 << "\b";
	cout << prompt << outSStream.str();
	while ((input = toupper(input = cin.get())) != choice1
		&& input != choice2 && input != '\n')
	{
		cin.ignore(FILENAME_MAX, '\n');
		cout << prompt << outSStream.str();
	}
	if (input == '\n')
		input = choice1;
	else
		cin.ignore(FILENAME_MAX, '\n');
	return input;
}

//----------------------------------------------------------------------------
// Function:	template<class T>
//		     void safeRead(istream& sin, T& input, const char* prompt)
//
// Title:	safeRead
//
// Description: Safely reads in a variable (input) from sin.
//			Re-prompts and re-enters if input is invalid  
//
// Programmer:	Paul Bladek
// 
// Date:		5/1/2006
//
// Version: 1.0
// 
// Environment: Hardware: PC
//              Software: Windows 10 
//              Compiles under Microsoft Visual C++ 2017
//
// Input: T& input from istream& sin
//
// Output: Screen display of prompt
//
// Calls: none
//
// Called By: 
//
// Parameters:	istream& sin	-- the input stream
//				T& input	-- theinput variable
//				const char* prompt-- prompt if not a number
// 
// Returns: none
//
// History Log:
//				5/1/06 PB completed version 1.0
// -------------------------------------------------------------------------
template<class T>
void safeRead(istream& sin, T& input, const char* prompt)
{
	while (!(sin >> input))	// read in number--enter loop if fail
	{
		sin.clear();
		sin.ignore(FILENAME_MAX, '\n');
		cout << prompt;
	}
	sin.ignore(FILENAME_MAX, '\n');
}