//----------------------------------------------------------------------------
// File:			CDirection.h
//
// Class:			CDirection
//----------------------------------------------------------------------------

#pragma once

#include "FleetLibrary.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Title:		CDirection
	//
	// Description: This file contains the class definition for CDirection
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
	// Environment:	Hardware: PC-compatible
	// 				OS: Microsoft Windows 10
	// 				Compiler: Microsoft Visual Studio 2017
	//
	// Properties:	Direction m_direction;
	//
	// Methods:
	//			Inline:
	//				CDirection(Direction initDirection = HORIZONTAL)
	//				operator Direction() const;
	//				void print() const;
	//
	//			Non-inline:
	//				void print(ostream &sout) const;
	//
	// History Log: 03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	class CDirection
	{
	public:
		CDirection(Direction initDirection = HORIZONTAL) :
			m_direction(initDirection) {}

		operator Direction() const { return m_direction; }
		void print(ostream &sout) const;
		void print() const { print(cout); }

	private:
		Direction m_direction;
	};

	ostream &operator<<(ostream &sout, const CDirection &direction);
	istream &operator>>(istream &sin, CDirection &direction);
}