//----------------------------------------------------------------------------
// File:		MainDriver.cpp
// 
// Functions:	main()
//----------------------------------------------------------------------------

#include "FleetLibrary.h"
#include "CSinkTheFleet.h"

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
#endif

//----------------------------------------------------------------------------
// Function:	main()
//
// Title:		Main
//
// Description: Runs the "Sink the Fleet" Game
//
// Programmer:	Aaron Miller
//				Albert Shymanskyy
//				Cameron Stevenson
//				Matthew Jacobson
//				Paul Jacobson
// 
// Date:		03/12/2018
//
// Version:		1.0.0
// 
// Environment: Hardware: PC-compatible
// 				OS: Microsoft Windows 10
// 				Compiler: Microsoft Visual Studio 2017
//
// Input:		Size of the grid
//
// Output:		A game
//
// Calls:		CSinkTheFleet::header()
//				safeChoice()
//				CSinkTheFleet::play()
//				CSinkTheFleet::endBox()
//
// Called By:	None
//
// Parameters:	None
// 
// Returns:		EXIT_SUCCESS of type integer upon successful completion
//
// History Log: 03/12/2018 Function completed v1.0.0
//----------------------------------------------------------------------------
int main()
{
	using namespace SINK_THE_FLEET;

	short winner;

	CSinkTheFleet::header();

	do
	{
		CSinkTheFleet game(safeChoice("Which size grid do you want to use?",
			'S', 'L'));

		winner = game.play();

		CSinkTheFleet::endBox(winner);
		system("cls");
	} while (safeChoice("Would you like to play again?", 'Y', 'N') == 'Y');

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
} 
