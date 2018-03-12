//----------------------------------------------------------------------------
// File:		CSinkTheFleet.cpp
//
// Functions:	CSinkTheFleet::CSinkTheFleet(char size);
//				short CSinkTheFleet::play();
//				void CSinkTheFleet::header();
//				void CSinkTheFleet::endBox(short winner);
//----------------------------------------------------------------------------

#include "CSinkTheFleet.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Class:			CSinkTheFleet
	//
	// Title:			CSinkTheFleet Class
	//
	// Description:		Definitions for CSinkTheFleet methods and related
	//					functions
	//
	// Programmer:		Aaron Miller
	//					Albert Shymanskyy
	//					Cameron Stevenson
	//					Matthew Jacobson
	//					Paul Jacobson
	//					
	// Date:			03/12/2018
	// 
	// Version:			1.0.0
	//  
	// Environment:		Hardware: PC-compatible
	// 					OS: Microsoft Windows 10
	// 					Compiler: Microsoft Visual Studio 2017
	//
	// Properties:		CPlayer m_players[2];
	//					char m_gridSize;
	//
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Class:			CSinkTheFleet
	// Method:			CSinkTheFleet()
	// Description:		Default constructor
	// Input:			Size of the grid
	// Output:			None
	// Calls:			None
	// Called By:		main()
	// Parameters:		char size
	// Returns:			None 
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	CSinkTheFleet::CSinkTheFleet(char size)
	{
		m_gridSize = size;

		m_players[0] = CPlayer(1, size);
		m_players[1] = CPlayer(2, size);
	}

	//------------------------------------------------------------------------
	// Class:			CSinkTheFleet
	// Method:			play()
	// Description:		Gameplay
	// Input:			Cell locations for firing during the game
	// Output:			The winner's number
	// Calls:			header()
	//					printGrid()
	//					inputCoordinates()
	//					getCell()
	//					getRow()
	//					getCol()
	//					setCell()
	//					hitShip()
	//					isSunk()
	//					getPiecesLeft()
	// Called By:		main()
	// Parameters:		None
	// Returns:			short whichPlayer 
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	short CSinkTheFleet::play()
	{
		short whichPlayer = 0;
		bool gameOver = false;
		bool shipSunk = false;
		bool reshot;
		CCell coord;
		CShip whichShip;

		system("cls");
		header();
		cout << "Press <Enter> to start the battle...";
		cin.get();

		do
		{
			system("cls");
			m_players[whichPlayer].printGrid(cout, 1);
			cout << "Player " << whichPlayer + 1 << ", enter coordinates for"
				"firing:" << endl;
			coord.inputCoordinates(cin, m_gridSize);

			while (m_players[whichPlayer].getCell(1, coord) != NOSHIP)
			{
				cout << "You have already shot at " << static_cast<char>
					(coord.getRow() + 'A') << coord.getCol() + 1 << endl;
				cout << "Player " << whichPlayer + 1 << ", enter coordinates"
					<< "for firing:" << endl;
				coord.inputCoordinates(cin, m_gridSize);
			}

			whichShip = m_players[whichPlayer].getCell(0, coord);

			if (whichShip != NOSHIP)
			{
				m_players[whichPlayer].setCell(1, coord, HIT);
				m_players[!whichPlayer].hitShip(whichShip);
				shipSunk = m_players[!whichPlayer][whichShip].isSunk()
					? true : false;
				reshot = true;
				cout << '\a';
			}
			else
			{
				m_players[whichPlayer].setCell(1, coord, MISSED);
				reshot = false;
			}

			system("cls");
			m_players[whichPlayer].printGrid(cout, 1);
			cout << (reshot ? "HIT" : "MISSED") << endl;

			if (shipSunk)
			{
				cout << CPlayer::shipNames[whichShip] << " SUNK" << endl;
				shipSunk = false;
			}

			cout << "Press <Enter> to continue...";
			cin.get();

			if (m_players[!whichPlayer].getPiecesLeft() == 0)
				gameOver = true;
			else
				if (!reshot)
					whichPlayer = !whichPlayer;
		} while (!gameOver);

		return whichPlayer;
	}

	//------------------------------------------------------------------------
	// Class:			CSinkTheFleet
	// Method:			header()
	// Description:		Game header
	// Input:			None
	// Output:			Game header
	// Calls:			boxTop()
	//					boxLine()
	//					boxBottom()
	// Called By:		main()
	//					play()
	// Parameters:		None
	// Returns:			None 
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	void CSinkTheFleet::header()
	{
		const string empty;
		const string sink("SINK THE FLEET!");
		const string by("Back Row Power Posse");
		const string institution("Edmonds Community College CS 132");

		boxTop(cout, BOXWIDTH);
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, sink, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, by, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, institution, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxBottom(cout, BOXWIDTH);
	}

	//------------------------------------------------------------------------
	// Class:			CSinkTheFleet
	// Method:			endBox()
	// Description:		Game end box
	// Input:			Winner's number
	// Output:			Game end box
	// Calls:			boxTop()
	//					boxLine()
	//					boxBottom()
	// Called By:		main()
	// Parameters:		short winner
	// Returns:			None 
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	void CSinkTheFleet::endBox(short winner)
	{
		const string empty;
		ostringstream msg;

		msg << "Congratulations player " << winner + 1 << "!";
		boxTop(cout, BOXWIDTH);
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, msg.str(), BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxBottom(cout, BOXWIDTH);
	}
}