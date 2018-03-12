//----------------------------------------------------------------------------
// File:			CShip.h
//
// Class:			CShip
//----------------------------------------------------------------------------

#pragma once

#include "FleetLibrary.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Title:		CShip
	//
	// Description: This file contains the class definition for CShip
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
	// Properties:	Ship m_ship;
	//
	// Methods:
	//			Inline:
	//				CShip(Ship ship = NOSHIP);
	//				operator Ship() const ;
	//				void print() const;
	//				void printName(ostream &sout) const;
	//				void setShip(Ship ship);
	//
	//			Non-inline:
	//				void print(ostream &sout) const;
	//
	// History Log: 03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	class CShip
	{
	public:
		CShip(Ship ship = NOSHIP) : m_ship(ship) {};
		
		operator Ship() const { return m_ship; };
		void print(ostream &sout) const;
		void print() const { print(cout); };
		void printName(ostream &sout) const { sout << shipNames[m_ship]; }

		void setShip(Ship ship) { m_ship = ship; }

		static const char *shipNames[SHIP_SIZE_ARRAYSIZE];

	private:
		Ship m_ship;
	};

	ostream &operator<<(ostream &sout, const CShip &ship);
	istream &operator>>(istream &sin, CShip &ship);
}