#include "CSinkTheFleet.h"

namespace SINK_THE_FLEET
{
	CSinkTheFleet::CSinkTheFleet(char size)
	{
		m_players[0] = CPlayer(1, size);
		m_players[1] = CPlayer(2, size);
	}

	short CSinkTheFleet::play()
	{
		
	}

	void CSinkTheFleet::header()
	{
		const string empty;
		const string sink("SINK THE FLEET!");
		const string by("Back Row Power Posse");
		const string institution("Edmonds Community College CS 132");

		boxTop(cout, BOXWIDTH);
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, sink, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, by, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, institution, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxBottom(cout, BOXWIDTH);
	}

	void CSinkTheFleet::endBox(short winner)
	{
		const string empty;
		ostringstream msg;

		msg << "Congratulations player " << winner + 1 << "!";
		boxTop(cout, BOXWIDTH);
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, msg.str(), BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxBottom(cout, BOXWIDTH);
	}
}