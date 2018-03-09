#include "CCell.h"

namespace SINK_THE_FLEET
{
	CCell::CCell()
	{
		m_row = 0;
		m_col = 0;
	}

	short CCell::getRow() const
	{
		return m_row;
	}

	short CCell::getCol() const
	{
		return m_col;
	}

	void CCell::print(ostream &sout) const
	{
		sout << (char)(m_row + 64) << (m_col + 1);
	}

	void CCell::print() const
	{
		print(cout);
	}

	void CCell::inputCoordinates(istream &sin, char size)
	{
		short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
		char highChar = static_cast<char>(numberOfRows - 1) + 'A';
		char row = 'A';
		short col = 0;
		do
		{
			col = 0;
			cout << "Row must be a letter from A to " << highChar
				<< " and column must be from 1 to "
				<< numberOfCols << ": ";
			while ((row = toupper(sin.get())) < 'A' || row  > highChar)
			{
				sin.ignore(FILENAME_MAX, '\n');
				cout << "Row must be a letter from A to " << highChar
					<< " and column must be from 1 to "
					<< numberOfCols << ": ";
			}
			sin >> col;
			if (!sin)
				sin.clear();
			sin.ignore(FILENAME_MAX, '\n');
		} while (col < 1 || col > numberOfCols);

		m_col = col - 1;
		m_row = static_cast<short>(row - 'A');
	}

	ostream &operator<<(ostream &sout, CCell &cell)
	{
		cell.print(sout);
		return sout;
	}
}