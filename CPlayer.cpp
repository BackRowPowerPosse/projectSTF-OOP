   #include "CPlayer.h"

namespace SINK_THE_FLEET
{
	//default constructor
	CPlayer::CPlayer(unsigned short whichPlayer, char gridSize)
	{

	}
	//copy constructor
	CPlayer::CPlayer(const CPlayer& playerObj)
		: m_whichPlayer(playerObj.m_whichPlayer),
		m_gridSize(playerObj.m_gridSize),
		m_piecesLeft(playerObj.m_piecesLeft)
	{
		m_ships = new CShipInfo[6];
		for (int i = 0; i < 6; i++)
		{
			m_ships[i].setName = playerObj.m_ships[i].getName;
			m_ships[i].setBowLocation = playerObj.m_ships[i].getBowLocation;
			m_ships[i].setOrientation = playerObj.m_ships[i].getOrientation;
			m_ships[i].setPiecesLeft = playerObj.m_ships[i].getPiecesLeft;
		}

	}

	CPlayer CPlayer::operator=(CPlayer& playerObj) //for deep copy
	{
		m_whichPlayer = playerObj.m_whichPlayer;
		m_gridSize = playerObj.m_gridSize;
		m_piecesLeft = playerObj.m_piecesLeft;
		//check for self assignment
		if (this != &playerObj)
		{
			//delete whats inside if there is something
			if (m_ships)
				delete[] m_ships;
			for (int i = 0; i < 6; i++)
			{
				m_ships[i].setName = playerObj.m_ships[i].getName;
				m_ships[i].setBowLocation = playerObj.m_ships[i].getBowLocation;
				m_ships[i].setOrientation = playerObj.m_ships[i].getOrientation;
				m_ships[i].setPiecesLeft = playerObj.m_ships[i].getPiecesLeft;
			}
		}
		return *this;
	}
	CPlayer::~CPlayer()
	{
		this->deleteMemory();
	}
	unsigned short CPlayer::getWhichPlayer() const
	{
		return this->m_whichPlayer;
	}
	short CPlayer::getPiecesLeft() const
	{
		return this->m_piecesLeft;
	}
	char CPlayer::getGridSize() const
	{
		return this->m_gridSize;
	}
	Ship CPlayer::getCell(short whichGrid, CCell cell) const
	{
		//return 
	}
	void CPlayer::printGrid(ostream & sout, short whichGrid) const
	{
		//clear the screen before printing the grid
		system("cls");
		short numberOfRows = (toupper(whichGrid) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(whichGrid) == 'L') ? LARGECOLS : SMALLCOLS;

		short whichGrid = (this->m_gridSize == 'S') ? 0 : 1; // 0 - small 1 - large
		char rowMarker = 'A';

		//print out first column (1-12)
		for (short i = 1; i <= numberOfCols; i++)
		{
			sout << right << setw(3) << i;
		}
		sout << endl;

		for (short i = 0; i < numberOfRows; i++)
		{
			//print row (A-H)
			sout << left << rowMarker++;

			//print out ship
			for (int j = 0; j < numberOfCols; j++)
			{
				//printShip(sout, grid[i][j]);
			}
			sout << endl;

			//finish row with 2 horizontal lines and cross right
			for (int k = 1; k < numberOfCols; k++)
			{
				if (k == 1)
				{
					sout << HORIZ << HORIZ << HORIZ << CR;
				}
				sout << HORIZ << HORIZ << CR;
			}
			//end line, go to next row
			sout << endl;
		}
	}
	void CPlayer::getGrid(string fileName) const
	{
	}
	bool CPlayer::isValidLocation(short whichShip)
	{
		short numberOfRows = (this->m_gridSize == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (this->m_gridSize == 'L') ? LARGECOLS : SMALLCOLS;
		short whichGrid = (this->m_gridSize == 'S') ? 0 : 1; // 0 - small 1 - large
		//get orientation
		short orientation = this->m_ships[whichShip].getOrientation();
		CCell bow = this->m_ships[whichShip].getBowLocation();
		short shipLength = this->m_ships[whichShip].getPiecesLeft();

		short i = 0;

		bool isOpen = true;

		switch (orientation)
		{
		case 0: //ship is horizontal
			while (isOpen && i < shipLength) 
			{
				if (((bow.getCol + shipLength) > numberOfCols) ||
					this->getCell(whichGrid, bow.getCol + i) != NOSHIP) //check if spot is empty
				{
					isOpen = false;
				}
				i++;
			}
			break;
		case 1://ship is vertical
			while (isOpen && i < shipLength)
			{
				if (((bow.getRow + shipLength) > numberOfRows) ||
					this->getCell(whichGrid, bow.getRow + i) != NOSHIP) // check overlapping from previous entries
				{
					isOpen = false;
				}
				i++;
			}
			break;
		}
		return isOpen;
	}
	CShipInfo CPlayer::operator[](short index) const
	{
		if ((index > SHIPSIZE) || (index < 1)) //ignore 0
		{
			throw range_error("Index out of range"); //throw range_error
		}
		return this->m_ships[index];
	}

	void CPlayer::setGridSize(char size)
	{
		this->m_gridSize = size;
	}
	void CPlayer::setCell(short whichGrid, CCell cell, CShip ship)
	{
	}
	void CPlayer::saveGrid()
	{
	}
	void CPlayer::setShips()
	{
		//char input = 'V';
		//char ok = 'Y';
		//char save = 'N';
		//char shipResponse = 'N';
		//ostringstream outSStream;
		//Cell location = { 0, 0 };
		//do
		//{

		//	for (short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
		//	{
		//		system("cls");
		//		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
		//		outSStream.str("");
		//		outSStream << "Player " << whichPlayer + 1 << " Enter "
		//			<< shipNames[j] << " orientation";
		//		input = safeChoice(outSStream.str(), 'V', 'H');
		//		players[whichPlayer].m_ships[j].m_orientation
		//			= (input == 'V') ? VERTICAL : HORIZONTAL;
		//		cout << "Player " << whichPlayer + 1 << " Enter " << shipNames[j] <<
		//			" bow coordinates <row letter><col #>: "
		//			<< endl;
		//		players[whichPlayer].m_ships[j].m_bowLocation = location = getCoord(cin, size);

		//		if (!isValidLocation(players[whichPlayer], j, size))
		//		{
		//			cout << "invalid location. Press <enter>";
		//			cin.get();
		//			j--; // redo by resetting the counter
		//			continue;
		//		}

		//		short bowLocationRow = players[whichPlayer].m_ships[j].m_bowLocation.m_row;
		//		short bowLocationCol = players[whichPlayer].m_ships[j].m_bowLocation.m_col;
		//		short finalLocationRow = (players[whichPlayer].m_ships[j].m_bowLocation.m_row) + shipSize[j];
		//		short finalLocationCol = (players[whichPlayer].m_ships[j].m_bowLocation.m_col) + shipSize[j];
		//		Ship shipType = static_cast<Ship>(j);

		//		//0 - horizontal
		//		//1 - vertical

		//		switch (input)
		//		{
		//		case 'H':

		//			for (short i = 0; (bowLocationRow + i) < finalLocationRow; i++)
		//			{
		//				players[whichPlayer].m_gameGrid[0][bowLocationRow][bowLocationCol + i] = shipType;
		//			}
		//			break;

		//		case 'V':

		//			for (short i = 0; (bowLocationCol + i) < finalLocationCol; i++)
		//			{
		//				players[whichPlayer].m_gameGrid[0][bowLocationRow + i][bowLocationCol] = shipType;
		//			}
		//			break;
		//		}

		//		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
		//		cout << "Player " << whichPlayer + 1 << " " << shipNames[j];
		//		shipResponse = safeChoice(" OK? ", 'Y', 'N');

		//		switch (shipResponse)
		//		{
		//		case 'Y':
		//			break;
		//		case 'N':
		//			if (input == 'H')
		//			{
		//				for (short i = 0; (bowLocationRow + i) < finalLocationRow; i++)
		//				{
		//					players[whichPlayer].m_gameGrid[0][bowLocationRow][bowLocationCol + i] = NOSHIP;
		//				}
		//			}
		//			else
		//			{
		//				for (short i = 0; (bowLocationCol + i) < finalLocationCol; i++)
		//				{
		//					players[whichPlayer].m_gameGrid[0][bowLocationRow + i][bowLocationCol] = NOSHIP;
		//				}
		//			}

		//			break;
		//		}
		//		if (shipResponse == 'N')
		//		{
		//			j--; //keep counter at current ship
		//		}
		//	}
		//} while (shipResponse != 'Y');
		//// end for j
		//save = safeChoice("\nSave starting grid?", 'Y', 'N');
		//if (save == 'Y')
		//	//saveGrid(players, whichPlayer, size);
	}
	void CPlayer::hitShip(CShip ship)
	{
		this->m_piecesLeft--;
		
	}
	CPlayer CPlayer::operator--()
	{
		this->m_piecesLeft--;
		return *this;
	}
	void CPlayer::allocateMemory()
	{
	}
	void CPlayer::deleteMemory()
	{
	}
}