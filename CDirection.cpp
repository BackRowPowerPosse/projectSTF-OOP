//----------------------------------------------------------------------------
// File:		CDirection.cpp
//
// Functions:	void CDirection::print(ostream &sout) const;
//				ostream &operator<<(ostream &sout, const CDirection
//					&direction);
//				istream &operator>>(istream &sin, CDirection &direction);
//----------------------------------------------------------------------------

#include "CDirection.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Class:			CDirection
	//
	// Title:			Direction Class
	//
	// Description:		Definitions for CDirection methods and related
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
	// Properties:		Direction m_direction;
	//
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Class:			CDirection
	// Method:			print()
	// Description:		Printer for CDirection
	// Input:			Output stream
	// Output:			The CDirection object
	// Calls:			None
	// Called By:		
	// Parameters:		ostream &sout
	// Returns:			None 
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	void CDirection::print(ostream &sout) const
	{
		// if not zero, therefore 1, therefore vertical
		if (m_direction)
			sout << "V";
		else
			sout << "H";
	}

	//------------------------------------------------------------------------
	// Method:			operator<<()
	// Description:		Extraction operator for CDirection
	// Input:			Output stream and CDirection object
	// Output:			The CDirection object
	// Calls:			print()
	// Called By:		
	// Parameters:		ostream &sout
	//					const CDirection &direction
	// Returns:			ostream&
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	ostream &operator<<(ostream &sout, const CDirection &direction)
	{
		direction.print(sout);

		return sout;
	}

	CDirection CDirection::operator=(const CDirection& other) {
		m_direction = other.m_direction;
		return *this;
	}

	//------------------------------------------------------------------------
	// Method:			operator>>()
	// Description:		Insertion operator for CDirection
	// Input:			Input stream and CDirection object
	// Output:			The CDirection object
	// Calls:			None
	// Called By:		
	// Parameters:		istream &sin
	//					CDirection &direction
	// Returns:			istream&
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	istream &operator>>(istream &sin, CDirection &direction)
	{
		char input;

		sin >> input;

		if (input == 'V')
			direction = CDirection(VERTICAL);

		if (input == 'H')
			direction = CDirection(HORIZONTAL);

		return sin;
	}
}