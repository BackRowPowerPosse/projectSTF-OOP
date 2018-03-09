#pragma once
#include "fleet.h"
#include "CPlayer.h"
#include "CShip.h"
#include "CCell.h"
#include "CDirection.h"
#include "CShipInfo.h"

namespace SINK_THE_FLEET
{
	class CSinkTheFleet
	{
	public:
		CSinkTheFleet(char size) : m_gridSize(size) {}

		CPlayer operator[](short index) const;

		short play();
		CPlayer operator[](short index);

		static void header();
		static void endBox(short winner);

	private:
		CPlayer m_players[2];
		char m_gridSize;
	};
}