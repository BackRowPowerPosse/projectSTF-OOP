#include "CShip.h"
	
namespace SINK_THE_FLEET
{
	const char *shipNames[SHIP_SIZE_ARRAYSIZE]
	{
		"No Ship",
		"Mine Sweeper",
		"Submarine",
		"Frigate",
		"Battleship",
		"Aircraft Carrier"
	};

	void CShip::print(ostream &sout) const
	{
		sout << ' ';

		switch (m_ship)
		{
		case NOSHIP:
			sout << ' ';
			break;
		case MINESWEEPER:
			sout << 'M';
			break;
		case SUB:
			sout << 'S';
			break;
		case FRIGATE:
			sout << 'F';
			break;
		case BATTLESHIP:
			sout << 'B';
			break;
		case CARRIER:
			sout << 'C';
			break;
		case HIT:
			sout << 'H';
			break;
		case MISSED:
			sout << MISS;
			break;
		default:
			sout << 'X';
		}

		sout << VERT;
	}

	ostream &operator<<(ostream &sout, const CShip &ship)
	{
		ship.print(sout);

		return sout;
	}

	istream &operator>>(istream &sin, CShip &ship)
	{

	}
}