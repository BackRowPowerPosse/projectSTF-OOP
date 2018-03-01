#pragma once
#include "fleet.h"

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

	private:
		Ship m_ship;
	};

	ostream &operator<<(ostream &sout, const CShip &ship);
	istream &operator>>(istream &sin, CShip &ship);

	//------------------------------------------------------------------------
	//	Enumerated type for ships
	//		(1-5) are used only for owner
	//		(6-7) are used only for other side
	//------------------------------------------------------------------------
	enum Ship
	{
		NOSHIP,		 // 0
		MINESWEEPER, // 1
		SUB,		 // 2
		FRIGATE,	 // 3
		BATTLESHIP,	 // 4
		CARRIER,	 // 5
		HIT,		 // 6
		MISSED,		 // 7 
	};
}