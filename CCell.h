#pragma once
#include "fleet.h"
#include "CSinkTheFleet.h"

namespace SINK_THE_FLEET
{
	class CCell
	{
	public:
		CCell();
		
		short getRow() const;
		short getCol() const;
		void print(ostream &sout) const;
		void print() const;

		void inputCoordinates(istream &sin, char size);

	private:
		unsigned short m_row;
		unsigned short m_col;
	};

	ostream &operator<<(ostream &sout, const CCell &ship);
}