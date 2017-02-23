/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		RentalStore.cpp												*/
/*	PARENT:		NONE														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "RentalStore.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
 
RentalStore::RentalStore()
{
}

/*****************************************************************************/
//	~buildDatabases()
//	Goes through the 3 main databases deleting each index, movieDatabase has 
//	pointers to all 3 of the subgenre lists so deleting it will delete those 3 
//	as well.
//	CALLED BY: COMPILER
/*****************************************************************************/
RentalStore::~RentalStore()
{
	for (std::vector<Movie*>::iterator it = movieDB.begin(); it != movieDB.end(); ++it)
	{
		delete (*it);
	}
	for (std::vector<Customer*>::iterator it = customerDB.begin(); it != customerDB.end(); ++it)
	{
		delete (*it);
	}
	for (std::vector<Command*>::iterator it = commandDB.begin(); it != commandDB.end(); ++it)
	{
		delete (*it);
	}
}

/*****************************************************************************/
//	buildDatabases(movieFileName, customerFileName, commandFileName):
//	Checks to see if each FileName can be found and opened, if they can it
//	calls buildMovies, buildCustomers, and buildCommands to create all the
//	databases this program needs to operate. Side note, Linux g++ cannot handle
//	ifStream iF(stringFileName), which is why it's (stringFileName.c_str()) as
//	well as why #include <cstdlib> is included up top
//	CALLED BY: Lab4[Driver]
/*****************************************************************************/
bool RentalStore::buildDatabases(std::string movieFileName, std::string customerFileName, std::string commandFileName)
{
	/* START Movie Text File */
	std::cout << "--- BUILDING MOVIES ---";
	std::ifstream inFileMovie(movieFileName.c_str());
	if (!inFileMovie) {
		std::cerr << "\nERROR: FileName: " << movieFileName <<" could not be opened." << std::endl;
		return false;
	}
	
	bool movieCheck = buildMovies(inFileMovie); //Build movie database
	inFileMovie.close();
	std::cout << "\n--- MOVIES DONE ---\n\n";
	/* END Movie Text File */

	/* START Customer Text File */
	std::cout << "--- BUILDING CUSTOMERS ---\n";
	std::ifstream inFileCustomer(customerFileName.c_str());
	if (!inFileCustomer) {
		std::cerr << "\nERROR: FileName: " << customerFileName << " could not be opened." << std::endl;
		return false;
	}
	
	bool customerCheck = buildCustomers(inFileCustomer); //Build customer database
	inFileCustomer.close();
	std::cout << "--- CUSTOMERS DONE ---\n\n";
	/* END Customer Text File */
	
	/* START Command Text File */
	std::cout << "--- BUILDING COMMANDS ---";
	std::ifstream inFileCommand(commandFileName.c_str());
	if (!inFileCommand) {
		std::cerr << "\nERROR: FileName: " << commandFileName << " could not be opened." << std::endl;
		return false;
	}

	bool commandCheck = buildCommands(inFileCommand); //Build command database
	inFileCommand.close();
	std::cout << "\n--- COMMANDS DONE ---\n\n";
	/* END Command Text File */
	return (movieCheck && customerCheck && commandCheck);
}


/*****************************************************************************/
//	buildMovies(inFile):
//	Gets the first char on each line, representing the VideoCode, then creates
//	a new instance for the corresponding Movie subclass; Comedy[F], Classic[C],
//	Drama[D].
//	For comedy movies :		F, Stock, Director, Title, Year it released
//	For drama movies :		D, Stock, Director, Title, Year it released
//	For classic movies :	C, Stock, Director, Title, Major actor Release date
//	CALLED BY: buildDatabases
/*****************************************************************************/
bool RentalStore::buildMovies(std::ifstream &inFile)
{
	std::string temp;
	char videoCode;

	while(true)
	{
		/* Get what type of movie type it is */
		videoCode = inFile.get();
		std::getline(inFile, temp, ',');
		/*	COMEDY	*/
		if (videoCode == 'F')
		{
			comedyArray.push_back(new Comedy(inFile));
		}
		/*	DRAMA	*/
		else if (videoCode == 'D')
		{
			dramaArray.push_back(new Drama(inFile));
		}
		/*	CLASSIC	*/
		else if (videoCode == 'C')
		{
			classicArray.push_back(new Classic(inFile));
		}
		/*	INVALID VIDEO CODE	*/
		else
		{
			std::cerr << "\nERROR: Video Code: " << videoCode << " not recognized";
			std::getline(inFile, temp);
		}

		if (inFile.eof())
		{
			break;
		}
	}

	/**********/
	sortMovieDatabase();
	/**********/
	movieDB.reserve(comedyArray.size() + dramaArray.size() + classicArray.size());
	movieDB.insert(movieDB.end(), comedyArray.begin(), comedyArray.end());
	movieDB.insert(movieDB.end(), dramaArray.begin(), dramaArray.end());
	movieDB.insert(movieDB.end(), classicArray.begin(), classicArray.end());
	if (movieDB.size() > 0)
	{
		return true;
	}
	return false;
}


/*****************************************************************************/
//	buildCustomers(inFile):
//	creates a new instance of customer for customerDB, 
//	Customer.buildCustomer(inFile) handles how to correctly read in from file
//	CALLED BY: buildDatabases
/*****************************************************************************/
bool RentalStore::buildCustomers(std::ifstream &inFile)
{	
	for (;;)
	{
		customerDB.push_back(new Customer(inFile));
		if (inFile.eof())
			break;
	}
	if (customerDB.size() > 0)
	{
		return true;
	}
	return false;
}

/*****************************************************************************/
//	buildCommands(inFile):
//	Called by buildDatabases, reads in the command text file for the action
//	code, then finds the corresponding class instance to create, handles the
//	inventory [I] and history[H] action codes here, otherwise calls either
//	borrowCommand [B] or returnCommand[R] to correctly handle those action
//	codes.
//	CALLED BY: buildDatabases
/*****************************************************************************/
bool RentalStore::buildCommands(std::ifstream &inFile)
{
	std::string actionType;
 std::string temp;
	int customerID;

	while (true)
	{
		/* Get the Action Type for command */
		inFile >> actionType;

		/*	INVENTORY	*/
		if (actionType == "I")
		{
			commandDB.push_back(new Inventory());
			std::getline(inFile, temp); //clear whats left of the line
		}
		/*	HISTORY	*/
		else if (actionType == "H")
		{
			inFile >> customerID;
			commandDB.push_back(new History(customerID));
			std::getline(inFile, temp); //clear whats left of the line
		}
		/*	RETURN	*/
		else if (actionType == "R")
		{
			returnCommand(inFile);
		}
		/*	BORROW	*/
		else if(actionType == "B")
		{
			borrowCommand(inFile);
		}
		/*	INVALID ACTION TYPE	*/
		else
		{
			std::cerr << "\nERROR: Invalid Action Type: " << actionType;
			std::getline(inFile, temp);
		}

		if (inFile.eof())
			break;
	}
	if (commandDB.size() > 0)
	{
		return true;
	}
	return false;
}
/*****************************************************************************/
//	returnCommand(inFile):
//	called when buildCommands gets an action type of 'R' for return. Reads in
//	until it gets the videoCode, then creates new instance of the correct
//	return subclass. The new instance will continue to read in from file to get
//	correct variables
//	CALLED BY: buildCommands
/*****************************************************************************/
void RentalStore::returnCommand(std::ifstream & inFile)
{
	int customerID;
	std::string mediaType;
	std::string videoCode;
	std::string temp;

	inFile >> customerID;
	inFile >> mediaType;
	inFile >> videoCode;
	/*	DRAMA	*/
	if (videoCode == "D")
	{
		commandDB.push_back(new ReturnDrama(customerID, mediaType, inFile));
	}
	
	/*	CLASSIC	*/
	else if (videoCode == "C")
	{
		commandDB.push_back(new ReturnClassic(customerID, mediaType, inFile));
	}
	
	/*	COMEDY	*/
	else if (videoCode == "F")
	{
		commandDB.push_back(new ReturnComedy(customerID, mediaType, inFile));
	}

	else
	{
		std::cerr << "\nERROR: Invalid Return Video Code: " << videoCode;
		std::getline(inFile, temp);
	}
}
/*****************************************************************************/
//	borrowCommand(inFile):
//	called when buildCommands gets an action type of 'B' for borrow. Reads in
//	until it gets the videoCode, then creates new instance of the correct
//	borrow subclass. The new instance will continue to read in from file to get
//	correct variables
//	CALLED BY: buildCommands
/*****************************************************************************/
void RentalStore::borrowCommand(std::ifstream & inFile)
{
	int customerID;
	std::string mediaType;
	std::string videoCode;
	std::string temp;

	inFile >> customerID;
	inFile >> mediaType;
	inFile >> videoCode;

	/*	DRAMA	*/
	if (videoCode == "D")
	{
		commandDB.push_back(new BorrowDrama(customerID, mediaType, inFile));
	}
	/*	CLASSIC	*/
	else if (videoCode == "C")
	{
		commandDB.push_back(new BorrowClassic(customerID, mediaType, inFile));
	}
	/*	COMEDY	*/
	else if (videoCode == "F")
	{
		commandDB.push_back(new BorrowComedy(customerID, mediaType, inFile));
	}
	/*	INVALID VIDEO CODE*/
	else
	{
		std::cerr << "\nERROR: Invalid Borrow Video Code: " << videoCode;
		std::getline(inFile, temp);
	}
}
/*****************************************************************************/
//	executeCommands():
//	Executes all the commands in the commandDB, commandDB was built
//	built in buildCommands()
//	CALLED BY: Lab4[Driver]
/*****************************************************************************/

bool RentalStore::executeCommands()
{
	if (commandDB.size() == 0)
	{
		std::cerr << "\nNO COMMANDS FOUND\n";
		return false;
	}
	for (int i = 0; i < commandDB.size(); i++)
	{
		commandDB[i]->executeCommand(customerDB, movieDB);
	}
	return true;
}
/*****************************************************************************/
//	FROM ASSIGNMENT PAGE, REMOVE AND COMMENT BEFORE SUBMISSION
//	To store the data in the system, the items should be sorted as follows :
//	* comedy movies(‘F’) sorted by Title, then Year it released
//	* dramas(‘D’) are sorted by Director, then Title
//	* classics(‘C’) are sorted by Release date, then Major actor
//	You can assume that each item is uniquely identified by its complete set 
//	of sorting attributes.
/*****************************************************************************/
bool RentalStore::sortMovieDatabase()
{
	// ALREADY SETUP WHEN THIS IS CALLED, JUST IMPLEMENT THE SORTING
	// ALSO NEED TO IMPLEMENT THE OPERATOR OVERLOADS
	// SORT comedyArray;
	// SORT dramaArray;
	// SORT classicArray;
	// THEY ARE COMBINED INTO movieDB IN buildDatabases()
	return false;
}

void RentalStore::hash(std::string toHash)
{
	// SINCE THE COMMANDS DON'T ALL GIVE US TITLE
	// WE MUST HASH BY:
	// CLASSIC BY ACTOR: getMainAct()
	// COMEDY BY TITLE: getTitle()
	// DRAMA BY TITLE: getTitle()
}
