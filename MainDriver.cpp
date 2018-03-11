//----------------------------------------------------------------------------
// File:		MainDriver.cpp
// 
// Functions:	main()
//----------------------------------------------------------------------------

#include "CCell.h"
#include "CDirection.h"
#include "CPlayer.h"
#include "CShip.h"
#include "CShipInfo.h"
#include "CSinkTheFleet.h"
#include "fleet.h"
#include "SafeIO.h"
#include "TextGraphics.h"

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
// Programmer:	Paul Bladek
// 
// Modified by: 
//				Albert Shymanskyy
//				Cameron Stevenson
// 
// Date:		01/30/2018
//
// Version:		1.0.0
// 
// Environment: 
//				Hardware: Variable
//				Software: OS: Windows 10;
//				Compiles under Microsoft Visual C++ 2017
//
// Input:		Grid files
//
// Output:		A game
//
// Calls:		
//				initializePlayer()
//				allocMem()
//				safeChoice()
//				loadGridFromFile()
//				printGrid()
//				resetGrid()
//				setships()
//				header()
//				getCoord()
//				deleteMem()
//				endBox()
//
// Called By:	None
//
// Parameters:	None
// 
// Returns:		EXIT_SUCCESS of type integer upon successful completion
//
// History Log: 
//				12/09/2010 PB completed v0.5.0
//				01/30/2018 Game completed v1.0.0
//   
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
	} while (safeChoice("Would you like to play again?", 'Y', 'N') == 'Y');
		
	// Code for CPlayer

	/*
	for(whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
	{
		outSStream.str("");
		outSStream.clear();
		// Enter grid files or let users enter ships
		outSStream << "Player " << whichPlayer + 1 << message;

		if (safeChoice(outSStream.str(), 'Y', 'N') == 'Y')
		{
			cout << "Enter file name: ";
			std::cin >> filename;
			cin.get();
			filename.append(".shp");

			if (!loadGridFromFile(game, whichPlayer, gridSize,
				filename))
			{
				system("cls");
				--whichPlayer;
				continue;
			}

			if (safeChoice("OK?", 'Y', 'N') == 'N')
				--whichPlayer;

			system("cls");
		}
		else
			setShips(game, gridSize, whichPlayer);
	}
	*/

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
} 
