#pragma once

#include "FleetLibrary.h"

namespace SINK_THE_FLEET
{
	class CShip
	{
	public:
		CShip(Ship ship = NOSHIP) : m_ship(ship) {};
		
		operator Ship() const { return m_ship; };
		void print(ostream &sout) const;
		void print() const { print(cout); };
		void printName(ostream &sout) const { sout << shipNames[m_ship]; }

		void setShip(Ship ship) { m_ship = ship; }

		static const char* shipNames[SHIP_SIZE_ARRAYSIZE];

	private:
		Ship m_ship;
	};

	ostream &operator<<(ostream &sout, const CShip &ship);
	istream &operator>>(istream &sin, CShip &ship);
}