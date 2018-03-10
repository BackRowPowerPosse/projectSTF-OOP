#include "CDirection.h"

namespace SINK_THE_FLEET
{

	CDirection::operator Direction2() const
	{
		return m_direction;
	}

	void CDirection::print(ostream &sout)const
	{
		if (m_direction)	// if not zero, therefore 1, therefore vertical
			sout << "V";
		else
			sout << "H";
	}

	void CDirection::print()const
	{
		print(cout);
	}

	ostream &operator<<(ostream &sout, const CDirection &direction)
	{
		direction.print(sout);
		return sout;
	}

	istream &operator>>(istream &sin, CDirection &direction)
	{
		char input;
		sin >> input;
		if (input == 'V')
			direction = CDirection(VERTICAL);
		if (input == 'H')
			direction = CDirection(HORIZONTAL);
		return sin;

	}
}