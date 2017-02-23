#include "RentalStore.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
 
RentalStore::RentalStore()
{
}


RentalStore::~RentalStore()
{
	for (std::vector<Movie*>::iterator it = mainMovie.begin(); it != mainMovie.end(); ++it)
	{
		delete (*it);
	}
	for (std::vector<Customer*>::iterator it = customerDatabase.begin(); it != customerDatabase.end(); ++it)
	{
		delete (*it);
	}
}

bool RentalStore::executeCommands(std::string commandData)
{
	/* START Command Text File */
	std::ifstream inFileCommand(commandData.c_str());
	if (!inFileCommand) {
		std::cout << "FileName: " << commandData << " could not be opened." << std::endl;
		return false;
	}

	bool commandCheck = buildCommands(inFileCommand); //Build command database
	inFileCommand.close();
	/* END Command Text File */
	return commandCheck;
}

/*****************************************************************************/
//----------------------------------START------------------------------------//
/*****************************************************************************/
bool RentalStore::buildStore(std::string movieData, std::string customerData)
{
	/* START Movie Text File */
	std::ifstream inFileMovie(movieData.c_str());
	if (!inFileMovie) {
		std::cout << "FileName: " << movieData <<" could not be opened." << std::endl;
		return false;
	}
	
	bool movieCheck = buildMovies(inFileMovie); //Build movie database
	inFileMovie.close();
	/* END Movie Text File */

	/* START Customer Text File */
	std::ifstream inFileCustomer(customerData.c_str());
	if (!inFileCustomer) {
		std::cout << "FileName: " << customerData << " could not be opened." << std::endl;
		return false;
	}
	
	bool customerCheck = buildCustomers(inFileCustomer); //Build customer database
	inFileCustomer.close();
	/* END Customer Text File */
	
	return (movieCheck && customerCheck);
}
/*****************************************************************************/
//	In data4movies.txt, the information about each movie is listed as follows:
//	For comedy movies :		F, Stock, Director, Title, Year it released
//	For drama movies :		D, Stock, Director, Title, Year it released
//	For classics movies :	C, Stock, Director, Title, Major actor Release date
/*****************************************************************************/
bool RentalStore::buildMovies(std::ifstream &inFile)
{
	std::string temp;
	char movieType;

	
	while(true)
	{
		/* Get what type of movie type it is */
		movieType = inFile.get();
		std::getline(inFile, temp, ',');
		
		if (movieType == 'F')
		{
			Movie *temp = new Comedy(inFile);
			comedyArray.push_back(temp);
		}
		/*	DRAMA	*/
		else if (movieType == 'D')
		{
			Movie *temp = new Drama(inFile);
			dramaArray.push_back(temp);
		}
		/*	CLASSIC	*/
		else if (movieType == 'C')
		{
			Movie *temp = new Classic(inFile);
			classicArray.push_back(temp);
		}
		else
		{
			std::cerr << std::endl << "Movie Type: " << movieType << " not recognized" << std::endl;
			std::getline(inFile, temp);
		}

		if (inFile.eof())
		{
			break;
		}
	}

	mainMovie.reserve(comedyArray.size() + dramaArray.size() + classicArray.size()+2);
	mainMovie.insert(mainMovie.end(), classicArray.begin(), classicArray.end());
	mainMovie.insert(mainMovie.end(), dramaArray.begin(), dramaArray.end());
	mainMovie.insert(mainMovie.end(), comedyArray.begin(), comedyArray.end());

	return false;
}

/*****************************************************************************/
//	data4customers.txt contains customer information, one line per customer.
//	Customers have a 4 - digit ID number that uniquely identifies them, 
//	followed by last name, first name, all separated by a space. For example,
//	1111 Mouse Mickey
//	1000 Mouse Minnie
//	You can also assume that this data is formatted correctly.
/*****************************************************************************/
bool RentalStore::buildCustomers(std::ifstream &inFile)
{	
	for (;;)
	{
		Customer *temp = new Customer(inFile);
		customerDatabase.push_back(temp);
		if (inFile.eof())
			break;
	}
	return true;
}

/*****************************************************************************/
//	data4commands.txt is used to test your code.The first field is action 
//	type(B, R, I, or H).Then the rest of fields are as follows :
//	•	Action types I : no more fields
//	•	Action type H : one more field customer ID. Fields are separated by a 
//		space
//	•	Action types B and R : customer ID followed by type of media(currently 
//		only ‘D’ for DVD) then movie type and movie data(with values of the two 
//		sorting attributes, using comma or space to separate them as in the 
//		movie data file).Fields are separated by a space.
/*****************************************************************************/
bool RentalStore::buildCommands(std::ifstream &inFile)
{
	std::string commandType;
	int customerID;

	while (inFile.good())
	{
		/* Get what type of movie type it is */
		inFile >> commandType;

		if (commandType == "I")
		{
			//displayInventory();
			Command *temp = new Inventory();
			temp->executeCommand(customerDatabase, mainMovie);
			delete temp;
		}
		else if (commandType == "H")
		{
			inFile >> customerID;
			Command *temp = new History(customerID, "n/a", "n/a");
			temp->executeCommand(customerDatabase, mainMovie);
			delete temp;
		}
		else if (commandType == "R")
		{
			returnCommand(inFile);
		}
		/*
		else if(commandType == "B")
		{
			borrowCommand(inFile);
		}
		*/
		else
		{
			std::cerr << std::endl << "Command Type: " << commandType << " not recognized" << std::endl;
			std::getline(inFile, commandType);
		}

		if (inFile.eof())
			break;
	}

	return false;
}
void RentalStore::returnCommand(std::ifstream & inFile)
{
	int customerID;
	std::string mediaType;
	std::string movieGenre;
	std::string temp;

	inFile >> customerID;
	inFile >> mediaType;
	inFile >> movieGenre;
	
	if (movieGenre == "D")
	{
		Return *temp = new ReturnDrama(customerID, mediaType, inFile);
		temp->executeCommand(customerDatabase, mainMovie);
		delete temp;
	}

	else if (movieGenre == "C")
	{
		Return *temp = new ReturnClassic(customerID, mediaType, inFile);
		temp->executeCommand(customerDatabase, mainMovie);
		delete temp;
	}

	else if (movieGenre == "F")
	{
		Return *temp = new ReturnComedy(customerID, mediaType, inFile);
		temp->executeCommand(customerDatabase, mainMovie);
		delete temp;
	}

	else
	{
		std::cerr << "Return Movie Genre: " << movieGenre << " not found";
		std::getline(inFile, temp);
	}
}

void RentalStore::borrowCommand(std::ifstream & inFile)
{
	/*else if (commandType == "B")
	{
	inFile >> customerID;
	inFile >> mediaType;
	inFile >> movieGenre;

	if (movieGenre == "D")
	{
	Borrow *temp = new BorrowDrama(customerID, mediaType, inFile);
	temp->executeCommand(customerDatabase, mainMovie);
	delete temp;
	}

	else if (movieGenre == "C")
	{
	Borrow *temp = new BorrowClassic(customerID, mediaType, inFile);
	temp->executeCommand(customerDatabase, mainMovie);
	delete temp;
	}

	else if (movieGenre == "F")
	{
	Borrow *temp = new BorrowComedy(customerID, mediaType, inFile);
	temp->executeCommand(customerDatabase, mainMovie);
	delete temp;
	}

	else
	{
	std::cerr << "Borrow Movie Genre: " << movieGenre << " not found";
	std::getline(inFile, movieTitle);
	}
	}*/
}
/*****************************************************************************/
//-----------------------------------END-------------------------------------//
/*****************************************************************************/