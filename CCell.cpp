#include "FleetLibrary.h"

namespace SINK_THE_FLEET
{

	//-----------------------------------------------------------------------------
	//	Class:         CCell
	//	method:        void print(ostream & sout)const;
	//	description:   prints out this object to the stream
	//	Input:         None
	//	Output:        Screen display of cell coordinates
	//	Calls:         None
	//	Called By:     ostream& operator<<(ostream& sout, const CCell &cell)
	//	Parameters:    ostream & sout  -- the stream used for output
	//	Returns:       n/a 
	//	History Log:
	//	               3/03/18
	//-----------------------------------------------------------------------------
	void CCell::print(ostream &sout) const
	{
		sout << (char)(m_row + 64) << (m_col + 1);
	}

	//-----------------------------------------------------------------------------
	//	Class:         CCell
	//	method:        void print()const;
	//	description:   prints out this object to cout
	//	Input:         None
	//	Output:        Screen display of cell coordinates
	//	Calls:         None
	//	Called By:     ostream& operator<<()
	//	Parameters:    n/a
	//	Returns:       n/a 
	//	History Log:
	//	               3/03/18
	//-----------------------------------------------------------------------------
	void CCell::print() const
	{
		print(cout);
	}
	//-----------------------------------------------------------------------------
	//	Class:         CCell
	//	method:        void inputCoordinates(istream &sin, char size);
	//	description:   converts a letter/number from sin to coordinates for a cell
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     ostream& operator<<()
	//	Parameters:	   istream &sin -- the input stream used for input.
	//				   char size -- character that determines gridsize
	//	Returns:       n/a 
	//	History Log:
	//	               3/03/18
	//-----------------------------------------------------------------------------

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
			if (&sin == &cin) {
				cout << "Row must be a letter from A to " << highChar
					<< " and column must be from 1 to "
					<< numberOfCols << ": ";
			}
			while ((row = toupper(sin.get())) < 'A' || row > highChar)
			{
				sin.ignore(FILENAME_MAX, '\n');
				if (&sin == &cin) {
				cout << "Row must be a letter from A to " << highChar
					<< " and column must be from 1 to "
					<< numberOfCols << ": ";
				}
			}
			sin >> col;
			if (!sin)
				sin.clear();
			sin.ignore(FILENAME_MAX, '\n');
		} while (col < 1 || col > numberOfCols);

		m_col = col - 1;
		m_row = static_cast<short>(row - 'A');
	}

	CCell CCell::operator=(const CCell & cell)
	{
		return cell;
	}

	// ----------------------------------------------------------------------------
	//	method:         ostream& operator<<(ostream& sout, const CCell &cell)
	//	description:    prints out the cell object to the stream
	//	Input:          None
	//	Output:         Screen display of cell coordinates
	//	Calls:          None
	//	Called By:      n/a
	//	Parameters:     ostream & sout  -- the stream used for output
	//	                const CCell &cell -- the object to print
	//	Returns:        a reference to sout 
	//	History Log:
	//	                3/04/18
	// ----------------------------------------------------------------------------
	ostream &operator<<(ostream &sout, CCell &cell)
	{
		cell.print(sout);
		return sout;
	}
}