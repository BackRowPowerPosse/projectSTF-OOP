#pragma once
#include "fleet.h"
#include "CSinkTheFleet.h"

enum Direction2	// change this to Direction after fleet.h and fleet.cpp are deleted
{				// calling this "Direction" was conflicting with the Direction enum declared in fleet.h
	HORIZONTAL, // 0
	VERTICAL	// 1
};


namespace SINK_THE_FLEET
{
	class CDirection
	{
	public:
		CDirection(Direction2 initDirection = HORIZONTAL) :m_direction(initDirection) {};
		operator Direction2() const;
		void print(ostream &sout) const;
		void print() const;

	private:
		Direction2 m_direction;
	};

	ostream &operator<<(ostream &sout, const CDirection &direction);
	istream &operator>>(istream &sin, CDirection &direction);
}