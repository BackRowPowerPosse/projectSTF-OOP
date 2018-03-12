//----------------------------------------------------------------------------
// File:			CPlayer.h
//
// Class:			CPlayer
//----------------------------------------------------------------------------

#pragma once

#include "FleetLibrary.h"
#include "CCell.h"
#include "CShip.h"
#include "CShipInfo.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Title:		CPlayer
	//
	// Description: This file contains the class definition for CPlayer
	//
	// Programmer:	Aaron Miller
	//				Albert Shymanskyy
	//				Cameron Stevenson
	//				Matthew Jacobson
	//				Paul Jacobson
	//   
	// Date:		03/12/2018
	// 
	// Version:		1.0.0
	//   
	// Environment:	Hardware: PC-compatible
	// 				OS: Microsoft Windows 10
	// 				Compiler: Microsoft Visual Studio 2017
	//
	// Properties:	unsigned short m_whichPlayer;
	//				short m_piecesLeft;
	//				CShipInfo m_ships[SHIP_SIZE_ARRAYSIZE];
	//				char m_gridSize;
	//				CShip **m_gameGrid[2];
	//
	// Methods:
	//			Inline:
	//				CPlayer();
	//				~CPlayer();
	//				unsigned short getWhichPlayer() const;
	//				short getPiecesLeft() const;
	//				char getGridSize() const;
	//				Ship getCell(short whichGrid, CCell cell) const;
	//				void setGridSize(char size);
	//				void setCell(short whichGrid, CCell cell, CShip ship);
	//
	//			Non-inline:
	//				CPlayer(unsigned short whichPlayer, char gridSize);
	//				CPlayer(const CPlayer &playerObj);
	//				void printGrid(ostream &sout, short whichGrid) const;
	//				bool getGrid(string fileName);
	//				bool isValidLocation(short whichShip);
	//				CShipInfo operator[](short index) const;
	//				CPlayer operator=(CPlayer &playerObj);
	//				bool saveGrid();
	//				bool setShips();
	//				void autoSetShips();
	//				void hitShip(CShip ship);
	//				void initializationSelection();
	//				CPlayer operator--();
	//				void allocateMemory();
	//				void deleteMemory();
	//
	// History Log: 03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	class CPlayer
	{
	public:
		CPlayer() {}
		CPlayer(unsigned short whichPlayer, char gridSize);
		CPlayer(const CPlayer &playerObj);

		~CPlayer() { this->deleteMemory(); }

		unsigned short getWhichPlayer() const { return m_whichPlayer; }
		short getPiecesLeft() const { return m_piecesLeft; }
		char getGridSize() const { return m_gridSize; }
		Ship getCell(short whichGrid, CCell cell) const
		{
			return m_gameGrid[whichGrid][cell.getRow()][cell.getCol()];
		}
		void printGrid(ostream &sout, short whichGrid) const;
		void clearGrid(short whichGrid);
		bool getGrid(string fileName);
		bool isValidLocation(short whichShip);
		CShipInfo operator[](short index) const;

		CPlayer operator=(CPlayer &playerObj);
		void setGridSize(char size) { m_gridSize = size; }
		void setCell(short whichGrid, CCell cell, CShip ship)
		{
			m_gameGrid[whichGrid][cell.getRow()][cell.getCol()] = ship;
		}
		bool saveGrid();
		bool setShips();
		void autoSetShips();
		void hitShip(CShip ship);
		void initializationSelection();
		CPlayer operator--();

		static const char *shipNames[SHIP_SIZE_ARRAYSIZE];

	private:
		void allocateMemory();
		void deleteMemory();
		bool constructed = false;
		unsigned short m_whichPlayer;
		short m_piecesLeft;
		CShipInfo m_ships[SHIP_SIZE_ARRAYSIZE];
		char m_gridSize;
		CShip **m_gameGrid[2];
	};
}