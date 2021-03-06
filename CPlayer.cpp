//----------------------------------------------------------------------------
// File:		CPlayer.cpp
//
// Functions:	CPlayer::CPlayer(unsigned short whichPlayer, char gridSize);
//				void CPlayer::initializationSelection();
//				CPlayer::CPlayer(const CPlayer& playerObj);
//				CPlayer CPlayer::operator=(CPlayer& playerObj);
//				void CPlayer::printGrid(ostream & sout, short whichGrid)
//					const;
//				bool CPlayer::getGrid(string fileName);
//				bool CPlayer::isValidLocation(short whichShip);
//				CShipInfo CPlayer::operator[](short index) const;
//				bool CPlayer::saveGrid();
//				bool CPlayer::setShips();
//				void CPlayer::autoSetShips();
//				void CPlayer::hitShip(CShip ship);
//				CPlayer CPlayer::operator--();
//				void CPlayer::allocateMemory();
//				void CPlayer::deleteMemory();
//----------------------------------------------------------------------------

#include "CPlayer.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Class:			CPlayer
	//
	// Title:			Player Class
	//
	// Description:		Definitions for CPlayer methods and related functions
	//
	// Programmer:		Aaron Miller
	//					Albert Shymanskyy
	//					Cameron Stevenson
	//					Matthew Jacobson
	//					Paul Jacobson
	//   
	// Date:			03/12/2018
	// 
	// Version:			1.0.0
	//  
	// Environment:		Hardware: PC-compatible
	// 					OS: Microsoft Windows 10
	// 					Compiler: Microsoft Visual Studio 2017
	//
	// Properties:		unsigned short m_whichPlayer;
	//					short m_piecesLeft;
	//					CShipInfo m_ships[SHIP_SIZE_ARRAYSIZE];
	//					char m_gridSize;
	//					CShip **m_gameGrid[2];
	//
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------

	const char *CPlayer::shipNames[SHIP_SIZE_ARRAYSIZE] = { "No Ship",
		"Mine Sweeper", "Submarine", "Frigate", "Battleship",
		"Aircraft Carrier" };

	//------------------------------------------------------------------------
	// Class:			CPlayer
	// Method:			CPlayer()
	// Description:		Default constructor
	// Input:			Player's number and size of the grid
	// Output:			None
	// Calls:			None
	// Called By:		CSinkTheFleet()
	// Parameters:		unsigned short whichPlayer
	//					char gridSize
	// Returns:			None 
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	CPlayer::CPlayer(unsigned short whichPlayer, char gridSize)
	{
		constructed = true;
		//	validates and sets m_gridSize
		if (toupper(gridSize) == 'L' || toupper(gridSize) == 'S') {
			m_gridSize = gridSize;
		}
		else {
			cout << "Bad gridSize input, defaulting to small" << endl;
			m_gridSize = 'S';
		}

		for (int i = 0; i < SHIP_SIZE_ARRAYSIZE; i++) {
			m_ships[i] = CShipInfo(CShip((Ship)i), VERTICAL, CCell(0, 0), shipSize[i]);
		}

		//	sets m_whichPlayer
		m_whichPlayer = whichPlayer;

		// set both gamegrids to null
		m_gameGrid[0] = nullptr;
		m_gameGrid[1] = nullptr;

		//	initialize m_piecesLeft
		m_piecesLeft = TOTALPIECES;

		// calls allocateMemory
		allocateMemory();

		/*cout << m_gameGrid[0][0][0] << endl;*/

		initializationSelection();
	}

	//------------------------------------------------------------------------
	// Class:			CPlayer
	// Method:			initializationSelection()
	// Description:		Function for choosing between three ways of setting
	//					ships
	// Input:			Which choice
	// Output:			None
	// Calls:			safeRead()
	//					getGrid()
	//					setShips()
	//					autoSetShips()
	// Called By:		CPlayer()
	// Parameters:		None
	// Returns:			None 
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	void CPlayer::initializationSelection() {
		constructed = true;
		short selection = 0;
		string filename;
		bool doPrompt = true;

		while (doPrompt) {
			clearGrid(0);	// ensure grid is empty
			doPrompt = true;
			system("cls");
			cout << "Player " << m_whichPlayer
				<< ", how would you like to set up your grid?" << endl;
			cout << "(1) Load grid from file" << endl;
			cout << "(2) Manually set ships" << endl;
			cout << "(3) Randomly place all ships" << endl;
			safeRead(cin, selection,
				"choose an option from above (enter a number)");
			//cout << "Choose an option from above (enter a number)" << endl;
			//cin >> selection;
			//cin.ignore(FILENAME_MAX, '\n');
			switch (selection)
			{
			case 1:
				safeRead(cin, filename, "enter filename");
				//cout << "Enter filename" << endl;
				//cin >> filename;
				//cin.ignore(FILENAME_MAX, '\n');
				if (getGrid(filename))
					// loading succeeds, exit prompt. Otherwise, prompt should
					// restart from the top of loop
					doPrompt = false;	
				break;

			case 2:
				if (setShips())
					// setting succeded, exit prompt
					doPrompt = false;

				break;

			case 3:
				if(autoSetShips())
				// autoSetShips should automatically succeed (will continue
				// re-rolling until success)
					doPrompt = false;

				break;

			default:
				cout << "Restarting prompt <press ENTER to continue>"
					<< endl;
				cin.ignore(FILENAME_MAX, '\n');
				// this might be unnecessary to hold prompt at this spot for 1
				// char input
				//cin.get();
			}
		}	
	}
	
	//------------------------------------------------------------------------
	// Class:			CPlayer
	// Method:			CPlayer()
	// Description:		Copy construcor, copies the properties of an existing
	//					object into a new object and creates new pointers for
	//					CShip
	// Input:			Another object
	// Output:			A copy of an object
	// Calls:			getBowLocation()
	//					getOrientation()
	//					getPiecesLeft()
	// Called By:		setShips()
	// Parameters:		const CPlayer& playerObj
	// Returns:			None 
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------
	CPlayer::CPlayer(const CPlayer& playerObj) :
		m_whichPlayer(playerObj.m_whichPlayer),
		m_gridSize(playerObj.m_gridSize), m_piecesLeft(playerObj.m_piecesLeft)
	{
		short numberOfRows = (toupper(playerObj.m_gridSize) == 'L') ?
			LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(playerObj.m_gridSize) == 'L') ?
			LARGECOLS : SMALLCOLS;

		for (int i = 0; i < 6; i++)
		{
			m_ships[i].setName(playerObj.m_ships[i].getName());
			m_ships[i].setBowLocation(playerObj.m_ships[i].getBowLocation());
			m_ships[i].setOrientation(playerObj.m_ships[i].getOrientation());
			m_ships[i].setPiecesLeft(playerObj.m_ships[i].getPiecesLeft());
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
						(this)->m_gameGrid[whichGrid][j][k] =
							playerObj.m_gameGrid[whichGrid][j][k];
					} // end for ->
				} // end for j

			} // end for i
		}
	}

	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:       CPlayer CPlayer::operator=(CPlayer& playerObj) 
	//	description:  assigns the members of an object to another 
	//	Input:        None 
	//	Output:       None 
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   CPlayer &playerObj reference to an existing CPlayer
	//					object
	//	Returns:      CPlayer object after the assignment is complete
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	CPlayer CPlayer::operator=(CPlayer& playerObj) 
	{
		short numberOfRows = (toupper(playerObj.m_gridSize) == 'L') ?
			LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(playerObj.m_gridSize) == 'L') ?
			LARGECOLS : SMALLCOLS;
    
		deleteMemory();	// delete BEFORE changing variables (remove current data)

		m_whichPlayer = playerObj.m_whichPlayer;
		m_gridSize = playerObj.m_gridSize;
		m_piecesLeft = playerObj.m_piecesLeft;

		for (short i = 1; i < SHIP_SIZE_ARRAYSIZE; i++) {
			m_ships[i] = playerObj.m_ships[i];
		}

		allocateMemory();	// allocate afterwards -- save data according to variables after changing
		

		for (short row = 0; row < numberOfRows; row++) 
		{
			for (short col = 0; col < numberOfCols; col++) 
			{
				for (short whichGrid = 0; whichGrid < NUMPLAYERS; whichGrid++) 
				{
					m_gameGrid[whichGrid][row][col] = playerObj.m_gameGrid[whichGrid][row][col];
				}
			}
		}
		return *this;
	}
	
	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:       CPlayer CPlayer::printGrid(ostream & sout, short
	//					whichGrid) const
	//	description:  prints grid based on whichGrid 
	//	Input:        None 
	//	Output:       players grid 
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   short whichGrid - 0 or 1 (ship grid or hits/misses)
	//				  ostream &sout - ostream reference
	//	Returns:      n/a
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
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
				CCell cell(i, j);
				sout << " ";
				sout << m_gameGrid[whichGrid][i][j];
				sout << VERT;
			}
				sout << endl;
				sout << HORIZ;

				for (short j = 0; j < numberOfCols; ++j)
					sout << HORIZ << HORIZ << CR;

				sout << endl;
		}
	}

	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:       bool CPlayer::getGrid(string fileName)
	//	description:  attempts to get grid that user inputs 
	//	Input:        fileName 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   n/a
	//	Returns:      true if successful, false otherwise
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	bool CPlayer::getGrid(string fileName)
	{
		string line;
		ifstream ifs;
		Ship ship = NOSHIP;
		short shipCount[SHIP_SIZE_ARRAYSIZE] = { 0 };
		char cell = ' ';
		char fsize = 'S';
		CCell bowCoordinates;

		//Start with fresh grid
		clearGrid(0);

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

		// loop through all 6 ship data components of playergrid
		for (int i = 1; i < 6; i++)
		{
			//Ship Orientation
			ifs >> line;
			if (line == "V")
				m_ships[i].setOrientation(CDirection(VERTICAL));
			else
			{
				m_ships[i].setOrientation(CDirection(HORIZONTAL));
			}

			// assuming inputCoordinates grabs both chars
			bowCoordinates.inputCoordinates(ifs, fsize); 
			m_ships[i].setBowLocation(bowCoordinates);

			if (!isValidLocation(i)) {
				cout << "Bad Grid. Ships intersect or out of bounds" << endl
							<< " press <enter> to continue" << endl;
				cin.ignore(FILENAME_MAX, '\n');

				clearGrid(0);
				return false;
			}

			// loop through each coordinate the ship touches
			for (int p = 0; p < shipSize[i]; p++) { 

				if (m_ships[i].getOrientation() == VERTICAL) //	if VERTICAL
				{
					CCell placement(bowCoordinates.getRow() + p,
						bowCoordinates.getCol());
					setCell(0, placement, m_ships[i].getName());
				}					
				else // if HORIZONTAL
				{
					CCell placement(bowCoordinates.getRow(),
						bowCoordinates.getCol() + p);
					setCell(0, placement, m_ships[i].getName());
				}									
			}
			m_ships[i].setPiecesLeft(shipSize[i]);
		}

		m_piecesLeft = TOTALPIECES;

		ifs.close();

		cout << "File " << fileName << " successfully loaded" << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(FILENAME_MAX, '\n');

		printGrid(cout, 0);

		//Final confirmation prompt. 'N' returns user to placement sytle menu.
		if (safeChoice("Is this grid ok?", 'Y', 'N') == 'N')
		{
			clearGrid(0);
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:       bool CPlayer::isValidLocation(short whichShip)
	//	description:  checks to see if ship location is valid
	//				  to be valid, ship must not go out of bounds
	//				  or collide with any other ships
	//	Input:        n/a 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   short whichShip - corresponds to number for ship in
	//					m_ships
	//	Returns:      true if location is valid, false otherwise
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	bool CPlayer::isValidLocation(short whichShip)
	{
		short numberOfRows = (m_gridSize == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (m_gridSize == 'L') ? LARGECOLS : SMALLCOLS;
		//get orientation
		Direction orientation = m_ships[whichShip].getOrientation();
		CCell bow = m_ships[whichShip].getBowLocation();
		short shipLength = shipSize[whichShip];

		bool isOpen = true;

		switch (orientation)
		{
		case HORIZONTAL: // ship is horizontal
			for (short i = 0; i < shipLength && isOpen; i++)
			{
				if (((bow.getCol() + shipLength) > numberOfCols) ||
					getCell(0, CCell(bow.getRow(), bow.getCol() + i)) != NOSHIP)
					// check if spot is empty
					isOpen = false;

			}

			break;

		case VERTICAL: // ship is vertical
			for (short i = 0; i < shipLength && isOpen; i++)
			{
				if (((bow.getRow() + shipLength) > numberOfRows) ||
					getCell(0, CCell(bow.getRow() + i, bow.getCol())) != NOSHIP)
					// check overlapping from previous entries
					isOpen = false;
			}

			break;
		}

		return isOpen;
	}

	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:      CShipInfo CPlayer::operator[](short index) const
	//	description:  overloaded [] operator for accessing m_ships
	//	Input:        n/a 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   short index - index to return in m_ships
	//	Returns:      CShipInfo object
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	CShipInfo CPlayer::operator[](short index) const
	{
		if ((index > SHIP_SIZE_ARRAYSIZE))
			throw range_error("Index out of range"); // throw range_error

		return m_ships[index];
	}

	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:		  clearGrid()
	//	description:  sets all indexes within both gamegrids to NOSHIP
	//	Input:        index of grid to clear
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   whichPlayer (short)
	//	Returns:      void
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	void CPlayer::clearGrid(short whichPlayer) {
		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS :
			SMALLROWS;
		short numberOfCols = (toupper(m_gridSize) == 'L') ? LARGECOLS :
			SMALLCOLS;

		for (short row = 0; row < numberOfRows; row++) {
			for (short col = 0; col < numberOfCols; col++) {
				m_gameGrid[whichPlayer][row][col] = NOSHIP;
			}
		}
	}

	//-----------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:      bool CPlayer::saveGrid()
	//	description:  saves current grid to a file
	//	Input:        n/a 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   n/a
	//	Returns:      true if grid saved successfully, false otherwise
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	bool CPlayer::saveGrid()
	{
		string filename;
		ofstream ofs;
		Ship ship = NOSHIP;
		short shipCount[SHIP_SIZE_ARRAYSIZE] = { 0 };
		char cell = ' ';
		char orientation;
		char row;
		short col;
		//short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
		//short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

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

		for (int i = 1; i < 6; i++)
		{
			// orientation
			if (m_ships[i].getOrientation() == VERTICAL)
				orientation = 'V';
			else
				orientation = 'H';

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

		return true;
	}

	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:       bool CPlayer::setShips()
	//	description:  prompt loop for setting ships
	//	Input:        n/a 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   n/a
	//	Returns:      true if grid saved successfully, false otherwise
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	bool CPlayer::setShips()
	{
		char input = 'V';
		char ok = 'Y';
		bool badShip;
		char save = 'N';
		ostringstream outSStream;
		CCell bow;

		//Start with empty grid
		clearGrid(0);
		m_piecesLeft = TOTALPIECES; // TOTALPIECES = 17

		// loop through each of this player's ships
		for (short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
		{
			do
			{
				badShip = false; // reset loop flag -- will exit by default

				printGrid(cout, NOSHIP); //Show grid. Empty at first.				
				
				// Initialize pieces left for each ship
				m_ships[j].setPiecesLeft(shipSize[j]); 
				
				// ORIENTATION
				outSStream.str("");
				outSStream << "Player " << m_whichPlayer << " Enter " 
					<< shipNames[j] << " orientation";
				input = safeChoice(outSStream.str(), 'V', 'H');

				if (input == 'V')
					m_ships[j].setOrientation(CDirection(VERTICAL));
				else
					m_ships[j].setOrientation(CDirection(HORIZONTAL));

				//BOW COORDINATE PROMPT
				cout << "Player " << m_whichPlayer << " Enter " <<
					shipNames[j] << " bow coordinates <row letter><col #>: "
					<< endl;			
				// BOW COORDINATE INPUT
				bow.inputCoordinates(cin, m_gridSize);
				m_ships[j].setBowLocation(bow);

				// if ok
				if (!isValidLocation(j))
				{
					cout << "invalid location. Press <enter>";
					cin.ignore(FILENAME_MAX, '\n');
					cin.get();
					j--; // redo current ship

					continue; // skip to next loop iteration
				}

				//	WRITING SHIPS INTO GRID ARRAYS
				for (int p = 0; p < shipSize[j]; p++) 
				{
					if (m_ships[j].getOrientation() == VERTICAL)
					{	//	if VERTICAL
						// write ship ID into location (Column incremented)
						CCell placement(bow.getRow() + p, bow.getCol());
						setCell(0, placement, m_ships[j].getName());
					}
					else // if HORIZONTAL
					{
						// write ship ID into location (Row incremented)
						CCell placement(bow.getRow(), bow.getCol() + p);
						setCell(0, placement, m_ships[j].getName());
					}
				}

				//GRID CONFIRMATION
				printGrid(cout, 0);
				outSStream.str("");
				outSStream << shipNames[j] << " location okay?";
				cin.ignore(FILENAME_MAX, '\n');

				if (safeChoice(outSStream.str(), 'Y', 'N') == 'N')	// is this ship ok
				{
					badShip = true; // redo loop

					for (int p = 0; p < shipSize[j]; p++)
					{  // erase ship from grid
						// if VERTICAL
						if (m_ships[j].getOrientation() == VERTICAL)
						{
							CCell placement(bow.getRow() + p,
								bow.getCol());
							// Sets cell to NOSHIP
							setCell(0, placement, NOSHIP);
						}
							
						else // if HORIZONTAL
						{
							CCell placement(bow.getRow(),
								bow.getCol() + p);
							//Sets cell to NOSHIP
							setCell(0, placement, NOSHIP);
						}							
					}
				}
			} while (badShip);
		} // end for j

		//Final confirmation prompt. 'N' returns user to placement sytle menu.
		if (safeChoice("Is this grid ok?", 'Y', 'N') == 'N')
		{
			clearGrid(0);
			return false;
		}			

		//Save prompt
		do
		{
			//cout << endl << "Do you wish to save this grid to a file?";
			if (safeChoice("Do you wish to save this grid to a file?", 'Y', 'N') == 'N')
				break;
		} while (saveGrid() != true);

		return true;
	}
	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:       void CPlayer::autoSetShips()
	//	description:  sets ships in the players grid to random locations
	//	Input:        n/a 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   n/a
	//	Returns:      n/a
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	bool CPlayer::autoSetShips()
	{
		bool repeatRoll;
		do {
			clearGrid(0);
			repeatRoll = false;
			short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS :
				SMALLROWS;
			short numberOfCols = (toupper(m_gridSize) == 'L') ? LARGECOLS :
				SMALLCOLS;

			//	the rand() function (from cstdlib) generates 'random' number based
			//	on a 'seed'
			//	multiple runs creating a series of rand() numbers based on the
			//	same 'seed' will produce the same series of numbers
			//	
			//	To make this more random, change the seed.
			//	srand(x) changes the seed according to x(integer type)
			//	time(0) gets the current system's time in milliseconds past the
			//	system's reference epoch

			//	srand(time(0)) plants an unpredictable 'seed', to make rand()
			//	'more' random
			srand(time(0));

			// loop through all ships
			for (short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
			{
				bool badCoord = true;
				int randX;
				int randY;
				CCell coord;

				//printGrid(cout, 0);
				while (badCoord)
				{
					badCoord = true;
					randX = rand() % numberOfCols;	// random number from 0 to numberOfCols
					randY = rand() % numberOfRows;	// random number from 0 to numberOfRows

					if (rand() % 2 == 0) 	// if rand() is even
						m_ships[j].setOrientation(CDirection(VERTICAL));
					else
						m_ships[j].setOrientation(CDirection(HORIZONTAL));

					m_ships[j].setBowLocation(CCell(randY, randX));

					// if m_ships[j] is in a valid location...
					if (isValidLocation(j)) {
						badCoord = false;	//	do NOT re-roll

						for (int i = 0; i < shipSize[j]; i++) {
							if ((Direction)m_ships[j].getOrientation() == VERTICAL)
								setCell(0, CCell(randY + i, randX), m_ships[j].getName());
							else
								setCell(0, CCell(randY, randX + i), m_ships[j].getName());
						}
					}

				}
			}

			printGrid(cout, 0);
			if (safeChoice("Re-roll ship random ship placements?", 'Y', 'N') == 'Y')
				repeatRoll = true;
			else
				if (safeChoice("Use this grid?", 'Y', 'N') == 'Y') {
					repeatRoll = false;
					if (safeChoice("Save this grid to file?", 'Y', 'N') == 'Y')
						saveGrid();
				}
				else {
					cout << "Grid will now be cleared <press ENTER to continue>" << endl;
					cin.ignore(FILENAME_MAX, '\n');
					return false;
				}

		} while (repeatRoll);

		return true;
	}
	
	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:      void CPlayer::hitShip(CShip ship)
	//	description:  decrements the pieces left in players fleet
	//				  and the pieces left of the passed in Ship
	//	Input:        n/a 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   
	//	Returns:      n/a
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	void CPlayer::hitShip(CShip ship)
	{
		--*this;
		--m_ships[ship];
	}
	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:      void CPlayer::hitShip(CShip ship)
	//	description:  decrements the pieces left in players fleet
	//				  and the pieces left of the passed in Ship
	//	Input:        n/a 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   
	//	Returns:      n/a
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	CPlayer CPlayer::operator--()
	{
		m_piecesLeft--;

		return *this;
	}
	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:      void CPlayer::hitShip(CShip ship)
	//	description:  decrements the pieces left in players fleet
	//				  and the pieces left of the passed in Ship
	//	Input:        n/a 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   
	//	Returns:      n/a
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	void CPlayer::allocateMemory()
	{
		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS :
			SMALLROWS;
		short numberOfCols = (toupper(m_gridSize) == 'L') ? LARGECOLS :
			SMALLCOLS;

		try
		{
			// loop through both grid types -- current player and opponent
			for (int whichGrid = 0; whichGrid < NUMPLAYERS; whichGrid++)	
			{
				// initialize to null pointer -- simplifies debugging if
				// exception thrown by line below -- cleans this spot in mem
				m_gameGrid[whichGrid] = nullptr;
				// allocate memory for array of pointers to ships -- each item
				// constitutes a row pointer
				m_gameGrid[whichGrid] = new CShip*[numberOfRows];
				for (short j = 0; j < numberOfRows; ++j)
				{
					// set the pointers to NULL, then allocate the
					// memory for each row in each grid
					m_gameGrid[whichGrid][j] = nullptr;
					// allocate a new ship array that each row pointer will
					// point to
					m_gameGrid[whichGrid][j] = new CShip[numberOfCols];	

						for (short k = 0; k < numberOfCols; ++k)
						{
							m_gameGrid[whichGrid][j][k] = NOSHIP;	//	initialize all items in row to NOSHIP
							/*cout << m_gameGrid[whichGrid][j][k];*/
						} // end for k
						cout << endl;
					} // end for j

				// end for i
			} // end for whichGrid
		}
		catch (bad_alloc e)	// badalloc might be better exception
		{
			deleteMemory();
			cerr << "exception: " << e.what() << endl;
			cout << "shutting down" << endl;
			cin.ignore(FILENAME_MAX, '\n');
			exit(EXIT_FAILURE);
		}
	}

	//------------------------------------------------------------------------
	//	Class:        CPlayer
	//	method:      void CPlayer::hitShip(CShip ship)
	//	description:  decrements the pieces left in players fleet
	//				  and the pieces left of the passed in Ship
	//	Input:        n/a 
	//	Output:       n/a
	//	Calls:        n/a 
	//	Called By:    n/a 
	//	Parameters:   
	//	Returns:      n/a
	//	History Log:
	//	              3/6/18
	//------------------------------------------------------------------------
	void CPlayer::deleteMemory()
	{
		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS :
			SMALLROWS;

		// delete[] in reverse order of allocMem()
		// be sure to check if the memory was allocated (!nullptr) BEFORE
		// deleting
		if (constructed) {
			// loop through both types of grids
			for (int whichGrid = 0; whichGrid < NUMPLAYERS; whichGrid++)
			{
				// loop through all of the rows
				for (short j = 0; j < numberOfRows; ++j)
				{
					cout << m_gameGrid[whichGrid][0][0] << endl;

					// if pointer is NOT null --> delete the array of ships this
					// row pointer points to
					if (m_gameGrid[whichGrid][j] != nullptr)
						delete[] m_gameGrid[whichGrid][j];
				}

				//	if pointer is NOT null --> delete the array of row pointers
				if (m_gameGrid[whichGrid] != nullptr)
					delete[] m_gameGrid[whichGrid];
			}
		}
	}
}