#pragma once

#include <cctype>
#include <crtdbg.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "SafeIO.h"
#include "TextGraphics.h"

using namespace std;
namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	//	Enumerated type for ships
	//		(1-5) are used only for owner
	//		(6-7) are used only for other side
	//------------------------------------------------------------------------
	enum Ship
	{
		NOSHIP,		 // 0
		MINESWEEPER, // 1
		SUB,		 // 2
		FRIGATE,	 // 3
		BATTLESHIP,	 // 4
		CARRIER,	 // 5
		HIT,		 // 6
		MISSED,		 // 7 
	};

	//----------------------------------------------------------------------------
	// Enumerated type for direction on grid
	//----------------------------------------------------------------------------
	enum Direction
	{
		HORIZONTAL, // 0
		VERTICAL	// 1
	};

	static const short shipSize[SHIP_SIZE_ARRAYSIZE] = { 0, 2, 3, 3, 4, 5 };
	static const char* shipNames[SHIP_SIZE_ARRAYSIZE] = { "No Ship", "Mine Sweeper",
		"Submarine", "Frigate", "Battleship", "Aircraft Carrier" };

	class CFleetLibrary
	{
	public:
		// Number of players in game
		static const short NUMPLAYERS = 2;
		// Number of rows/columns in small sea array
		static const short SMALLROWS = 8;
		// Number of rows/columns in large sea array
		static const short LARGEROWS = 10;
		// Number of rows/columns in small sea array
		static const short SMALLCOLS = 12;
		// Number of rows/columns in large sea array
		static const short LARGECOLS = 24;
		// Maximum screen line length
		static const short BOXWIDTH = 79;
		// Size of the shipSize array
		static const int SHIP_SIZE_ARRAYSIZE = 6;
		// Number of elements for each ship
		

		static const int TOTALPIECES = 17;

		

		
		

	}

	

}