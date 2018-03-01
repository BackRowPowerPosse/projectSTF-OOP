#pragma once
#include "fleet.h"

namespace SINK_THE_FLEET
{
	class CSinkTheFleet
	{
	public:
		CSinkTheFleet();

		CPlayer operator[](short index) const;

		short play();
		CPlayer operator[](short index);

		static void header();
		static void endBox();

	private:
		CPlayer m_players[2];
		char m_gridSize;
	};
}