#include "FleetLibrary.h"
#include "CSinkTheFleet.h"

namespace SINK_THE_FLEET
{
	CSinkTheFleet::CSinkTheFleet(char size)
	{
		m_gridSize = size;

		m_players[0] = CPlayer(1, size);
		m_players[1] = CPlayer(2, size);
	}

	short CSinkTheFleet::play()
	{
		short whichPlayer = 0;
		bool gameOver = false;
		bool shipSunk = false;
		bool reshot;
		CCell coord;
		CShip whichShip;

		system("cls");
		header();
		cout << "Press <Enter> to start the battle...";
		cin.get();

		do
		{
			system("cls");
			m_players[whichPlayer].printGrid(cout, 1);
			cout << "Player " << whichPlayer + 1 << ", enter coordinates for"
				"firing:" << endl;
			coord.inputCoordinates(cin, m_gridSize);

			while (m_players[whichPlayer].getCell(1, coord) != NOSHIP)
			{
				cout << "You have already shot at " << static_cast<char>
					(coord.getRow() + 'A') << coord.getCol() + 1 << endl;
				cout << "Player " << whichPlayer + 1 << ", enter coordinates"
					<< "for firing:" << endl;
				coord.inputCoordinates(cin, m_gridSize);
			}

			whichShip = m_players[whichPlayer].getCell(0, coord);

			if (whichShip != NOSHIP)
			{
				m_players[whichPlayer].setCell(1, coord, HIT);
				m_players[!whichPlayer].hitShip(whichShip);
				shipSunk = m_players[!whichPlayer][whichShip].isSunk()
					? true : false;
				reshot = true;
				cout << '\a';
			}
			else
			{
				m_players[whichPlayer].setCell(1, coord, MISSED);
				reshot = false;
			}

			system("cls");
			m_players[whichPlayer].printGrid(cout, 1);
			cout << (reshot ? "HIT" : "MISSED") << endl;

			if (shipSunk)
			{
				cout << CPlayer::shipNames[whichShip] << " SUNK" << endl;
				shipSunk = false;
			}

			cout << "Press <Enter> to continue...";
			cin.get();

			if (m_players[!whichPlayer].getPiecesLeft() == 0)
				gameOver = true;
			else
				if (!reshot)
					whichPlayer = !whichPlayer;
		} while (!gameOver);

		return whichPlayer;
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