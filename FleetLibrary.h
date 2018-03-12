#pragma once

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "CCell.h"
#include "CDirection.h"
#include "CPlayer.h"
#include "CShip.h"
#include "CShipInfo.h"
#include "CSinkTheFleet.h"
#include "SafeIO.h"
#include "TextGraphics.h"

using namespace std;

// Number of players in game
const short NUMPLAYERS = 2;
// Number of rows/columns in small sea array
const short SMALLROWS = 8;
// Number of rows/columns in large sea array
const short LARGEROWS = 10;
// Number of rows/columns in small sea array
const short SMALLCOLS = 12;
// Number of rows/columns in large sea array
const short LARGECOLS = 24;
// Maximum screen line length
const short BOXWIDTH = 79;
// Size of the shipSize array
const int SHIP_SIZE_ARRAYSIZE = 6;
// Number of elements for each ship
const short shipSize[SHIP_SIZE_ARRAYSIZE] = { 0, 2, 3, 3, 4, 5 };

const char* shipNames[SHIP_SIZE_ARRAYSIZE] = { "No Ship", "Mine Sweeper",
"Submarine", "Frigate", "Battleship", "Aircraft Carrier" };

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