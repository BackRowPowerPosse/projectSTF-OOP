#include "CShip.h"
	
namespace SINK_THE_FLEET
{
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
		short number;
		string string;

		if (isdigit(sin.peek()))
		{
			if (!(sin >> number))
				return sin;
			
			ship.setShip(Ship(number));
		}
		else
		{
			if (!(sin >> string))
				return sin;

			for (short i = 0; i < string.size(); i++)
				string.at(i) = toupper(string.at(i));

			if (string == "NOSHIP")
				ship.setShip(Ship(0));
			else if (string == "MINESWEEPER")
				ship.setShip(Ship(1));
			else if (string == "SUB")
				ship.setShip(Ship(2));
			else if (string == "FRIGATE")
				ship.setShip(Ship(3));
			else if (string == "BATTLESHIP")
				ship.setShip(Ship(4));
			else if (string == "CARRIER")
				ship.setShip(Ship(5));
			else if (string == "HIT")
				ship.setShip(Ship(6));
			else if (string == "MISSED")
				ship.setShip(Ship(7));
		}

		return sin;
	}
}