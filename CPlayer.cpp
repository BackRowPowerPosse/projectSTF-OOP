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
		short numberOfRows = (toupper(playerObj.m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(playerObj.m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;

		for (int i = 0; i < 6; i++)
		{
			m_ships[i].setName = playerObj.m_ships[i].getName;
			m_ships[i].setBowLocation = playerObj.m_ships[i].getBowLocation;
			m_ships[i].setOrientation = playerObj.m_ships[i].getOrientation;
			m_ships[i].setPiecesLeft = playerObj.m_ships[i].getPiecesLeft;
		}
		for (int whichGrid = 0; whichGrid < NUMPLAYERS; whichGrid++)
		{
			// loop through both players -- player 1 and player 2
			for (short i = 0; i < NUMPLAYERS; ++i)
			{
				// initialize to null pointer -- simplifies debugging if
				// exception thrown by line below --cleans this spot
				m_gameGrid[whichGrid] = nullptr;
				// allocate memory for array of pointers to ships
				// -- each item constitutes a row pointer.
				m_gameGrid[whichGrid] = new CShip *[numberOfRows];
				for (short j = 0; j < numberOfRows; ++j)
				{
					m_gameGrid[whichGrid][j] = nullptr;
					m_gameGrid[whichGrid][j] = new CShip[numberOfCols];

					for (short k = 0; k < numberOfCols; ++k)
					{
						// initialize all items in row to NOSHIP
						(this)->m_gameGrid[whichGrid][j][k] = NOSHIP;
					} // end for k
				} // end for j

			} // end for i
		}

	}

	CPlayer CPlayer::operator=(CPlayer& playerObj) //for deep copy
	{
		short numberOfRows = (toupper(playerObj.m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(playerObj.m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;
		m_whichPlayer = playerObj.m_whichPlayer;
		m_gridSize = playerObj.m_gridSize;
		m_piecesLeft = playerObj.m_piecesLeft;
		//check for self assignment
		if (this != &playerObj)
		{
			for (int i = 0; i < 6; i++)
			{
				m_ships[i].setName = playerObj.m_ships[i].getName;
				m_ships[i].setBowLocation = playerObj.m_ships[i].getBowLocation;
				m_ships[i].setOrientation = playerObj.m_ships[i].getOrientation;
				m_ships[i].setPiecesLeft = playerObj.m_ships[i].getPiecesLeft;
			}
			for (int whichGrid = 0; whichGrid < NUMPLAYERS; whichGrid++)
			{
				// loop through both players -- player 1 and player 2
				for (short i = 0; i < NUMPLAYERS; ++i)
				{
					// initialize to null pointer -- simplifies debugging if
					// exception thrown by line below --cleans this spot
					m_gameGrid[whichGrid] = nullptr;
					// allocate memory for array of pointers to ships
					// -- each item constitutes a row pointer.
					m_gameGrid[whichGrid] = playerObj.m_gameGrid[whichGrid];
					for (short j = 0; j < numberOfRows; ++j)
					{
						m_gameGrid[whichGrid][j] = nullptr;
						m_gameGrid[whichGrid][j] = new CShip[numberOfCols];

						for (short k = 0; k < numberOfCols; ++k)
						{
							// initialize all items in row to NOSHIP
							(this)->m_gameGrid[whichGrid][j][k] = NOSHIP;
						} // end for k
					} // end for j

				} // end for i
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
		return m_whichPlayer;
	}
	short CPlayer::getPiecesLeft() const
	{
		return m_piecesLeft;
	}
	char CPlayer::getGridSize() const
	{
		return m_gridSize;
	}
	Ship CPlayer::getCell(short whichGrid, CCell cell) const
	{
		return (**m_gameGrid[whichGrid][cell.getCol][cell.getRow]); 
	}
	void CPlayer::printGrid(ostream & sout, short whichGrid) const
	{
		//clear the screen before printing the grid
		system("cls");
		short numberOfRows = (m_gridSize == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (m_gridSize == 'L') ? LARGECOLS : SMALLCOLS;

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
			for (short j = 0; j < numberOfCols; j++)
			{
				CCell cell(i,j);
				Ship ship = getCell(whichGrid, cell);
				cout << ship;
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
	void CPlayer::getGrid(string fileName)
	{

		string line;
		//string fileName;
		ifstream ifs;
		Ship ship = NOSHIP;
		short shipCount[SHIP_SIZE_ARRAYSIZE] = { 0 };
		char cell = ' ';
		char fsize = 'S';
		char row;
		short col;
		CCell bowCoordinates;
		//short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
		//short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

		//~-~-~-File name already passed in. Assuming prompted before method is called.~-~-~-~
		//cout << "Please enter file name: ";		// filename prompt
		//cin >> fileName;						// string prompt for filename
		//cin.ignore(FILENAME_MAX, '\n');

		//~_~_~_~_~_~Unsure what to do with clearGrid section here.
		//clearGrid(players[whichPlayer].m_gameGrid[0], size); // start with a fresh grid



		try		// attempt to open file
		{
			ifs.open(fileName.c_str()); // open file
			if (!ifs)	// check if file opened successfully
			{
				cout << "could not open file " << fileName << endl
					<< " press <enter> to continue" << endl;
				cin.ignore(FILENAME_MAX, '\n');
				return false; // communicate to program that loading failed
			}
		}
		catch (exception e) // other exception thrown, file couldn't load
		{
			cout << "could not open file " << fileName << endl
				<< " press <enter> to continue" << endl;
			cin.ignore(FILENAME_MAX, '\n');
			return false; // communicate to program that loading failed
		}
		
		// read grid size, check that it matches current game's size
		ifs >> fsize;
		if (fsize != m_gridSize) {
			cout << "Grid size from file does not match" << endl
				<< " press <enter> to continue" << endl;
			cin.ignore(FILENAME_MAX, '\n');
			return false;
		}

		for (int i = 1; i < 6; i++)	// loop through all 6 ship data components of playergrid
		{
			//Ship Orientation
			ifs >> line;
			if (line == "V")
				m_ships[i].setOrientation(CDirection(VERTICAL));
			else
			{
				m_ships[i].setOrientation(CDirection(HORIZONTAL));
			}

			//Ship Bow
			bowCoordinates.inputCoordinates(ifs, fsize); // ----====assuming inputCoordinates grabs both chars
			m_ships[i].setBowLocation(bowCoordinates);


			// ~_~_~_~_~Old Validation. Update to check validity of current coords?
			//if (!isValidLocation(players[whichPlayer], i, size)) {
			//	cout << "Bad Grid. Ships intersect or out of bounds" << endl
			//		<< " press <enter> to continue" << endl;
			//	cin.ignore(FILENAME_MAX, '\n');
			//	// clear the grid
			//	clearGrid(players[whichPlayer].m_gameGrid[0], size);
			//	return false;
			//}

			if (!isValidLocation(i)) {
				cout << "Bad Grid. Ships intersect or out of bounds" << endl
							<< " press <enter> to continue" << endl;
				cin.ignore(FILENAME_MAX, '\n');
				cin.get();
				//!!!!call clear grid here when it's done!!!!
				return false;
			}
				

			//!!double check whether .shipSize property is allowed to be called like that
			for (int p = 0; p < shipSize[i]; p++) { // loop through each coordinate the ship touches

				if (m_ships[i].getOrientation() == VERTICAL)	//	if VERTICAL
					m_gameGrid[0][m_ships[i].getBowLocation.getRow() + p][m_ships[i].getBowLocation.getCol()] = m_ships[i];
					
				else				// if HORIZONTAL
					m_gameGrid[0][m_ships[i].getBowLocation.getRow()][m_ships[i].getBowLocation.getCol() + p] = m_ships[i];					
			}

			//players[whichPlayer].m_ships[i].m_piecesLeft = shipSize[i];		// initialize piecesLeft for each ship

			m_ships[i].setPiecesLeft(shipSize[i]);

		}

		m_piecesLeft = TOTALPIECES;

		ifs.close();

		cout << "File " << fileName << " successfully loaded" << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(FILENAME_MAX, '\n');

		return true;
	}
	bool CPlayer::isValidLocation(short whichShip)
	{
		short numberOfRows = (m_gridSize == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (m_gridSize == 'L') ? LARGECOLS : SMALLCOLS;
		//get orientation
		short orientation = m_ships[whichShip].getOrientation();
		CCell bow = m_ships[whichShip].getBowLocation();
		short shipLength = m_ships[whichShip].getPiecesLeft();

		short i = 0;

		bool isOpen = true;

		switch (orientation)
		{
		case 0: //ship is horizontal
			while (isOpen && i < shipLength) 
			{
				if (((bow.getCol + shipLength) > numberOfCols) ||
					getCell(**this->m_gameGrid[0], bow.getCol + i) != NOSHIP) 
					//check if spot is empty
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
					getCell(**this->m_gameGrid[0], bow.getRow + i) != NOSHIP) 
					// check overlapping from previous entries
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
		if ((index > SHIP_SIZE_ARRAYSIZE))
		{
			throw range_error("Index out of range"); //throw range_error
		}
		return m_ships[index];
	}

	void CPlayer::setGridSize(char size)
	{
		m_gridSize = size;
	}
	void CPlayer::setCell(short whichGrid, CCell cell, CShip ship)
	{
		m_gameGrid[whichGrid][cell.getRow][cell.getCol] = ship;
	}
	void CPlayer::saveGrid()
	{
	}
	void CPlayer::setShips()
	{
		char input = 'V';
		char ok = 'Y';
		bool badShip;
		char save = 'N';
		ostringstream outSStream;
		//Cell location = { 0, 0 };
		CCell bow;
		//clearGrid(players[whichPlayer].m_gameGrid[0], size); // clear the grid

		m_piecesLeft = TOTALPIECES; //TOTALPIECES = 17

		for (short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)	// loop through each of this player's ships
		{
			do {
				badShip = false; // reset loop flag -- will exit by default

				printGrid(outSStream, 0); //Show grid. Empty at first.				
				
				//Initialize pieces left for each ship
				m_ships[j].setPiecesLeft(shipSize[j]); 
				
				//ORIENTATION
				outSStream.str("");
				outSStream << "Player " << this + 1 << " Enter " //Should show "Player (number of player) Enter (shipName) orientation"
					<< shipNames[j] << " orientation";
				
				input = safeChoice(outSStream.str(), 'V', 'H');
				if (input == 'V')
					m_ships[j].setOrientation(CDirection(VERTICAL));
				else
					m_ships[j].setOrientation(CDirection(HORIZONTAL));

				//BOW COORDINATE PROMPT
				cout << "Player " << this + 1 << " Enter " << shipNames[j] <<
					" bow coordinates <row letter><col #>: " << endl;			
				//BOW COORDINATE INPUT
				bow.inputCoordinates(cin, m_gridSize);
				m_ships[j].setBowLocation(bow);

				// if ok
				if (!isValidLocation(j))
				{
					cout << "invalid location. Press <enter>";
					cin.get();
					j--; // redo
					continue; // skip to next loop iteration
				}

				//	WRITING SHIPS INTO GRID ARRAYS
				for (int p = 0; p < shipSize[j]; p++) 
				{

					//int shipX = players[whichPlayer].m_ships[j].m_bowLocation.m_col;	// get x coordinate
					//int shipY = players[whichPlayer].m_ships[j].m_bowLocation.m_row;	// get y coordinate

					if (m_ships[j].getOrientation == VERTICAL)
					{	//	if VERTICAL
						// write ship ID into location (Column incremented)
						CCell placement = (bow.getCol() + j, bow.getRow());
						setCell(0, placement, m_ships[j].getName());
					}
						
					else// if HORIZONTAL
					{
						// write ship ID into location (Row incremented)
						CCell placement = (bow.getCol(), bow.getRow() + j);
						setCell(0, placement, m_ships[j].getName());

					}
				}

				//GRID CONFIRMATION
				printGrid(cout, j);
				
				outSStream.str("");
				outSStream << shipNames[j] << " location okay?";
				ok = safeChoice(outSStream.str(), 'Y', 'N'); // is ship ok?
				if (ok == 'N') {
					badShip = true; // redo loop

					for (int p = 0; p < shipSize[j]; p++) {  // erase ship from grid

						if (m_ships[j].getOrientation() == VERTICAL)	//	if VERTICAL
						{
							CCell placement = (bow.getCol() + j, bow.getRow());
							setCell(0, placement, m_ships[0].getName()); //Sets cell to NOSHIP
						}
							
						else				// if HORIZONTAL
						{
							CCell placement = (bow.getCol(), bow.getRow() + j);
							setCell(0, placement, m_ships[0].getName()); //Sets cell to NOSHIP
						}							
					}
				}
			} while (badShip);
		} // end for j
	}
	void CPlayer::hitShip(CShip ship)
	{
		static_cast<short>(ship);
		m_ships[ship].setPiecesLeft((m_ships[ship].getPiecesLeft) - 1);
		m_piecesLeft--;
		
	}
	CPlayer CPlayer::operator--()
	{
		m_piecesLeft--;
		return *this;
	}
	void CPlayer::allocateMemory()
	{
	}
	void CPlayer::deleteMemory()
	{

	}
}