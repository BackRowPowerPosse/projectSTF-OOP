//----------------------------------------------------------------------------
// File:			CSinkTheFleet.h
//
// Class:			CSinkTheFleet
//----------------------------------------------------------------------------

#pragma once

#include "FleetLibrary.h"
#include "CPlayer.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Title:		CSinkTheFleet
	//
	// Description: This file contains the class definition for CSinkTheFleet
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
	// Properties:	CPlayer m_players[2];
	//				char m_gridSize;
	//
	// Methods:
	//			Inline:
	//				CPlayer operator[](short index) const;
	//				CPlayer operator[](short index);
	//
	//			Non-inline:
	//				short play();
	//				static void header();
	//				static void endBox(short winner);
	//
	// History Log: 03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	class CSinkTheFleet
	{
	public:
		CSinkTheFleet(char size);

		CPlayer operator[](short index) const { return m_players[index]; }

		short play();
		CPlayer operator[](short index) { return m_players[index]; }

		static void header();
		static void endBox(short winner);

	private:
		CPlayer m_players[2];
		char m_gridSize;
	};
}