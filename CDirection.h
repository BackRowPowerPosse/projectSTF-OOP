#pragma once

#include "FleetLibrary.h"

namespace SINK_THE_FLEET
{
	class CDirection
	{
	public:
		CDirection(Direction initDirection = HORIZONTAL) : m_direction(initDirection) {};

		operator Direction() const;
		void print(ostream &sout) const;
		void print() const;

		CDirection operator=(const CDirection& other);


	private:
		Direction m_direction;
	};

	ostream &operator<<(ostream &sout, const CDirection &direction);
	istream &operator>>(istream &sin, CDirection &direction);
}