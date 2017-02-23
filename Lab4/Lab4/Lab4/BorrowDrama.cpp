/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		BorrowDrama.cpp												*/
/*	PARENT:		Borrow														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "BorrowDrama.h"



BorrowDrama::BorrowDrama()
{
}


BorrowDrama::~BorrowDrama()
{
}

BorrowDrama::BorrowDrama(int accNum, std::string medType, std::ifstream & inFile) :
	Borrow(accNum, medType, "D")
{
	buildCommand(inFile);
}

bool BorrowDrama::buildCommand(std::ifstream & inFile)
{
	std::string dirFirst;
	std::string dirLast;
	/* Get Director name */
	std::getline(inFile, director, ',');	// Get Full Name to comma
	std::istringstream dirName(director);	// Put in string stream 
	dirName >> dirFirst;	// dirName[1] = First Name
	dirName >> dirLast;		// dirName[2] = Last name
	while (dirName.good())	//If last name has a split. eg De Broca
	{
		std::string temp = dirLast;
		dirName >> dirLast;
		temp.append(" ");
		temp.append(dirLast);
		dirLast = temp;
	}
	director = dirFirst + " " + dirLast;
	/* Get Movie Title*/
	std::getline(inFile, movieTitle, ',');

	std::string temp;
	std::getline(inFile, temp);
	return true;
}

bool BorrowDrama::executeCommand(std::vector<Customer*> &custDB, std::vector<Movie*> &movieDB)
{
	Customer *curCustomer;
	Movie *curMovie;
	int tempAcc = getAccountNumber();
	bool foundMovie = false;
	bool foundCust = false;

	for (int i = 0; i < custDB.size(); i++)
	{
		if (tempAcc == custDB[i]->getAccountNumber())
		{
			curCustomer = custDB[i];
			foundCust = true;
		}
	}
	if (foundCust == true)
	{
		for (int i = 0; i < movieDB.size(); i++)
		{
			if (director == movieDB[i]->getDirector())
			{
				if (movieTitle == movieDB[i]->getTitle())
				{
					curMovie = movieDB[i];
					foundMovie = true;
				}
			}
		}
		if (foundMovie)
		{
			if (curMovie->borrowMovie())
			{
				curCustomer->addHistory(toString());
				return true;
			}
			std::cerr << "ERROR: No More Copies of - Title:" << movieTitle << " - Director:" << director << " \n";
			return false;
		}
		std::cerr << "ERROR: Movie Does Not exist- Title:" << movieTitle << " - Director:" << director << " \n";
		return false;
	}
	std::cerr << "ERROR: Invalid Account Number: " << tempAcc << " does not exsist\n";
	return false;
}

std::string BorrowDrama::toString()
{
	std::string intToString;
	std::stringstream its;
	its << getAccountNumber();
	intToString = its.str();

	std::string retVal;
	retVal.append("B " + intToString);
	retVal.append(" " + getMediaType());
	retVal.append(" " + getMovieType());
	retVal.append(" " + director);
	retVal.append(", " + movieTitle);
	retVal.append(", ");
	return retVal;
}
