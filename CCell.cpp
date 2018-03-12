//----------------------------------------------------------------------------
// File:		CCell.cpp
//
// Functions:	void CCell::inputCoordinates(istream &sin, char size);
//				ostream &operator<<(ostream &sout, CCell &cell);
//----------------------------------------------------------------------------

#include "CCell.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Class:			CCell
	//
	// Title:			Cell Class
	//
	// Description:		Definitions for CCell methods and related functions
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
	// Properties:		unsigned short m_row;
	//					unsigned short m_col;
	//
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Class:			CCell
	// method:			void inputCoordinates(istream &sin, char size);
	// description:		converts a letter/number from sin to coordinates for a
	//					cell
	// Input:			None
	// Output:			None
	// Calls:			None
	// Called By:		ostream& operator<<()
	// Parameters:		istream &sin -- the input stream used for input.
	//					char size -- character that determines gridsize
	// Returns:			n/a 
	// History Log:		3/03/18
	//------------------------------------------------------------------------
	void CCell::inputCoordinates(istream &sin, char size)
	{
		short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
		char highChar = static_cast<char>(numberOfRows - 1) + 'A';
		char row = 'A';
		short col = 0;
		do
		{
			col = 0;
			if (&sin == &cin) {
				cout << "Row must be a letter from A to " << highChar
					<< " and column must be from 1 to "
					<< numberOfCols << ": ";
			}
			sin >> row;
			while (toupper(row) < 'A' || row > highChar)
			{
				sin.ignore(FILENAME_MAX, '\n');
				if (&sin == &cin) {
				cout << "Row must be a letter from A to " << highChar
					<< " and column must be from 1 to "
					<< numberOfCols << ": ";
				}
			}
			sin >> col;
			if (!sin)
				sin.clear();
			sin.ignore(FILENAME_MAX, '\n');
		} while (col < 1 || col > numberOfCols);

		m_col = col - 1;
		m_row = static_cast<short>(row - 'A');
	}

	CCell CCell::operator=(const CCell & cell)
	{
		m_row = cell.m_row;
		m_col = cell.m_col;
		return *this;
	}

	// ----------------------------------------------------------------------------
	//	method:         ostream& operator<<(ostream& sout, const CCell &cell)
	//	description:    prints out the cell object to the stream
	//	Input:          None
	//	Output:         Screen display of cell coordinates
	//	Calls:          None
	//	Called By:      n/a
	//	Parameters:     ostream & sout  -- the stream used for output
	//	                const CCell &cell -- the object to print
	// Returns:			a reference to sout 
	// History Log:		3/04/18
	// -----------------------------------------------------------------------
	ostream &operator<<(ostream &sout, CCell &cell)
	{
		cell.print(sout);

		return sout;
	}
}