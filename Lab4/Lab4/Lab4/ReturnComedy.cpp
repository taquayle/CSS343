/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		ReturnComedy.cpp											*/
/*	PARENT:		Return														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "ReturnComedy.h"


ReturnComedy::ReturnComedy()
{
}

ReturnComedy::ReturnComedy(int accNum, std::string medType, std::ifstream & inFile) : Return(accNum, medType, "F")
{
	buildCommand(inFile);
}


ReturnComedy::~ReturnComedy()
{
}

bool ReturnComedy::buildCommand(std::ifstream & inFile)
{
	std::getline(inFile, movieTitle, ',');
	inFile >> releaseYear;
	std::string temp;
	std::getline(inFile, temp);
	return false;
}

bool ReturnComedy::executeCommand(std::vector<Customer*> &custDB, std::vector<Movie*> &movieDB)
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

			if (movieTitle == movieDB[i]->getTitle())
			{
				if (releaseYear == movieDB[i]->getReleaseYear())
				{
					curMovie = movieDB[i];
					foundMovie = true;
				}
			}
		}
		if (foundMovie)
		{
			if (curMovie->returnMovie())
			{
				curCustomer->addHistory(toString());
				return true;
			}
			std::cerr << "ERROR: All copies accounted for - Title:" << movieTitle << " - Release Year:" << releaseYear << " \n";
			return false;
		}
		std::cerr << "ERROR: Movie Does Not exist - Title:" << movieTitle << " - Release Year:" << releaseYear << " \n";
		return false;
	}
	std::cerr << "ERROR: Invalid Account Number: " << tempAcc << " does not exsist\n";
	return false;
}


std::string ReturnComedy::toString()
{
  std::string intToString;
  std::stringstream its;
  its << getAccountNumber();
  intToString = its.str();
	  its.str(std::string());
  std::string retVal;
	retVal.append("R " + intToString);
	retVal.append(" " + getMediaType());
	retVal.append(" " + getMovieType());
	retVal.append("" + movieTitle);
    its << releaseYear;
  intToString = its.str();
	retVal.append(", " + intToString);
	return retVal;
}
