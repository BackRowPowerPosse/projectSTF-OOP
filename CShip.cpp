//----------------------------------------------------------------------------
// File:		CShip.cpp
//
// Functions:	void CShip::print(ostream &sout) const;
//				ostream &operator<<(ostream &sout, const CShip &ship);
//				istream &operator>>(istream &sin, CShip &ship);
//----------------------------------------------------------------------------

#include "CShip.h"
	
namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Class:			CShip
	//
	// Title:			Ship Class
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
	// Properties:		Ship m_ship;
	//
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Class:			CShip
	// Method:			CShip()
	// Description:		Printer for CShip
	// Input:			Output stream
	// Output:			The CShip object
	// Calls:			None
	// Called By:		
	// Parameters:		ostream &sout
	// Returns:			None 
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	void CShip::print(ostream &sout) const
	{

		switch (m_ship)
		{
		case NOSHIP:
			sout << ' ';

			break;

		case MINESWEEPER:
			sout << 'M';

			break;

		case SUB:
			sout << 'S';

			break;

		case FRIGATE:
			sout << 'F';

			break;

		case BATTLESHIP:
			sout << 'B';

			break;

		case CARRIER:
			sout << 'C';

			break;

		case HIT:
			sout << 'H';

			break;

		case MISSED:
			sout << MISS;

			break;

		default:
			sout << 'X';
		}

	}

	//------------------------------------------------------------------------
	// Class:			CShip
	// Method:			operator=()
	// Description:		overloaded equals operator
	// Input:			Other CShip object
	// Output:			this object (after copying)
	// Calls:			None
	// Called By:		
	// Parameters:		ostream &sout
	// Returns:			this object (after copying)
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	CShip CShip::operator=(const CShip& other) {
		m_ship = other.m_ship;
		return *this;
	}

	//------------------------------------------------------------------------
	// Method:			operator<<()
	// Description:		Extraction operator for CShip
	// Input:			Output stream and CShip object
	// Output:			The CShip object
	// Calls:			print()
	// Called By:		
	// Parameters:		ostream &sout
	//					const CShip &ship
	// Returns:			ostream&
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	ostream &operator<<(ostream &sout, const CShip &ship)
	{
		ship.print(sout);

		return cout;
	}

	//------------------------------------------------------------------------
	// Method:			operator>>()
	// Description:		Insertion operator for CShip
	// Input:			Input stream and CShip object
	// Output:			The CShip object
	// Calls:			setShip()
	// Called By:		
	// Parameters:		istream &sin
	//					CShip &ship
	// Returns:			istream&
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	istream &operator>>(istream &sin, CShip &ship)
	{
		short number;
		string string;

		if (isdigit(sin.peek()))
		{
			if (!(sin >> number))
				return sin;
			
			ship.setShip(Ship(number));
		}
		else
		{
			if (!(sin >> string))
				return sin;

			for (short i = 0; i < string.size(); i++)
				string.at(i) = toupper(string.at(i));

			if (string == "NOSHIP")
				ship.setShip(Ship(0));
			else if (string == "MINESWEEPER")
				ship.setShip(Ship(1));
			else if (string == "SUB")
				ship.setShip(Ship(2));
			else if (string == "FRIGATE")
				ship.setShip(Ship(3));
			else if (string == "BATTLESHIP")
				ship.setShip(Ship(4));
			else if (string == "CARRIER")
				ship.setShip(Ship(5));
			else if (string == "HIT")
				ship.setShip(Ship(6));
			else if (string == "MISSED")
				ship.setShip(Ship(7));
		}

		return sin;
	}
}