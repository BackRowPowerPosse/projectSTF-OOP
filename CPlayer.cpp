#include "CPlayer.h"

namespace SINK_THE_FLEET
{
	CPlayer::CPlayer()
	{
		
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

	bool CPlayer::getGrid(string fileName)
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
		short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

		short bowLocationRow = player.m_ships[shipNumber].m_bowLocation.m_row;
		short bowLocationColumn = player.m_ships[shipNumber].m_bowLocation.m_col;
		short shipLength = shipSize[shipNumber];
		short shipOrientation = player.m_ships[shipNumber].m_orientation; // 0 is horizontal, 1 is vertical

		short i = 0;

		bool isOpen = true;

		switch (shipOrientation)
		{
		case 0: //ship is horizontal
			while (isOpen && i < shipLength) {
				if (((bowLocationColumn + shipLength) > numberOfCols) ||
					player.m_gameGrid[0][bowLocationRow][bowLocationColumn + i] != NOSHIP) //check if spot is empty
				{
					isOpen = false;
				}
				i++;
			}
			break;
		case 1://ship is vertical
			while (isOpen && i < shipLength) {
				if (((bowLocationRow + shipLength) > numberOfRows) ||
					player.m_gameGrid[0][bowLocationRow + i][bowLocationColumn] != NOSHIP) // check overlapping from previous entries
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
		return CShipInfo();
	}
	CPlayer CPlayer::operator=(CPlayer & player)
	{
		return CPlayer();
	}
	void CPlayer::setGridSize(char size)
	{
		this->m_gridSize = size;
	}
	void CPlayer::setCell(short whichGrid, CCell cell, CShip ship)
	{
	}

	bool CPlayer::saveGrid()
	{
		//~~~~~~~~~~~~~Ready for testing
		string filename;
		ofstream ofs;
		Ship ship = NOSHIP;
		short shipCount[SHIP_SIZE_ARRAYSIZE] = { 0 };
		char cell = ' ';
		char orientation;
		char row;
		short col;
		/*short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;*/


		cout << "Please enter file name: ";		// filename prompt
		cin >> filename;						// enter filename
		cin.ignore(FILENAME_MAX, '\n');			// clean buffer

		try		// attempt to open file
		{
			ofs.open(filename.c_str()); // open file
			if (!ofs)	// check if file opened successfully
			{
				cout << "could not open file " << filename << endl
					<< " press <enter> to continue" << endl;
				cin.ignore(FILENAME_MAX, '\n');
				return false; // communicate to program that loading failed
			}
		}
		catch (exception e) // other exception thrown, file couldn't load
		{
			cout << "could not open file " << filename << endl
				<< " press <enter> to continue" << endl;
			cin.ignore(FILENAME_MAX, '\n');
			return false; // communicate to program that loading failed
		}

		// grid size
		ofs << m_gridSize << endl;
		for (int i = 1; i < 6; i++) {

			// orientation
			if (m_ships[i].getOrientation() == VERTICAL) {
				orientation = 'V';
			}
			ofs << orientation << ' ';

			// row
			row = 'A' + m_ships[i].getBowLocation().getRow();
			ofs << row << ' ';

			// column
			col = m_ships[i].getBowLocation().getCol() + 1;
			ofs << col << endl;

		}

		ofs << endl;
		printGrid(ofs, 0); // print show grid on file

		cout << "File " << filename << " successfully saved" << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(FILENAME_MAX, '\n');
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