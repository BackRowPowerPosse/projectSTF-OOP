//-----------------------------------------------------------------------------
//	File:           CShipInfo.h
//
//	class:		CShipInfo
//-----------------------------------------------------------------------------

#pragma once
#include "fleet.h"
#include "CSinkTheFleet.h"

namespace SINK_THE_FLEET
{
	class CShipInfo
	{
	public:
		CShipInfo(CShip name, CDirection direction, CCell bow, short pieces)
			: m_name(name), m_orientation(direction), m_bowLocation(bow), m_piecesLeft(pieces) {}
		void print(ostream &sout) const;
		void print() const;
		CShip getName() const;
		CDirection getOrientation() const;
		CCell getBowLocation() const;
		short getPiecesLeft() const;
		bool isSunk();

		void setName(CShip &name);
		void setOrientation(CDirection &orientation);
		void setBowLocation(CCell &bowLocation);
		void setPiecesLeft(short pieces);
		CShipInfo operator--();

		//static const short shipSize[6];

	private:
		CShip m_name;
		CDirection m_orientation;
		CCell m_bowLocation;
		short m_piecesLeft;
	};

	ostream &operator<<(ostream &sout, const CShipInfo &shipInfo);
}