#pragma once
#include "fleet.h"
#include <string.h>
#include "CSinkTheFleet.h"


namespace SINK_THE_FLEET
{
	class CPlayer
	{
	public:
		CPlayer(unsigned short whichPlayer, char gridSize);
		CPlayer(const CPlayer& playerObj);

		~CPlayer();

		unsigned short getWhichPlayer() const;
		short getPiecesLeft() const;
		char getGridSize() const;
		Ship getCell(short whichGrid, CCell cell) const;
		void printGrid(ostream &sout, short whichGrid) const;
		bool getGrid(string fileName);
		bool isValidLocation(short whichShip);
		CShipInfo operator[](short index) const;

		CPlayer operator=(CPlayer &playerObj);
		void setGridSize(char size);
		void setCell(short whichGrid, CCell cell, CShip ship);
		bool saveGrid();
		void setShips();
		void hitShip(CShip ship);
		CPlayer operator--();
	private:
		void allocateMemory();
		void deleteMemory();

		unsigned short m_whichPlayer;
		short m_piecesLeft;
		CShipInfo m_ships[SHIP_SIZE_ARRAYSIZE];
		char m_gridSize;
		CShip **m_gameGrid[2];
	};
}