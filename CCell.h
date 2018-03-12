//----------------------------------------------------------------------------
// File:			CCell.h
//
// Class:			CCell
//----------------------------------------------------------------------------

#pragma once

#include "FleetLibrary.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Title:		CCell
	//
	// Description: This file contains the class definition for CCell
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
	// Properties:	unsigned short m_row;
	//				unsigned short m_col;
	//
	// Methods:
	//			Inline:
	//				CCell(short row = 0, short column = 0);
	//				short getRow() const;
	//				short getCol() const;
	//				void print() const;
	//				CCell operator=(const CCell &cell);
	//
	//			Non-inline:
	//				void print(ostream &sout) const;
	//				void inputCoordinates(istream &sin, char size);
	//
	// History Log: 03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	class CCell
	{
	public:
		CCell(short row = 0, short column = 0) : m_row(row), m_col(column) {}

		short getRow() const { return m_row; }
		short getCol() const { return m_col; }
		void print(ostream &sout) const
		{
			sout << char(m_row + 64) << (m_col + 1);
		}
		void print() const { print(cout); }

		void inputCoordinates(istream &sin, char size);
		CCell operator=(const CCell & cell) { return cell; }

	private:
		unsigned short m_row;
		unsigned short m_col;
	};

	ostream &operator<<(ostream &sin, CCell &cell);
}