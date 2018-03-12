#pragma once

#include "FleetLibrary.h"

namespace SINK_THE_FLEET
{
	class CCell
	{
	public:

		CCell(short row = 0, short column = 0)
			: m_row(row), m_col(column) {}

		
		short getRow() const { return m_row; }
		short getCol() const { return m_col; }
		void print(ostream &sout) const;
		void print() const;

		void inputCoordinates(istream &sin, char size);
		CCell operator=(const CCell &cell);

	private:
		unsigned short m_row;
		unsigned short m_col;
	};

	ostream &operator<<(ostream &sin, CCell &cell);
}