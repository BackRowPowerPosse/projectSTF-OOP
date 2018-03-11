#pragma once
#include "fleet.h"
#include "CSinkTheFleet.h"

namespace SINK_THE_FLEET
{
	class CPlayer
	{
	public:
		CPlayer(unsigned short whichPlayer, char gridSize);
		CPlayer(const CPlayer& playerObj);

		~CPlayer();

		const int TOTALPIECES = 17;
		unsigned short getWhichPlayer() const;
		short getPiecesLeft() const;
		char getGridSize() const;
		Ship getCell(short whichGrid, CCell cell) const;
		void printGrid(ostream &sout, short whichGrid) const;
		bool getGrid(string fileName);
		bool isValidLocation(short whichShip);
		CShipInfo operator[](short index) const;
		const short shipSize[SHIP_SIZE_ARRAYSIZE] = { 0, 2, 3, 3, 4, 5 }; // array of ship sizes.
		//SHIP_SIZE_ARRAYSIZE is constant in "fleet.h" and will need to be replaced

		CPlayer operator=(CPlayer &playerObj);
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
		CShipInfo m_ships[SHIP_SIZE_ARRAYSIZE];
		char m_gridSize;
		CShip **m_gameGrid[2];
	};
}