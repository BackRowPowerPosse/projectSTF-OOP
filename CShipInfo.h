//----------------------------------------------------------------------------
// File:			CShipInfo.h
//
// Class:			CShipInfo
//----------------------------------------------------------------------------

#pragma once

#include "FleetLibrary.h"
#include "CCell.h"
#include "CDirection.h"
#include "CShip.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Title:		CShipInfo
	//
	// Description: This file contains the class definition for CShipInfo
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
	// Properties:	CShip m_name;
	//				CDirection m_orientation;
	//				CCell m_bowLocation;
	//				short m_piecesLeft;
	//
	// Methods:
	//			Inline:
	//				CShipInfo();
	//				CShipInfo(CShip name, CDirection direction, CCell bow,
	//					short pieces);
	//				void print() const;
	//				CShip getName() const;
	//				CDirection getOrientation() const;
	//				CCell getBowLocation() const;
	//				short getPiecesLeft() const;
	//				bool isSunk() const;
	//				void setName(CShip &name);
	//				void setOrientation(CDirection &orientation);
	//				void setPiecesLeft(short pieces);
	//
	//			Non-inline:
	//				void print(ostream &sout) const;
	//				void setBowLocation(CCell &bowLocation);
	//				CShipInfo operator--();
	//
	// History Log: 03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	class CShipInfo
	{
	public:
		CShipInfo() {}
		CShipInfo(CShip name, CDirection direction, CCell bow, short pieces) :
			m_name(name), m_orientation(direction), m_bowLocation(bow),
			m_piecesLeft(pieces) {}

		void print(ostream &sout) const;
		void print() const { print(cout); }
		CShip getName() const { return this->m_name; }
		CDirection getOrientation() const { return this->m_orientation; }
		CCell getBowLocation() const { return this->m_bowLocation; }
		short getPiecesLeft() const { return this->m_piecesLeft; }
		bool isSunk() const { return (this->m_piecesLeft == 0); }

		void setName(CShip &name) { this->m_name = name; }
		void setOrientation(CDirection &orientation)
		{
			this->m_orientation = orientation;
		}
		void setBowLocation(CCell &bowLocation);
		void setPiecesLeft(short pieces) { this->m_piecesLeft = pieces; }
		CShipInfo operator--();
		CShipInfo operator=(const CShipInfo& other);

	private:
		CShip m_name;
		CDirection m_orientation;
		CCell m_bowLocation;
		short m_piecesLeft;
	};

	ostream &operator<<(ostream &sout, const CShipInfo &shipInfo);
}