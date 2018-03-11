#pragma once
#include "fleet.h"
#include "CSinkTheFleet.h"

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
    
		// Number of players in game
		const short NUMPLAYERS = 2;
		// Number of rows/columns in small sea array
		const short SMALLROWS = 8;
		// Number of rows/columns in large sea array
		const short LARGEROWS = 10;
		// Number of rows/columns in small sea array
		const short SMALLCOLS = 12;
		// Number of rows/columns in large sea array
		const short LARGECOLS = 24;

	private:
		unsigned short m_row;
		unsigned short m_col;
	};

	ostream &operator<<(ostream &sin, CCell &cell);
}