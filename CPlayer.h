#pragma once
#include "fleet.h"

namespace SINK_THE_FLEET
{
	class CPlayer
	{
	public:
		CPlayer();
		CPlayer();

		~CPlayer();

		unsigned short getWhichPlayer() const;
		short getPiecesLeft() const;
		char getGridSize() const;
		Ship getCell(short whichGrid, CCell cell) const;
		void printGrid(ostream &sout, short whichGrid) const;
		void getGrid(string fileName) const;
		bool isValidLocation(short whichShip);
		CShipInfo operator[](short index) const;

		CPlayer operator=(CPlayer &player);
		void setGridSize(char size);
		void setCell(short whichGrid, CCell cell, CShip ship);
		void saveGrid();
		void setShips();
		void hitShip(CShip ship);
		CPlayer operator--();

	private:
		void allocateMemory();
		void deleteMemory();

		unsigned short m_whichPlayer;
		short m_piecesLeft;
		CShipInfo m_ships[6];
		char m_gridSize;
		CShip **m_gameGrid[2];
	};
}