   #include "CPlayer.h"

namespace SINK_THE_FLEET
{
	//default constructor
	CPlayer::CPlayer(unsigned short whichPlayer, char gridSize)
	{
		//	validates and sets m_gridSize
		if (toupper(gridSize) == 'L' || toupper(gridSize) == 'S') {
			m_gridSize = gridSize;
		}
		else {
			cout << "Bad gridSize input, defaulting to small" << endl;
			m_gridSize = 'S';
		}

		//	sets m_whichPlayer
		m_whichPlayer = whichPlayer;

		//	set both gamegrids to null
		m_gameGrid[0] = nullptr;
		m_gameGrid[1] = nullptr;

		//	calls allocateMemory
		allocateMemory();

		initializationSelection();

		
	}

	void CPlayer::initializationSelection() {

		short selection;
		string filename;
		bool doPrompt = true;

		while (doPrompt) {
			doPrompt = true;
			system("cls");
			cout << "Player " << m_whichPlayer + 1 << ", how would you like to set up your grid?" << endl;
			cout << "(1) Load grid from file" << endl;
			cout << "(2) Manually set ships" << endl;
			cout << "(3) Randomly place all ships" << endl;
			safeRead(cin, selection, "choose an option from above (enter a number)");

			switch (selection) {
			case 1:
				safeRead(cin, filename, "enter filename");
				if (getGrid(filename))
					doPrompt = false;	// loading succeeds, exit prompt. Otherwise, prompt should restart from the top of loop
				else
					cout << "grid failed to load. restarting this player's prompt... <press ENTER to continue>" << endl;
					cin.ignore(FILENAME_MAX, '\n');
					cin.get();	// this might be unnecessary to hold prompt at this spot for 1 char input
				break;
			case 2:
				if (setShips())	// this will show as error until setShips() is developed to return bool
					doPrompt = false;	// setting succeded, exit prompt
				break;
			case 3:
				autoSetShips();
				doPrompt = false;	// autoSetShips should automatically succeed (will continue re-rolling until success)
				break;
			default:
				cout << "bad input, try again <press ENTER to continue>" << endl;
				cin.ignore(FILENAME_MAX, '\n');
				cin.get();	// this might be unnecessary to hold prompt at this spot for 1 char input

			}
		}

		
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
			//location.getRow();
			ifs >> row;
			bowCoordinates.inputCoordinates(ifs, fsize); // ----====assuming inputCoordinates grabs both chars
			m_ships[i].setBowLocation(bowCoordinates);
			//players[whichPlayer].m_ships[i].m_bowLocation.m_row = (short)(row - 'A');  // row


			//ifs >> col;
			//m_ships[i].setBowLocation();
			//players[whichPlayer].m_ships[i].m_bowLocation.m_col = col - 1;	// column

			// ~_~_~_~_~Old Validation. Update to check validity of current coords?
			//if (!isValidLocation(players[whichPlayer], i, size)) {
			//	cout << "Bad Grid. Ships intersect or out of bounds" << endl
			//		<< " press <enter> to continue" << endl;
			//	cin.ignore(FILENAME_MAX, '\n');
			//	// clear the grid
			//	clearGrid(players[whichPlayer].m_gameGrid[0], size);
			//	return false;
			//}

			//!!double check whether .shipSize property is allowed to be called like that
			for (int p = 0; p < (int)m_ships[i].shipSize; p++) { // loop through each coordinate the ship touches

				//int shipX = players[whichPlayer].m_ships[i].m_bowLocation.m_col;	// get x coordinate --old
				int shipX = m_ships[i].getBowLocation().getCol();	// get x coordinate
				int shipY = m_ships[i].getBowLocation().getRow();	// get y coordinate

				if (m_ships[i].getOrientation() == VERTICAL)	//	if VERTICAL
					m_gameGrid[0]
					players[whichPlayer].m_gameGrid[0][shipY + p][shipX] = players[whichPlayer].m_ships[i].m_name;	// write ship ID into location (y incremented)
				else				// if HORIZONTAL
					players[whichPlayer].m_gameGrid[0][shipY][shipX + p] = players[whichPlayer].m_ships[i].m_name;	// write ship ID into location (x incremented)
			}

			players[whichPlayer].m_ships[i].m_piecesLeft = shipSize[i];		// initialize piecesLeft for each ship

		}

		players[whichPlayer].m_piecesLeft = TOTALPIECES; // player starts with 17 pieces total

		ifs.close();

		cout << "File " << fileName << " successfully loaded" << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(FILENAME_MAX, '\n');

		return true;
	}

	bool CPlayer::isValidLocation(short whichShip)
	{
		short numberOfRows = (this->m_gridSize == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (this->m_gridSize == 'L') ? LARGECOLS : SMALLCOLS;
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
					this->getCell(**this->m_gameGrid[0], bow.getCol + i) != NOSHIP) //check if spot is empty
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
					this->getCell(**this->m_gameGrid[0], bow.getRow + i) != NOSHIP) // check overlapping from previous entries
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

	void CPlayer::autoSetShips() {

		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;

		//	the rand() function (from cstdlib) generates 'random' number based on a 'seed'
		//	multiple runs creating a series of rand() numbers based on the same 'seed' will produce the same series of numbers
		//	
		//	To make this more random, change the seed.
		//	srand(x) changes the seed according to x(integer type)
		//	time(0) gets the current system's time in milliseconds past the system's reference epoch

		//	srand(time(0)) plants an unpredictable 'seed', to make rand() 'more' random
		srand(time(0));

		for (short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++) {	// loop through all ships

			bool badCoord = true;
			int randX;
			int randY;
			CCell coord;
			while (badCoord) {
				badCoord = true;
				randX = rand() % numberOfCols;	// random number from 0 to numberOfCols
				randY = rand() % numberOfRows;	// random number from 0 to numberOfRows
				m_ships[j].setBowLocation(CCell(randY, randX));
				if (isValidLocation(j))	// if m_ships[j] is in a valid location...
					badCoord = false;	//	do NOT re-roll

			}
		}
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
		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;

		try
		{
			for (int whichGrid = 0; whichGrid < NUMPLAYERS; whichGrid++)	// loop through both grid types -- current player and opponent
			{
				
					m_gameGrid[whichGrid] = nullptr;					//	initialize to null pointer -- simplifies debugging if exception thrown by line below -- cleans this spot in mem
					m_gameGrid[whichGrid] = new CShip*[numberOfRows];	//	allocate memory for array of pointers to ships -- each item constitutes a row pointer
					for (short j = 0; j < numberOfRows; ++j)
					{
						// set the pointers to NULL, then allocate the
						// memory for each row in each grid
						m_gameGrid[whichGrid][j] = nullptr;
						m_gameGrid[whichGrid][j] = new CShip[numberOfCols];	//	allocate a new ship array that each row pointer will point to

						for (short k = 0; k < numberOfCols; ++k)
						{
							m_gameGrid[whichGrid][j][k] = NOSHIP;	//	initialize all items in row to NOSHIP
						} // end for k
					} // end for j

				// end for i
			} // end for whichGrid
		}
		catch (bad_alloc e)	// badalloc might be better exception
		{
			deleteMem();
			cerr << "exception: " << e.what() << endl;
			cout << "shutting down" << endl;
			cin.ignore(FILENAME_MAX, '\n');
			exit(EXIT_FAILURE);
		}

	}
	void CPlayer::deleteMemory()
	{
		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;

		// delete[] in reverse order of allocMem()
		// be sure to check if the memory was allocated (!nullptr) BEFORE deleting

		for (int whichGrid = 0; whichGrid < NUMPLAYERS; whichGrid++) {	// loop through both types of grids

				for (short j = 0; j < numberOfRows; ++j) {	//	loop through all of the rows

															//	if pointer is NOT null --> delete the array of ships this row pointer points to
					if (m_gameGrid[whichGrid][j] != nullptr)
						delete[] m_gameGrid[whichGrid][j];
				}

				//	if pointer is NOT null --> delete the array of row pointers
				if (m_gameGrid[whichGrid] != nullptr)
					delete[] m_gameGrid[whichGrid];

			

		}

	}
}