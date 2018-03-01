#pragma once
#include "fleet.h"


namespace SINK_THE_FLEET
{
	class CShipInfo
	{
	public:
		CShipInfo();

		void print(ostream &sout) const;
		void print() const;
		CShip getName() const;
		CDirection getOrientation() const;
		CCell getBowLocation() const;
		short getPiecesLeft() const;
		bool isSunk();

		void setName();
		void setOrientation();
		void setBowLocation();
		void setPiecesLeft();
		CShipInfo operator--();

		static const short shipSize[6];

	private:
		CShip m_name;
		CDirection m_orientation;
		CCell m_bowLocation;
		short m_piecesLeft;
	};

	ostream &operator<<(ostream &sout, const CShipInfo &shipInfo);
}