#pragma once
#include "fleet.h"
#include "CSinkTheFleet.h"

namespace SINK_THE_FLEET
{
	class CDirection
	{
	public:
		CDirection();
		operator Direction() const;
		void print(ostream &sout);
		void print();
		
	private:
		Direction m_direction;
	};

	ostream &operator<<(ostream &sout, const CDirection &direction);
	istream &operator>>(istream &sin, CDirection &direction);
}